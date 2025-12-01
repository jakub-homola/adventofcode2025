#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    int curr = 50;
    int result = 0;
    for(const std::string & line : lines)
    {
        char dir = line[0];
        int rot = atoi(line.data() + 1);

        if(dir == 'L') curr -= rot;
        if(dir == 'R') curr += rot;
        curr = (curr + 100) % 100;

        if(curr == 0) result++;
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
