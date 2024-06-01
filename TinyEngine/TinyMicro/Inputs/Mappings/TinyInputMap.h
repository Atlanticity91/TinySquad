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
 * @creation : 14/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyInputQuery.h"

tm_class TinyInputMap final {

private:
	tiny_map<TinyInputQueries> m_queries;

public:
	TinyInputMap( );

	~TinyInputMap( ) = default;

	void Clear( );

	void Lock( tiny_hash input_hash );

	void UnLock( tiny_hash input_hash );

	void Register( 
		const tiny_string& input_alias, 
		tiny_init<TinyInputQuery> querys 
	);

	void Register( 
		const tiny_string& input_alias, 
		const tiny_list<TinyInputQuery>& querys 
	);

	void Erase( const tiny_string& input );

	void Tick( );

public:
	tiny_map<TinyInputQueries>& Get( );
	
	const tiny_map<TinyInputQueries>& Get( ) const;

	bool Find( tiny_hash input_hash ) const;

	TinyInputQueries* Query( tiny_hash input_hash );

};
