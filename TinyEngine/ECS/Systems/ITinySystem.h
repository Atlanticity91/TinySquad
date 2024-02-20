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

#include <TinyEngine/ECS/Components/TinyComponent_Interop.h>

te_struct TinyEntityGhost {

	tiny_hash Hash{ };
	tiny_uint EntityID	  = 0;
	tiny_uint ComponentID = TINY_UINT_MAX;

};

te_interface ITinySystem {

	tiny_abstract( void RegisterInterop( TinyGame* game ) );

	tiny_abstract( void Enable( TinyGame* game ) );

	tiny_abstract( void Disable( TinyGame* game ) );

	tiny_abstract( void Toggle( TinyGame* game ) );

	tiny_abstract( std::shared_ptr<TinyComponent> Create( const tiny_hash entity_hash ) );

	tiny_abstract( TinyComponent* Append( TinyGame* game, const tiny_hash entity_hash ) );

	tiny_abstract( bool Append( TinyGame* game, std::shared_ptr<TinyComponent> component ) );

	tiny_abstract( bool Set( TinyGame* game, std::shared_ptr<TinyComponent> component ) );

	tiny_abstract( void Remove( TinyGame* game, const tiny_hash entity_hash ) );

	tiny_abstract( void Erase( const TinyEntityGhost& ghost ) );
	
	tiny_abstract( void PreTick( TinyGame* game ) );

	tiny_abstract( void PostTick( TinyGame* game ) );

	tiny_abstract( bool GetIsActive( ) const );

	tiny_abstract( tiny_string GetName( ) const );

	tiny_abstract( bool GetHasPreTick( ) const );

	tiny_abstract( bool GetHasPostTick( ) const );

	tiny_abstract( tiny_uint GetComponentID( const tiny_hash entity_hash ) const );

	tiny_abstract( TinyComponent* GetComponent( const tiny_hash entity_hash ) const );

	tiny_abstract( bool GetComponent( 
		const tiny_uint component_id, 
		TinyComponent*& component
	) );

};
