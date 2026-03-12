#include <cstdint>
#include <expected>
#include <string_view>

#include "loom/loom.hpp"

/**
 * @brief The main build specification file for Loom.
 * @details Use this to describe your target, application, and whatnot.
 */

using tBuildStatus = std::expected<void, std::string_view>;

tBuildStatus weave() {



    return {};
};
