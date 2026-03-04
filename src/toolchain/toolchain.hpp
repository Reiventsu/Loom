#pragma once
#include <expected>
#include <string>
#include <filesystem>

namespace loom {

    enum class eCompiler {
        Clang,
        gcc,
        MSVC,
    };

    struct sToolchain {
        eCompiler  compiler;
        std::string cxx;
        std::string ar;
        std::string linker;

        [[nodiscard]]
        static std::expected<sToolchain, std::string> getToolchain(eCompiler _compiler, const std::string &_version = "");

        [[nodiscard]]
        static sToolchain toolchainAt(const std::filesystem::path &_cxx_path);

        [[nodiscard]]
        std::string validate() const;

        [[nodiscard]]
        std::string cxx_version() const;

    private:
        static sToolchain tc_Clang(const std::string &_version = "");
        static sToolchain tc_gcc(std::string _version = "");
        static sToolchain tc_MSVC(std::string _version = "");
    };
}
