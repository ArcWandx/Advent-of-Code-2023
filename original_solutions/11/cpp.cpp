#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define vec vector
#define umap unordered_map
#define uset unordered_set

vec<string> grid;

struct Point {
	long r, c;
	Point(long row, long col) : r(row), c(col) {}
};

void push_down(long i, vec<Point> &g) {
	for (auto &p : g) {
		if (p.r > i) {
			// p.r++;
			p.r += 999999;
		}
	}
}

void push_right(long i, vec<Point> &g) {
	for (auto &p : g) {
		if (p.c > i) {
			// p.c++;
			p.c += 999999;
		}
	}
}

int main() {
	string line;
	while (getline(cin, line)) {
		grid.push_back(line);
	}

	vec<Point> g;
	vec<bool> r(grid.size(), true);
	vec<bool> c(grid[0].size(), true);

	FOR(i, grid.size()) {
		FOR(j, grid[i].size()) {
			if (grid[i][j] == '#') {
				g.push_back(Point(i, j));
				r[i] = false;
				c[j] = false;
			}
		}
	}

	for(long i = r.size() - 1; i >= 0; i--) {
		if (r[i]) {
			push_down(i, g);
		}
	}
	for(int i = c.size() - 1; i >= 0; i--) {
		if (c[i]) {
			push_right(i, g);
		}
	}

	// for every point, find distance to every other point
	long sum = 0;
	FOR(i, g.size()) {
		FORR(j, i + 1, g.size()) {
			sum += abs(g[i].r - g[j].r) + abs(g[i].c - g[j].c);
		}
	}

	cout << sum << endl;
}
