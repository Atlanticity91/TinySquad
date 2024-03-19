/******************************************************************************************
 *
 *   _______ _             __  __ _
 *  |__   __(_)           |  \/  (_)
 *     | |   _ _ __  _   _| \  / |_  ___ _ __ ___
 *     | |  | | '_ \| | | | |\/| | |/ __| '__/ _ \
 *     | |  | | | | | |_| | |  | | | (__| | | (_) |
 *     |_|  |_|_| |_|\__, |_|  |_|_|\___|_|  \___/
 *                    __/ |
 *	                 |___/
 *
 * @author   : ALVES Quentin
 * @creation : 18/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include "MsdfAtlasGenerator.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MsdfAtlasGenerator::MsdfAtlasGenerator( )
	: _freetype{ nullptr },
	_font{ nullptr },
	_charset{ },
	_packer{ }
{ }

MsdfAtlasGenerator::~MsdfAtlasGenerator( ) {
	if ( _freetype ) {
		if ( _font ) {
			msdfgen::destroyFont( _font );
		}

		msdfgen::deinitializeFreetype( _freetype );
	}
}

bool MsdfAtlasGenerator::Prepare( const uint8_t* buffer, size_t length ) {
	_freetype = msdfgen::initializeFreetype( );

	if ( _freetype )
		_font = msdfgen::loadFontData( _freetype, buffer, length );

	return _freetype && _font;
}

MsdfAtlasGenerator& MsdfAtlasGenerator::AddCharset( uint32_t start, uint32_t stop ) {
	auto char_id = start;

	stop += 1;

	while ( char_id < stop )
		_charset.add( char_id++ );

	return (*this);
}

bool MsdfAtlasGenerator::GenerateCharset( MsdfAtlas& atlas, MsdfBitmap& bitmap ) {
	atlas.Geometry.loadCharset( _font, 1.0, _charset );

	_packer.setPixelRange( 2.0 );
	_packer.setMiterLimit( 1.0 );
	_packer.setPadding( 0 );
	_packer.setScale( 40.0 );

	auto state = _packer.pack( atlas.Glyphs.data( ), (int)( atlas.Glyphs.size( ) ) ) == 0;

	if ( state ) {
		_packer.getDimensions( bitmap.Width, bitmap.Height );

		bitmap.Component = 3;
		bitmap.Length	 = bitmap.Width * bitmap.Height * bitmap.Component;
	}

	return state;
}

void MsdfAtlasGenerator::Process( const MsdfParameters& parameters, MsdfAtlas& atlas, MsdfBitmap& bitmap ) {
	PreProcess( parameters, atlas, bitmap );

	auto attributes = msdf_atlas::GeneratorAttributes{ };
	auto generator  = msdf_atlas::ImmediateAtlasGenerator<
		float, 3,
		msdf_atlas::msdfGenerator,
		msdf_atlas::BitmapAtlasStorage<uint8_t, 3>
	>{ bitmap.Width, bitmap.Height };
	
	attributes.config.overlapSupport = true;
	attributes.scanlinePass			 = true;

	generator.setAttributes( attributes );
	generator.setThreadCount( 2 );
	generator.generate( atlas.Glyphs.data( ), (int)( atlas.Glyphs.size( ) ) );

	auto pixels = (Bitmap_t)generator.atlasStorage( );

#	ifdef _WIN32
		memcpy_s( bitmap.Buffer, bitmap.Length, pixels.pixels, bitmap.Length );
#	else
		memcpy( bitmap.Buffer, pixels.pixels, bitmap.Length );
#	endif
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE===
////////////////////////////////////////////////////////////////////////////////////////////
void MsdfAtlasGenerator::PreProcess(
	const MsdfParameters& parameters,
	MsdfAtlas& atlas,
	MsdfBitmap& bitmap
) {
	#define LCG_MULTIPLIER 6364136223846793005ull
	#define LCG_INCREMENT 1442695040888963407ull

	if ( parameters.UseFastColoring ) {
		unsigned long long glyphSeed = parameters.Seed;

		for ( msdf_atlas::GlyphGeometry& glyph : atlas.Glyphs ) {
			glyphSeed *= LCG_MULTIPLIER;
			glyph.edgeColoring( msdfgen::edgeColoringInkTrap, parameters.Threshold, glyphSeed );
		}
	} else {
		msdf_atlas::Workload(
			[ &glyphs = atlas.Glyphs, &parameters ]( int i, int threadNo ) -> bool {
				unsigned long long glyphSeed = ( LCG_MULTIPLIER * ( parameters.Seed ^ i ) + LCG_INCREMENT ) * !!parameters.Seed;
			
				glyphs[ i ].edgeColoring( msdfgen::edgeColoringInkTrap, parameters.Threshold, glyphSeed );

				return true;
			},
			atlas.Glyphs.size( )
		).finish( parameters.Threads );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
