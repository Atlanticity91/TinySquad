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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyLogger::Initialize( TinyFilesystem& filesystem ) { 
	GetInstance( ).Init( filesystem );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLogger::TinyLogger( ) 
	: m_core{ },
	m_client{ }
{ }

void TinyLogger::Init( TinyFilesystem& filesystem ) {
	auto sinks = std::vector<spdlog::sink_ptr>{
		std::make_shared<spdlog::sinks::stdout_color_sink_mt>( ),
		std::make_shared<spdlog::sinks::basic_file_sink_mt>( "TinySquad.log", true )
	};

	sinks[ 0 ]->set_pattern( "%^[%T] %n: %v%$" );
	sinks[ 1 ]->set_pattern( "[%T] [%l] %n: %v" );

	m_core = std::make_shared<spdlog::logger>( "DEV", begin( sinks ), end( sinks ) );
	spdlog::register_logger( m_core );
	m_core->set_level( spdlog::level::trace );
	m_core->flush_on( spdlog::level::trace );

	m_client = std::make_shared<spdlog::logger>( "CLIENT", begin( sinks ), end( sinks ) );
	spdlog::register_logger( m_client );
	m_client->set_level( spdlog::level::trace );
	m_client->flush_on( spdlog::level::trace );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLogger::logger_t TinyLogger::GetCore( ) { return m_core; }

TinyLogger::logger_t TinyLogger::GetClient( ) { return m_client; }
