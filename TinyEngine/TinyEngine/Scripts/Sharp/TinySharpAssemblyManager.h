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
 * @creation : 23/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinySharpAssembly.h"

te_class TinySharpAssemblyManager final {

private:
	tiny_map<TinySharpAssembly> m_assemblies;

public:
	TinySharpAssemblyManager( );

	~TinySharpAssemblyManager( ) = default;

	void Terminate( TinySharpContext& context );

public:
	TinySharpAssembly* GetAssembly( const tiny_string& alias ) const;

public:
	TinySharpAssembly* operator[]( const tiny_string& alias ) const;

};
