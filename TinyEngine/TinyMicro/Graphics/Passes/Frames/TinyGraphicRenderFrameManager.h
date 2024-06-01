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

#include "TinyGraphicRenderFrame.h"

tm_class TinyGraphicRenderFrameManager final {

private:
	tiny_list<TinyGraphicRenderFrame> m_frames;

public:
	TinyGraphicRenderFrameManager( );

	~TinyGraphicRenderFrameManager( ) = default;

	bool Create(
		const TinyGraphicLogical& logical,
		const TinyGraphicRenderFrameProperties& frame 
	);

	void Terminate( const TinyGraphicLogical& logical );

public:
	tiny_uint GetCount( ) const;

	const VkFramebuffer GetFramebuffer( 
		TinyGraphicWorkContext& work_context, 
		tiny_uint frame 
	) const;

};
