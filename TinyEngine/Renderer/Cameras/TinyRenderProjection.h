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
 * @creation : 15/03/2024
 * @version  : 2024.2.6
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Renderer/Animation3D/TinyAnimation3DManager.h>

tiny_enum( TinyRenderProjectionTypes ) { 

	TRP_TYPE_ORTHOGRAPHIC = 0,
	TRP_TYPE_PERSPECTIVE,
	TRP_TYPE_CUSTOM

};

te_class TinyRenderProjection final {

private:
	TinyRenderProjectionTypes _type;
	tiny_mat4				  _matrix;

public:
	TinyRenderProjection( );

	~TinyRenderProjection( ) = default;

	TinyRenderProjection& SetType( TinyRenderProjectionTypes type );

	TinyRenderProjection& SetOrthographic( );

	TinyRenderProjection& SetPerspective( );

	TinyRenderProjection& SetCustom( const tiny_mat4& projection );

	void ReCalculate( TinyGraphicBoundaries& boundaries );

public:
	TinyRenderProjectionTypes GetType( ) const;

	const tiny_mat4& Get( ) const;

public:
	operator const tiny_mat4& ( ) const;

};
