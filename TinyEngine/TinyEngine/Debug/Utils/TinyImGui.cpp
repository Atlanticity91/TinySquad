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
 * @creation : 29/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace TinyImGui {

    ImTextureID CreateTextureID( TinyTexture2D* texture ) {
        auto texture_id = tiny_cast( nullptr, VkDescriptorSet );

        if ( texture ) {
            auto sampler = texture->GetSampler( );
            auto view    = texture->GetView( );
            
            texture_id = ImGui_ImplVulkan_AddTexture( sampler, view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );
        }

        return tiny_cast( texture_id, ImTextureID );
    }

    ImTextureID CreateTextureID( TinyTexture2D& texture ) {
        return CreateTextureID( tiny_rvalue( texture ) );
    }

    void Image( ImTextureID& image, const TinyTexture2D* texture, const ImVec2& dimensions ) {
        if ( image != nullptr ) {
            ImGui::Image( image, dimensions, { .0f, 0.f }, { 1.f, 1.f } );

            auto cursor = ImGui::GetCursorScreenPos( );

            if ( ImGui::BeginItemTooltip( ) ) {
                auto columns = texture->GetColumns( );
                auto rows    = texture->GetRows( );
                auto& io     = ImGui::GetIO( );
                auto uv      = tiny_vec2{ dimensions.x / columns, dimensions.y / rows };

                cursor.y = cursor.y - dimensions.y;
                columns  = tiny_cast( ( io.MousePos.x - cursor.x ) / uv.x, tiny_int );
                rows     = tiny_cast( ( io.MousePos.y - cursor.y ) / uv.y, tiny_int );
                uv       = texture->GetUV( );

                auto uv0 = ImVec2{ columns * uv.x, rows * uv.y };
                auto uv1 = ImVec2{ uv0.x + uv.x, uv0.y + uv.y };

                ImGui::Image( image, ImVec2{ 128.f, 128.f }, uv0, uv1 );
                ImGui::EndTooltip( );
            }
        }
    }

    void Asset(
        TinyGame* game,
        const tiny_string& label,
        TinyAssetHandle& asset
    ) {
        auto& assets    = game->GetAssets( );
        auto asset_list = assets.GetAssetList( asset.Type );
        auto context    = TinyImGui::DropdownContext{ asset_list, asset.Hash };

        if ( TinyImGui::Dropdown( label, context ) ) {
            assets.Release( game, asset );

            if ( context.Index > 0 ) {
                asset.Hash = tiny_hash{ context.Values[ context.Index ] };

                if ( !assets.Acquire( game, asset ) )
                    asset.Hash.undefined( );
            } else
                asset.Hash.undefined( );
        }
    }

};
