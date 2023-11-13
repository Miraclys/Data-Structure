#include "algo.hpp"
#include "algo_base.hpp"
#include <cstring>
#include <queue>
#include <unistd.h>
#include <iostream>

namespace rubik_cube {

	void output(moves_t s) {
		for (int i = 0; i < s.valid_length; i++) {
			std::cout << " ";
			int movesteps = (s.steps[i] % 3 + 1);
			if (movesteps == 3) {
				std::cout << "UDFBLR"[s.steps[i] / 3] << "'";
			} else if (movesteps == 1) {
				std::cout << "UDFBLR"[s.steps[i] / 3];
			} else {
				std::cout << "UDFBLR"[s.steps[i] / 3] << s.steps[i] % 3 + 1;
			}
		}
		std::cout << std::endl;
	}

	static int factorial_8[] = {1, 2, 6, 24, 120, 720, 5040, 40320};
	static int factorial_4[] = {1, 2, 6, 24};

	namespace algorithm {
		int cantor(int *nums, int size, int *factorial_n) {
			int ans = 0, sum = 0;
			for (int i = 0; i < size; ++i) {
				for (int j = i + 1; j < size; ++j) {
					if (nums[j] < nums[i]) ++sum;
				}
				ans += sum * factorial_n[size - i - 2];
				sum = 0;
			}
			return ans;
		}

		int combination(int m, int n) {
			if (m < n) return 0;
			int distribution = 1;
			int arrangement = 1;
			for (int i = 0; i < n; ++i) {
				arrangement *= m - i;
				distribution *= n - i;
			}
			return arrangement / distribution;
		}

		int comb_index(int *nums, int m, int n) {
			int tar_index = 1;
			int ret = 0;
			for (int i = m - 1; i >= 0; --i) {
				if (nums[i] > 0) {
					ret += combination(m - 1 - i, tar_index);
					tar_index++;
				}
			}
			return ret;
		}
	};

	algo_t::algo_t() {
		init();
	}

	void algo_t::init() {
		cube_t cube;
		memset(ud_edges_perm_move, 0xff, sizeof(ud_edges_perm_move));
		phase2_fill_buffer(cube, ud_edges_perm, __UD_EDGES_PERM_SIZE, mid_edges_perm_index);

		memset(mid_edges_perm_move, 0xff, sizeof(mid_edges_perm_move));
		phase2_fill_buffer(cube, ud_edges_perm, __MID_EDGES_PERM_SIZE, mid_edges_perm_index);

		memset(corners_perm_move, 0xff, sizeof(corners_perm_move));
		phase2_fill_buffer(cube, ud_edges_perm, __CORNERS_PERM_SIZE, corners_perm_index);

		memset(mid_edges_perm_orientation, 0xff, sizeof(mid_edges_perm_orientation));
		phase1_fill_buffer(cube, mid_edges_perm_orientation, __MID_EDGES_PERM_ORIENTATION_SIZE, me_combine_index);

		memset(corners_orientation_move, 0xff, sizeof(corners_orientation_move));
		phase1_fill_buffer(cube, corners_orientation, __CORNERS_ORIENTATION_SIZE, co_index);

		memset(edges_orientation_move, 0xff, sizeof(edges_orientation_move));
		phase1_fill_buffer(cube, edges_orientation, __EDGES_ORIENTATION_SIZE, eo_index);

		phase2_fill_pre();
		phase1_fill_pre();
	}

