#include "../helpers/helpers.hpp"



struct range
{
    int64_t l;
    int64_t r;
};



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    std::vector<range> ranges;

    for(size_t i = 0; i < lines.size(); i++) {
        std::string & line = lines[i];
        if(line.length() == 0) {
            break;
        }
        range rng;
        sscanf(line.c_str(), "%ld-%ld", &rng.l, &rng.r);
        ranges.push_back(rng);
    }

    while(true) {
        for(size_t i = 0; i < ranges.size(); i++) {
            range & rng_i = ranges[i];
            for(size_t j = i+1; j < ranges.size(); j++) {
                range & rng_j = ranges[j];
                if(rng_j.r >= rng_i.l && rng_j.l <= rng_i.r) {
                    range rng_new;
                    rng_new.l = std::min(rng_i.l, rng_j.l);
                    rng_new.r = std::max(rng_i.r, rng_j.r);
                    ranges[i] = rng_new;
                    ranges[j] = ranges.back();
                    ranges.pop_back();
                    goto again;
                }
            }
        }
        break;
        again: ;
    }

    int64_t result = 0;
    for(range & rng : ranges) {
        int64_t span = rng.r - rng.l + 1;
        result += span;
    }

    printf("%ld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
