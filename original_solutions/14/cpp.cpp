#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define vec vector
#define umap unordered_map
#define uset unordered_set

#define CYCLES 1000

void print(vec<string> &v) { for (auto &s : v) { cout << s << endl; } }

void swap(vec<string> &grid, int i, int j, int i2, int j2) {
	char tmp = grid[i][j];
	grid[i][j] = grid[i2][j2];
	grid[i2][j2] = tmp;
}

void tilt_north(vec<string> &grid) {
	FOR(c, grid[0].size()) {
		int mark = -1;
		FOR(r, grid.size()) {
			if (grid[r][c] == 'O') {
				if (mark != -1) {
					swap(grid, r, c, mark, c);
					mark++;
				}
			} else if (grid[r][c] == '.') {
				if (mark == -1) {
					mark = r;
				}
			} else if (grid[r][c] == '#') {
				mark = -1;
			}
		}
	}
}

void tilt_west(vec<string> &grid) {
	FOR(r, grid.size()) {
		int mark = -1;
		FOR(c, grid[0].size()) {
			if (grid[r][c] == 'O') {
				if (mark != -1) {
					swap(grid, r, c, r, mark);
					mark++;
				}
			} else if (grid[r][c] == '.') {
				if (mark == -1) {
					mark = c;
				}
			} else if (grid[r][c] == '#') {
				mark = -1;
			}
		}
	}
}

void tilt_south(vec<string> &grid) {
	FOR(c, grid[0].size()) {
		int mark = -1;
		for (int r = grid.size() - 1; r >= 0; r--) {
			if (grid[r][c] == 'O') {
				if (mark != -1) {
					swap(grid, r, c, mark, c);
					mark--;
				}
			} else if (grid[r][c] == '.') {
				if (mark == -1) {
					mark = r;
				}
			} else if (grid[r][c] == '#') {
				mark = -1;
			}
		}
	}
}

void tilt_east(vec<string> &grid) {
	FOR(r, grid.size()) {
		int mark = -1;
		for (int c = grid[0].size() - 1; c >= 0; c--) {
			if (grid[r][c] == 'O') {
				if (mark != -1) {
					swap(grid, r, c, r, mark);
					mark--;
				}
			} else if (grid[r][c] == '.') {
				if (mark == -1) {
					mark = c;
				}
			} else if (grid[r][c] == '#') {
				mark = -1;
			}
		}
	}
}

int row_count(vec<string> &grid, int r) {
	int count = 0;
	FOR(c, grid[r].size()) {
		if (grid[r][c] == 'O') {
			count++;
		}
	}
	return count;
}

int main(int, char** argv) {
	int cycles = atoi(argv[1]);

	string line;
	vec<string> grid;
	while (getline(cin, line)) {
		grid.push_back(line);
	}

	FOR(i, cycles) {
		tilt_north(grid);
		tilt_west(grid);
		tilt_south(grid);
		tilt_east(grid);
	}


	int sum = 0;
	int weight = 1;
	for (int r = grid.size() - 1; r >= 0; r--) {
		sum += row_count(grid, r) * weight;
		weight++;
	}

	cout << sum << endl;

	// print(grid);
}
