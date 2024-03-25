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

#include "TinyRenderUniform.h"

te_class TinyRenderUniformManager final {

private:
	tiny_map<TinyRenderUniform> _uniforms;

public:
	TinyRenderUniformManager( );

	~TinyRenderUniformManager( ) = default;

	bool Create( TinyGraphicManager& graphics, TinyGraphicBufferStaging& staging );

	bool Create( TinyGraphicManager& graphics, const TinyRenderUniformBuilder& builder );

	void Destroy( TinyGraphicManager& graphics, const tiny_string& name );

	void Terminate( TinyGraphicManager& graphics );

private:
	void GenerateIndexBuffer(  
		TinyGraphicManager& graphics, 
		TinyGraphicBufferStaging& staging
	);

public:
	bool GetExist( const tiny_string& name ) const;

	bool GetExist( const tiny_hash hash ) const;

	TinyRenderUniform& GetUniform( const tiny_string& name );

	TinyRenderUniform& GetUniform( const tiny_hash hash );

	TinyGraphicBuffer& GetBuffer( const tiny_string& name );

	TinyGraphicBuffer& GetBuffer( const tiny_hash hash );

public:
	TinyRenderUniform& operator[]( const tiny_string& name );

	TinyRenderUniform& operator[]( const tiny_hash hash );

};
