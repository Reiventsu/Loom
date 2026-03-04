#include "suggest.hpp"
#include <algorithm>

namespace loom::diagnostics {

    size_t editDistance( const std::string_view _a
                       , const std::string_view _b) {

        // For more info on how this works
        // https://en.wikipedia.org/wiki/Levenshtein_distance

        const size_t m = _a.length();
        const size_t n = _b.length();

        std::vector dp(m + 1, std::vector<size_t>(n + 1, 0));

        for (size_t i = 0; i < m; ++i) dp[i][0] = i;
        for (size_t j = 0; j < n; ++j) dp[0][j] = j;

        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 1; j < n; ++j) {
                if (_a[i - 1] == _b[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + std::min({ dp[i - 1][j]
                                           ,  dp[i][j - 1]
                                           ,  dp[i - 1][j - 1]
                    });
            }
        }
        return dp[m][n];
    }

    std::optional<std::string> closestMatch( std::string_view _query
                                           , const std::vector<std::string> &_candidates) {
    }

    std::string did_you_mean( std::string_view _query
                            , const std::vector<std::string> &_candidates) {
    }

}