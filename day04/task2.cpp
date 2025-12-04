#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines_orig = read_lines();
    std::vector<std::string> grid = grid_pad(lines_orig, '.', 1);
    int height = lines_orig.size();
    int width = lines_orig[0].length();

    int result = 0;

    std::vector<Loc2<int>> poss;

    for(int r = 1; r <= height; r++) {
        for(int c = 1; c <= width; c++) {
            if(grid[r][c] == '@') {
                poss.push_back(Loc2(r,c));
            }
        }
    }

    std::vector<Loc2<int>> poss_next;
    while(true) {
        for(size_t i = 0; i < poss.size(); i++) {
            int r = poss[i].r;
            int c = poss[i].c;
            int count = 0;
            for(int dr = -1; dr <= 1; dr++) {
                for(int dc = -1; dc <= 1; dc++) {
                    int rr = r + dr;
                    int cc = c + dc;
                    if(grid[rr][cc] == '@') {
                        count++;
                    }
                }
            }
            if(count <= 4) {
                result++;
                grid[r][c] = '.';
            }
            else {
                poss_next.push_back(Loc2(r,c));
            }
        }
        if(poss_next.size() == poss.size()) {
            break;
        }
        std::swap(poss, poss_next);
        poss_next.clear();
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
