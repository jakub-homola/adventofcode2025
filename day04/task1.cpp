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

    for(int r = 1; r <= height; r++) {
        for(int c = 1; c <= width; c++) {
            if(grid[r][c] == '@') {
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
                }
            }
        }
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
