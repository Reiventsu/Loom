#include "Scanner.hpp"

namespace loom {

    enum class State { Normal, LineComment, BlockComment, StringLiteral };

    static auto flush(std::string &_current, std::vector<std::string> &_tokens) -> void {
        if (!_current.empty()) {
            _tokens.push_back(std::move(_current));
            _current.clear();
        }
    }

    auto scan(const std::filesystem::path &_path) -> sScanResult {
        sScanResult result;

        return result;
    }

    auto tokenize(std::string_view _source) -> std::vector<std::string> {
        std::vector<std::string> tokens;
        std::string current;
        auto state = State::Normal;

        for (size_t i = 0; i < _source.size(); ++i) {
            char c    = _source[i];
            char next = (i + 1 < _source.size() ? _source[i + 1] : '\0');

            switch (state) {
                case State::Normal:
                    if      ( c == '/' && next == '/') { flush( current, tokens ); state = State::LineComment;   ++i; }
                    else if ( c == '/' && next == '*') { flush( current, tokens ); state = State::BlockComment;  ++i; }
                    else if ( c == '"')                { flush( current, tokens ); state = State::StringLiteral;      }
                    else if ( c == ';')                { flush( current, tokens ); tokens.push_back(";");             }
                    else if ( std::isspace(c))         { flush( current, tokens );                                    }
                    else                               { current += c;                                                }
                    break;

                case State::LineComment:
                    if ( c == '\n') { state = State::Normal; }
                    break;

                case State::BlockComment:
                    if ( c == '*' && next == '/') { state = State::Normal; ++i; }
                    break;

                case State::StringLiteral:
                    if      (c == '\\') { ++i; }
                    else if (c == '"')  { state = State::Normal; }
                    break;
            }
        }
        flush( current, tokens );
        return tokens;
    }

}