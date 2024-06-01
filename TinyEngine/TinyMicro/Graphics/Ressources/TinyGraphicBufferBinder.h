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

	bool Read( TinyGraphicWrapper& graphic, const TinyGraphicBufferBind& bind );

	bool Write( TinyGraphicWrapper& graphic, const TinyGraphicBufferBind& bind );

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
		TinyGraphicWrapper& graphic,
		const TinyGraphicBufferBind& bind, 
		Type& data
	) {
		auto* data_ptr = tiny_cast( tiny_rvalue( data ), native_pointer );

		return Read( graphic, { bind, data_ptr } );
	};

	template<typename Type>
	bool Write(
		TinyGraphicWrapper& graphic,
		const TinyGraphicBufferBind& bind,
		Type& data
	) {
		auto* data_ptr = tiny_cast( tiny_rvalue( data ), native_pointer );

		return Write( graphic, { bind, data_ptr } );
	};

};
