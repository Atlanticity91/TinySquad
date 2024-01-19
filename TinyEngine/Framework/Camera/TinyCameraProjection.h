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
 * @creation : 21/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyCamera_Component.h"

tiny_enum( TinyProjectionTypes ) {

	TP_TYPE_ORTHOGRAPHIC = 0,
	TP_TYPE_PERSPECTIVE

};

te_class TinyCameraProjection final {

private:
	TinyProjectionTypes _type;
	float				_parameter;
	tiny_mat4			_matrix;

public:
	TinyCameraProjection( );

	~TinyCameraProjection( ) = default;

	void SetType( TinyProjectionTypes type );

	void SetParameter( float value );

	void Set( TinyProjectionTypes type, float parameter );

	void Calculate( TinyGraphicBoundaries& boundaries );

public:
	TinyProjectionTypes GetType( ) const;

	float GetParamter( ) const;

	const tiny_mat4& GetMatrix( ) const;

};