	int algo_t::calc_index(cube_t &cube, int type) {
		int ret = 0;
		switch (type) {
			case co_index: {
				for (int i = 0; i < 7; i++) {
					ret = ret * 3 + cube.co[i];
				}
			} break;
			case eo_index: {
				for (int i = 0; i < 11; i++) {
					ret = ret * 2 + cube.eo[i];
				}
			} break;
			case me_combine_index: {
				int com_arr[12] = {0};
				int perm_arr[4] = {0};
				int x = 0;
				for (int i = 0; i < 12; i++) {
					if (cube.ep[i] >= 8) {
						com_arr[i] = 1;
						perm_arr[x++] = cube.ep[i] - 8;
					}
				}
				int combina_index = algorithm::comb_index(com_arr, 12, 4);
				int permu_index = algorithm::cantor(perm_arr, 4, factorial_4);
				ret = combina_index * 24 + permu_index;

			} break;
			case ud_edges_perm_index: {
				int perm_arr[8] = {0};
				for (int i = 0; i < 8; i++)
					perm_arr[i] = cube.ep[i];
				ret = algorithm::cantor(perm_arr, 8, factorial_8);
			} break;
			case mid_edges_perm_index: {
				int permArr[4] = {0};
				for (int i = 0; i < 4; i++)
					permArr[i] = cube.ep[i + 8] - 8;
				ret = algorithm::cantor(permArr, 4, factorial_4);
			} break;
			case corners_perm_index: {
				int permArr[8] = {0};
				for (int i = 0; i < 8; i++)
					permArr[i] = cube.cp[i];
				ret = algorithm::cantor(permArr, 8, factorial_8);
			} break;
		}
		return ret;
	}
	void algo_t::phase2_fill_buffer(cube_t cube, int8 *dest, int destSize, enum phase_type type) {
		std::queue<std::pair<cube_t, int>> q;
		memset(dest, 0xff, destSize);
		q.push(std::make_pair(cube, 0));

		dest[0] = 0;
		if (type == mid_edges_perm_index) {
			mid_edges_perms.push_back(cube);
		}
		while (!q.empty()) {
			std::pair<cube_t, int> front = q.front();
			int father_index = calc_index(front.first, type);
			for (int move = 0; move < 18; move++) {
				if (__MOVE_LIMIT & (1 << move)) {

					cube_t current = cube_state::rotate(move, front.first);
					int Index = calc_index(current, type);

					if (type == corners_perm_index) {
						corners_perm_move[father_index][move] = Index;
					} else if (type == ud_edges_perm_index) {
						ud_edges_perm_move[father_index][move] = Index;
					} else if (type == mid_edges_perm_index) {
						mid_edges_perm_move[father_index][move] = Index;
					}
					if (dest[Index] == -1) {
						int step = front.second;
						dest[Index] = step + 1;
						q.push(std::make_pair(current, step + 1));
						if (type == mid_edges_perm_index) {
							mid_edges_perms.push_back(current);
						}
					}
				}
			}
			q.pop();
		}
	}

