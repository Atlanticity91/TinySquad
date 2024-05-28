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
 * @creation : 09/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
bool Internal_ImportShader(
	TinyGame* game,
	TinyFile* file,
	const TinyPathInformation& path_info,
	bool is_hlsl
) {
	auto storage = tiny_storage{ TS_TYPE_HEAP };
	auto builder = TinyGraphicShaderSpecification{ };
	auto state   = false;
	auto size    = file->GetSize( );

	if ( tiny_allocate( storage, size ) ) {
		auto* data = storage.GetAddress( );

		if ( file->ReadAll( size, data ) ) {
			auto& graphics = game->GetGraphics( );
			auto context   = TinyGraphicShaderCompilationContext{ };

			context.Optimization = TGS_OPTIMIZATION_PERF;
			context.Name		 = tiny_string{ path_info.Name };
			context.Entry		 = "main";
			context.Source		 = tiny_string{ tiny_cast( size, tiny_uint ), data };
			context.IsHLSL		 = is_hlsl;

			if ( graphics.CompileShader( context, builder ) )
				state = TinyImport::ExportShader( game, file, tiny_rvalue( builder ) );
		}

		tiny_deallocate( storage );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace TinyImport {

	bool ImportShaderGLSL(
		TinyGame* game,
		TinyFile* file,
		const TinyPathInformation& path_info
	) {
		return Internal_ImportShader( game, file, path_info, false );
	}
	
	bool ImportShaderHLSL(
		TinyGame* game,
		TinyFile* file,
		const TinyPathInformation& path_info
	) {
		return Internal_ImportShader( game, file, path_info, true );
	}
	
	bool ExportShader(
		TinyGame* game,
		TinyFile* file,
		const native_pointer builder
	) {
		if ( builder ) {
			auto* builder_ = tiny_cast( builder, TinyGraphicShaderSpecification* );

			file->Write( TinyAssetHeader{ TA_TYPE_SHADER } );
			file->Write( builder_->Type );
			file->Write( builder_->Entry );
			file->Write( builder_->Code );
		}

		return builder;
	}
	
	bool ExportMaterial(
		TinyGame* game,
		TinyFile* file,
		const native_pointer builder
	) {
		if ( builder ) {
			auto* builder_ = tiny_cast( builder, TinyMaterialBuilder* );

			file->Write( TinyAssetHeader{ TA_TYPE_MATERIAL } );
			file->Write( builder_->PassType );
			file->Write( builder_->PassName );
			file->Write( builder_->Subpass );
			file->Write( builder_->ShaderStages );
			file->Write( builder_->InputBinding );
			file->Write( builder_->InputAttributes );
			file->Write( builder_->Topology );
			file->Write( builder_->Tessellation );
			file->Write( builder_->DepthEnable );
			file->Write( builder_->StencilEnable );
			file->Write( builder_->DepthOperation );
			file->Write( builder_->DepthStencilFront );
			file->Write( builder_->DepthStencilBack );
			file->Write( builder_->ColorBlends );
			file->Write( builder_->Dynamics );
			file->Write( builder_->Descriptors );
			file->Write( builder_->Constants );
		}

		return builder;
	}

};
