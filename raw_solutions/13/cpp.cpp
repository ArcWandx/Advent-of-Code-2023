#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define vec vector
#define umap unordered_map
#define uset unordered_set

bool debug = false;

// check for symmetry about the given row
bool is_row_sym(vec<string> &grid, int row) {
	int d = min(row, (int)grid.size()-row-2);
	int start = row - d;
	int end = row + d;

	FORR(i, start, row+1) {
		if (grid[i].compare(grid[end-i+start+1]) != 0) {
			return false;
		}
	}

	return true;
}

// check for symmetry about the given column
bool is_col_sym(vec<string> &grid, int col) {
	int d = min(col, (int)grid[0].size()-col-2);
	int start = col - d;
	int end = col + d;

	FORR(i, start, col+1) {
		FOR(j, grid.size()) {
			if (grid[j][i] != grid[j][end-i+start+1]) {
				return false;
			}
		}
	}

	return true;
}

int rows(vec<string> &grid, int skip) {
	FOR(i, grid.size()-1) {
		if (i + 1 == skip) {
			if (debug) cout << "skipping row " << i << endl;
			continue;
		}

		if (debug) cout << "row " << i;
		if (is_row_sym(grid, i)) {
			if (debug) cout << " found" << endl;
			return i+1;
		}
		if (debug) cout << endl;
	}
	return -10;
}

int cols(vec<string> &grid, int skip) {
	FOR(i, grid[0].size()-1) {
		if (i + 1 == skip) {
			if (debug) cout << "skipping col " << i << endl;
			continue;
		}

		if (debug) cout << "col " << i;
		if (is_col_sym(grid, i)) {
			if (debug) cout << " found" << endl;
			return i+1;
		}
		if (debug) cout << endl;
	}
	return -10;
}

int sym(vec<string> &grid, int skip) {
	int r_skip = (skip % 100 == 0) ? skip/100 : -10;
	int r = rows(grid, r_skip);
	if (r != -10) {
		return 100*r;
	}

	int c_skip = (skip != -10) ? skip % 100 : -10;
	int c = cols(grid, c_skip);
	if (c != -10) {
		return c;
	}

	return -10;
}

void toggle_symbol(vec<string> &grid, int row, int col) {
	if (grid[row][col] == '#') {
		grid[row][col] = '.';
	} else {
		grid[row][col] = '#';
	}
}

int try_smudges(vec<string> &grid) {
	int old = sym(grid, -10);

	// try changing one symbol at a time
	FOR(i, grid.size()) {
		FOR(j, grid[0].size()) {
			if (i == -1 && j == -1) {
				debug = true;
				// debug
				cout << "old: " << old << endl;
				cout << "grid: " << endl;
				FOR(i, grid.size()) {
					cout << grid[i] << endl;
				}
			}

			toggle_symbol(grid, i, j);
			int new_sym = sym(grid, old);

			if (i == -1 && j == -1) {
				// debug
				cout << "new sym: " << new_sym << endl;
				cout << "new grid: " << endl;
				FOR(i, grid.size()) {
					cout << grid[i] << endl;
				}
			}
			debug = false;

			if (new_sym != -10) {
				return new_sym;
			}
			toggle_symbol(grid, i, j);
		}
	}

	return -10;
}

int main() {
	vec<string> grid;
	string line;
	int sum = 0;
	while (getline(cin, line)) {
		if (line.empty()) {
			// for (auto &s : grid) {
				// cout << s << endl;
			// }

			// sum += sym(grid);
			sum += try_smudges(grid);

			grid.clear();
			continue;
		}
		grid.push_back(line);
	}

	cout << sum << endl;
}
