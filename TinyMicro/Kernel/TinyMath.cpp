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
 * @creation : 02/02/2024
 * @version  : 2024.1.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
void Internal_Normalize( tiny_mat4& matrix ) {
    if ( glm::epsilonEqual( matrix[ 3 ][ 3 ], .0f, glm::epsilon<float>( ) ) ) {
        if (
            glm::epsilonNotEqual( matrix[ 0 ][ 3 ], .0f, glm::epsilon<float>( ) ) ||
            glm::epsilonNotEqual( matrix[ 1 ][ 3 ], .0f, glm::epsilon<float>( ) ) ||
            glm::epsilonNotEqual( matrix[ 2 ][ 3 ], .0f, glm::epsilon<float>( ) )
        ) {
            matrix[ 0 ][ 3 ] = .0f;
            matrix[ 1 ][ 3 ] = .0f;
            matrix[ 2 ][ 3 ] = .0f;
            matrix[ 3 ][ 3 ] = 1.f;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec3 TinyMath::GrabTransform( tiny_mat4& matrix ) {
    Internal_Normalize( matrix );

    return { matrix[ 3 ][ 0 ], matrix[ 3 ][ 1 ], matrix[ 3 ][ 2 ] };
}

tiny_vec3 TinyMath::GrabRotation( tiny_mat4& matrix ) {
    auto rotation = tiny_vec3{ .0f };

    Internal_Normalize( matrix );

    matrix[ 3 ] = tiny_vec4{ 0, 0, 0, matrix[ 3 ].w };

    tiny_vec3 Row[ 3 ];

    for ( auto i = 0; i < 3; ++i )
        for ( auto j = 0; j < 3; ++j )
            Row[ i ][ j ] = matrix[ i ][ j ];

    rotation.y = asin( -Row[ 0 ][ 2 ] );

    if ( cos( rotation.y ) != 0 ) {
        rotation.x = atan2( Row[ 1 ][ 2 ], Row[ 2 ][ 2 ] );
        rotation.z = atan2( Row[ 0 ][ 1 ], Row[ 0 ][ 0 ] );
    } else {
        rotation.x = atan2( -Row[ 2 ][ 0 ], Row[ 1 ][ 1 ] );
        rotation.z = 0;
    }

    return { 
        glm::degrees( rotation.x ),
        glm::degrees( rotation.y ),
        glm::degrees( rotation.z ) 
    };
}

tiny_vec3 TinyMath::GrabScale( tiny_mat4& matrix ) {
    auto scale = tiny_vec3{ .0f };

    Internal_Normalize( matrix );

    matrix[ 3 ] = tiny_vec4{ 0, 0, 0, matrix[ 3 ].w };

    tiny_vec3 Row[ 3 ];

    for ( auto i = 0; i < 3; ++i )
        for ( auto j = 0; j < 3; ++j )
            Row[ i ][ j ] = matrix[ i ][ j ];

    scale.x  = length( Row[ 0 ] );
    Row[ 0 ] = glm::detail::scale( Row[ 0 ], 1.f );

    scale.y  = length( Row[ 1 ] );
    Row[ 1 ] = glm::detail::scale( Row[ 1 ], 1.f );

    scale.z  = length( Row[ 2 ] );
    Row[ 2 ] = glm::detail::scale( Row[ 2 ], 1.f );

    return scale;
}

void TinyMath::Decompose(
	tiny_mat4& matrix,
	tiny_vec3& transform,
	tiny_vec3& rotation,
	tiny_vec3& scale
) {
    Internal_Normalize( matrix );

    transform = { matrix[ 3 ][ 0 ], matrix[ 3 ][ 1 ], matrix[ 3 ][ 2 ] };

    matrix[ 3 ] = tiny_vec4{ 0, 0, 0, matrix[ 3 ].w };

    tiny_vec3 Row[ 3 ];

    for ( auto i = 0; i < 3; ++i )
        for ( auto j = 0; j < 3; ++j )
            Row[ i ][ j ] = matrix[ i ][ j ];

    scale.x  = length( Row[ 0 ] );
    Row[ 0 ] = glm::detail::scale( Row[ 0 ], 1.f );

    scale.y  = length( Row[ 1 ] );
    Row[ 1 ] = glm::detail::scale( Row[ 1 ], 1.f );

    scale.z  = length( Row[ 2 ] );
    Row[ 2 ] = glm::detail::scale( Row[ 2 ], 1.f );

    rotation.y = asin( -Row[ 0 ][ 2 ] );

    if ( cos( rotation.y ) != 0 ) {
        rotation.x = atan2( Row[ 1 ][ 2 ], Row[ 2 ][ 2 ] );
        rotation.z = atan2( Row[ 0 ][ 1 ], Row[ 0 ][ 0 ] );
    } else {
        rotation.x = atan2( -Row[ 2 ][ 0 ], Row[ 1 ][ 1 ] );
        rotation.z = 0;
    }

    rotation.x = glm::degrees( rotation.x );
    rotation.y = glm::degrees( rotation.y );
    rotation.z = glm::degrees( rotation.z );
}
