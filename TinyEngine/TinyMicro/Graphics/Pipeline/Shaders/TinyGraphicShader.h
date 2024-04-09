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
 * @creation : 26/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicShaderSpecification.h"

tm_class TinyGraphicShader { 

private:
	std::string						_entry;
	VkPipelineShaderStageCreateInfo _pipeline_stage;

public:
	TinyGraphicShader( );

	TinyGraphicShader( const TinyGraphicShader& other );

	~TinyGraphicShader( ) = default;

	bool Create(
		const TinyGraphicContext& context,
		const TinyGraphicShaderSpecification& specification
	);

	void Terminate( const TinyGraphicContext& context );

public:
	const VkPipelineShaderStageCreateInfo& Get( );

	tiny_string GetEntry( ) const;

private:
	bool GetShaderModule(
		const TinyGraphicLogical& logical,
		const TinyGraphicShaderSpecification& specification
	);

	void GetProperties( const TinyGraphicShaderSpecification& specification );

public:
	operator const VkPipelineShaderStageCreateInfo& ( );

};
