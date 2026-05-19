#pragma once
#include <expected>
#include <string>
#include <filesystem>

namespace loom {
    enum class eCompiler {
        Clang,
        GCC, // unimplemented
        MSVC, // Unimplemented
    };

    struct sToolchain {
        eCompiler compiler;
        std::string cxx;
        std::string ar;
        std::string linker;

        [[nodiscard]]
        static auto getToolchain(eCompiler _compiler, const std::string &_version = "")
            -> std::expected<sToolchain, std::string>;

        [[nodiscard]]
        static auto toolchainAt(const std::filesystem::path &_cxx_path) -> sToolchain;

        [[nodiscard]]
        auto validate() const
            -> std::string;

        [[nodiscard]]
        auto cxx_version() const
            -> std::string;

    private:
        static auto tc_Clang(const std::string &_version = "") -> sToolchain;

        static auto tc_GCC(std::string _version = "") -> sToolchain;

        static auto tc_MSVC(std::string _version = "") -> sToolchain;
    };
}
