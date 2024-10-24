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
 * @creation : 25/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Kernel/TinySingleton.h>

#define __TINY_LOG( MODE, ... )\
	if ( TinyLogger::GetInstance( ).Get( ) )\
		TinyLogger::GetInstance( ).Get( )->##MODE##( __VA_ARGS__ )

#define TINY_LOG_TRACE( ... ) __TINY_LOG( trace,__VA_ARGS__ )
#define TINY_LOG_INFO( ... ) __TINY_LOG( info, __VA_ARGS__ )
#define TINY_LOG_WARN( ... ) __TINY_LOG( warn, __VA_ARGS__ )
#define TINY_LOG_ERRR( ... ) __TINY_LOG( error, __VA_ARGS__ )

tiny_enum( TinyLoggerLevels ) { 

	TL_LEVEL_TRACE = 0,
	TL_LEVEL_INFO,
	TL_LEVEL_WARNING,
	TL_LEVEL_ERROR,

};

tm_class TinyLogger final : tiny_inherit( TinySingleton<TinyLogger> ) {

	using logger_t = std::shared_ptr<spdlog::logger>;

private:
	logger_t m_logger;

public:
	TinyLogger( );

	~TinyLogger( ) = default;

public:
	static void Initialize( TinyFilesystem & filesystem );

private:
	void Init( TinyFilesystem& filesystem );

public:
	logger_t Get( );

};
