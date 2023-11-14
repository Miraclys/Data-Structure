#ifndef __RUBIK_CUBE_SEARCH_HPP
#define __RUBIK_CUBE_SEARCH_HPP

#include "cube.hpp"
#define MAX_STEP 20

namespace rubik_cube {
	struct phase2_pru_t {
		int corners;
		int edges1;
		int edges2;
	};

	struct phase1_pru_t {
		int co, eo;
		int mid_edges_combination;
	};

	struct moves_t {
		int steps[16];
		int valid_length;
		moves_t(int size) {
			for (int i = 0; i < 16; ++i) {
				steps[i] = 0;
			}
			valid_length = size;
		}
	};

	struct search_info_t {
		cube_t init_state;
		int face, total_depth, current_depth;
		moves_t *steps;
		int co_index;
		int eo_index;
		int me_combine_index;
		int ud_edges_perm_index;
		int mid_edges_perm_index;
		int corners_perm_index;
	};
	enum phase_type {
		eo_index = 0,
		co_index,
		me_combine_index,
		ud_edges_perm_index,
		mid_edges_perm_index,
		corners_perm_index
	};
}

#endif