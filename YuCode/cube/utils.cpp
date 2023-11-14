#include "utils.hpp"

namespace rubik_cube::utils {
	bool verify(cube_t &cube) {

		int co_sum = 0;
		int eo_sum = 0;
		int flag_c[8] = {0};
		int flag_e[12] = {0};
		for (int i = 0; i < 12; i++) {

			if (cube.ep[i] >= 12 || cube.ep[i] < 0) {
				// fprintf(stderr, "not legal edge block number : %d !\n", cube.ep[i]);
				return false;
			}
			if (flag_e[cube.ep[i]] == 1) {
				// fprintf(stderr, "edge block repeated! illegal!\n");
				return false;
			}
			flag_e[cube.ep[i]] = 1;
			eo_sum += cube.eo[i];

			if (i < 8) {
				if (cube.cp[i] >= 8 || cube.cp[i] < 0) {
					// fprintf(stderr, "not legal cornor block number : %d !\n", cube.cp[i]);
					return false;
				}
				if (flag_c[cube.cp[i]] == 1) {
					// fprintf(stderr, "corner block repeated! illegal!\n");
					return false;
				}
				flag_c[cube.cp[i]] = 1;
				co_sum += cube.co[i];
			}
		}
		if ((eo_sum % 2 != 0) || (co_sum % 3 != 0)) {
			// fprintf(stderr, "block orientation is illegal!\n");
			return false;
		}

		int ce_swap_count = 0;
		ce_swap_count += swap_count(cube.ep, 12);
		ce_swap_count += swap_count(cube.cp, 8);
		if (ce_swap_count % 2 != 0) {
			// fprintf(stderr, "block position is illegal!\n");
			return false;
		}

		return true;
	}
	int swap_count(int8_t *nums, int size) {
		int ret = 0;
		int current_position = 0;
		int flags[size] = {0};
		while (1) {
			int i;
			for (i = 0; i < size; i++) {
				if (flags[i] == 0 && nums[i] != i) {
					current_position = i;
					break;
				}
			}
			if (i == size) break;
			ret -= 1;
			while (flags[current_position] == 0) {
				ret += 1;
				flags[current_position] = 1;
				current_position = nums[current_position];
			}
		}
		return ret;
	}
}