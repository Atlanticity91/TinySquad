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
 * @creation : 22/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicBufferBind.h"

tm_class TinyGraphicBufferBinder final {

public:
	TinyGraphicBufferBinder( );

	~TinyGraphicBufferBinder( ) = default;

	bool Read( TinyGraphicContext& context, const TinyGraphicBufferBind& bind );

	bool Write( TinyGraphicContext& context, const TinyGraphicBufferBind& bind );

private:
	VkDeviceMemory Map(
		TinyGraphicLogical& logical,
		const TinyGraphicBufferBind& bind,
		native_pointer& storage
	);

	void Unmap( TinyGraphicLogical& logical, VkDeviceMemory memory );

public:
	template<typename Type>
	bool Read( 
		TinyGraphicContext& context, 
		const TinyGraphicBufferBind& bind, 
		Type& data
	) {
		auto* data_ptr = tiny_cast( tiny_rvalue( data ), native_pointer );

		return Read( context, { bind, data_ptr } );
	};

	template<typename Type>
	bool Write(
		TinyGraphicContext& context, 
		const TinyGraphicBufferBind& bind,
		Type& data
	) {
		auto* data_ptr = tiny_cast( tiny_rvalue( data ), native_pointer );

		return Write( context, { bind, data_ptr } );
	};

};
