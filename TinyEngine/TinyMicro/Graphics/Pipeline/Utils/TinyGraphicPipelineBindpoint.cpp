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
 * @creation : 22/12/2023
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
TinyGraphicPipelineBindpoint::TinyGraphicPipelineBindpoint( )
	: TinyGraphicPipelineBindpoint{ TGB_TYPE_UPDATE, 0, 0 } 
{ }

TinyGraphicPipelineBindpoint::TinyGraphicPipelineBindpoint(
	tiny_uint set,
	tiny_uint binding,
	const TinyGraphicTexture& texture
) 
	: TinyGraphicPipelineBindpoint{ TGB_TYPE_TEXTURE, set, binding } 
{
	Description = texture.GetDescriptorType( );
	Value = tiny_cast( texture.GetDescriptor( ), native_pointer );
}

TinyGraphicPipelineBindpoint::TinyGraphicPipelineBindpoint(
	tiny_uint set,
	tiny_uint binding,
	const TinyGraphicBuffer& buffer
) 
	: TinyGraphicPipelineBindpoint{ TGB_TYPE_BUFFER, set, binding } 
{
	Description = buffer.GetDescriptorType( );
	Value = tiny_cast( buffer.GetDescriptor( ), native_pointer );
}

TinyGraphicPipelineBindpoint::TinyGraphicPipelineBindpoint(
	tiny_uint set,
	tiny_uint binding,
	VkDescriptorType type,
	VkDescriptorBufferInfo* buffer
) 
	: TinyGraphicPipelineBindpoint{ TGB_TYPE_BUFFER, set, binding } 
{
	Description = type;
	Value = tiny_cast( buffer, native_pointer );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicPipelineBindpoint::TinyGraphicPipelineBindpoint(
	TinyGraphicBindpointTypes type,
	tiny_uint set,
	tiny_uint binding
)
	: Type{ type },
	Description{ 0 },
	Set{ set },
	Binding{ binding },
	Value{ nullptr } 
{ }
