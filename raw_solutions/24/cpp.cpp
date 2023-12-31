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

}
