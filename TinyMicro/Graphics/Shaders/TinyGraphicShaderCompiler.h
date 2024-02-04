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
 * @creation : 24/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicShaderIncluder.h"

tm_struct TinyGraphicShaderMacro {

	tiny_string Name  = "";
	tiny_string Value = "";

};

tm_class TinyGraphicShaderCompiler final {

private:
	shaderc::Compiler			  _compiler;
	shaderc::CompileOptions		  _options;
	TinyGraphicShaderIncluder	  _includer;
	tiny_map<shaderc_shader_kind> _types;

public:
	TinyGraphicShaderCompiler( );

	~TinyGraphicShaderCompiler( ) = default;

	bool Initialize( );

	void AddMacro( const tiny_string& name, const tiny_string& value );

	void AddMacros( tiny_init<TinyGraphicShaderMacro> macros );

	bool Compile(
		const TinyPathInformation& path,
		tiny_storage& file,
		TinyGraphicShaderProperties& properties 
	);

	bool Compile(
		TinyGraphicShaderProperties& properties,
		const TinyGraphicShaderCompilationContext& context
	);

private:
	bool CompileGLSL(
		shaderc_shader_kind type,
		const tiny_string& name,
		const tiny_string& source,
		TinyGraphicShaderProperties& properties
	);

	bool CompileGLSL(
		TinyGraphicShaderProperties& properties,
		const TinyGraphicShaderCompilationContext& context
	);

public:
	const shaderc::CompileOptions& GetCompilerOptions( ) const;

private:
	shaderc_optimization_level GrabOptimization( 
		TinyGraphicShaderOptimizations value 
	) const;

	TinyGraphicShaderTypes GrabType( shaderc_shader_kind kind ) const;

	TinyGraphicShaderTypes GrabType( char identifier ) const;

	shaderc_shader_kind GrabKind( TinyGraphicShaderTypes type ) const;

	TinyGraphicShaderProperties GrabProperties(
		TinyGraphicShaderTypes type,
		const std::string entry,
		const shaderc::SpvCompilationResult& code
	);

};
