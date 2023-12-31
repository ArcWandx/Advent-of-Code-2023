#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i=0; i<(a); i++)
#define FORR(i, a, b) for (int i=a; i<(b); i++)
#define umap unordered_map
#define uset unordered_set

int main() {
	string inst;
	getline(cin, inst);

	umap<string, vector<string>> dir;
	string line, left, right;
	while (cin >> line >> left >> right) {
		dir[line].push_back(left);
		dir[line].push_back(right);
	}

	string curr = "AAA";
	string dest = "ZZZ";
	int out = 0;
	for (int i = 0, ind; curr != dest; i = (i+1)%inst.size(), out++) {
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

	cout << out << endl;
}
