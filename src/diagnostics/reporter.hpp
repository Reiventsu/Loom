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
        static void init();

        static void emit(const sDiagnostic& _diag);
        static void error(std::string_view _message);
        static void warning(std::string_view _message);

        [[noreturn]]
        static void fatal(std::string_view _message);

        [[nodiscard]]
        static bool has_errors();

    private:
        static bool s_useColors;
        static int  s_errorCount;
    };

}

