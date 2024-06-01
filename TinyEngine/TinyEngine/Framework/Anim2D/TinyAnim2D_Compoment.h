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
 * @creation : 29/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Framework/Transform2D/TinyTransform2D_System.h>

tiny_enum( TinyAnimationFlags ) {

	TA_FLAG_PLAYING = TINY_LEFT_SHIFT( 1, 0 ),
	TA_FLAG_LOOPING = TINY_LEFT_SHIFT( 1, 1 ),
	TA_FLAG_REVERSE = TINY_LEFT_SHIFT( 1, 2 )

};

TINY_FRAMEWORK_COMP( TinyAnim2D ) {

private:
	TinyAssetHandle	m_collection;
	tiny_string m_animation;
	tiny_hash m_animation_hash;
	tiny_uint m_flags;
	tiny_uint m_frame_id;
	float m_frame_time;
	float m_frame_duration;

public:
	TinyAnim2D( );

	TinyAnim2D( const tiny_hash entity_hash );

	~TinyAnim2D( ) = default;

	tiny_implement( bool Create( TinyGame* game ) );

	TinyAnim2D& SetCollection( TinyGame* game, const tiny_string& collection );

	TinyAnim2D& SetAnimation( TinyGame* game, const tiny_string& animation );

	TinyAnim2D& SetFrame( TinyGame*game, tiny_uint frame_id );

	TinyAnim2D& Play( );

	TinyAnim2D& Pause( );

	void Tick( TinyAnimation2DManager* animations, TinyInputManager& inputs, TinyECS& ecs );

	tiny_implement( void Delete( TinyGame* game ) );

	tiny_implement( void DisplayWidget( TinyGame* game, TinyToolbox& toolbox ) );

private:
	void SetFrame( 
		TinyGame*game, 
		tiny_uint frame_id, 
		const TinyAnimation2D::FrameCollection* frames 
	);

public:
	TINY_COMP_NAME( TinyAnim2D );

	tiny_implement( bool GetIsActive( ) const );

	TinyAssetHandle& GetCollection( );
	
	const tiny_string& GetAnimation( ) const;

	tiny_uint GetFlags( ) const;
	
	bool GetIsPlaying( ) const;

	bool GetLoop( ) const;

	bool GetReverse( ) const;

	tiny_uint GetFrameID( ) const;
	
	float GetFrameTime( ) const;

	float GetFrameDuration( ) const;

};
