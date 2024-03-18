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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderUniform::TinyRenderUniform( )
	: _buffer{ },
	_bind_point{ }
{ }

bool TinyRenderUniform::Create(
	TinyGraphicContext& context,
	const TinyRenderUniformBuilder& builder
) {
	auto state = _buffer.Create( context, builder );

	if ( state ) {
		_bind_point.Type		= TGB_TYPE_BUFFER;
		_bind_point.Description = _buffer.GetDescriptorType( );
		_bind_point.Set			= builder.Set;
		_bind_point.Binding		= builder.Binding;
	}

	return state;
}

void TinyRenderUniform::Terminate( TinyGraphicContext& context ) {
	_buffer.Terminate( context );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyRenderUniform::GetSet( ) const { return _bind_point.Set; }

tiny_uint TinyRenderUniform::GetBinding( ) const { return _bind_point.Binding; }

TinyGraphicBuffer& TinyRenderUniform::GetBuffer( ) { return _buffer; }

TinyGraphicPipelineBindpoint& TinyRenderUniform::GetBindpoint( ) {
	_bind_point.Value = tiny_cast( _buffer.GetDescriptor( ), c_pointer );

	return _bind_point; 
}

const TinyGraphicPipelineBindpoint& TinyRenderUniform::GetBindpoint( ) const {
	_bind_point.Value = tiny_cast( _buffer.GetDescriptor( ), c_pointer );

	return _bind_point;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderUniform::operator TinyGraphicBuffer& ( ) { return GetBuffer( ); }

TinyRenderUniform::operator TinyGraphicPipelineBindpoint& ( ) { return GetBindpoint( ); }

TinyRenderUniform::operator const TinyGraphicPipelineBindpoint& ( ) const { 
	return GetBindpoint( ); 
}
