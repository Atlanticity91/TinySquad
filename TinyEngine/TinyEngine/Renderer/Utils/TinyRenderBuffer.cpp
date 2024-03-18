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
 * @creation : 20/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderBuffer::TinyRenderBuffer( ) 
	: _chunk_size{ 0 },
	_buffer{ },
	_descriptors{ }
{ }

bool TinyRenderBuffer::Create(
	TinyGraphicManager& graphics,
	const TinyGraphicBufferProperties& properties
) {
	auto descriptor_count = graphics.GetSwapchainCapacity( );
	auto _properties	  = properties;
	auto context		  = graphics.GetContext( );

	_properties.Size *= descriptor_count;

	auto state = _buffer.Create( context, _properties );

	if ( state ) {
		auto buffer = _buffer.GetDescriptor( )->buffer;

		_chunk_size = properties.Size;

		while ( descriptor_count-- > 0 ) {
			auto& descriptor = _descriptors[ descriptor_count ];

			descriptor.buffer = buffer;
			descriptor.offset = tiny_cast( descriptor_count * _chunk_size, VkDeviceSize );
			descriptor.range  = tiny_cast( _chunk_size, VkDeviceSize );
		}
	}

	return state;
}

void TinyRenderBuffer::Terminate( TinyGraphicManager& graphics ) {
	auto context = graphics.GetContext( );
	
	_buffer.Terminate( context );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderBuffer::GetChunkSize( ) const { return _chunk_size; }

const TinyGraphicBuffer& TinyRenderBuffer::GetBuffer( ) const { return _buffer; }

VkDescriptorType TinyRenderBuffer::GetDescriptorType( ) const {
	return _buffer.GetDescriptorType( );
}

VkDescriptorBufferInfo* TinyRenderBuffer::GetDescriptor( tiny_uint work_id ) {
	return &_descriptors[ work_id ];
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
VkDescriptorBufferInfo* TinyRenderBuffer::operator[]( tiny_uint work_id ) {
	return GetDescriptor( work_id );
}
