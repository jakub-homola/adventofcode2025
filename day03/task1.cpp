#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    int result = 0;
    for(const std::string & line : lines) {
        int max = 0;
        for(size_t i = 0; i < line.length(); i++) {
            for(size_t j = i+1; j < line.length(); j++) {
                int val1 = line[i] - '0';
                int val2 = line[j] - '0';
                int val = 10 * val1 + val2;
                max = std::max(max, val);
            }
        }
        result += max;
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
