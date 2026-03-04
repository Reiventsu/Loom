#include "suggest.hpp"
#include <algorithm>
#include <format>

namespace loom::diagnostics {
    size_t editDistance( const std::string_view _a
                       , const std::string_view _b ) {
        // For more info on how this works
        // https://en.wikipedia.org/wiki/Levenshtein_distance

        const size_t m = _a.length();
        const size_t n = _b.length();

        std::vector dp( m + 1, std::vector< size_t >( n + 1, 0) );

        for( size_t i = 0; i < m; ++i ) dp[i][0] = i;
        for( size_t j = 0; j < n; ++j ) dp[0][j] = j;

        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 1; j < n; ++j) {
                if (_a[i - 1] == _b[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + std::min({
                                   dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]
                               });
            }
        }
        return dp[m][n];
    }

    std::optional< std::string > closestMatch( const std::string_view _query
                                             , const std::vector<std::string> &_candidates ) {
        if( _candidates.empty() ) return std::nullopt;
        const size_t threshold = std::max( size_t{ 2 }, _query.size() / 3 );

        std::string bestMatch;
        size_t bestDistance = threshold + 1;

        for( const auto &candidate: _candidates ) {
            if( const size_t distance = editDistance( _query, candidate ); distance < bestDistance ) {
                bestDistance = distance;
                bestMatch = candidate;
            }
        }

        if( bestDistance <= threshold ) return bestMatch;
        return std::nullopt;
    }

    std::string did_you_mean( const std::string_view _query
                            , const std::vector<std::string> &_candidates) {
        const auto match = closestMatch( _query, _candidates );
        if( !match ) return "";
        return std::format( "did you mean `{}`?", *match );
    }
}
