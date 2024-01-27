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

#include "TinyCore.h"

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

#define TINY_GLM_REG( TYPE, QUERY ) typedef glm::TYPE tiny_##QUERY

TINY_GLM_REG( ivec2, point );
TINY_GLM_REG( vec2, vec2 );
TINY_GLM_REG( vec3, vec3 );
TINY_GLM_REG( vec4, vec4 );
TINY_GLM_REG( mat3x3, mat3 );
TINY_GLM_REG( mat4x4, mat4 );
TINY_GLM_REG( quat, quat );

#define TINY_PI ( 3.1415926535897932384626433832795 )
#define TINY_PIF tiny_cast( TINY_PI, float )
