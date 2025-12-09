#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    // assume already sorted neighbors
    // assume each row/col in the room contains exactly 0 or 2 red tiles
    std::vector<Point2<int64_t>> tiles;
    tiles.reserve(input.size());
    for(std::string & line : input) {
        Point2<int64_t> pt;
        sscanf(line.c_str(), "%ld,%ld\n", &pt.x, &pt.y);
        tiles.push_back(pt);
    }


    int64_t max_x = 0;
    int64_t max_y = 0;
    for(auto & pt : tiles) {
        max_x = std::max(max_x, pt.x);
        max_y = std::max(max_y, pt.y);
    }

    std::vector<Point2<int64_t>> tiles_copy = tiles;

    std::sort(tiles_copy.begin(), tiles_copy.end(), [](const auto & l, const auto & r) { return l.x < r.x; });
    std::vector<int64_t> map_x_large_small(max_x+1, -1);
    std::vector<int64_t> map_x_small_large;
    for(auto & pt : tiles_copy) {
        if(map_x_large_small[pt.x] < 0) {
            map_x_large_small[pt.x] = map_x_small_large.size();
            map_x_small_large.push_back(pt.x);
        }
    }

    std::sort(tiles_copy.begin(), tiles_copy.end(), [](const auto & l, const auto & r) { return l.y < r.y; });
    std::vector<int64_t> map_y_large_small(max_y+1, -1);
    std::vector<int64_t> map_y_small_large;
    for(auto & pt : tiles_copy) {
        if(map_y_large_small[pt.y] < 0) {
            map_y_large_small[pt.y] = map_y_small_large.size();
            map_y_small_large.push_back(pt.y);
        }
    }

    std::vector<std::vector<char>> grid(map_y_small_large.size()+2, std::vector<char>(map_x_small_large.size()+2, '.'));

    for(auto & pt_large : tiles) {
        auto small_x = map_x_large_small[pt_large.x] + 1;
        auto small_y = map_y_large_small[pt_large.y] + 1;
        grid[small_y][small_x] = '#';
    }

    for(size_t i = 0; i < tiles.size(); i++) {
        size_t j = (i+1) % tiles.size();
        auto & tile_i_large = tiles[i];
        auto & tile_j_large = tiles[j];
        auto tile_i_small = Point2<int64_t>(map_x_large_small[tile_i_large.x], map_y_large_small[tile_i_large.y]);
        auto tile_j_small = Point2<int64_t>(map_x_large_small[tile_j_large.x], map_y_large_small[tile_j_large.y]);
        Point2<int64_t> diff = tile_j_small - tile_i_small;
        if(diff.x != 0) diff.x /= std::abs(diff.x);
        if(diff.y != 0) diff.y /= std::abs(diff.y);
        for(Point2<int64_t> curr = tile_i_small + diff; curr != tile_j_small; curr = curr + diff) {
            grid[curr.y+1][curr.x+1] = '+';
        }
    }

    std::vector<Point2<int64_t>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    std::deque<Point2<int64_t>> deq;
    deq.emplace_back(0,0);
    grid[0][0] = ':';
    while(!deq.empty()) {
        auto & curr = deq.front();
        deq.pop_front();
        for(auto & dir : dirs) {
            auto next = curr + dir;
            if(next.x >= 0 && next.x < grid[0].size() && next.y >= 0 && next.y < grid.size()) {
                if(grid[next.y][next.x] == '.') {
                    grid[next.y][next.x] = ':';
                    deq.emplace_back(next.x, next.y);
                }
            }
        }
    }

    // for(const auto & row : grid) {
    //     for(const char & c : row) {
    //         putc(c, stdout);
    //     }
    //     putc('\n', stdout);
    // }
    // fflush(stdout);

    int64_t max_area = 0;

    for(size_t i = 0; i < tiles.size(); i++) {
        auto & tile_i_large = tiles[i];
        auto tile_i_small = Point2<int64_t>(map_x_large_small[tile_i_large.x], map_y_large_small[tile_i_large.y]);
        for(size_t j = i+1; j < tiles.size(); j++) {
            auto & tile_j_large = tiles[j];
            auto tile_j_small = Point2<int64_t>(map_x_large_small[tile_j_large.x], map_y_large_small[tile_j_large.y]);

            int64_t x_min = std::min(tile_i_small.x, tile_j_small.x);
            int64_t x_max = std::max(tile_i_small.x, tile_j_small.x);
            int64_t y_min = std::min(tile_i_small.y, tile_j_small.y);
            int64_t y_max = std::max(tile_i_small.y, tile_j_small.y);

            for(int64_t x = x_min; x <= x_max; x++) if(grid[y_min+1][x+1] == ':') goto next_iter;
            for(int64_t x = x_min; x <= x_max; x++) if(grid[y_max+1][x+1] == ':') goto next_iter;
            for(int64_t y = y_min; y <= y_max; y++) if(grid[y+1][x_min+1] == ':') goto next_iter;
            for(int64_t y = y_min; y <= y_max; y++) if(grid[y+1][x_max+1] == ':') goto next_iter;

            {
                int64_t dx = std::abs(tile_i_large.x - tile_j_large.x);
                int64_t dy = std::abs(tile_i_large.y - tile_j_large.y);
                int64_t area = (dx + 1) * (dy + 1);
                max_area = std::max(max_area, area);
            }

            next_iter: ;
        }
    }

    printf("%ld\n", max_area);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
