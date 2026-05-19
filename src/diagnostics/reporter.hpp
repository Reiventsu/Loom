#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace loom::diagnostics {

    enum class eLevel {
        Error,
        Warning,
        Info,
        Hint,
    };

    struct sSourceLocation {
        std::string_view file;
        uint32_t         line;
        uint32_t         column;
    };

    struct sDiagnostic {
        eLevel                   level;
        std::string              message;
        sSourceLocation          location;
        std::string              sourceLine;
        std::string              underline;
        std::vector<sDiagnostic> children;
    };

    class Reporter {
    public:
        static auto init() -> void;

        static auto emit(const sDiagnostic& _diag) -> void;
        static auto error(std::string_view _message) -> void;
        static auto warning(std::string_view _message) -> void;

        [[noreturn]]
        static auto fatal(std::string_view _message) -> void;

        [[nodiscard]]
        static auto has_errors() -> bool;

    private:
        static bool s_useColors;
        static int  s_errorCount;
    };

}