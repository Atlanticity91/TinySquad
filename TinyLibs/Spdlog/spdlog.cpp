// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef SPDLOG_COMPILED_LIB
    #error Please define SPDLOG_COMPILED_LIB to compile this file.
#endif

#include <TinyLibs/Spdlog/common-inl.h>
#include <TinyLibs/Spdlog/details/backtracer-inl.h>
#include <TinyLibs/Spdlog/details/log_msg-inl.h>
#include <TinyLibs/Spdlog/details/log_msg_buffer-inl.h>
#include <TinyLibs/Spdlog/details/null_mutex.h>
#include <TinyLibs/Spdlog/details/os-inl.h>
#include <TinyLibs/Spdlog/details/registry-inl.h>
#include <TinyLibs/Spdlog/logger-inl.h>
#include <TinyLibs/Spdlog/pattern_formatter-inl.h>
#include <TinyLibs/Spdlog/sinks/base_sink-inl.h>
#include <TinyLibs/Spdlog/sinks/sink-inl.h>
#include <TinyLibs/Spdlog/spdlog-inl.h>

#include <mutex>

// template instantiate logger constructor with sinks init list
template SPDLOG_API spdlog::logger::logger(std::string name,
                                           sinks_init_list::iterator begin,
                                           sinks_init_list::iterator end);
template class SPDLOG_API spdlog::sinks::base_sink<std::mutex>;
template class SPDLOG_API spdlog::sinks::base_sink<spdlog::details::null_mutex>;
