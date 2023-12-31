#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define len(a) ((int)a.size())
#define vec vector
#define umap unordered_map
#define uset unordered_set

#define DEBUG true

vec<vec<int>> grid;

enum Dir { U, R, D, L };

char dtoa(Dir d) {
	switch (d) {
		case U: return '^';
		case D: return 'v';
		case L: return '<';
		case R: return '>';
		default: return ' ';
	}
}

Dir back(Dir d) {
	switch (d) {
		case U: return D;
		case D: return U;
		case L: return R;
		case R: return L;
		default: return U;
	}
}

int dr(Dir d) {
	switch (d) {
		case U: return -1;
		case D: return 1;
		case L: return 0;
		case R: return 0;
		default: return 0;
	}
}

int dc(Dir d) {
	switch (d) {
		case U: return 0;
		case D: return 0;
		case L: return -1;
		case R: return 1;
		default: return 0;
	}
}

umap<int, umap<int, umap<Dir, umap<int, tuple<int, int, Dir, int>>>>> parents;
int dijkstra() {
	umap<int, umap<int, umap<Dir, umap<int, bool>>>> visited;
	umap<int, umap<int, umap<Dir, umap<int, int>>>> distance_map;
	priority_queue<tuple<int, int, int, Dir, int>, vec<tuple<int, int, int, Dir, int>>, greater<tuple<int, int, int, Dir, int>>> pq;

	// initialize dm to all INT_MAX
	FOR(i, len(grid)) {
		FOR(j, len(grid[0])) {
			FOR(k, 4) {
				FOR(l, 10) {
					distance_map[i][j][(Dir)k][l] = INT_MAX;
				}
			}
		}
	}

	distance_map[0][0][R][0] = 0;
	distance_map[0][0][D][0] = 0;
	pq.push(make_tuple(0, 0, 0, R, 0));
	pq.push(make_tuple(0, 0, 0, D, 0));

	while (!pq.empty()) {
		// row, column, Dir, straight count, distance
		auto [dist, r, c, d, s] = pq.top();
		pq.pop();

		if (!visited[r][c][d][s]) {
			visited[r][c][d][s] = true;
			if (DEBUG) cout << r << " " << c << " " << dtoa(d) << " " << s << " " << dist << endl;

			FOR(i, 4) {
				Dir nd = (Dir)i;
				if (nd == back(d)) continue;

				int nr = r + dr(nd);
				int nc = c + dc(nd);
				int ns = (nd == d) ? s+1 : 0;

				if (DEBUG) cout << "attempting (" << r << ", " << c << ") -> (" << nr << ", " << nc << ") " << dtoa(nd) << " " << ns << endl;

				if (s+1 > 10) {
					if (DEBUG) cout << "wobbly, ns: " << ns << endl;
					continue;
				}
				if (s+1 < 4 && nd != d) {
					if (DEBUG) cout << "can't turn yet, ns: " << ns << endl;
					continue;
				}

				if (nr >= 0 && nr < len(grid) && nc >= 0 && nc < len(grid[0])) {
					int ndist = distance_map[r][c][d][s] + grid[nr][nc];
					if (ndist < distance_map[nr][nc][nd][ns]) {
						distance_map[nr][nc][nd][ns] = ndist;
						pq.push(make_tuple(ndist, nr, nc, nd, ns));
						parents[nr][nc][nd][ns] = make_tuple(r, c, d, s);
						if (DEBUG) cout << "adding" << endl;
					}
				}
			}
		}
	}

	int ind = 0;

	int min = INT_MAX;
	FOR(i, 4) {
		Dir d = (Dir)i;
		FORR(j, 3, 10) {
			if (distance_map[len(grid)-1][len(grid[0])-1][d][j] != 0) {
				if (distance_map[len(grid)-1][len(grid[0])-1][d][j] < min) {
					ind = j;
				}
				min = std::min(min, distance_map[len(grid)-1][len(grid[0])-1][d][j]);
			}
		}
	}

	if (DEBUG) {
		vec<tuple<int, int, Dir, int>> path;
		int r = len(grid)-1;
		int c = len(grid[0])-1;
		int s = ind;
		Dir d = (distance_map[r][c][R][s] < distance_map[r][c][D][s]) ? R : D;
		while (r != 0 || c != 0 ) {
			path.push_back(make_tuple(r, c, d, s));
			auto [pr, pc, pd, ps] = parents[r][c][d][s];
			r = pr;
			c = pc;
			d = pd;
			s = ps;
		}
		path.push_back(make_tuple(r, c, d, s));
		reverse(path.begin(), path.end());
		cout << endl;
		cout << "path:" << endl;
		for (auto [r, c, d, s] : path) {
			cout << r << " " << c << " " << dtoa(d) << " " << s << ": + " << grid[r][c] << " -> " << distance_map[r][c][d][s] << endl;
		}
		cout << endl;
	}

	return min;
}

int main() {
	string line;
	while (getline(cin, line)) {
		stringstream ss(line);
		vec<int> row;
		char n;
		while (ss >> n) {
			row.push_back(n-'0');
		}
		grid.push_back(row);
	}

	cout << dijkstra() << endl;
}
