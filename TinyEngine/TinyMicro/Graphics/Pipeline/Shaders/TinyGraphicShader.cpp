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
 * @creation : 26/10/2023
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
TinyGraphicShader::TinyGraphicShader( )
    : _entry{ "" },
    _pipeline_stage{ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO }
{ }

TinyGraphicShader::TinyGraphicShader( const TinyGraphicShader& other )
    : _entry{ other._entry },
    _pipeline_stage{ other._pipeline_stage }
{ 
    _pipeline_stage.pName = _entry.c_str( );
}

bool TinyGraphicShader::Create(
    const TinyGraphicContext& context, 
    const TinyGraphicShaderSpecification& specification
) {
    auto state = GetShaderModule( context.Logical, specification );

    if ( state )
        GetProperties( specification );

    return state;
}

void TinyGraphicShader::Terminate( const TinyGraphicContext& context ) {
    if ( vk::GetIsValid( _pipeline_stage.module ) ) 
        vkDestroyShaderModule( context.Logical, _pipeline_stage.module, vk::GetAllocator( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkPipelineShaderStageCreateInfo& TinyGraphicShader::Get( ) { return _pipeline_stage; }

tiny_string TinyGraphicShader::GetEntry( ) const { return tiny_string{ _entry.c_str( ) }; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicShader::GetShaderModule( 
    const TinyGraphicLogical& logical, 
    const TinyGraphicShaderSpecification& specification
) {
    auto shader_info = VkShaderModuleCreateInfo{ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };

    shader_info.pNext    = VK_NULL_HANDLE;
    shader_info.flags    = VK_NULL_FLAGS;
    shader_info.codeSize = specification.Code.size( );
    shader_info.pCode    = tiny_cast( specification.Code.data( ), const tiny_uint* );

    return vk::Check( vkCreateShaderModule( logical, tiny_rvalue( shader_info ), vk::GetAllocator( ), tiny_rvalue( _pipeline_stage.module ) ) );
}

void TinyGraphicShader::GetProperties( const TinyGraphicShaderSpecification& specification ) {
    _entry                              = std::string{ specification.Entry };
    _pipeline_stage.pNext               = VK_NULL_HANDLE;
    _pipeline_stage.flags               = VK_NULL_FLAGS;
    _pipeline_stage.pName               = _entry.c_str( );
    _pipeline_stage.pSpecializationInfo = VK_NULL_HANDLE;

    switch ( specification.Type ) {
        case TGS_TYPE_VERTEX   : _pipeline_stage.stage = VK_SHADER_STAGE_VERTEX_BIT;   break;
        case TGS_TYPE_FRAGMENT : _pipeline_stage.stage = VK_SHADER_STAGE_FRAGMENT_BIT; break;
        case TGS_TYPE_GEOMETRY : _pipeline_stage.stage = VK_SHADER_STAGE_GEOMETRY_BIT; break;
        case TGS_TYPE_COMPUTE  : _pipeline_stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;  break;

        default : break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicShader::operator const VkPipelineShaderStageCreateInfo& ( ) { return Get( ); }
