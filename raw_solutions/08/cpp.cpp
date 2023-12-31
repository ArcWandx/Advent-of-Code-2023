#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i=0; i<(a); i++)
#define FORR(i, a, b) for (int i=a; i<(b); i++)
#define umap unordered_map
#define uset unordered_set

int lcm(int a, int b) {
	return a*b/__gcd(a, b);
}

vector<string> start_vec(umap<string, vector<string>>& dir) {
	// for all keys, return vector of ones with third character 'A'
	vector<string> out;
	for (auto pair : dir) {
		if (pair.first[2] == 'A') {
			out.push_back(pair.first);
		}
	}
	return out;
}

bool at_dest(string& curr) {
	// Return true if all strings in curr have third character 'Z'
	return curr[2] == 'Z';
}

int main() {
	string inst;
	getline(cin, inst);

	umap<string, vector<string>> dir;
	string line, left, right;
	while (cin >> line >> left >> right) {
		dir[line].push_back(left);
		dir[line].push_back(right);
	}

	vector<string> start = start_vec(dir);
	vector<int> out = vector<int>(start.size(), 0);
	for (int c = 0; c < (int)start.size(); c++) {
		string curr = start[c];
		for (int i = 0, ind; !at_dest(curr); i = (i+1)%inst.size(), out[c]++) {
			switch (inst[i]) {
				case 'L':
					ind = 0;
					break;
				case 'R':
					ind = 1;
					break;
				default:
					ind = -1;
			}

			// cout << "at " << curr << ", going " << inst[i] << " to " << dir[curr][ind] << endl;

			curr = dir[curr][ind];
		}
	}

	long ans = out[0];
	for (int i = 1; i < (int)out.size(); i++) {
		cout << out[i] << endl;
		ans = lcm(ans, out[i]);
	}
	cout << ans << endl;
}
