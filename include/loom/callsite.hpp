#pragma once
#include <cstdint>
#include <source_location>
#include <string_view>

namespace loom {

    struct sCallSite {
        std::string_view file;
        uint32_t         line;
        uint32_t         column;

        [[nodiscard]]
        static auto here(const std::source_location &_loc = std::source_location::current() ) noexcept -> sCallSite {
            return { _loc.file_name(), _loc.line(), _loc.column() };
        }
    };

}
