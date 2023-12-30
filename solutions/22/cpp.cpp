#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <string>
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

#define SIZE 10
#define HEIGHT 400

struct Brick;

Brick* grid[HEIGHT][SIZE][SIZE] = {nullptr};
uset<Brick*> bricks;

struct Point {
	int x, y, z;
};

char global_name = 'A';
struct Brick {
	char name;

	uset<Brick*> supports;
	uset<Brick*> supported_by;
	vec<Point> cubes;
	int z;

	Brick(Point a, Point b) {
		name = global_name++;

		FORR(z, a.z, b.z + 1) {
		FORR(y, a.y, b.y + 1) {
		FORR(x, a.x, b.x + 1) {
			cubes.push_back({x, y, z});
			grid[z][y][x] = this;
		}}}

		this->z = min(a.z, b.z);
	}
};

void print_grid(int height, int width, int length) {
	for (int z = height - 1; z >= 0; z--) {
		FOR(y, width) {
			FOR(x, length) {
				if (grid[z][y][x] == nullptr) { cout << '.'; }
				else { cout << grid[z][y][x]->name; }
			}
			cout << endl;
		}
		cout << endl;
	}
}

bool is_settled(Brick &b) {
	for (auto cube : b.cubes) {
		if (cube.z == 1
				|| (grid[cube.z - 1][cube.y][cube.x] != nullptr
				&& grid[cube.z - 1][cube.y][cube.x] != &b))
			return true;
	}
	return false;
}

void fall(Brick &b) {
	FOR(i, len(b.cubes)) {
		Point cube = b.cubes[i];
		grid[cube.z][cube.y][cube.x] = nullptr;
		grid[cube.z - 1][cube.y][cube.x] = &b;

		b.cubes[i].z--;
	}
}

int gravity() {
	uset<Brick*> settled;
	int falls = 0;

	FOR(z, HEIGHT) {
	FOR(y, SIZE) {
	FOR(x, SIZE) {
		if (grid[z][y][x] == nullptr) { continue; }

		Brick* brick = grid[z][y][x];
		if (settled.find(brick) != settled.end()) {
			continue;
		}
		settled.insert(brick);

		if (is_settled(*brick)) { continue; }
		while (!is_settled(*brick)) {
			fall(*brick);
		}
		falls++;
	}}}

	return falls;
}

void calculate_supports() {
	FOR(z, HEIGHT) {
	FOR(y, SIZE) {
	FOR(x, SIZE) {
		if (grid[z][y][x] == nullptr) { continue; }

		Brick* brick = grid[z][y][x];
		FOR(i, len(brick->cubes)) {
			Point cube = brick->cubes[i];
			if (cube.z == 1) { continue; }

			Brick* below = grid[cube.z - 1][cube.y][cube.x];
			if (below == nullptr) { continue; }
			if (below == brick) { continue; }

			brick->supported_by.insert(below);
			below->supports.insert(brick);
		}
	}}}
}

vec<Point> get_unsafe() {
	vec<Point> unsafe;

	for (auto brick : bricks) {
		bool is_unsafe = false;
		for (auto support : brick->supports) {
			if (len(support->supported_by) <= 1) {
				is_unsafe = true;
				break;
			}
		}
		if (is_unsafe) {
			unsafe.push_back(brick->cubes[0]);
		}
	}
	
	return unsafe;
}

void disintegrate(Brick* brick) {
	for (auto cube : brick->cubes) {
		grid[cube.z][cube.y][cube.x] = nullptr;
	}
}

void brick_copy(uset<Brick*> from) {
	FOR(z, HEIGHT) {
	FOR(y, SIZE) {
	FOR(x, SIZE) {
		grid[z][y][x] = nullptr;
	}}}
	for (auto brick : bricks) {
		delete brick;
	}
	bricks.clear();

	for (auto brick : from) {
		bricks.insert(new Brick(brick->cubes[0], brick->cubes[len(brick->cubes) - 1]));
	}
}

int main() {
	string line;
	while (getline(cin, line)) {
		stringstream ss(line);
		int x1, y1, z1, x2, y2, z2;
		char c;
		ss >> x1 >> c >> y1 >> c >> z1 >> c >> x2 >> c >> y2 >> c >> z2;

		bricks.insert(new Brick({x1, y1, z1}, {x2, y2, z2}));
	}

	gravity();
	calculate_supports();

	vec<Point> unsafe = get_unsafe();

	cout << "p1: " << len(bricks) - len(unsafe) << endl;

	uset<Brick*> saved;
	for (auto brick : bricks) {
		saved.insert(new Brick(brick->cubes[0], brick->cubes[len(brick->cubes) - 1]));
	}

	int sum = 0;
	for (auto cube : unsafe) {
		brick_copy(saved);
		disintegrate(grid[cube.z][cube.y][cube.x]);
		sum += gravity();
	}
	cout << "p2: " << sum << endl;

}
