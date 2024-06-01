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
	TinyRenderProjectionTypes m_type;
	float m_parameter;
	tiny_mat4 m_matrix;

public:
	TinyRenderProjection( );

	~TinyRenderProjection( ) = default;

	TinyRenderProjection& SetType( TinyRenderProjectionTypes type );

	TinyRenderProjection& SetOrthographic( float zoom );

	TinyRenderProjection& SetPerspective( float fov );

	TinyRenderProjection& SetCustom( const tiny_mat4& projection );

	void ReCalculate( TinyGraphicBoundaries& boundaries );

public:
	TinyRenderProjectionTypes GetType( ) const;

	const tiny_mat4& Get( ) const;

	const float* GetBuffer( ) const;

public:
	operator const tiny_mat4& ( ) const;

	operator const float* ( ) const;

};
