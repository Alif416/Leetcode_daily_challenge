#include <functional>
#include <string>
#include <cstring>
#include <algorithm>

class Solution {
public:
    // Calculate the number of powerful integers within the range [start, finish]
    // where each digit is less than or equal to `limit` and the number itself is
    // greater than or equal to the string `s`
    long long numberOfPowerfulInt(long long start, long long finish, int limit, std::string s) {
        // Convert 'start - 1' to string and use it as a starting point
        std::string numStr = std::to_string(start - 1);
        // Initialize memoization array, which caches results for dynamic programming
        long long memo[20];
        std::memset(memo, -1, sizeof(memo));

        // Define recursive function using lambda for depth-first search
        std::function<long long(int, bool)> dfs = [&](int pos, bool isLimited) -> long long {
            // If the remaining number length is shorter than s, return 0
            if (numStr.size() < s.size()) {
                return 0;
            }
            // Use memoization to avoid redundant calculations
            if (!isLimited && memo[pos] != -1) {
                return memo[pos];
            }
            // If we are at a digit where the total remaining digits match s's length,
            // only one number can be formed, check if it's valid
            if (numStr.size() - pos == s.size()) {
                return isLimited ? s <= numStr.substr(pos) : 1;
            }
            long long count = 0;
            // Determine upper bound for the current digit
            int upper = std::min(isLimited ? numStr[pos] - '0' : 9, limit);
            // Explore possible digits at the current position
            for (int i = 0; i <= upper; ++i) {
                count += dfs(pos + 1, isLimited && i == (numStr[pos] - '0'));
            }
            // Cache the result if it's not limited by a previous digit
            if (!isLimited) {
                memo[pos] = count;
            }
            return count;
        };

        // Calculate number of powerful integers up to 'start - 1'
        long long countStart = dfs(0, true);

        // Update numStr to represent 'finish' and reset memoization
        numStr = std::to_string(finish);
        std::memset(memo, -1, sizeof(memo));

        // Calculate number of powerful integers up to 'finish'
        long long countFinish = dfs(0, true);

        // The result is the difference in counts which gives the powerful ints in range
        return countFinish - countStart;
    }
};