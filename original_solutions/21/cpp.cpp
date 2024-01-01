#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <sstream>
#include <string>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define len(a) ((int)a.size())
#define long long long
#define vec vector
#define umap unordered_map
#define uset unordered_set
int DEBUG_COUNT = 0;
void debug(string s = "") { cerr << "DEBUG " << DEBUG_COUNT++ << ": " << s << endl; }

#define LEN 131
#define STEPS 26501365
#define N (long)(STEPS - STEPS%LEN) / LEN

vec<string> grid;

struct Point {
	int r;
	int c;
};

Point find_start() {
	return {len(grid) / 2, len(grid[0]) / 2};
}

bool in_bounds(Point p) {
	return p.r >= 0 && p.r < len(grid) && p.c >= 0 && p.c < len(grid[0]);
}

bool is_garden(Point p) {
	return in_bounds(p) && grid[p.r][p.c] != '#';
}

long count(byte visited[LEN][LEN], bool even) {
	long ans = 0;
	FOR(r, LEN) {
		FOR(c, LEN) {
			if (!even) {
				if (visited[r][c] == (byte)1) { ans++; }
			} else {
				if (visited[r][c] == (byte)2) { ans++; }
			}
		}
	}
	return ans;
}

// return the amount floodfilled
long floodfill(int steps, Point start, bool even) {
	deque<Point> curr;
	deque<Point> next;
	byte visited[LEN][LEN] = {(byte)0};
	curr.push_back(start);

	FOR(i, steps+1) {
		next.clear();
		while (!curr.empty()) {
			Point p = curr.front();
			curr.pop_front();

			if ((bool)visited[p.r][p.c]) { continue; }
			visited[p.r][p.c] = (byte)(i % 2 + 1);

			Point n = {p.r - 1, p.c};
			Point e = {p.r, p.c + 1};
			Point s = {p.r + 1, p.c};
			Point w = {p.r, p.c - 1};

			if (!(bool)visited[n.r][n.c] && is_garden(n)) { next.push_back(n); }
			if (!(bool)visited[e.r][e.c] && is_garden(e)) { next.push_back(e); }
			if (!(bool)visited[s.r][s.c] && is_garden(s)) { next.push_back(s); }
			if (!(bool)visited[w.r][w.c] && is_garden(w)) { next.push_back(w); }
		}

		swap(curr, next);
	}

	return count(visited, even);
}

int main() {
	string line;
	while (getline(cin, line)) {
		grid.push_back(line);
	}

	Point n  = {0, len(grid[0]) / 2};
	Point e  = {len(grid) / 2, len(grid[0]) - 1};
	Point s  = {len(grid) - 1, len(grid[0]) / 2};
	Point w  = {len(grid) / 2, 0};
	Point nw = {0, 0};
	Point ne = {0, len(grid[0]) - 1};
	Point sw = {len(grid) - 1, 0};
	Point se = {len(grid) - 1, len(grid[0]) - 1};

	long odd  = floodfill(130, find_start(), true);
	long even = floodfill(130, find_start(), false);
	long p1nw = floodfill(64, nw, false);
	long p1ne = floodfill(64, ne, false);
	long p1sw = floodfill(64, sw, false);
	long p1se = floodfill(64, se, false);
	long p2n  = floodfill(130, n, false);
	long p2e  = floodfill(130, e, false);
	long p2s  = floodfill(130, s, false);
	long p2w  = floodfill(130, w, false);
	long p3nw = floodfill(195, nw, true);
	long p3ne = floodfill(195, ne, true);
	long p3sw = floodfill(195, sw, true);
	long p3se = floodfill(195, se, true);

	long count_odd = (N-1) * (N-1);
	long count_even = N * N;
	long count_p1 = N;
	long count_p2 = 1;
	long count_p3 = N - 1;

	long ans = count_odd * odd + count_even * even
		+ count_p1 * (p1nw + p1ne + p1sw + p1se)
		+ count_p2 * (p2n + p2e + p2s + p2w)
		+ count_p3 * (p3nw + p3ne + p3sw + p3se);

	cout << ans << endl;

}
