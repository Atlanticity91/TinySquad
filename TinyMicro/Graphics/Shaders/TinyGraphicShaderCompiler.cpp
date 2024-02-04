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
 * @creation : 24/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h> 

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicShaderCompiler::TinyGraphicShaderCompiler( ) 
	: _compiler{ },
	_options{ },
	_includer{ },
	_types{ }
{ }

bool TinyGraphicShaderCompiler::Initialize( ) {
	_types.emplace( "vert", shaderc_vertex_shader  );
	_types.emplace( "frag", shaderc_fragment_shader );
	_types.emplace( "geom", shaderc_geometry_shader );
	_types.emplace( "comp", shaderc_compute_shader  );

	//_options.SetIncluder( std::make_unique<TinyGraphicShaderIncluder>( &_includer ) );
	_options.SetTargetEnvironment( shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3 );
	_options.SetOptimizationLevel( shaderc_optimization_level_performance );
	_options.SetTargetSpirv( shaderc_spirv_version_1_6 );

	return true;
}

void TinyGraphicShaderCompiler::AddMacro( 
	const tiny_string& name,
	const tiny_string& value 
) {
	if ( !name.is_empty( ) && !value.is_empty( ) ) {
		auto* name_str  = name.as_chars( );
		auto name_len	= name.length( );
		auto* value_str = value.as_chars( );
		auto value_len  = value.length( );

		_options.AddMacroDefinition( name_str, name_len, value_str, value_len );
	}
}

void TinyGraphicShaderCompiler::AddMacros( tiny_init<TinyGraphicShaderMacro> macros ) {
	for ( auto& macro : macros )
		AddMacro( macro.Name, macro.Value );
}

bool TinyGraphicShaderCompiler::Compile(
	const TinyPathInformation& path,
	tiny_storage& file,
	TinyGraphicShaderProperties& properties 
) {
	auto source = tiny_string{ file.GetAddress( ), tiny_cast( file.Capacity, tiny_uint ) };
	auto type	= shaderc_glsl_infer_from_source;
	auto name	= tiny_string{ path.Name };

	if ( path.Extension != "glsl" ) {
		type = _types[ path.Extension ];

		properties.Type = GrabType( type );
	} else
		properties.Type = GrabType( path.Name[ 0 ] );

	return CompileGLSL( type, name, source, properties );
}

