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
 * @creation : 29/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyImGuiSpecification.h"

tm_class TinyImGuiBackend final {

private:
	VkDescriptorPool m_local_pools;

public:
	TinyImGuiBackend( );

	~TinyImGuiBackend( ) = default;

	bool Create( 
		TinyWindow& window, 
		TinyGraphicManager& graphics,
		const TinyImGuiSpecification& specification 
	);

	void Prepare( );

	void Flush( TinyGraphicManager& graphics );

	void Terminate( TinyGraphicManager& graphics );

private:
	bool CreatePools(
		TinyGraphicManager& graphics, 
		const TinyImGuiSpecification& specification 
	);

	bool CreateInstance( 
		TinyWindow& window, 
		TinyGraphicManager& graphics,
		const TinyImGuiSpecification& specification 
	);

private:
	static void CheckVulkanResult( VkResult result );

public:
	const VkDescriptorPool& GetLocalPools( ) const;

};
