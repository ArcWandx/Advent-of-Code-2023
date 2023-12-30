#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define vec vector
#define umap unordered_map
#define uset unordered_set

vec<string> rec;
vec<vec<int>> checks;

bool works(string line, vec<int> check, bool* is_good) {
	FOR(i, line.length()) {
		if (line[i] == '.' &&  is_good[i]) return false;
		if (line[i] == '#' && !is_good[i]) return false;
	}

	// find all contiguous blocks in test
	vec<int> cont;
	int count = 0;
	FOR(i, line.length()) {
		if (is_good[i]) {
			count++;
		} else {
			if (count > 0) {
				cont.push_back(count);
				count = 0;
			}
		}
	}
	if (count > 0) cont.push_back(count);

	// make sure check represents all contiguous blocks
	if (cont.size() != check.size()) return false;
	FOR(i, cont.size()) {
		if (cont[i] != check[i]) return false;
	}

	return true;
}

//
// bool better_works(

int main() {
	string line;
	while (getline(cin, line)) {
		stringstream ss(line);
		string record;
		ss >> record;
		rec.push_back(record);
		checks.push_back(vec<int>());
		int n;
		char c;
		do {
			ss >> n;
			checks.back().push_back(n);
		} while (ss >> c);
	}

	// on each line, check if any given permutation is valid
	long sum = 0;
	FOR(i, rec.size()) {
		// permutate all binary strings of the right length
		int len = rec[i].length();
		bool test[len];
		int end = pow(2, len);
		FOR(j, end) {
			int k = j;
			FOR(l, len) {
				test[l] = k % 2;
				k /= 2;
			}
			if (works(rec[i], checks[i], test)) { sum++; }
		}
	}

	cout << sum << endl;

}
