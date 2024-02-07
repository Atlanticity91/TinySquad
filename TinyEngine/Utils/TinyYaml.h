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
 * @creation : 07/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyCore.h"

namespace YAML {

    // === tiny_point ===
    template<>
    struct convert<tiny_point> {

        static Node encode( const tiny_point& point ) {
            Node node;

            node.push_back( point.x );
            node.push_back( point.y );

            return node;
        };

        static bool decode( const Node& node, tiny_point& point ) {
            auto state = node.IsSequence( ) && node.size( ) == 2;

            if ( state ) {
                point.x = node[ 0 ].as<tiny_int>( );
                point.y = node[ 1 ].as<tiny_int>( );
            }

            return state;
        };

    };

    // === tiny_vectors ===
    #define TINY_YAML_VEC( POWER ) template<>\
        struct convert<tiny_vec##POWER> {\
            static Node encode( const tiny_vec##POWER& vector ) {\
                Node node;\
                for ( auto power = 0; power < POWER; power++ )\
                    node.push_back( vector[ power ] );\
                return node;\
            };\
            static bool decode( const Node& node, tiny_vec##POWER& vector ) {\
                auto state = node.IsSequence( ) && node.size( ) == POWER;\
                if ( state ) {\
                    for ( auto power = 0; power < POWER; power++ )\
                        vector[ power ] = node[ power ].as<glm::highp_f32>( );\
                }\
                return state;\
            };\
        }

    TINY_YAML_VEC( 2 );
    TINY_YAML_VEC( 3 );
    TINY_YAML_VEC( 4 );

    // === tiny_color ===
    template<>
    struct convert<tiny_color> {

        static Node encode( const tiny_color& color ) {
            Node node;

            for ( auto channel = 0; channel < 4; channel++ )
                node.push_back( color.Channels[ channel ] );

            return node;
        };

        static bool decode( const Node& node, tiny_color& color ) {
            auto state = node.IsSequence( ) && node.size( ) == 4;

            if ( state ) {
                for ( auto channel = 0; channel < 4; channel++ )
                    color.Channels[ channel ] = node[ channel ].as<float>( );
            }

            return state;
        };

    };

    template<typename Type>
    struct convert<tiny_list<Type>> {

        static Node encode( const tiny_list<Type>& list ) {
            Node node;

            for ( auto data : list )
                node.push_back( data );

            return node;
        };

        static bool decode( const Node& node, tiny_list<Type>& list ) {
            auto state = node.IsSequence( ) && node.size( ) == 4;

            if ( state ) {
                auto count = tiny_cast( node.size( ), tiny_uint );

                list = count;

                while ( count-- > 0 )
                    list[ count ] = node[ count ].as<Type>( );
            }

            return state;
        };

    };

};
