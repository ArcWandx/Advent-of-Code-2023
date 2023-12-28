#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (a); i++)
#define FORR(i, a, b) for (int i = a; i < (b); i++)
#define len(a) ((int)a.size())
#define vec vector
#define umap unordered_map
#define uset unordered_set
#define DEBUG false
int DEBUG_COUNT = 0;
void debug(string s = "") { cerr << "DEBUG " << DEBUG_COUNT++ << ": " << s << endl; }

constexpr int SIZE = 880;
constexpr int MAX_BEAM = SIZE*4;

constexpr int MAX_THREAD = 8;
constexpr int BLOCK_SIZE = SIZE / MAX_THREAD;

char grid[SIZE*SIZE];

enum Dir {
	L,R,U,D
};

struct Beam {
	int r, c;
	Dir dir;
};

void print_grid(u_int8_t energized[SIZE*SIZE]) {
	// print grid with energized
	FOR(r, SIZE) {
		FOR(c, SIZE) {
			if ((bool) energized[r*SIZE + c] && grid[r*SIZE + c] == '.') {
				cout << 'X';
			} else {
				cout << grid[r*SIZE + c];
			}
		}
		cout << endl;
	}
}

int count_energized(u_int8_t energized[SIZE*SIZE]) {
	int count = 0;
	FOR(r, SIZE) {
		FOR(c, SIZE) {
			if ((bool) energized[r*SIZE + c]) count++;
		}
	}
	return count;
}

void mark(Beam& beam, u_int8_t energized[SIZE*SIZE]) {
	energized[beam.r*SIZE + beam.c] |= (u_int8_t)(1 << beam.dir);
}

void mark(vec<Beam>& beams, u_int8_t energized[SIZE*SIZE]) {
	for (auto& beam : beams) {
		mark(beam, energized);
	}
}

bool prune(Beam& beam, u_int8_t energized[SIZE*SIZE]) {
	return beam.r < 0 || beam.r >= SIZE
			|| beam.c < 0 || beam.c >= SIZE
			|| (bool)(energized[beam.r*SIZE + beam.c] & (u_int8_t)(1 << beam.dir));
}

void remove(vec<Beam>& beams, int ind) {
	beams[ind] = beams.back();
	beams.pop_back();
}

void prune(vec<Beam>& beams, u_int8_t energized[SIZE*SIZE]) {
	for (int i = len(beams) - 1; i >= 0; i--) {
		if (prune(beams[i], energized)) {
			// erase from middle is O(1) when not preserving order
			remove(beams, i);
		}
	}
}

void increment(Beam& beam) {
	switch (beam.dir) {
		case L: --beam.c; break;
		case R: ++beam.c; break;
		case U: --beam.r; break;
		case D: ++beam.r; break;
	}
}

void run(Beam& beam, vec<Beam>& beams, int ind, u_int8_t energized[SIZE*SIZE]) {
	switch (beam.dir) {
		case L:
			while (beam.c > 0 && grid[beam.r*SIZE + --beam.c] == '.') {
				mark(beam, energized);
			}
			if (beam.c == 0 && grid[beam.r*SIZE + beam.c] == '.') {
				remove(beams, ind);
			}
			break;
		case R:
			while (beam.c < SIZE - 1 && grid[beam.r*SIZE + ++beam.c] == '.') {
				mark(beam, energized);
			}
			if (beam.c == SIZE - 1 && grid[beam.r*SIZE + beam.c] == '.') {
				remove(beams, ind);
			}
			break;
		case U:
			while (beam.r > 0 && grid[(--beam.r)*SIZE + beam.c] == '.') {
				mark(beam, energized);
			}
			if (beam.r == 0 && grid[beam.r*SIZE + beam.c] == '.') {
				remove(beams, ind);
			}
			break;
		case D:
			while (beam.r < SIZE - 1 && grid[(++beam.r)*SIZE + beam.c] == '.') {
				mark(beam, energized);
			}
			if (beam.r == SIZE - 1 && grid[beam.r*SIZE + beam.c] == '.') {
				remove(beams, ind);
			}
			break;
	}
}

void beam_reflect_slash(Beam& beam) {
	beam.dir = (Dir)(beam.dir ^ 0b11);
	increment(beam);
}

void beam_reflect_backslash(Beam& beam) {
	beam.dir = (Dir)(beam.dir ^ 0b10);
	increment(beam);
}

void beam_split_vertical(Beam& beam, vec<Beam>& beams) {
	if (beam.dir == U) {
		--beam.r;
		return;
	} else if (beam.dir == D) {
		++beam.r;
		return;
	}

	beam.dir = U;
	--beam.r;
	beams.push_back({beam.r+1, beam.c, D});
}

void beam_split_horizontal(Beam& beam, vec<Beam>& beams) {
	if (beam.dir == L) {
		--beam.c;
		return;
	} else if (beam.dir == R) {
		++beam.c;
		return;
	}

	beam.dir = L;
	--beam.c;
	beams.push_back({beam.r, beam.c+1, R});
}

void step(vec<Beam>& beams, u_int8_t energized[SIZE*SIZE]) {
	for (int i = len(beams) - 1; i >= 0; i--) {
		Beam& beam = beams[i];
		switch (grid[beam.r*SIZE + beam.c]) {
			case '.':  run(beam, beams, i, energized); break;
			case '/':  beam_reflect_slash(beam); break;
			case '\\': beam_reflect_backslash(beam); break;
			case '|':  beam_split_vertical(beam, beams); break;
			case '-':  beam_split_horizontal(beam, beams); break;
		}
	}
}

int energize(int r, int c, Dir dir) {
	u_int8_t energized[SIZE*SIZE] = {0};
	vec<Beam> beams(MAX_BEAM, Beam());
	beams[0] = {r, c, dir};
	while (!beams.empty()) {
		mark(beams, energized);
		step(beams, energized);
		prune(beams, energized);
	}

	if (DEBUG) print_grid(energized);

	return count_energized(energized);
}

int main() {
	FOR(i, SIZE) {
		FOR(j, SIZE) {
			cin >> grid[i*SIZE + j];
		}
	}

	// int max_value = energize(0, 0, R);
	int max_value = 0;
#pragma omp parallel for reduction(max: max_value)
	FOR(i, SIZE) {
		max_value = max(max_value, energize(i, 0, R));
		max_value = max(max_value, energize(i, SIZE - 1, L));
		max_value = max(max_value, energize(0, i, D));
		max_value = max(max_value, energize(SIZE - 1, i, U));
	}

	cout << max_value << endl;
}
