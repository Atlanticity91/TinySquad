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
 * @creation : 20/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include "TinyGraphicRenderpass.h"

tm_class TinyGraphicRenderpassManager final {

private:
	tiny_map<TinyGraphicRenderpass> _passes;

public:
	TinyGraphicRenderpassManager( );

	~TinyGraphicRenderpassManager( ) = default;

	bool Create( 
		const TinyGraphicLogical& logical, 
		const tiny_string& name,
		const TinyGraphicRenderpassBundle& bundle
	);

	TinyGraphicRenderpass& Begin(
		TinyGraphicWorkContext& work_context, 
		const TinyGraphicRenderFrameManager& frames
	);

	void Terminate( const TinyGraphicLogical& logical );

public:
	bool GetExist( tiny_hash pass_name );

	TinyGraphicRenderpass& GetPass( tiny_hash pass_name );

};
