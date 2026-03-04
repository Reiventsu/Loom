#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace loom::diagnostics
{

    [[nodiscard]] size_t editDistance(std::string_view _a, std::string_view _b);

    [[nodiscard]] std::optional<std::string> closestMatch(
        std::string_view                _query,
        const std::vector<std::string>& _candidates
    );

    [[nodiscard]] std::string did_you_mean(
        std::string_view                _query,
        const std::vector<std::string>& _candidates
    );

} // namespace loom::diagnostics