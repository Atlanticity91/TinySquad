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

tiny_enum( TinyJobPriorities ) {

	TJ_PRIORITY_HIGH = 0,
	TJ_PRIORITY_NORMAL,
	TJ_PRIORITY_LOW

};

tm_struct TinyJobData {

	tiny_uint Size  = 0;
	native_pointer Value	= nullptr;

};

tm_struct TinyJob{

	using JobExecutalbe = std::function<bool( TinyJobData&, native_pointer )>;
	using JobCallback   = std::function<void( TinyJobData&, native_pointer )>;

	TinyJobPriorities Priority = TJ_PRIORITY_NORMAL;
	TinyJobData Data{ };
	JobExecutalbe Execute{ };
	JobCallback Success{ };
	JobCallback Failure{ };

};