bool TinyGraphicShaderCompiler::Compile(
	TinyGraphicShaderProperties& properties,
	const TinyGraphicShaderCompilationContext& context
) {
	auto state = false;

	if ( !context.IsHLSL )
		state = CompileGLSL( properties, context );

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicShaderCompiler::CompileGLSL(
	shaderc_shader_kind type,
	const tiny_string& name,
	const tiny_string& source,
	TinyGraphicShaderProperties& properties
) {
	_options.SetSourceLanguage( shaderc_source_language_glsl );
	
	auto preprocess = _compiler.PreprocessGlsl( source.get( ), source.length( ), type, name.get( ), _options );
	auto state		= preprocess.GetCompilationStatus( ) == shaderc_compilation_status_success;

	if ( state ) {
		auto spirv = _compiler.CompileGlslToSpv( preprocess.begin( ), type, name.get( ), _options );

		state = spirv.GetCompilationStatus( ) == shaderc_compilation_status_success;

		if ( state ) {
			properties.Code = (tiny_uint)( spirv.end( ) - spirv.begin( ) ) * tiny_sizeof( tiny_uint );

			Tiny::Memcpy( (const c_pointer)spirv.begin( ), (c_pointer)properties.Code.data( ), properties.Code.size( ) );
		} else
			printf( "[ VK ] Shader Compilation Error : %s\n%s\n", name.get( ), spirv.GetErrorMessage( ).c_str( ) );
	} else
		printf( "[ VK ] Shader Preprocess Error : %s\n%s\n", name.get( ), preprocess.GetErrorMessage( ).c_str( ) );

	return state;
}

bool TinyGraphicShaderCompiler::CompileGLSL(
	TinyGraphicShaderProperties& properties,
	const TinyGraphicShaderCompilationContext& context
) {
	_options.SetSourceLanguage( shaderc_source_language_glsl );

	auto preprocess = _compiler.PreprocessGlsl( context.Source, shaderc_glsl_infer_from_source, context.Name, _options );
	auto state		= preprocess.GetCompilationStatus( ) == shaderc_compilation_status_success;

	if ( state ) {
		auto spirv = _compiler.CompileGlslToSpv( preprocess.begin( ), shaderc_glsl_infer_from_source, context.Name, _options );

		state = spirv.GetCompilationStatus( ) == shaderc_compilation_status_success;

		if ( state ) {
			properties.Entry = std::string{ context.Entry.get( ) };
			properties.Code  = (tiny_uint)( spirv.end( ) - spirv.begin( ) ) * tiny_sizeof( tiny_uint );

			Tiny::Memcpy( (const c_pointer)spirv.begin( ), (c_pointer)properties.Code.data( ), properties.Code.size( ) );
		} else
			printf( "[ VK ] Shader Compilation Error : %s\n%s\n", context.Name.get( ), spirv.GetErrorMessage( ).c_str( ) );
	} else 
		printf( "[ VK ] Shader Compilation Error : %s\n%s\n", context.Name.get( ), preprocess.GetErrorMessage( ).c_str( ) );

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const shaderc::CompileOptions& TinyGraphicShaderCompiler::GetCompilerOptions( ) const {
	return _options;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
shaderc_optimization_level TinyGraphicShaderCompiler::GrabOptimization(
	TinyGraphicShaderOptimizations value
) const {
	auto optimization = shaderc_optimization_level_zero;

	if ( value == TGS_OPTIMIZATION_SIZE )
		optimization = shaderc_optimization_level_size;
	else if ( value == TGS_OPTIMIZATION_PERF )
		optimization = shaderc_optimization_level_performance;

	return optimization;
}

TinyGraphicShaderTypes TinyGraphicShaderCompiler::GrabType( 
	shaderc_shader_kind kind 
) const {
	auto type = TGS_TYPE_VERTEX;

	switch ( kind ) {
		case shaderc_fragment_shader : type = TGS_TYPE_FRAGMENT; break;
		case shaderc_geometry_shader : type = TGS_TYPE_GEOMETRY; break;
		case shaderc_compute_shader  : type = TGS_TYPE_COMPUTE;  break;

		default : break;
	}

	return type;
}

TinyGraphicShaderTypes TinyGraphicShaderCompiler::GrabType( char identifier ) const {
	auto type = TGS_TYPE_VERTEX;

	switch ( identifier ) {
		case 'f' : type = TGS_TYPE_FRAGMENT; break;
		case 'g' : type = TGS_TYPE_GEOMETRY; break;
		case 'c' : type = TGS_TYPE_COMPUTE;  break;

		default: break;
	}

	return type;
}

shaderc_shader_kind TinyGraphicShaderCompiler::GrabKind(
	TinyGraphicShaderTypes type 
) const {
	auto kind = shaderc_vertex_shader;

	switch ( type ) {
		case TGS_TYPE_FRAGMENT : kind = shaderc_fragment_shader; break;
		case TGS_TYPE_GEOMETRY : kind = shaderc_geometry_shader; break;
		case TGS_TYPE_COMPUTE  : kind = shaderc_compute_shader;  break;

		default : break;
	}

	return kind;
}

TinyGraphicShaderProperties TinyGraphicShaderCompiler::GrabProperties( 
	TinyGraphicShaderTypes type,
	const std::string entry,
	const shaderc::SpvCompilationResult& result
) {
	auto properties = TinyGraphicShaderProperties{ type, entry };
	auto length		= (tiny_uint)( result.end( ) - result.begin( ) );

	properties.Code = length;

	Tiny::Memcpy( (const c_pointer)result.begin( ), (c_pointer)properties.Code.data( ), length * tiny_sizeof( tiny_uint ) );

	return properties;
}
