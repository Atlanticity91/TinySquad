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
 * @creation : 11/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Kernel/TinyCore.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL

#include <TinyThirdparty/glm/glm.hpp>
#include <TinyThirdparty/glm/gtc/matrix_inverse.hpp>
#include <TinyThirdparty/glm/gtc/matrix_transform.hpp>
#include <TinyThirdparty/glm/gtc/type_ptr.hpp>
#include <TinyThirdparty/glm/gtx/matrix_decompose.hpp>
#include <TinyThirdparty/glm/gtx/transform.hpp>
#include <TinyThirdparty/glm/gtx/quaternion.hpp>
#include <TinyThirdparty/glm/gtx/string_cast.hpp>

#define TINY_GLM_REG( TYPE, QUERY ) typedef glm::TYPE tiny_##QUERY

typedef glm::vec<2, tiny_uint, glm::defaultp> tiny_upoint;

TINY_GLM_REG( ivec2, point );
TINY_GLM_REG( vec2, vec2 );
TINY_GLM_REG( vec3, vec3 );
TINY_GLM_REG( vec4, vec4 );
TINY_GLM_REG( mat3x3, mat3 );
TINY_GLM_REG( mat4x4, mat4 );
TINY_GLM_REG( quat, quat );

#define TINY_PI ( 3.1415926535897932384626433832795 )
#define TINY_PIF tiny_cast( TINY_PI, float )

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<( OStream& os, const glm::vec<L, T, Q>& vector ) {
	return os << glm::to_string( vector );
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<( OStream& os, const glm::mat<C, R, T, Q>& matrix ) {
	return os << glm::to_string( matrix );
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<( OStream& os, glm::qua<T, Q> quaternion ) {
	return os << glm::to_string( quaternion );
}

namespace TinyMath { 

	typedef tiny_vec3( *GrabSignature )( tiny_mat4& );

	tm_dll tiny_vec3 GrabTransform( tiny_mat4& matrix );
	
	tm_dll tiny_vec3 GrabRotation( tiny_mat4& matrix );
	
	tm_dll tiny_vec3 GrabScale( tiny_mat4& matrix );

	tm_dll void Decompose(
		tiny_mat4& matrix, 
		tiny_vec3& transform, 
		tiny_vec3& rotation,
		tiny_vec3& scale
	);

};
