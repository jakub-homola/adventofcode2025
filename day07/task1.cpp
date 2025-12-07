#include "../helpers/helpers.hpp"






int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();
    std::vector<std::string> grid = grid_pad(input, 'X', 1);

    Loc2<int> Spos;
    for(size_t r = 0; r < grid.size(); r++) {
        for(size_t c = 0; c < grid[r].length(); c++) {
            if(grid[r][c] == 'S') {
                Spos = Loc2<int>(r, c);
                goto phase2;
            }
        }
    }
    phase2:

    int64_t result = 0;

    struct beam {
        Loc2<int> pos;
        int64_t multiplicity;
    };

    auto insert_or_increment = [](std::vector<beam> & beams, beam toadd) {
        auto it = std::find_if(beams.begin(), beams.end(), [&toadd](const beam & b){ return b.pos.r == toadd.pos.r && b.pos.c == toadd.pos.c;});
        if(it == beams.end()) {
            beams.push_back(toadd);
        } else {
            it->multiplicity += toadd.multiplicity;
        }
    };

    std::vector<beam> beams_curr;
    beams_curr.push_back(beam{Spos, 1});
    std::vector<beam> beams_next;
    while(beams_curr[0].pos.r < grid.size()) {
        for(const beam & curr : beams_curr) {
            if(grid[curr.pos.r][curr.pos.c] == '^') {
                result++;
                insert_or_increment(beams_next, beam{Loc2<int>(curr.pos.r+1, curr.pos.c+1), curr.multiplicity});
                insert_or_increment(beams_next, beam{Loc2<int>(curr.pos.r+1, curr.pos.c-1), curr.multiplicity});
            } else {
                insert_or_increment(beams_next, beam{Loc2<int>(curr.pos.r+1, curr.pos.c), curr.multiplicity});
            }
        }
        std::swap(beams_curr, beams_next);
        beams_next.clear();
    }

    printf("%ld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
