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
    std::vector<int64_t> ids;

    size_t i = 0;
    for(; i < lines.size(); i++) {
        std::string & line = lines[i];
        if(line.length() == 0) {
            break;
        }
        range rng;
        sscanf(line.c_str(), "%ld-%ld", &rng.l, &rng.r);
        ranges.push_back(rng);
    }
    i++;
    for(; i < lines.size(); i++) {
        std::string & line = lines[i];
        int64_t id;
        sscanf(line.c_str(), "%ld", &id);
        ids.push_back(id);
    }

    int result = 0;
    for(size_t i = 0; i < ids.size(); i++) {
        int64_t id = ids[i];
        for(size_t j = 0; j < ranges.size(); j++) {
            range & rng = ranges[j];
            if(id >= rng.l && id <= rng.r) {
                result++;
                break;
            }
        }
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
