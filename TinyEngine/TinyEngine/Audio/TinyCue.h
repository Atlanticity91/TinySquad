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
 * @creation : 04/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyCueBuilder.h"

te_class TinyCue final : tiny_inherit( TinyAsset ) {

private:
	TinyCueFormat  _format;
	TinyCueContext _context;
	tiny_storage   _storage;

public:
	TinyCue( );

	~TinyCue( ) = default;

	bool Create( const TinyCueBuilder& builder );

	tiny_implement( void Terminate( TinyGame* game ) );

public:
	const TinyCueFormat& GetFormat( ) const;

	const TinyCueContext& GetContext( ) const;

	const tiny_storage& GetStorage( ) const;

	TinyCueBuffer GetBuffer( ) const;

};
