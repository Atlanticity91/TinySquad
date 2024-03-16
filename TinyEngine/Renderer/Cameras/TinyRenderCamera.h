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
 * @creation : 16/03/2024
 * @version  : 2024.2.6
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderProjection.h"

te_class TinyRenderCamera final {

private:
	tiny_hash _projection;
	tiny_mat4 _view;
	tiny_mat4 _proj_view;
	tiny_mat4 _inverse;

public:
	TinyRenderCamera( );

	~TinyRenderCamera( ) = default;

	void SetTransform(
		const tiny_vec2& location,
		float rotation,
		const tiny_vec2& scale
	);

	void SetTransform(
		const tiny_vec3& location,
		const tiny_vec3& rotation,
		const tiny_vec3& scale 
	);

	void ReCalculate( const tiny_map<TinyRenderProjection>& projections );

public:
	const tiny_hash GetProjection( ) const;

	const tiny_mat4& Get( ) const;
	
	const tiny_mat4& GetProjView( ) const;

	const tiny_mat4& GetInverse( ) const;

	const float* GetBuffer( ) const;

public:
	operator const tiny_mat4& ( ) const;

	operator const float* ( ) const;

};
