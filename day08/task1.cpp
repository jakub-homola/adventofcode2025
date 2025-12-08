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

    size_t connections_needed = 1000;

    for(size_t i = 0; i < connections_needed; i++) {
        distinfo connection = dists[i];
        int64_t parent1 = unionfind_get(connection.idx1);
        int64_t parent2 = unionfind_get(connection.idx2);
        // printf("attempting %2zu %2zu   =   %3ld,%3ld,%3ld   %3ld,%3ld,%3ld   %15ld\n", connection.idx1, connection.idx2, points[connection.idx1].x, points[connection.idx1].y, points[connection.idx1].z, points[connection.idx2].x, points[connection.idx2].y, points[connection.idx2].z, connection.dist);
        if(parent1 != parent2) {
            unionfind[parent2] = parent1;
            setsizes[parent1] += setsizes[parent2];
            // printf("  joined, setsize = %ld\n", setsizes[parent1]);
        }
    }

    // for(size_t i = 0; i < unionfind.size(); i++) {
    //     printf("%5ld: %5ld %5ld\n", i, unionfind[i], setsizes[i]);
    // }

    std::vector<int64_t> parent_sizes;
    for(size_t i = 0; i < points.size(); i++) {
        if(unionfind[i] == i) {
            parent_sizes.push_back(setsizes[i]);
        }
    }

    size_t num_sets_to_multiply = 3;

    std::partial_sort(parent_sizes.begin(), parent_sizes.begin() + num_sets_to_multiply, parent_sizes.end(), std::greater<>());

    int64_t result = 1;
    for(size_t i = 0; i < num_sets_to_multiply; i++) {
        result *= parent_sizes[i];
    }

    printf("%ld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
