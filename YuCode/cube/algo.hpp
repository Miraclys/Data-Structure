#ifndef __RUBIK_CUBE_ALGO_HPP
#define __RUBIK_CUBE_ALGO_HPP

namespace rubik_cube {

    namespace algorithm {
        int cantor(int* nums, int size, int* factorial_n);
        int combination(int m, int n);
        int comb_index(int* nums, int m, int n);
    }

}

#endif