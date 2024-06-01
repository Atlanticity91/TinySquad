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
	: m_chunk_size{ 0 },
	m_buffer{ },
	m_descriptors{ }
{ }

bool TinyRenderBuffer::Create(
	TinyGraphicManager& graphics,
	const TinyGraphicBufferSpecification& specification
) {
	auto descriptor_count = graphics.GetSwapchainCapacity( );
	auto specification_   = specification;
	auto graphic		  = graphics.GetWrapper( );

	specification_.Size *= descriptor_count;

	auto state = m_buffer.Create( graphic, specification_ );

	if ( state ) {
		auto buffer = m_buffer.GetDescriptor( )->buffer;

		m_chunk_size = specification_.Size;

		while ( descriptor_count-- > 0 ) {
			auto& descriptor = m_descriptors[ descriptor_count ];

			descriptor.buffer = buffer;
			descriptor.offset = tiny_cast( descriptor_count * m_chunk_size, VkDeviceSize );
			descriptor.range  = tiny_cast( m_chunk_size, VkDeviceSize );
		}
	}

	return state;
}

void TinyRenderBuffer::Terminate( TinyGraphicManager& graphics ) {
	auto graphic = graphics.GetWrapper( );
	
	m_buffer.Terminate( graphic );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderBuffer::GetChunkSize( ) const { return m_chunk_size; }

const TinyGraphicBuffer& TinyRenderBuffer::GetBuffer( ) const { return m_buffer; }

VkDescriptorType TinyRenderBuffer::GetDescriptorType( ) const {
	return m_buffer.GetDescriptorType( );
}

VkDescriptorBufferInfo* TinyRenderBuffer::GetDescriptor( tiny_uint work_id ) {
	return tiny_rvalue( m_descriptors[ work_id ] );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
VkDescriptorBufferInfo* TinyRenderBuffer::operator[]( tiny_uint work_id ) {
	return GetDescriptor( work_id );
}
