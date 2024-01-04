#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define vec vector
#define umap unordered_map
#define uset unordered_set
int HERE_COUNTER = 1; void debug() { cout << "here" << HERE_COUNTER++ << endl; }

#define start_dir W

vec<string> grid;

struct Point {
	int r, c;
	Point(int r, int c) : r(r), c(c) {}

	Point operator+(const Point& p) const {
		return Point(r + p.r, c + p.c);
	}

	Point& operator+=(const Point& p) {
		r += p.r;
		c += p.c;
		return *this;
	}
};

enum Dir {
	N, E, S, W
};

Point find_start() {
	FOR(r, grid.size()) {
		FOR(c, grid[r].size()) {
			if (grid[r][c] == 'S') {
				return Point(r, c);
			}
		}
	}
	return Point(-1, -1);
}

Dir follow(Dir d, char c) {
	switch (d) {
		case N:
			if (c == '|') return N;
			if (c == '7') return W;
			if (c == 'F') return E;
			break;
		case E:
			if (c == '-') return E;
			if (c == 'J') return N;
			if (c == '7') return S;
			break;
		case S:
			if (c == '|') return S;
			if (c == 'L') return E;
			if (c == 'J') return W;
			break;
		case W:
			if (c == '-') return W;
			if (c == 'L') return N;
			if (c == 'F') return S;
			break;
	}
	return N;
}

Point d2p(Dir d) {
	switch (d) {
		case N: return Point(-1, 0);
		case E: return Point(0, 1);
		case S: return Point(1, 0);
		case W: return Point(0, -1);
	}
	return Point(0, 0);
}

// Bounds check
bool in_bounds(Point p) {
	return p.r >= 0 && p.r < (int)grid.size() && p.c >= 0 && p.c < (int)grid[0].size();
}

// Advance to the next point
void go(Point &p, Dir& d) {
	d = follow(d, grid[p.r][p.c]);
	p += d2p(d);
}

// count intersection on the top half
int top_intersect(int c, string s) {
	int count = 0;

	FORR(i, c, s.size()) {
		switch (s[i]) {
			case 'J':
			case 'L':
			case '|':
				count++;
				break;
		}
	}

	return count;
}

// count the number of spaces on the inside on each line
int count_inside(string& s) {
	int start = 0, end = s.size() - 1;
	while (start < (int)s.size() && s[start] == ' ') start++;
	while (end >= 0 && s[end] == ' ') end--;

	int count = 0;
	FORR(i, start, end + 1) {
		if (s[i] == ' ' && top_intersect(i, s) % 2 == 1) {
			count++;
			s[i] = 'I';
		}
	}

	return count;
}

int main() {
	string line;
	while (getline(cin, line)) {
		grid.push_back(line);
	}

	vec<Point> path;
	Point p = find_start();
	Dir d = start_dir;
	p += d2p(d);
	do {
		// cout << "(" << p.r << ", " << p.c << "): " << grid[p.r][p.c] << endl;
		path.push_back(p);
		go(p, d);
	} while (grid[p.r][p.c] != 'S');
	path.push_back(p);


	cout << path.size() << " / 2 = " << path.size() / 2 << endl;

	// construct new reduced grid, only highlighting the parts in the path
	vec<string> rgrid(grid.size(), string(grid[0].size(), ' '));
	for (Point p : path) {
		rgrid[p.r][p.c] = grid[p.r][p.c];
	}

	int sum = 0;
	for (string s : rgrid) {
		sum += count_inside(s);
		cout << s << endl;
	}

	cout << sum << endl;
}
