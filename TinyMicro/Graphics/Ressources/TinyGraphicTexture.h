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

#include "TinyGraphicTextureBuilder.h"

tm_class TinyGraphicTexture {

	friend class TinyGraphicBurner;

private:
	VkImage						 _image;
	VkDescriptorImageInfo		 _descriptor;
	TinyGraphicMemory			 _memory;
	TinyGraphicTextureProperties _properties;

public:
	TinyGraphicTexture( );

	~TinyGraphicTexture( ) = default;

	bool Create( 
		TinyGraphicContext& context, 
		const TinyGraphicTextureProperties& properties 
	);

	bool Create( 
		TinyGraphicContext& context,
		const TinyGraphicTextureBuilder& builder,
		const TinyGraphicBufferStaging& stagging
	);

	bool Fill( TinyGraphicContext& context, const TinyGraphicBufferStaging& stagging );

	void Terminate( TinyGraphicContext& context );

private:
	bool CreateImageCopy( );

	bool CreateImage(
		const TinyGraphicLogical& logical,
		const TinyGraphicQueueManager& queues
	);

	bool CreateView( const TinyGraphicLogical& logical );

	bool CreateImageSampler( const TinyGraphicLogical& logical );

	void GenerateMipmaps( const TinyGraphicLogical& logical );

	void SetLayout( VkImageLayout layout );

public:
	bool GetIsCopy( ) const;

	const VkImage GetImage( ) const;

	const VkImageView GetView( ) const;

	const VkSampler GetSampler( ) const;

	VkDescriptorType GetDescriptorType( ) const;

	const VkDescriptorImageInfo* GetDescriptor( ) const;

	const TinyGraphicTextureProperties& GetProperties( ) const;

	VkImageLayout GetLayout( ) const;

private:
	VkImageType GetImageType( ) const;

	VkImageViewType GetViewType( ) const;

public:
	operator const VkImage ( ) const;

};
