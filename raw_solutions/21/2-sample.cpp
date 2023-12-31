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
	return get(p) != '#';
}

uset<Point, point_hash> floodfill(int steps, Point start) {
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

	return next;
}

bool in(Point p, int a, int b, int c, int d) {
	a *= 131; b *= 131; c *= 131; d *= 131;
	return p.r >= a && p.r < b && p.c >= c && p.c < d;
}
bool in(Point p, int a, int c) { return in(p, a, a+1, c, c+1); }

int main() {
	string line;
	while (getline(cin, line)) {
		grid.push_back(line);
	}

	uset<Point, point_hash> s = floodfill(131 * 2 + 65, find_start());

	long odd, even, p1nw, p1ne, p1sw, p1se, p2n, p2e, p2s, p2w, p3nw, p3ne, p3sw, p3se;
	odd=even=p1nw=p1ne=p1sw=p1se=p2n=p2e=p2s=p2w=p3nw=p3ne=p3sw=p3se = 0;
	for (Point p : s) {
		// N121N
		// 13E31
		// 2EOE2
		// 13E31
		// N121N

		if (in(p, 0, 0)) { odd++; }
		if (in(p, 0, 1)) { even++; }

		if (in(p, -1, -2)) { p1nw++; }
		if (in(p, -1, 2)) { p1ne++; }
		if (in(p, 1, -2)) { p1sw++; }
		if (in(p, 1, 2)) { p1se++; }

		if (in(p, -2, 0)) { p2n++; }
		if (in(p, 0, 2)) { p2e++; }
		if (in(p, 2, 0)) { p2s++; }
		if (in(p, 0, -2)) { p2w++; }

		if (in(p, -1, -1)) { p3nw++; }
		if (in(p, -1, 1)) { p3ne++; }
		if (in(p, 1, -1)) { p3sw++; }
		if (in(p, 1, 1)) { p3se++; }
	}

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
