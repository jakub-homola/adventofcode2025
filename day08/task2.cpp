#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    std::vector<Point3<int64_t>> points;
    points.reserve(input.size());
    for(std::string line : input) {
        Point3<int64_t> pt;
        sscanf(line.c_str(), "%ld,%ld,%ld", &pt.x, &pt.y, &pt.z);
        points.push_back(pt);
    }

    struct distinfo {
        size_t idx1;
        size_t idx2;
        int64_t dist;
    };
    std::vector<distinfo> dists;
    for(size_t i = 0; i < points.size(); i++) {
        for(size_t j = i+1; j < points.size(); j++) {
            Point3<int64_t> diff = points[i] - points[j];
            int64_t dist = diff.magnitude2();
            dists.push_back(distinfo{i, j, dist});
        }
    }

    std::sort(dists.begin(), dists.end(), [](const distinfo & dil, const distinfo & dir){ return dil.dist < dir.dist; });

    std::vector<int64_t> unionfind(points.size());
    for(size_t i = 0; i < unionfind.size(); i++) unionfind[i] = i;

    std::vector<int64_t> setsizes(points.size());
    for(size_t i = 0; i < unionfind.size(); i++) setsizes[i] = 1;

    auto unionfind_get = [&unionfind](int64_t orig) {
        int64_t parent = orig;
        while(parent != unionfind[parent]) {
            parent = unionfind[parent];
        }
        int64_t curr = orig;
        int64_t next;
        while(curr != unionfind[curr]) {
            next = unionfind[curr];
            unionfind[curr] = parent;
        }
        return parent;
    };

    size_t num_connections_done = 0;

    int64_t result;

    for(size_t i = 0; i < dists.size(); i++) {
        distinfo connection = dists[i];
        int64_t parent1 = unionfind_get(connection.idx1);
        int64_t parent2 = unionfind_get(connection.idx2);
        // printf("attempting %2zu %2zu   =   %3ld,%3ld,%3ld   %3ld,%3ld,%3ld   %15ld\n", connection.idx1, connection.idx2, points[connection.idx1].x, points[connection.idx1].y, points[connection.idx1].z, points[connection.idx2].x, points[connection.idx2].y, points[connection.idx2].z, connection.dist);
        if(parent1 != parent2) {
            unionfind[parent2] = parent1;
            setsizes[parent1] += setsizes[parent2];
            // printf("  joined, setsize = %ld\n", setsizes[parent1]);
            num_connections_done++;
            if(num_connections_done == points.size() - 1) {
                result = points[dists[i].idx1].x * points[dists[i].idx2].x;
            }
        }
    }

    printf("%ld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
