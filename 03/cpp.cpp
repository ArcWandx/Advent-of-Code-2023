#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i=0; i<(a); i++)
#define FORR(i, a, b) for (int i=a; i<(b); i++)

bool is_symbol(char c) {
	return !isdigit(c) && c != '.';
}

int main() {
	vector<string> grid;

	string line;
	while (cin >> line) {
		grid.push_back(line);
	}
	int h = grid.size();
	int w = grid[0].size();
	vector<vector<vector<int>>> gears(h, vector<vector<int>>(w));

	int sum = 0;
	FOR(i, h) {
		FOR(j, w) {
			if (isdigit(grid[i][j])) {
				int start = j;
				int n = 0;
				while (j < w && isdigit(grid[i][j])) {
					n = n*10 + grid[i][j] - '0';
					j++;
				}

				bool flag = false;
				FORR(j2, start-1, j+1) {
					FORR(i2, i-1, i+2) {
						if (i2 < 0 || i2 >= h || j2 < 0 || j2 >= w) continue;
						flag |= is_symbol(grid[i2][j2]);
						if (flag) {
							gears[i2][j2].push_back(n);
						}
					}
				}
				if (flag) { sum += n; }
			}
		}
	}

	// print gears
	int gear_sum = 0;
	FOR(i, h) {
		FOR(j, w) {
			if (grid[i][j] == '*' && gears[i][j].size() == 2) {
				gear_sum += gears[i][j][0] * gears[i][j][1];
			}
		}
	}

	cout << sum << endl;
	cout << gear_sum << endl;
}

