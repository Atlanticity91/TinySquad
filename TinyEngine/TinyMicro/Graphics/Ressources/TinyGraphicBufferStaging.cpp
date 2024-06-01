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
	: m_buffer{ },
	m_access{ nullptr }
{ }

bool TinyGraphicBufferStaging::Create( TinyGraphicWrapper& graphic, tiny_uint length ) {
	return m_buffer.Create( graphic, { TGB_TYPE_STAGING, length } );
}

bool TinyGraphicBufferStaging::CreateMap( TinyGraphicWrapper& graphic, tiny_uint length ) {
	return Create( graphic, length ) && Map( graphic, 0, length );
}

bool TinyGraphicBufferStaging::CreateMap(
	TinyGraphicWrapper& graphic,
	tiny_uint length, 
	const native_pointer data 
) {
	auto state = Create( graphic, length ) && Map( graphic, 0, length, data );
	
	if ( state )
		UnMap( graphic );

	return state;
}

bool TinyGraphicBufferStaging::Map( TinyGraphicWrapper& graphic, tiny_uint length ) {
	return Map( graphic, 0, length );
}

bool TinyGraphicBufferStaging::Map(
	TinyGraphicWrapper& graphic,
	tiny_uint offset,
	tiny_uint length 
) {
	auto state = m_buffer.GetIsValid( );

	if ( state ) {
		UnMap( graphic );

		auto& properties = m_buffer.GetProperties( );
		auto memory		 = m_buffer.GetMemory( ).Memory;

		length = length > 0 ? length : properties.Size;

		if ( offset + length > properties.Size )
			length = properties.Size - offset;

		state = vk::Check( vkMapMemory( graphic.Logical, memory, offset, length, VK_NULL_FLAGS, tiny_rvalue( m_access ) ) );
	}

	return state;
}

void TinyGraphicBufferStaging::UnMap( TinyGraphicWrapper& graphic ) {
	if ( _access ) {
		auto& memory = m_buffer.GetMemory( ).Memory;

		vkUnmapMemory( graphic.Logical, memory );

		m_access = nullptr;
	}
} 

bool TinyGraphicBufferStaging::Map(
	TinyGraphicWrapper& graphic,
	tiny_uint length,
	const native_pointer data
) {
	return Map( graphic, 0, length, data );
}

bool TinyGraphicBufferStaging::Map(
	TinyGraphicWrapper& graphic,
	tiny_uint offset,
	tiny_uint length,
	const native_pointer data
) {
	auto state = Map( graphic, offset, length );

	if ( state ) {
		Tiny::Memcpy( data, _access, length );

		UnMap( graphic );
	}

	return state;
}

void TinyGraphicBufferStaging::Terminate( TinyGraphicWrapper& graphic ) {
	UnMap( graphic );

	m_buffer.Terminate( graphic );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicBufferStaging::GetIsValid( ) const { return m_buffer.GetIsValid( ); }

bool TinyGraphicBufferStaging::GetIsMapped( ) const { return _access != nullptr; }

tiny_uint TinyGraphicBufferStaging::GetSize( ) const { 
	return m_buffer.GetProperties( ).Size; 
}

const TinyGraphicBuffer& TinyGraphicBufferStaging::GetBuffer( ) const { return m_buffer; }

native_pointer TinyGraphicBufferStaging::GetAccess( ) const { return _access; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBufferStaging::operator const TinyGraphicBuffer&( ) const { 
	return GetBuffer( ); 
}

TinyGraphicBufferStaging::operator native_pointer( ) const { return GetAccess( ); }
