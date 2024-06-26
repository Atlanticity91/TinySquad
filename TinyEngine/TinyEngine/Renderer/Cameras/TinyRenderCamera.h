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

class TinyRenderer;

te_class TinyRenderCamera final {

private:
	tiny_hash m_projection;
	tiny_mat4 m_view;
	tiny_mat4 m_proj_view;
	tiny_mat4 m_inverse;

public:
	TinyRenderCamera( );

	~TinyRenderCamera( ) = default;

	TinyRenderCamera& SetProjection( const tiny_hash& projection );

	void Set( const TinyRenderCamera& other );

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

	tiny_inline const tiny_mat4 GetProjection( TinyRenderer& renderer ) const;

	const tiny_mat4& Get( ) const;
	
	const tiny_mat4& GetProjView( ) const;

	const tiny_mat4& GetInverse( ) const;

	const float* GetBuffer( ) const;

public:
	operator const tiny_mat4& ( ) const;

	operator const float* ( ) const;

};
