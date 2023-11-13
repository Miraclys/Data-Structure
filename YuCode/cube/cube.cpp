#include "cube.hpp"

namespace rubik_cube {

	inline int8 __increase(int8 x) {
		int var = x;
		if (x < 2) var = 1;
		else var = -2;
		return x + var;
	}

	inline int8 __decrease(int8 x) {
		int var = x;
		if (x > 0) var = -1;
		else var = 2;
		return x + var;
	}

	cube_t::cube_t() {
		for (int i = 0; i < 8; ++i) {
			cp[i] = i, co[i] = 0;
		}
		for (int i = 0; i < 12; ++i) {
			ep[i] = i, eo[i] = 0;
		}
	}

	cube_t cube_state::rotate(int move, cube_t& cb) {
		int face = move / 3;
		int rcount = move % 3 + 1;
		cube_t ret = cb;

		for (int i = 0; i < 4; ++i) {
			ret.ep[face_edges[face][i]] = cb.ep[face_edges[face][(i + rcount) % 4]];
			ret.cp[face_corners[face][i]] = cb.cp[face_corners[face][(i + rcount) % 4]];
		}

		// counter clockwise
		// F/B/L/R 2->1, 1->0, 0-2 when block move from D face to U face or U face to D face  
		// F/B/L/R 0->1, 1->2, 2-0 when block move from D face to D face or U face to U face 
	
		// clockwise
		// F/B/L/R 0->1, 1->2, 2-0 when block move from D face to U face or U face to D face  
		// F/B/L/R 2->1, 1->0, 0-2 when block move from D face to D face or U face to U face 

		if (face > 1 && (rcount == 1 || rcount == 3)) {
			if (rcount == 1) {
				ret.co[face_corners[face][0]] = __decrease(cb.co[face_corners[face][1]]);
				ret.co[face_corners[face][1]] = __increase(cb.co[face_corners[face][2]]);
				ret.co[face_corners[face][2]] = __decrease(cb.co[face_corners[face][3]]);
				ret.co[face_corners[face][3]] = __increase(cb.co[face_corners[face][0]]);
			} else {
				ret.co[face_corners[face][0]] = __decrease(cb.co[face_corners[face][3]]);
				ret.co[face_corners[face][1]] = __increase(cb.co[face_corners[face][0]]);
				ret.co[face_corners[face][2]] = __decrease(cb.co[face_corners[face][1]]);
				ret.co[face_corners[face][3]] = __increase(cb.co[face_corners[face][2]]);
			}
		} else {
			for (int i = 0; i < 4; ++i) {
				ret.co[face_corners[face][i]] = cb.co[face_corners[face][(i + rcount) % 4]];
			}
		}

		for (int i = 0; i < 4; ++i) {
			if ((face == 2 || face == 3) && (rcount == 1 || rcount == 3)) {
				ret.eo[face_edges[face][i]] = cb.eo[face_edges[face][(i + rcount) % 4]] == 1 ? 0 : 1;
			} else {
				ret.eo[face_edges[face][i]] = cb.eo[face_edges[face][(i + rcount) % 4]];
			}
		}

		return ret;

	}

	cube_t cube_state::parse(const std::string& s) {
		cube_t ret;
		if (s[4] != 'B' || s[13] != 'L' || s[22] != 'U' || s[31] != 'R' || s[40] != 'F' || s[49] != 'D') {
			throw std::exception(), "Illegal sequence."; 
		}

		for (int i = 0; i < 8; ++i) {
			int8 face1 = corners_map[i][0] - 1;
			int8 face2 = corners_map[i][1] - 1;
			int8 face3 = corners_map[i][2] - 1;
			for (int j = 0; j < 8; ++j) {
				if (corners[j][0] == s[face1] && corners[j][1] == s[face2] && corners[j][2] == s[face3]) {
					ret.cp[i] = j, ret.co[i] = 0; break;
				} else if (corners[j][1] == s[face1] && corners[j][2] == s[face2] && corners[j][0] == s[face3]) {
					ret.cp[i] = j, ret.co[i] = 2; break;
				} else if (corners[j][2] == s[face1] && corners[j][0] == s[face2] && corners[j][1] == s[face3]) {
					ret.cp[i] = j, ret.co[i] = 1; break;
				}
			}
		}

		for (int i = 0; i < 12; ++i) {
			int8 face1 = edges_map[i][0] - 1;
			int8 face2 = edges_map[i][1] - 1;
			for (int j = 0; j < 12; ++j) {
				if (edges[j][0] == s[face1] && edges[j][1] == s[face2]) {
					ret.ep[i] = j, ret.eo[i] = 0; break;
				} else if (edges[j][1] == s[face1] && edges[j][0] == s[face2]) {
					ret.ep[i] = j, ret.eo[i] = 1; break;
				}
			}
		}

		return ret;
	}
}