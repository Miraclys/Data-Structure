#ifndef __RUBIK_CUBE_UTILS_HPP
#define __RUBIK_CUBE_UTILS_HPP

#include "cube.hpp"

namespace rubik_cube {
    namespace utils {
        bool verify(cube_t& cube);
        int swap_count(int8* num, int size);
    }
}

#endif