/*
 * Copyright (C) 2024-present ScyllaDB
 */

/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <seastar/core/sharded.hh>
#include "cql3/functions/user_function.hh"

namespace lang {

class manager : public seastar::peering_sharded_service<manager> {
    unsigned _await_mock;

public:
    const unsigned lua_max_bytes;
    const unsigned lua_max_contiguous;
    const std::chrono::milliseconds lua_timeout;

public:
    struct lua_config {
        unsigned max_bytes;
        unsigned max_contiguous;
        std::chrono::milliseconds timeout;
    };
    struct config {
        lua_config lua;
    };
    manager(config);
    future<> start();
    future<> stop();

    using context = std::optional<cql3::functions::user_function::context>;
    future<context> create(sstring language, sstring name, const std::vector<sstring>& arg_names, std::string script);
};

} // lang namespace
