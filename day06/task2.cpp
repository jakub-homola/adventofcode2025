#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input_trans = read_lines();
    std::vector<char> input;

    size_t width = input_trans[0].size();
    for(size_t i = 0; i < width; i++) {
        bool all_spaces = true;
        for(size_t j = 0; j < input_trans.size(); j++) {
            char c = input_trans[j][i];
            if(c) input.push_back(c);
            if(c && c != ' ') all_spaces = false;
        }
        if(all_spaces) input.push_back('\n');
    }
    input.push_back('\0');

    // printf("%s\n", input.data());

    std::vector<std::vector<int64_t>> numbers(1);
    std::vector<char> ops;

    const char * str = input.data();
    int64_t num = 0;
    bool prev_space = true;
    while(*str) {
        if(*str == '\n') {
            numbers.push_back(std::vector<int64_t>());
        }
        else {
            if(*str >= '0' && *str <= '9') {
                num *= 10;
                num += *str - '0';
                prev_space = false;
            }
            else {
                if(!prev_space) {
                    numbers.back().push_back(num);
                    num = 0;
                }
                prev_space = true;
            }
            if(*str == '+' || *str == '*') {
                ops.push_back(*str);
            }
        }
        str++;
    }

    // for(size_t i = 0; i < numbers.size(); i++) {
    //     for(auto num : numbers[i]) printf(" %5ld", num);
    //     printf("     %c\n", ops[i]);
    // }

    int64_t result = 0;

    for(size_t i = 0; i < ops.size(); i++) {
        char op = ops[i];
        int64_t res;
        if(op == '+') res = 0;
        if(op == '*') res = 1;
        for(size_t j = 0; j < numbers[i].size(); j++) {
            if(op == '+') res += numbers[i][j];
            if(op == '*') res *= numbers[i][j];
        }
        result += res;
    }

    printf("%ld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
