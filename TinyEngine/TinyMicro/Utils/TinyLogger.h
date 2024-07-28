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

#define __TINY_LOG( TARGET, MODE, ... )\
	TinyLogger::GetInstance( ).Get##TARGET##( )->##MODE##( __VA_ARGS__ )

#ifndef TINY_LOG_PRINT
#	define TINY_LOG_CORE_TRACE( ... ) __TINY_LOG( Core, trace, __VA_ARGS__ )
#	define TINY_LOG_CORE_INFO( ... ) __TINY_LOG( Core, info, __VA_ARGS__ )
#	define TINY_LOG_CORE_WARN( ... ) __TINY_LOG( Core, warn, __VA_ARGS__ )
#	define TINY_LOG_CORE_ERRR( ... ) __TINY_LOG( Core, error, __VA_ARGS__ )

#	define TINY_LOG_CLIENT_TRACE( ... ) __TINY_LOG( Client, trace, __VA_ARGS__ )
#	define TINY_LOG_CLIENT_INFO( ... ) __TINY_LOG( Client, info, __VA_ARGS__ )
#	define TINY_LOG_CLIENT_WARN( ... ) __TINY_LOG( Client, warn, __VA_ARGS__ )
#	define TINY_LOG_CLIENT_ERRR( ... ) __TINY_LOG( Client, error, __VA_ARGS__ )
#else
#	define TINY_LOG_CORE_TRACE( ... ) printf( __VA_ARGS__ )
#	define TINY_LOG_CORE_INFO( ... ) printf( __VA_ARGS__ )
#	define TINY_LOG_CORE_WARN( ... ) printf( __VA_ARGS__ )
#	define TINY_LOG_CORE_ERRR( ... ) printf( __VA_ARGS__ )

#	define TINY_LOG_CLIENT_TRACE( ... ) printf( __VA_ARGS__ )
#	define TINY_LOG_CLIENT_INFO( ... ) printf( __VA_ARGS__ )
#	define TINY_LOG_CLIENT_WARN( ... ) printf( __VA_ARGS__ )
#	define TINY_LOG_CLIENT_ERRR( ... ) printf( __VA_ARGS__ )
#endif

tiny_enum( TinyLoggerLevels ) { 

	TL_LEVEL_TRACE = 0,
	TL_LEVEL_INFO,
	TL_LEVEL_WARNING,
	TL_LEVEL_ERROR,

};

tm_class TinyLogger final : tiny_inherit( TinySingleton<TinyLogger> ) {

	using logger_t = std::shared_ptr<spdlog::logger>;

private:
	logger_t m_core;
	logger_t m_client;

public:
	TinyLogger( );

	~TinyLogger( ) = default;

public:
	static void Initialize( TinyFilesystem & filesystem );

private:
	void Init( TinyFilesystem& filesystem );

public:
	logger_t GetCore( );

	logger_t GetClient( );

};
