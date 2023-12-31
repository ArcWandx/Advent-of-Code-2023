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

	friend bool operator==(const Point& a, const Point& b) {
		return a.r == b.r && a.c == b.c;
	}
	friend bool operator<(const Point& a, const Point& b) {
		return a.r < b.r || (a.r == b.r && a.c < b.c);
	}

	friend ostream& operator<<(ostream& os, const Point& p) {
		return os << "(" << p.r << ", " << p.c << ")";
	}
};
struct point_hash {
	size_t operator()(const Point& p) const {
		return ((p.r + p.c)*(p.r + p.c + 1)/2) + p.c;
	}
};

Point find_start() {
	return {len(grid) / 2, len(grid[0]) / 2};
}

int mod(int a, int b) {
	return (a % b + b) % b;
}

char get(Point p) {
	return grid[mod(p.r, len(grid))][mod(p.c, len(grid[0]))];
}

bool in_bounds(Point p) {
	return p.r >= 0 && p.r < len(grid) && p.c >= 0 && p.c < len(grid[0]);
}

bool is_garden(Point p) {
	return get(p) != '#' && in_bounds(p);
}

// return the amount floodfilled
int floodfill(int steps, Point start) {
	deque<Point> curr;
	uset<Point, point_hash> next;
	curr.push_back(start);

	FOR(i, steps) {
		next.clear();
		while (!curr.empty()) {
			Point p = curr.front();
			curr.pop_front();

			Point n = {p.r - 1, p.c};
			Point e = {p.r, p.c + 1};
			Point s = {p.r + 1, p.c};
			Point w = {p.r, p.c - 1};

			if (is_garden(n)) { next.insert(n); }
			if (is_garden(e)) { next.insert(e); }
			if (is_garden(s)) { next.insert(s); }
			if (is_garden(w)) { next.insert(w); }
		}

		for (Point p : next) {
			curr.push_back(p);
		}
	}

	return len(next);
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

	long odd  = floodfill(301, find_start());
	long even = floodfill(300, find_start());
	long p1nw = floodfill(64, nw);
	long p1ne = floodfill(64, ne);
	long p1sw = floodfill(64, sw);
	long p1se = floodfill(64, se);
	long p2n  = floodfill(130, n);
	long p2e  = floodfill(130, e);
	long p2s  = floodfill(130, s);
	long p2w  = floodfill(130, w);
	long p3nw = floodfill(195, nw);
	long p3ne = floodfill(195, ne);
	long p3sw = floodfill(195, sw);
	long p3se = floodfill(195, se);

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
