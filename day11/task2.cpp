#include "../helpers/helpers.hpp"



int chars_to_id(char a, char b, char c)
{
    return (a - 'a') * 26 * 26 + (b - 'a') * 26 + (c - 'a');
}

int mangle_node_id(int id)
{
    int a = id / (26*26);
    int b = (id / 26) % 26;
    int c = id % 26;
    return a * 10000 + b * 100 + c;
}



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    std::vector<std::vector<int>> edges_out(26*26*26);
    std::vector<std::vector<int>> edges_in(26*26*26);
    for(const auto & line : input) {
        const char * str = line.c_str();
        char a, b, c;
        sscanf(str, "%c%c%c", &a, &b, &c);
        int node_src = chars_to_id(a, b, c);
        while(true) {
            str = strchr(str, ' ');
            if(str == nullptr) break;
            str++;
            sscanf(str, "%c%c%c", &a, &b, &c);
            int node_dst = chars_to_id(a, b, c);
            edges_out[node_src].push_back(node_dst);
            edges_in[node_dst].push_back(node_src);
        }
    }

    struct path {
        int64_t non = 0;
        int64_t dac = 0;
        int64_t fft = 0;
        int64_t all = 0;
    };

    std::vector<path> curr_paths(26*26*26);
    std::vector<int> edges_in_used(26*26*26, 0);

    std::deque<int> nodes;
    for(int node = 0; node < 26*26*26; node++) {
        if(edges_in[node].size() == 0 && edges_out[node].size() > 0) {
            nodes.push_back(node);
        }
        if(node == chars_to_id('s', 'v', 'r')) {
            curr_paths[node] = path{1,0,0,0};
        }
    }

    while(!nodes.empty()) {
        int node_src = nodes.front();
        // printf("node id %6d paths %ld\n", mangle_node_id(node_src), curr_paths[node_src]);
        nodes.pop_front();
        std::vector<int> & nodes_dst = edges_out[node_src];
        for(int node_dst : nodes_dst) {
            if(node_src == chars_to_id('d', 'a', 'c')) {
                curr_paths[node_dst].dac += curr_paths[node_src].non;
                curr_paths[node_dst].dac += curr_paths[node_src].dac;
                curr_paths[node_dst].all += curr_paths[node_src].fft;
                curr_paths[node_dst].all += curr_paths[node_src].all;
            } else if(node_src == chars_to_id('f', 'f', 't')) {
                curr_paths[node_dst].fft += curr_paths[node_src].non;
                curr_paths[node_dst].all += curr_paths[node_src].dac;
                curr_paths[node_dst].fft += curr_paths[node_src].fft;
                curr_paths[node_dst].all += curr_paths[node_src].all;
            } else{
                curr_paths[node_dst].non += curr_paths[node_src].non;
                curr_paths[node_dst].dac += curr_paths[node_src].dac;
                curr_paths[node_dst].fft += curr_paths[node_src].fft;
                curr_paths[node_dst].all += curr_paths[node_src].all;
            }
            edges_in_used[node_dst]++;
            if(edges_in[node_dst].size() == edges_in_used[node_dst]) {
                nodes.push_back(node_dst);
            }
        }
    }

    int64_t result = curr_paths[chars_to_id('o', 'u', 't')].all;
    printf("%ld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
