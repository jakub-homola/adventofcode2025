#include "../helpers/helpers.hpp"



int64_t get_power(int64_t x, int64_t n)
{
    int64_t result = 1;
    for(int64_t i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

std::vector<std::vector<int64_t>> memo;

int64_t get_max_joltage(std::vector<int64_t> vec, int start_idx, int num_bats_left)
{
    if(num_bats_left == 0) {
        return 0;
    }

    int64_t & memo_val = memo[start_idx][num_bats_left];

    if(memo_val < 0) {
        int64_t pow_ten = get_power(10, num_bats_left-1);

        int64_t max_val = -1;
        int max_digit = -1;
        int end_i = vec.size() - num_bats_left + 1;
        for(int i = start_idx; i < end_i; i++) {
            if(vec[i] < max_digit) continue;
            int64_t max_remaining = get_max_joltage(vec, i+1, num_bats_left-1);
            int64_t val = pow_ten * vec[i] + max_remaining;
            max_val = std::max(max_val, val);
            max_digit = vec[i];
        }

        memo_val = max_val;
    }

    return memo_val;
}



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    int64_t result = 0;
    for(const std::string & line : lines) {
        std::vector<int64_t> vec(line.length());
        std::transform(line.begin(), line.end(), vec.begin(), [](char c){ return c - '0'; });

        memo = std::vector<std::vector<int64_t>>(lines[0].length(), std::vector<int64_t>(lines[0].length(), -1));

        int64_t max = get_max_joltage(vec, 0, 12);
        result += max;
    }

    printf("%ld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
