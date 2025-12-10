#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    int result = 0;

    for(const auto & line : input) {
        const char * str = line.c_str();
        const char * target_start = str + 1;
        const char * target_end = strchr(target_start, ']');
        const char * buttons_start = target_end + 2;
        const char * buttons_end = strchr(buttons_start, '{');

        int num_lights = target_end - target_start;
        uint32_t target = 0;
        for(const char * s = target_end - 1; s >= target_start; s--) {
            target <<= 1;
            if(*s == '#') {
                target |= 1;
            }
        }

        std::vector<uint32_t> buttons;
        for(const char * s = buttons_start; s < buttons_end; s = strchr(s,' ')+1) {
            uint32_t button = 0;
            while(true) {
                if(*s >= '0' && *s <= '9') {
                    int but = *s - '0';
                    button |= (1 << but);
                }
                if(*s == ')') {
                    buttons.push_back(button);
                    break;
                }
                s++;
            }
        }

        uint32_t num_buttons = buttons.size();
        uint32_t num_options = 1 << num_buttons;
        int min_buts = 1000;
        for(uint32_t config = 0; config < num_options; config++) {
            int32_t lights = 0;
            for(int32_t but = 0; but < num_buttons; but++) {
                if((config & (1 << but)) != 0) {
                    lights ^= buttons[but];
                }
            }
            if(lights == target) {
                min_buts = std::min(min_buts, std::popcount(config));
            }
        }

        result += min_buts;
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
