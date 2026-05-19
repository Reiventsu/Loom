#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace loom::diagnostics
{

    [[nodiscard]] auto editDistance(std::string_view _a, std::string_view _b) -> size_t;

    [[nodiscard]] auto closestMatch(
        std::string_view                _query,
        const std::vector<std::string>& _candidates
    ) -> std::optional<std::string>;

    [[nodiscard]] auto did_you_mean(
        std::string_view                _query,
        const std::vector<std::string>& _candidates
    ) -> std::string;

} // namespace loom::diagnostics