	void algo_t::phase2_fill_pre() {
		memset(cp_mep, 0xff, sizeof(int8_t) * __MID_EDGES_PERM_SIZE * __CORNERS_PERM_SIZE);
		std::queue<std::pair<phase2_pru_t, int>> q;
		phase2_pru_t first_t;
		first_t.corners = 0;
		first_t.edges2 = 0;
		q.push(std::make_pair(first_t, 0));
		cp_mep[0] = 0;

		while (!q.empty()) {
			std::pair<phase2_pru_t, int> front = q.front();
			int depth = front.second;
			for (int move = 0; move < 18; move++) {
				if (__MOVE_LIMIT & (1 << move)) {
					phase2_pru_t new_t;
					new_t.corners = corners_perm_move[front.first.corners][move];
					new_t.edges2 = mid_edges_perm_move[front.first.edges2][move];
					if (cp_mep[new_t.corners * 24 + new_t.edges2] == -1) {
						q.push(std::make_pair(new_t, depth + 1));
						cp_mep[new_t.corners * 24 + new_t.edges2] = depth + 1;
					}
				}
			}
			q.pop();
		}

		memset(ep_mep, 0xff, sizeof(int8_t) * __MID_EDGES_PERM_SIZE * __UD_EDGES_PERM_SIZE);
		std::queue<std::pair<phase2_pru_t, int>> q2;
		phase2_pru_t first_t2;
		first_t2.edges1 = 0;
		first_t2.edges2 = 0;
		q2.push(std::make_pair(first_t2, 0));
		ep_mep[0] = 0;
		while (!q2.empty()) {
			std::pair<phase2_pru_t, int> front = q2.front();
			int depth = front.second;
			for (int move = 0; move < 18; move++) {
				if (__MOVE_LIMIT & (1 << move)) {
					phase2_pru_t new_t;
					new_t.edges1 = ud_edges_perm_move[front.first.edges1][move];
					new_t.edges2 = mid_edges_perm_move[front.first.edges2][move];
					if (ep_mep[new_t.edges1 * 24 + new_t.edges2] == -1) {
						q2.push(std::make_pair(new_t, depth + 1));
						ep_mep[new_t.edges1 * 24 + new_t.edges2] = depth + 1;
					}
				}
			}
			q2.pop();
		}
	}
	void algo_t::phase1_fill_buffer(cube_t goalstate, int8_t *dest, int destSize, enum phase_type type) {
		std::queue<std::pair<cube_t, int>> q;
		memset(dest, 0xff, destSize);
		std::pair<cube_t, int> firstPair(goalstate, 0);
		q.push(firstPair);
		dest[0] = 0;
		if (type == me_combine_index) {
			for (int i = 0; i < __MID_EDGES_PERM_SIZE; i++) {
				q.push(std::make_pair(mid_edges_perms[i], 0));
				int Index = calc_index(mid_edges_perms[i], me_combine_index);
				dest[Index] = 0;
			}
		}

		while (!q.empty()) {
			std::pair<cube_t, int> front = q.front();
			int father_index = calc_index(front.first, type);
			for (int move = 0; move < 18; move++) {
				int step = front.second;
				cube_t currstate = cube_state::rotate(move, front.first);
				int Index = calc_index(currstate, type);
				if (type == co_index) {
					corners_orientation_move[father_index][move] = Index;
				} else if (type == eo_index) {
					edges_orientation_move[father_index][move] = Index;
				} else {
					mid_edges_perm_orientation_move[father_index][move] = Index;
				}
				if (dest[Index] == -1) {
					dest[Index] = step + 1;
					q.push(std::make_pair(currstate, step + 1));
				}
			}
			q.pop();
		}
	}
	void algo_t::phase1_fill_pre() {
		int search_count = 0;
		memset(co_mec, 0xff, sizeof(int8_t) * __CORNERS_ORIENTATION_SIZE * __MID_EDGES_COMBINATION);
		std::queue<std::pair<phase1_pru_t, int>> q;
		phase1_pru_t first_t;
		first_t.co = 0;
		first_t.mid_edges_combination = 0;
		q.push(std::make_pair(first_t, 0));
		co_mec[0] = 0;
		while (!q.empty()) {
			std::pair<phase1_pru_t, int> front = q.front();
			int depth = front.second;
			search_count++;
			for (int move = 0; move < 18; move++) {
				phase1_pru_t new_t;
				new_t.co = corners_orientation_move[front.first.co][move];
				new_t.mid_edges_combination = mid_edges_perm_orientation_move[front.first.mid_edges_combination][move];
				if (co_mec[new_t.co * __MID_EDGES_COMBINATION + new_t.mid_edges_combination / 24] == -1) {
					q.push(std::make_pair(new_t, depth + 1));
					co_mec[new_t.co * __MID_EDGES_COMBINATION + new_t.mid_edges_combination / 24] = depth + 1;
				}
			}
			q.pop();
		}

		search_count = 0;
		memset(eo_mec, 0xff, sizeof(int8_t) * __EDGES_ORIENTATION_SIZE * __MID_EDGES_COMBINATION);
		std::queue<std::pair<phase1_pru_t, int>> q2;
		phase1_pru_t first_t2;
		first_t2.eo = 0;
		first_t2.mid_edges_combination = 0;
		q2.push(std::make_pair(first_t2, 0));
		eo_mec[0] = 0;
		while (!q2.empty()) {
			std::pair<phase1_pru_t, int> front = q2.front();
			int depth = front.second;
			search_count++;
			for (int move = 0; move < 18; move++) {
				phase1_pru_t new_t;
				new_t.eo = edges_orientation_move[front.first.eo][move];
				new_t.mid_edges_combination = mid_edges_perm_orientation_move[front.first.mid_edges_combination][move];
				if (eo_mec[new_t.eo * __MID_EDGES_COMBINATION + new_t.mid_edges_combination / 24] == -1) {
					q2.push(std::make_pair(new_t, depth + 1));
					eo_mec[new_t.eo * __MID_EDGES_COMBINATION + new_t.mid_edges_combination / 24] = depth + 1;
				}
			}
			q2.pop();
		}
	}
	bool algo_t::dfs_phase2(search_info_t &se_t) {
		for (int move = 0; move < 18; move++) {
			if (__MOVE_LIMIT & (1 << move)) {
				if (move / 3 == se_t.face) continue;
				int ud_edges_perm_index = ud_edges_perm_move[se_t.ud_edges_perm_index][move];
				int mid_edges_perm_index = mid_edges_perm_move[se_t.mid_edges_perm_index][move];
				int corners_perm_index = corners_perm_move[se_t.corners_perm_index][move];
				int val = std::max(ep_mep[ud_edges_perm_index * 24 + mid_edges_perm_index], cp_mep[corners_perm_index * 24 + mid_edges_perm_index]);
				if (val + se_t.current_depth < se_t.total_depth) {
					(*se_t.steps).steps[se_t.current_depth] = move;
					if (val == 0) {
						return true;
					}
					search_info_t newSe_t = se_t;
					newSe_t.current_depth += 1;
					newSe_t.ud_edges_perm_index = ud_edges_perm_index;
					newSe_t.mid_edges_perm_index = mid_edges_perm_index;
					newSe_t.corners_perm_index = corners_perm_index;
					newSe_t.face = move / 3;
					if (dfs_phase2(newSe_t))
						return true;
				}
			}
		}

		return false;
	}

