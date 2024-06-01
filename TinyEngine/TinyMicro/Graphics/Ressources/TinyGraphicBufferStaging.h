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
	TinyGraphicBuffer m_buffer;
	native_pointer m_access;

public:
	TinyGraphicBufferStaging( );

	~TinyGraphicBufferStaging( ) = default;

	bool Create( TinyGraphicWrapper& graphic, tiny_uint length );

	bool CreateMap( TinyGraphicWrapper& graphic, tiny_uint length );

	bool CreateMap( TinyGraphicWrapper& graphic, tiny_uint length, const native_pointer data );

	tiny_inline bool Map( TinyGraphicWrapper& graphic, tiny_uint length );

	bool Map( TinyGraphicWrapper& graphic, tiny_uint offset, tiny_uint length );

	void UnMap( TinyGraphicWrapper& graphic );

	tiny_inline bool Map(
		TinyGraphicWrapper& graphic,
		tiny_uint length,
		const native_pointer data
	);

	bool Map(
		TinyGraphicWrapper& graphic,
		tiny_uint offset, 
		tiny_uint length,
		const native_pointer data
	);

	void Terminate( TinyGraphicWrapper& graphic );

public:
	bool GetIsValid( ) const;

	bool GetIsMapped( ) const;

	tiny_uint GetSize( ) const;

	const TinyGraphicBuffer& GetBuffer( ) const;

	native_pointer GetAccess( ) const;

public:
	operator const TinyGraphicBuffer&( ) const;

	operator native_pointer( ) const;

};
