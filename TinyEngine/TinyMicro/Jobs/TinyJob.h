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
 * @creation : 23/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Graphics/TinyGraphicManager.h>

tiny_enum( TinyJobFilters ) {

	TJ_FILTER_ASSET = 0,
	TJ_FILTER_GRAPHICS,
	TJ_FILTER_AUDIO,
	TJ_FILTER_ECS,
	TJ_FILTER_NONE,

	TJ_FILTER_COUNT

};

tiny_enum( TinyJobPriorities ) {

	TJ_PRIORITY_HIGH = 0,
	TJ_PRIORITY_NORMAL,
	TJ_PRIORITY_LOW,

	TJ_PRIORITY_COUNT

};

tm_struct TinyJobData {

	native_pointer Value = nullptr;
	tiny_uint Size		 = 0;

};

tm_struct TinyJob {

	using JobTask = std::function<bool( TinyJobData&, native_pointer )>;
	using JobCallback   = std::function<void( TinyJobData&, native_pointer )>;

	TinyJobFilters Filter	   = TJ_FILTER_NONE;
	TinyJobPriorities Priority = TJ_PRIORITY_NORMAL;
	TinyJobData Data{ };
	JobTask Task{ };
	JobCallback Success{ };
	JobCallback Failure{ };

};
