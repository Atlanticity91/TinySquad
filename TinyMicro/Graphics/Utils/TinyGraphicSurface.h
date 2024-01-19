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
 * @creation : 13/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicInstance.h"

tm_class TinyGraphicSurface final {

	using VkSurfaceFormatList = tiny_list<VkSurfaceFormatKHR>;

private:
	VkSurfaceKHR		_handle;
	VkSurfaceFormatList	_formats;

public:
	TinyGraphicSurface( );

	~TinyGraphicSurface( ) = default;

	bool Create( TinyWindow& window, TinyGraphicInstance& instance );

	bool Initialize( const class TinyGraphicPhysical& physical );

	void Terminate( TinyGraphicInstance& instance );

public:
	const VkSurfaceCapabilitiesKHR GetCapabilities( const TinyGraphicPhysical& physical ) const;

	const VkSurfaceFormatList& GetFormats( ) const;

public:
	operator VkSurfaceKHR ( ) const;

};
