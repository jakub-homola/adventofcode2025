#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    std::vector<std::vector<int64_t>> numbers;
    std::vector<char> ops;

    for(std::string & line : input) {
        const char * str = line.c_str();
        if(*str == '+' || *str == '*') {
            while(true) {
                if(*str == '\0') {
                    break;
                }
                if(*str != ' ') {
                    ops.push_back(*str);
                }
                str++;
            }
            break;
        }
        numbers.push_back(std::vector<int64_t>());
        std::vector<int64_t> & nums = numbers.back();
        int64_t num = 0;
        bool prev_space = true;
        while(true) {
            if(*str == ' ' || *str == '\0') {
                if(!prev_space) {
                    nums.push_back(num);
                    num = 0;
                }
                prev_space = true;
                if(*str == '\0') {
                    break;
                }
            }
            else {
                num *= 10;
                num += *str - '0';
                prev_space = false;
            }
            str++;
        }
    }

    // for(auto vec : numbers) {
    //     for(auto num : vec) {
    //         printf(" %5ld", num);
    //     }
    //     printf("\n");
    // }
    // for(char c : ops) {
    //     printf("     %c", c);
    // }
    // printf("\n");

    for(auto vec : numbers) {
        if(vec.size() != ops.size()) {
            fprintf(stderr, "wrong input parsing, nonmatching sizes\n");
            return 1;
        }
    }

    int64_t result = 0;

    for(size_t i = 0; i < ops.size(); i++) {
        char op = ops[i];
        int64_t res;
        if(op == '+') res = 0;
        if(op == '*') res = 1;
        for(size_t j = 0; j < numbers.size(); j++) {
            if(op == '+') res += numbers[j][i];
            if(op == '*') res *= numbers[j][i];
        }
        result += res;
    }

    printf("%ld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
