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
 * @creation : 08/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicBufferBinder.h"

tm_class TinyGraphicBufferStaging final {

private:
	TinyGraphicBuffer _buffer;
	c_pointer		  _access;

public:
	TinyGraphicBufferStaging( );

	~TinyGraphicBufferStaging( ) = default;

	bool Create( TinyGraphicContext& context, tiny_uint length );

	tiny_inline bool Create2( TinyGraphicContext& context, tiny_uint length );

	tiny_inline bool Map( TinyGraphicContext& context, tiny_uint length );

	bool Map( TinyGraphicContext& context, tiny_uint offset, tiny_uint length );

	void UnMap( TinyGraphicContext& context );

	tiny_inline bool Map(
		TinyGraphicContext& context,
		tiny_uint length,
		const c_pointer data
	);

	bool Map(
		TinyGraphicContext& context, 
		tiny_uint offset, 
		tiny_uint length,
		const c_pointer data
	);

	void Terminate( TinyGraphicContext& context );

public:
	bool GetIsValid( ) const;

	bool GetIsMapped( ) const;

	tiny_uint GetSize( ) const;

	const TinyGraphicBuffer& GetBuffer( ) const;

	c_pointer GetAccess( ) const;

public:
	operator const TinyGraphicBuffer&( ) const;

	operator c_pointer( ) const;

};
