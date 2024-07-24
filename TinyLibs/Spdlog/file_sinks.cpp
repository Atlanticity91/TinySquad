// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef SPDLOG_COMPILED_LIB
    #error Please define SPDLOG_COMPILED_LIB to compile this file.
#endif

#include <TinyLibs/Spdlog/details/file_helper-inl.h>
#include <TinyLibs/Spdlog/details/null_mutex.h>
#include <TinyLibs/Spdlog/sinks/base_sink-inl.h>
#include <TinyLibs/Spdlog/sinks/basic_file_sink-inl.h>

#include <mutex>

template class SPDLOG_API spdlog::sinks::basic_file_sink<std::mutex>;
template class SPDLOG_API spdlog::sinks::basic_file_sink<spdlog::details::null_mutex>;

#include <TinyLibs/Spdlog/sinks/rotating_file_sink-inl.h>
template class SPDLOG_API spdlog::sinks::rotating_file_sink<std::mutex>;
template class SPDLOG_API spdlog::sinks::rotating_file_sink<spdlog::details::null_mutex>;
