//
// Copyright(c) 2016-2018 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

//
// Include a bundled header-only copy of fmtlib or an external one.
// By default spdlog include its own copy.
//
#include <TinyLibs/Spdlog/tweakme.h>

#if defined(SPDLOG_USE_STD_FORMAT)  // SPDLOG_USE_STD_FORMAT is defined - use std::format
    #include <format>
#elif !defined(SPDLOG_FMT_EXTERNAL)
    #if !defined(SPDLOG_COMPILED_LIB) && !defined(FMT_HEADER_ONLY)
        #define FMT_HEADER_ONLY
    #endif
    #ifndef FMT_USE_WINDOWS_H
        #define FMT_USE_WINDOWS_H 0
    #endif

    #include <TinyLibs/Spdlog/fmt/bundled/core.h>
    #include <TinyLibs/Spdlog/fmt/bundled/format.h>

#else  // SPDLOG_FMT_EXTERNAL is defined - use external fmtlib
    #include <TinyLibs/Spdlog/fmt/core.h>
    #include <TinyLibs/Spdlog/fmt/format.h>
#endif
