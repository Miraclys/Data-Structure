#include "algo_base.hpp"
#include "algo.hpp"
#include "cube.hpp"
#include "search.hpp"
#include "utils.hpp"
#include <cstdio>
#include <cstdlib>
#include <map>
#include <chrono>
#include <ctime>
#include <functional>
#include <cassert>
#include <iostream>

std::map<std::string, int> str2move {
	{"U", 0}, {"U2", 1}, {"U'", 2},
	{"D", 3}, {"D2", 4}, {"D'", 5},
	{"F", 6}, {"F2", 7}, {"U'", 8},
	{"B", 9}, {"B2", 10}, {"B'", 11},
	{"L", 12}, {"L2", 13}, {"L'", 14},
	{"R", 15}, {"R2", 16}, { "R'", 17 }
};

int main(int argc, char* argv[]) {

    /*
                1   2   3
                4   5   6
                7   8   9
    10  11  12  19  20  21  28  29  30
    13  14  15  22  23  24  31  32  33
    16  17  18  25  26  27  34  35  36
                37  38  39
                40  41  42
                43  44  45
                46  47  48
                49  50  51
                52  53  54
    */
   /*
            B
        L   U   R
            F
            D
   */

    // const std::string s = "BBBBBBRRRLLBLLBLLBUUUUUUUUUFRRFRRFRRLLLFFFFFFDDDDDDDDD";
    const std::string s = "BBBBBBRRRLLBLLBLLBUUUUUUUUU";


    auto dfs_init = [](const std::string& s) {
        auto mapping = [](char x) {
            if (x == 'B') return 1;
            if (x == 'F') return 2;
            if (x == 'D') return 3;
            if (x == 'U') return 4;
            if (x == 'L') return 5;
            if (x == 'R') return 6;
            assert(0);
        };
        std::shared_ptr<rubik_cube::algo_t> algo_base(new rubik_cube::algo_t());

        int rem[6] = {9, 9, 9, 9, 9, 9};
        int ans = 0;
        
        for (const auto& i : s) {
            --rem[mapping(i)];
        }
        std::string cur = s;
        
        auto check = [&](int pos) {
            if (pos == 4 + 1 && cur[pos - 1] != 'B' 
            || pos == 13 + 1 && cur[pos - 1] != 'L' 
            || pos == 22 + 1 && cur[pos - 1] != 'U' 
            || pos == 31 + 1 && cur[pos - 1] != 'R' 
            || pos == 40 + 1 && cur[pos - 1] != 'F' 
            || pos == 49 + 1 && cur[pos - 1] != 'D') {
                return 0;
            }
            rubik_cube::cube_t cube;

            int co_sum = 0;
            int eo_sum = 0;
            int flag_c[8] = {0};
            int flag_e[12] = {0};

            for (int i = 0; i < 8; ++i) {
                int8 face1 = rubik_cube::corners_map[i][0] - 1;
                int8 face2 = rubik_cube::corners_map[i][1] - 1;
                int8 face3 = rubik_cube::corners_map[i][2] - 1;
                if (face1 >= pos || face2 >= pos || face3 >= pos) continue;
                int flag = 1;
                for (int j = 0; j < 8; ++j) {
                    if (rubik_cube::corners[j][0] == cur[face1] 
                        && rubik_cube::corners[j][1] == cur[face2] 
                        && rubik_cube::corners[j][2] == cur[face3]) {
                        cube.cp[i] = j, cube.co[i] = 0;
                        if (flag_c[cube.cp[i]] == 1) { return 0; }
                        flag_c[cube.cp[i]] = 1;
                        co_sum += cube.co[i];
                        flag = 0; break;
                    } else if (rubik_cube::corners[j][1] == cur[face1] 
                        && rubik_cube::corners[j][2] == cur[face2] 
                        && rubik_cube::corners[j][0] == cur[face3]) {
                        cube.cp[i] = j, cube.co[i] = 2;
                        if (flag_c[cube.cp[i]] == 1) { return 0; }
                        flag_c[cube.cp[i]] = 1;
                        co_sum += cube.co[i];
                        flag = 0; break;
                    } else if (rubik_cube::corners[j][2] == cur[face1] 
                        && rubik_cube::corners[j][0] == cur[face2] 
                        && rubik_cube::corners[j][1] == cur[face3]) {
                        cube.cp[i] = j, cube.co[i] = 1;
                        if (flag_c[cube.cp[i]] == 1) { return 0; }
                        flag_c[cube.cp[i]] = 1;
                        co_sum += cube.co[i];
                        flag = 0; break;
                    }
                }
                if (flag) return 0;
            }


            for (int i = 0; i < 12; ++i) {
                int8 face1 = rubik_cube::edges_map[i][0] - 1;
                int8 face2 = rubik_cube::edges_map[i][1] - 1;
                if (face1 >= pos || face2 >= pos) continue;
                int flag = 1;
                for (int j = 0; j < 12; ++j) {
                    if (rubik_cube::edges[j][0] == cur[face1] && rubik_cube::edges[j][1] == cur[face2]) {
                        cube.ep[i] = j, cube.eo[i] = 0;
                        if (flag_e[cube.ep[i]] == 1) { return 0; }
                        flag_e[cube.ep[i]] = 1;
                        eo_sum += cube.eo[i];
                        flag = 0; break;
                    } else if (rubik_cube::edges[j][1] == cur[face1] && rubik_cube::edges[j][0] == cur[face2]) {
                        cube.ep[i] = j, cube.eo[i] = 1;
                        if (flag_e[cube.ep[i]] == 1) { return 0; }
                        flag_e[cube.ep[i]] = 1;
                        eo_sum += cube.eo[i];
                        flag = 0; break;
                    }
                }
                if (flag) return 0;
            }
            return 1;
        };

        int cnt = 0;

        std::function<void(int)> dfs = [&](int x) -> void {
            if (x == 54 + 1) {
                // if (++cnt % 1000 == 0) std::cerr << cnt << " " << ans << std::endl;                
                rubik_cube::cube_t cube;
                try {
                    cube = rubik_cube::cube_state::parse(cur);
                } catch (const std::exception e) {
                    return;
                }
                if (rubik_cube::utils::verify(cube)) {
                    std::cout << "Case: #" << ++ans << ": " << cur << std::endl;
                    algo_base->solve(cube);
                }
                return;
            }
            for (const auto& i : {'B', 'F', 'D', 'U', 'L', 'R'}) {
                auto *p = &rem[mapping(i)];
                if (*p <= 0) continue;

                cur.push_back(i);
                --*p;
                if (!check(x + 1)) {
                    cur.pop_back();
                    ++*p;
                    continue;
                }
                dfs(x + 1);
                cur.pop_back();
                ++*p;
            }
        };
        dfs(27);
        return ans;
    };

    auto begin = std::chrono::system_clock().now().time_since_epoch().count();
    
    std::cout << "Total count: " << dfs_init(s) << std::endl;

    auto end = std::chrono::system_clock().now().time_since_epoch().count();

    printf("Time consumed: %.10lf\n", 1.0 * (end - begin) / 1000000);
    

}