	bool algo_t::phase2(cube_t cube, moves_t moves) {
		for (int i = 0; i < moves.valid_length; i++) {
			cube = cube_state::rotate(moves.steps[i], cube);
		}
		int phase2_len = (MAX_STEP - moves.valid_length) > 10 ? 10 : (MAX_STEP - moves.valid_length);
		for (int depth = 0; depth <= phase2_len; depth++) {
			moves_t moves2(depth);
			search_info_t search;
			search.face = -1;
			search.ud_edges_perm_index = calc_index(cube, ud_edges_perm_index);
			search.mid_edges_perm_index = calc_index(cube, mid_edges_perm_index);
			search.corners_perm_index = calc_index(cube, corners_perm_index);
			search.current_depth = 0;
			search.total_depth = depth;
			search.steps = &moves2;

			if (dfs_phase2(search)) {
				// solution found: moves moves2
				output(moves);
				output(moves2);
				return true;
			}
		}
		return false;
	}

	bool algo_t::dfs_phase1(search_info_t &se_t) {

		for (int move = 0; move < 18; move++) {
			if (move / 3 == se_t.face) continue;

			int co_index = corners_orientation_move[se_t.co_index][move];
			int eo_index = edges_orientation_move[se_t.eo_index][move];
			int me_combine_index = mid_edges_perm_orientation_move[se_t.me_combine_index][move];

			int val = std::max(co_mec[__MID_EDGES_COMBINATION * co_index + me_combine_index / 24],
							   eo_mec[__MID_EDGES_COMBINATION * eo_index + me_combine_index / 24]);
			if (val + se_t.current_depth < se_t.total_depth) {
				(*se_t.steps).steps[se_t.current_depth] = move;
				if (val == 0) {
					if (phase2(se_t.init_state, *se_t.steps))
						return true;
				}
				search_info_t newSe_t = se_t;
				newSe_t.current_depth += 1;
				newSe_t.face = move / 3;
				newSe_t.co_index = co_index;
				newSe_t.eo_index = eo_index;
				newSe_t.me_combine_index = me_combine_index;
				if (dfs_phase1(newSe_t)) {
					return true;
				}
			}
		}

		return false;
	}

	void algo_t::solve(cube_t cube) {
		int depth = 0;

		while (true) {
			moves_t moves(depth);
			search_info_t search;

			search.face = -1;
			search.init_state = cube;
			search.current_depth = 0;
			search.total_depth = depth;
			search.steps = &moves;
			search.co_index = calc_index(cube, co_index);
			search.eo_index = calc_index(cube, eo_index);
			search.me_combine_index = calc_index(cube, me_combine_index);

			if (dfs_phase1(search))
				break;
			depth++;
		}
	}

}
