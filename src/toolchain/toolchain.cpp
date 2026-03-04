#include "toolchain.hpp"

#include <array>
#include <cstdlib>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

static FILE *(*platform_popen)(char const *_Command, char const *_Mode) = _popen;

static int (*platform_pclose)(FILE *_File) = _pclose;
#elif defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
static FILE *(*platform_popen)(char const *_Command, char const *_Mode) = popen;
static int (*platform_pclose)(FILE *_File) = pclose;
#endif

namespace loom {
    static std::string run_command(const std::string &_command) {
        std::string result;

        FILE *pipe = platform_popen(_command.c_str(), "r");

        if (!pipe) return "";
        std::array<char, 256> buffer;

        while (fgets(buffer.data(), buffer.size(), pipe))
            result += buffer.data();

        platform_pclose(pipe);

        return result;
    }

    static bool binary_exists(const std::string &_name) {
#ifdef _WIN32
        return !run_command("where " + _name + " 2>nul").empty();
#elif defined(__linux__) || defined(__APPLE__)
        return !run_command("which " + _name + " 2>/dev/null").empty();
#endif
    }

    std::expected<sToolchain, std::string> sToolchain::getToolchain( const eCompiler _compiler
                                                                   , const std::string &_version ) {
        switch (_compiler)
        {
            case eCompiler::Clang: return tc_Clang(_version);
            case eCompiler::gcc:   return tc_gcc(_version);
            case eCompiler::MSVC:  return tc_MSVC(_version);
            default:               return std::unexpected<std::string>("unknown compiler");
        }
    }

    sToolchain sToolchain::toolchainAt(const std::filesystem::path &_cxx_path)
    {
        return sToolchain {
            .compiler = eCompiler::Clang,
            .cxx      = _cxx_path.string(),
            .ar       = "llvm-ar",
            .linker   = "lld"
        };
    }

    std::string sToolchain::validate() const {
    }

    std::string sToolchain::cxx_version() const
    {
        return run_command(cxx + " --version");
    }

    sToolchain sToolchain::tc_Clang(const std::string &_version) {
        if (!_version.empty()) {
            if (const std::string versioned = "clang++-" + _version; binary_exists(versioned)) {
                sToolchain toolchain {
                    .compiler = eCompiler::Clang,
                    .cxx = versioned,
                    .ar = "llvm-ar",
                    .linker = "lld",
                };
                return toolchain;
            }
        }

        sToolchain toolchain {
            .compiler = eCompiler::Clang,
            .cxx = "clang++",
            .ar = "llvm-ar",
            .linker = "lld",
        };
        return toolchain;
    }

    sToolchain sToolchain::tc_gcc(std::string _version) {
        return {};
    }

    sToolchain sToolchain::tc_MSVC(std::string _version) {
        return {};
    }
}
