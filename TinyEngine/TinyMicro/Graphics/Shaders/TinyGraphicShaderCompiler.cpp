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

#include <TinyMicro/__tiny_micro_pch.h> 

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicShaderCompiler::TinyGraphicShaderCompiler( ) 
	: m_compiler{ },
	m_options{ },
	m_includer{ }
{ }

bool TinyGraphicShaderCompiler::Initialize( ) {
	//_options.SetIncluder( std::make_unique<TinyGraphicShaderIncluder>( &_includer ) );
	m_options.SetTargetEnvironment( shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3 );
	m_options.SetTargetSpirv( shaderc_spirv_version_1_6 );

	return true;
}

void TinyGraphicShaderCompiler::AddMacro( 
	const tiny_string& name,
	const tiny_string& value 
) {
	if ( !name.get_is_empty( ) && !value.get_is_empty( ) ) {
		auto* name_str  = name.get( );
		auto name_len	= name.length( );
		auto* value_str = value.get( );
		auto value_len  = value.length( );

		m_options.AddMacroDefinition( name_str, name_len, value_str, value_len );
	}
}

void TinyGraphicShaderCompiler::AddMacros( tiny_init<TinyGraphicShaderMacro> macros ) {
	for ( auto& macro : macros )
		AddMacro( macro.Name, macro.Value );
}

bool TinyGraphicShaderCompiler::Compile(
	const TinyGraphicShaderCompilationContext& context,
	TinyGraphicShaderSpecification& specification
) {
	return context.IsHLSL ? CompileHLSL( context, specification ) : CompileGLSL( context, specification );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicShaderCompiler::CompileGLSL(
	const TinyGraphicShaderCompilationContext& context,
	TinyGraphicShaderSpecification& specification
) {
	auto optimization = GrabOptimization( context.Optimization );

	m_options.SetSourceLanguage( shaderc_source_language_glsl );
	m_options.SetOptimizationLevel( shaderc_optimization_level_performance );

	auto* source_str = context.Source.get( );
	auto source_len  = context.Source.length( );
	auto* name_str   = context.Name.get( );
	auto preprocess  = m_compiler.PreprocessGlsl( source_str, source_len, shaderc_glsl_infer_from_source, name_str, m_options );
	auto status		 = preprocess.GetCompilationStatus( );
	
	if ( status == shaderc_compilation_status_success ) {
		auto spirv = m_compiler.CompileGlslToSpv( preprocess.begin( ), shaderc_glsl_infer_from_source, name_str, m_options );

		status = spirv.GetCompilationStatus( );
		
		if ( status == shaderc_compilation_status_success ) {
			auto size = tiny_cast( spirv.end( ) - spirv.begin( ), tiny_uint ) * tiny_sizeof( tiny_uint );
			
			specification.Type  = PeekType( context.Source );
			specification.Entry = context.Entry.as_string( );
			specification.Code  = size;

			auto* src = spirv.begin( );
			auto* dst = specification.Code.data( );

			Tiny::Memcpy( src, dst, size );
		} else
			printf( "[ VK ] Shader Compilation Error : %s\n%s\n", name_str, spirv.GetErrorMessage( ).c_str( ) );
	} else 
		printf( "[ VK ] Shader Compilation Error : %s\n%s\n", name_str, preprocess.GetErrorMessage( ).c_str( ) );

	return status == shaderc_compilation_status_success;
}

bool TinyGraphicShaderCompiler::CompileHLSL(
	const TinyGraphicShaderCompilationContext& context,
	TinyGraphicShaderSpecification& specification
) {
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const shaderc::CompileOptions& TinyGraphicShaderCompiler::GetCompilerOptions( ) const {
	return m_options;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
shaderc_optimization_level TinyGraphicShaderCompiler::GrabOptimization(
	TinyGraphicShaderOptimizations value
) const {
	auto optimization = shaderc_optimization_level_zero;

	if ( value == TGS_OPTIMIZATION_SIZE )
		optimization = shaderc_optimization_level_size;
	else if ( value == TGS_OPTIMIZATION_PERF )
		optimization = shaderc_optimization_level_performance;

	return optimization;
}

TinyGraphicShaderTypes TinyGraphicShaderCompiler::PeekType(
	const tiny_string& source 
) const {
	auto* type_str = source.sub_chars( "shader_stage(", true );
	auto type	   = TGS_TYPE_VERTEX;

	while ( type_str[ 0 ] == ' ' && type_str[ 0 ] != '\0' )
		type_str += 1;

	switch ( type_str[ 0 ] ) {
		case 'f' : type = TGS_TYPE_FRAGMENT; break;
		case 'g' : type = TGS_TYPE_GEOMETRY; break;
		case 'c' : type = TGS_TYPE_COMPUTE;  break;

		default : break;
	}

	return type;
}
