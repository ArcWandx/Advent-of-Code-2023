#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
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

#define LOWER 200000000000000l
#define UPPER 400000000000000l

struct Hail {
	long px, py, pz;
	long vx, vy, vz;

	friend ostream& operator<<(ostream& os, const Hail& h) {
		os << h.px << ", " << h.py << ", " << h.pz << " @ "
			<< h.vx << ", " << h.vy << ", " << h.vz;
		return os;
	}
};

bool double_equals(double a, double b, double epsilon = 0.001) {
	return abs(a - b) < epsilon;
}

bool intersects(Hail a, Hail b) {
	double x, y;
	double slope_a = (double)a.vy / a.vx;
	double slope_b = (double)b.vy / b.vx;
	double intercept_a = a.py - slope_a * a.px;
	double intercept_b = b.py - slope_b * b.px;

	// Check parallel
	if (double_equals(slope_a, slope_b)) {
		// Check same line
		return double_equals(intercept_a, intercept_b);
	}

	x = (intercept_b - intercept_a) / (slope_a - slope_b);
	y = slope_a * x + intercept_a;

	// Check if intersection is in the past for either hailstone
	if (a.vx > 0 && x < a.px) return false;
	if (a.vx < 0 && x > a.px) return false;
	if (b.vx > 0 && x < b.px) return false;
	if (b.vx < 0 && x > b.px) return false;

	return x >= LOWER && x <= UPPER && y >= LOWER && y <= UPPER;
}

int main() {
	string line;
	vec<Hail> hails;
	while (getline(cin, line)) {
		long px, py, pz;
		long vx, vy, vz;
		char c;

		stringstream ss(line);
		ss >> px >> c >> py >> c >> pz
			>> c
			>> vx >> c >> vy >> c >> vz;
		hails.push_back({px, py, pz, vx, vy, vz});
	}

	int count = 0;
	FOR(i, len(hails)) {
		FORR(j, i + 1, len(hails)) {
			if (intersects(hails[i], hails[j])) {
				count++;
			}
		}
	}
	cout << count << endl;

}
