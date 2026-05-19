#include "reporter.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#endif


namespace loom::diagnostics {
    constexpr auto cxpr_reset  = "\033[0m";
    constexpr auto cxpr_bold   = "\033[1m";
    constexpr auto cxpr_dim    = "\033[2m";
    constexpr auto cxpr_red    = "\033[1;31m";
    constexpr auto cxpr_yellow = "\033[1;33m";
    constexpr auto cxpr_cyan   = "\033[1;36m";
    constexpr auto cxpr_blue   = "\033[1;34m";

    bool Reporter::s_useColors  = false;
    int  Reporter::s_errorCount = 0;

    static auto levelColor( const eLevel _level ) -> const char * {
        switch ( _level ) {
            case eLevel::Error: return cxpr_red;
            case eLevel::Warning: return cxpr_yellow;
            case eLevel::Info: return cxpr_cyan;
            case eLevel::Hint: return cxpr_blue;
        }
        return "";
    }

    static auto levelString( const eLevel _level ) -> const char * {
        switch ( _level ) {
            case eLevel::Error: return "error";
            case eLevel::Warning: return "warning";
            case eLevel::Info: return "info";
            case eLevel::Hint: return "hint";
        }
        return "";
    }

    static auto readSourceLine( const std::filesystem::path &_file, const uint32_t _lineNum ) -> std::string {
        std::ifstream f{ _file };
        if ( !f.is_open() ) return "";
        std::string line;
        for ( uint32_t i = 1; i <= _lineNum; ++i )
            if ( !std::getline( f, line ) ) return "";

        return line;
    };

    auto Reporter::init() -> void {
#ifdef _WIN32
        HANDLE h = GetStdHandle(STD_ERROR_HANDLE);
        DWORD mode = 0;
        if (GetConsoleMode(h, &mode)) {
            SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            s_useColors = true;
        }
#elif defined(__linux__) || defined(__APPLE__)
        s_useColors = isatty(fileno(stderr));
#endif
    }

    auto Reporter::error( std::string_view _message ) -> void {
        ++s_errorCount;
        if( s_useColors )
            std::println( std::cerr, "{}error{}: {}"
                        , cxpr_red, cxpr_reset, _message
            );
        else
            std::println( std::cerr, "error: {}"
                        , _message
            );
    }

    auto Reporter::warning( std::string_view _message ) -> void {
        if( s_useColors )
            std::println( std::cerr, "{}warning{}: {}"
                        , cxpr_yellow, cxpr_reset, _message
            );
        else
            std::println( std::cerr, "warning: {}"
                        , _message
            );
    }

    auto Reporter::fatal( const std::string_view _message ) -> void {
        error( _message );
        std::exit( -1 );
    }

    auto Reporter::has_errors() -> bool {
        return s_errorCount > 0;
    }

    auto Reporter::emit( const sDiagnostic &_diag ) -> void {
        if( _diag.level == eLevel::Error ) ++s_errorCount;

        const char *col = s_useColors   ? levelColor( _diag.level ) : "";
        const char *reset = s_useColors ? cxpr_reset : "";
        const char *bold = s_useColors  ? cxpr_bold : "";
        const char *dim = s_useColors   ? cxpr_dim : "";

        std::println( std::cerr, "{}{}{}{}{}: {}{}"
                    , bold, col, levelString( _diag.level ), reset, bold, _diag.message, reset
        );

        if( _diag.location.line > 0 ) {
            std::println( std::cerr, "{} --> {}{}:{}:{}"
                        , dim, reset, _diag.location.file, _diag.location.line, _diag.location.column
            );

            std::string src = _diag.sourceLine.empty()
                            ? readSourceLine(_diag.location.file, _diag.location.line)
                            : _diag.sourceLine;

            if( !src.empty() ) {
                std::string num = std::format( "{}", _diag.location.line );
                std::string padding( num.size(), ' ' );

                std::println( std::cerr, "{}{} |{}", dim, padding, reset );
                std::println( std::cerr, "{}{}{} | {}{}", bold, num, dim, reset, src );

                if( !_diag.underline.empty() )
                    std::println( std::cerr, "{}{} | {}{}{}", dim, padding, reset, col, _diag.underline );

                std::println( std::cerr, "{}{} |{}", dim, padding, reset );
            }
        }

        for( const auto &child: _diag.children ) {
             const char *ccol = s_useColors ? levelColor( child.level ) : "";
             std::println( std::cerr, "{}{}{}{}: {}"
                         , ccol, bold, levelString( child.level ), reset, child.message );
        }

        std::println( std::cerr, "" );
    }
}