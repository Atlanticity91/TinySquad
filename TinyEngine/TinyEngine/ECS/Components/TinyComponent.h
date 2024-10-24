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
 * @creation : 24/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Renderer/TinyRenderer.h>

#define TINY_COMPONENT( API, COMP ) class API COMP : tiny_inherit( TinyComponent )
#define TINY_FRAMEWORK_COMP( COMP ) TINY_COMPONENT( tiny_dll, COMP )

#define TINY_COMP_NAME( COMP )\
	tiny_implement( tiny_string GetName( ) const ) { return {#COMP}; };\
	static tiny_string sGetName( ) { return {#COMP}; }

#define TINY_MAX_COMPONENT 32
#define TINY_NO_ENTITY { }

class TinyECS;

te_abstract_class TinyComponent : tiny_inherit( TinyDebugWidget ) {

protected:
	bool m_is_active;
	tiny_hash m_owner;

public:
	TinyComponent( );

	TinyComponent( const tiny_hash owner );

	virtual ~TinyComponent( ) = default;

	tiny_virtualv( true, bool Create( TinyGame* game ) );

	void Enable( TinyGame* game );

	void Disable( TinyGame* game );

	void Toggle( TinyGame* game );

	tiny_virtual( void Delete( TinyGame* game ) );

	tiny_implement( void TickWidget(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		TinyGame* game
	) );

protected:
	tiny_virtual( void OnEnable( TinyGame* game ) );

	tiny_virtual( void OnDisable( TinyGame* game ) );

	tiny_virtual( void OnTickWidget(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		TinyGame* game
	) );

public:
	tiny_abstract( tiny_string GetName( ) const );

	virtual bool GetIsActive( ) const;

	tiny_hash GetOwner( ) const;

};
