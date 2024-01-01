#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <sstream>
#include <string>
#include <deque>
#include <unordered_set>
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

#define STEPS 64

vec<string> grid;

struct Point {
	int r;
	int c;
	friend bool operator<(const Point& a, const Point& b) {
		return a.r < b.r || (a.r == b.r && a.c < b.c);
	}
};

Point find_start() {
	FOR(r, len(grid)) {
		FOR(c, len(grid[r])) {
			if (grid[r][c] == 'S') {
				return {r, c};
			}
		}
	}
	return {-1, -1};
}

bool is_garden(Point p) {
	return p.r > 0 && p.r < len(grid) - 1
		&& p.c > 0 && p.c < len(grid[0]) - 1
		&& (grid[p.r][p.c] == '.' || grid[p.r][p.c] == 'S');
}

int main() {
	string line;
	while (getline(cin, line)) {
		grid.push_back(line);
	}

	deque<Point> curr;
	set<Point> next;
	curr.push_back(find_start());

	FOR(i, STEPS) {
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
		next.clear();
	}

	cout << len(curr) << endl;
}
