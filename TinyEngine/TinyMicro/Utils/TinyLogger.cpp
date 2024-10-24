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
TinyLogger::TinyLogger( )
	: m_logger{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyLogger::Initialize( TinyFilesystem& filesystem ) { 
	GetInstance( ).Init( filesystem );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyLogger::Init( TinyFilesystem& filesystem ) {
	auto log_path = filesystem.GetLogDir( ) + "TinyLog-" + Tiny::GetDateAsString( ) + ".log";
	auto sinks	  = std::vector<spdlog::sink_ptr>{
		std::make_shared<spdlog::sinks::stdout_color_sink_mt>( ),
		std::make_shared<spdlog::sinks::basic_file_sink_mt>( log_path, true )
	};
	
	sinks[ 0 ]->set_pattern( "%^[ %T ] %n: %v%$" );
	sinks[ 1 ]->set_pattern( "[ %T ][ %l ] %n: %v" );

	m_logger = std::make_shared<spdlog::logger>( "DEV", begin( sinks ), end( sinks ) );
	
	m_logger->set_level( spdlog::level::trace );
	m_logger->flush_on( spdlog::level::trace );

	spdlog::register_logger( m_logger );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLogger::logger_t TinyLogger::Get( ) { return m_logger; }
