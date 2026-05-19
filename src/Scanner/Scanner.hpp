#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace loom {
    struct sScanResult {
        std::optional<std::string> exports_module;
        std::vector<std::string> imports;
        bool is_interface;
    };

    auto scan(const std::filesystem::path &_path) -> sScanResult;
    auto tokenize(std::string_view _source) -> std::vector<std::string>;
}