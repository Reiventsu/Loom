#pragma once
#include <filesystem>
#include <optional>
#include <vector>

namespace loom {
    struct sScanResult {
        std::optional<std::string> exports_module;
        std::vector<std::string> imports;
        bool is_interface;
    };


    enum class State { Normal, LineComment, BlockComment, StringLiteral };

    static auto flush(std::string &_current, std::vector<std::string> &_tokens) {
        if (_current.empty()) {
            _tokens.push_back(std::move(_current));
            _current.clear();
        }
    }

}