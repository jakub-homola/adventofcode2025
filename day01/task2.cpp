#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    int curr = 50;
    int result = 0;
    for(const std::string & line : lines) {
        char dir = line[0];
        int rot = atoi(line.data() + 1);

        result += rot / 100;
        rot = rot % 100;

        bool was_zero = (curr == 0);

        if(dir == 'L') curr -= rot;
        if(dir == 'R') curr += rot;
        int curr2 = (curr + 100) % 100;

        bool is_zero = (curr2 == 0);
        bool through_zero = !was_zero && !is_zero && (curr2 != curr);

        if(is_zero || through_zero) result++;

        curr = curr2;
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
