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
 * @creation : 13/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Graphics/Utils/TinyGraphicSurface.h>

tm_class TinyGraphicPhysical final {

	using VkPhysicalDeviceQueues = tiny_list<VkPhysicalDeviceQueue>;

private:
	VkPhysicalDevice m_handle;
	VkPhysicalDeviceFeatures2 m_features;
	VkPhysicalDeviceProperties m_properties;
	VkPhysicalDeviceQueues m_queues;
	VkPhysicalDeviceDescriptorIndexingFeatures m_indexing;

public:
	TinyGraphicPhysical( );

	~TinyGraphicPhysical( ) = default;

	bool Initialize( 
		const TinyGraphicInstance& instance, 
		const TinyGraphicSurface& surface 
	);

	void Terminate( );

private:
	void CreateIndexing( );

public:
	bool GetIsValid( ) const;

	VkPhysicalDevice Get( ) const;

	tiny_string GetVendor( ) const;

	const VkPhysicalDeviceFeatures2* GetFeatures( ) const;

	const VkPhysicalDeviceFeatures& GetFeatureCore( ) const;

	const VkPhysicalDeviceDescriptorIndexingFeatures& GetFeatureIndexing( ) const;

	const VkPhysicalDeviceProperties& GetProperties( ) const;

	const VkPhysicalDeviceLimits& GetLimits( ) const;

	const VkPhysicalDeviceQueues& GetQueues( ) const;

	VkSampleCountFlagBits GetSamplesLimit( ) const;

private:
	bool GetHasExtensions( ) const;

	bool GetHasDepth( ) const;

	bool GetPhysicalDevice( const TinyGraphicInstance& instance );

	void GetQueuesFamilies( const TinyGraphicSurface& surface );

public:
	operator VkPhysicalDevice ( ) const;

};
