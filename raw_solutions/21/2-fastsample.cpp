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
int visited[5*LEN][5*LEN] = {0};

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
	return !visited[p.r+2*LEN][p.c+2*LEN] && get(p) != '#';
}

int floodfill(int steps, Point start) {
	deque<Point> curr;
	deque<Point> next;
	curr.push_back(start);

	FOR(i, steps+1) {
		next.clear();
		while (!curr.empty()) {
			Point p = curr.front();
			curr.pop_front();

			if (visited[p.r+2*LEN][p.c+2*LEN]) { continue; }
			visited[p.r+2*LEN][p.c+2*LEN] = i % 2 + 1;

			Point n = {p.r - 1, p.c};
			Point e = {p.r, p.c + 1};
			Point s = {p.r + 1, p.c};
			Point w = {p.r, p.c - 1};

			if (is_garden(n)) { next.push_back(n); }
			if (is_garden(e)) { next.push_back(e); }
			if (is_garden(s)) { next.push_back(s); }
			if (is_garden(w)) { next.push_back(w); }
		}

		swap(curr, next);
	}

	return len(curr);
}

long count(int r, int c) {
	long ans = 0;
	FORR(i, LEN*r, LEN*(r+1)) {
		FORR(j, LEN*c, LEN*(c+1)) {
			if (visited[i+2*LEN][j+2*LEN] == 2) {
				ans++;
			}
		}
	}
	return ans;
}

int main() {
	string line;
	while (getline(cin, line)) {
		grid.push_back(line);
	}

	floodfill(131 * 2 + 65, find_start());

	// N121N
	// 13E31
	// 2EOE2
	// 13E31
	// N121N
	long odd =  count( 0,  0);
	long even = count( 0,  1);
	long p1nw = count(-1, -2);
	long p1ne = count(-1,  2);
	long p1sw = count( 1, -2);
	long p1se = count( 1,  2);
	long p2n  = count(-2,  0);
	long p2e  = count( 0,  2);
	long p2s  = count( 2,  0);
	long p2w  = count( 0, -2);
	long p3nw = count(-1, -1);
	long p3ne = count(-1,  1);
	long p3sw = count( 1, -1);
	long p3se = count( 1,  1);

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
