#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    std::vector<Point2<int64_t>> tiles;
    tiles.reserve(input.size());
    for(std::string & line : input) {
        Point2<int64_t> pt;
        sscanf(line.c_str(), "%ld,%ld\n", &pt.x, &pt.y);
        tiles.push_back(pt);
    }

    int64_t max_area = 0;

    for(size_t i = 0; i < tiles.size(); i++) {
        Point2<int64_t> pt_i = tiles[i];
        for(size_t j = 0; j < tiles.size(); j++) {
            Point2<int64_t> pt_j = tiles[j];

            int64_t dx = std::abs(pt_i.x - pt_j.x);
            int64_t dy = std::abs(pt_i.y - pt_j.y);

            int64_t area = (dx + 1) * (dy + 1);

            max_area = std::max(max_area, area);
        }
    }

    printf("%ld\n", max_area);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
