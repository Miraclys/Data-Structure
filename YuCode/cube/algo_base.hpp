#ifndef __RUBIK_CUBE_ALGO_BASE_HPP
#define __RUBIK_CUBE_ALGO_BASE_HPP

#include "cube.hpp"
#include "search.hpp"
#include <vector>
#include <memory>

namespace rubik_cube {

#define __MOVE_COUNT 18
#define __MOVE_LIMIT 74943

#define __CORNERS_PERM_SIZE 40320 // 8!
#define __UD_EDGES_PERM_SIZE  40320 // 8!
#define __MID_EDGES_PERM_SIZE 24 // 4!

#define __MID_EDGES_PERM_ORIENTATION_SIZE 11880 // A(4, 12)
#define __CORNERS_ORIENTATION_SIZE 2187 // 3 ^ 7
#define __EDGES_ORIENTATION_SIZE 2048 // 2 ^ 11

#define __MID_EDGES_COMBINATION 495 // C(4, 12)

class algo_t {

public:
    algo_t();
    void solve(cube_t);

private:
	static int calc_index(cube_t &, int);
	void init();
	void phase2_fill_buffer(cube_t, int8 *, int, enum phase_type);
	void phase2_fill_pre();
	void phase1_fill_buffer(cube_t, int8 *, int, enum phase_type);
	void phase1_fill_pre();
	bool dfs_phase2(search_info_t &);
	bool phase2(cube_t, moves_t);
	bool dfs_phase1(search_info_t &);

    int8 corners_orientation[__CORNERS_ORIENTATION_SIZE];
    int8 edges_orientation[__EDGES_ORIENTATION_SIZE];
    int8 mid_edges_perm_orientation[__MID_EDGES_PERM_ORIENTATION_SIZE];

    int corners_orientation_move[__CORNERS_ORIENTATION_SIZE][__MOVE_COUNT];
    int edges_orientation_move[__EDGES_ORIENTATION_SIZE][__MOVE_COUNT];
    int mid_edges_perm_orientation_move[__MID_EDGES_PERM_ORIENTATION_SIZE][__MOVE_COUNT];

    int8 co_mec[__CORNERS_ORIENTATION_SIZE * __MID_EDGES_COMBINATION];
    int8 eo_mec[__EDGES_ORIENTATION_SIZE * __MID_EDGES_COMBINATION];

    int8 corners_perm[__CORNERS_PERM_SIZE];
	int8 ud_edges_perm[__UD_EDGES_PERM_SIZE];
	int8 mid_edges_perm[__MID_EDGES_PERM_SIZE];

    int corners_perm_move[__CORNERS_PERM_SIZE][__MOVE_COUNT];
	int ud_edges_perm_move[__UD_EDGES_PERM_SIZE][__MOVE_COUNT];
	int mid_edges_perm_move[__MID_EDGES_PERM_SIZE][__MOVE_COUNT];

    int8 cp_mep[__MID_EDGES_PERM_SIZE * __CORNERS_PERM_SIZE];
    int8 ep_mep[__MID_EDGES_PERM_SIZE * __UD_EDGES_PERM_SIZE];

    std::vector<cube_t> mid_edges_perms;
};

}

#endif