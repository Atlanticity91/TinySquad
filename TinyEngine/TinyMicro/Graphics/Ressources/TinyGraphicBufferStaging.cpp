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
 * @creation : 08/11/2023
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
TinyGraphicBufferStaging::TinyGraphicBufferStaging( ) 
	: _buffer{ },
	_access{ nullptr }
{ }

bool TinyGraphicBufferStaging::Create( TinyGraphicContext& context, tiny_uint length ) {
	return _buffer.Create( context, { TGB_TYPE_STAGING, length } );
}

bool TinyGraphicBufferStaging::CreateMap( TinyGraphicContext& context, tiny_uint length ) {
	return Create( context, length ) && Map( context, 0, length );
}

bool TinyGraphicBufferStaging::CreateMap(
	TinyGraphicContext& context, 
	tiny_uint length, 
	const native_pointer data 
) {
	auto state = Create( context, length ) && Map( context, 0, length, data );
	
	if ( state )
		UnMap( context );

	return state;
}

bool TinyGraphicBufferStaging::Map( TinyGraphicContext& context, tiny_uint length ) {
	return Map( context, 0, length );
}

bool TinyGraphicBufferStaging::Map(
	TinyGraphicContext& context, 
	tiny_uint offset,
	tiny_uint length 
) {
	auto state = _buffer.GetIsValid( );

	if ( state ) {
		UnMap( context );

		auto& properties = _buffer.GetProperties( );
		auto memory		 = _buffer.GetMemory( ).Memory;

		length = length > 0 ? length : properties.Size;

		if ( offset + length > properties.Size )
			length = properties.Size - offset;

		state = vk::Check( vkMapMemory( context.Logical, memory, offset, length, VK_NULL_FLAGS, tiny_rvalue( _access ) ) );
	}

	return state;
}

void TinyGraphicBufferStaging::UnMap( TinyGraphicContext& context ) {
	if ( _access ) {
		auto& memory = _buffer.GetMemory( ).Memory;

		vkUnmapMemory( context.Logical, memory );

		_access = nullptr;
	}
} 

bool TinyGraphicBufferStaging::Map(
	TinyGraphicContext& context,
	tiny_uint length,
	const native_pointer data
) {
	return Map( context, 0, length, data );
}

bool TinyGraphicBufferStaging::Map(
	TinyGraphicContext& context,
	tiny_uint offset,
	tiny_uint length,
	const native_pointer data
) {
	auto state = Map( context, offset, length );

	if ( state ) {
		Tiny::Memcpy( data, _access, length );

		UnMap( context );
	}

	return state;
}

void TinyGraphicBufferStaging::Terminate( TinyGraphicContext& context ) {
	UnMap( context );

	_buffer.Terminate( context );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicBufferStaging::GetIsValid( ) const { return _buffer.GetIsValid( ); }

bool TinyGraphicBufferStaging::GetIsMapped( ) const { return _access != nullptr; }

tiny_uint TinyGraphicBufferStaging::GetSize( ) const { 
	return _buffer.GetProperties( ).Size; 
}

const TinyGraphicBuffer& TinyGraphicBufferStaging::GetBuffer( ) const { return _buffer; }

native_pointer TinyGraphicBufferStaging::GetAccess( ) const { return _access; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBufferStaging::operator const TinyGraphicBuffer&( ) const { 
	return GetBuffer( ); 
}

TinyGraphicBufferStaging::operator native_pointer( ) const { return GetAccess( ); }
