#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define FOR_(i, a, b) for (int i = a; i >= (int)(b); i--)
#define len(a) ((int)a.size())
#define long long long
#define vec vector
#define umap unordered_map
#define uset unordered_set
int DEBUG_COUNT = 0;
void debug(string s = "") { cerr << "DEBUG " << DEBUG_COUNT++ << ": " << s << endl; }
#define DEBUG

vec<string> grid;
vec<vec<int*>> nums;
vec<vec<uset<int*>>> parts;

void print_grids() {
	FOR(r, len(grid)) {
		FOR(c, len(grid[r])) {
			if (nums[r][c] != nullptr) {
				cout << setw(3) << *nums[r][c] << " ";
			} else {
				cout << setw(3) << grid[r][c] << " ";
			}
		}
		cout << endl;
	}
}

bool is_part(char c) {
	return !isdigit(c) && c != '.';
}

bool is_gear(char c) {
	return c == '*';
}

bool is_valid(int r, int c) {
	if (r < 0 || r >= len(grid) || c < 0 || c >= len(grid[r])) { return false; }
	if (nums[r][c] == nullptr) { return false; }
	return true;
}

int main() {
	string line;
	while (getline(cin, line)) { grid.push_back(line); }
	FOR(i, len(grid)) {
		nums.push_back(vec<int*>(len(grid[i])));
		parts.push_back(vec<uset<int*>>(len(grid[i])));
	}

	FOR(r, len(grid)) {
		int* num = new int(0);
		FOR(c, len(grid[r])) {
			if (isdigit(grid[r][c])) {
				*num *= 10;
				*num += grid[r][c] - '0';
			} else if (*num != 0) {
				int i = 1;
				for (int d = *num; d > 0; d /= 10) {
					delete nums[r][c - i];
					nums[r][c - i] = num;
					i++;
				}
				num = new int(0);
			}
		}
	}

	FOR(r, len(grid)) {
		FOR(c, len(grid[r])) {
			if (!is_gear(grid[r][c])) { continue; }
			FORR(dr, -1, 2) {
				FORR(dc, -1, 2) {
					int nr = r + dr;
					int nc = c + dc;
					if (!is_valid(nr, nc)) { continue; }
					parts[r][c].insert(nums[nr][nc]);
				}
			}
		}
	}

	int sum = 0;
	FOR(r, len(grid)) {
		FOR(c, len(grid[r])) {
			if (!is_gear(grid[r][c])) { continue; }
			if (parts[r][c].size() != 2) { continue; }
			int ratio = 1;
			for (int* p : parts[r][c]) { ratio *= *p; }
			sum += ratio;
		}
	}
	cout << sum << endl;

}
