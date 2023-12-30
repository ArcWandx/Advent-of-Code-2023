#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define vec vector
#define umap unordered_map
#define uset unordered_set

bool is_zero(vector<long> v) {
	for (long i : v) {
		if (i != 0) return false;
	}
	return true;
}

vector<long> diffs(vector<long> v) {
	vector<long> res;
	FOR(i, (long)v.size()-1) {
		res.push_back(v[i+1]-v[i]);
	}
	return res;
}

long predict(vector<vector<long>> stack) {
	long res = 0;
	FOR(i, (long)stack.size()) {
		if (stack[i].size() == 0) continue;
		res += stack[i].back();
	}
	return res;
}

long reverse(vector<vector<long>> stack) {
	long res = 0;
	for (long i = stack.size()-1; i >= 0; i--) {
		if (stack[i].size() == 0) continue;
		res = stack[i].front() - res;
	}
	return res;
}

int main() {
	long p1 = 0;
	long p2 = 0;
	string line;
	while (getline(cin, line)) {
		vector<vector<long>> stack;

		long n;
		vector<long> v;
		stringstream ss(line);
		while (ss >> n) {
			v.push_back(n);
		}
		stack.push_back(v);

		while (!is_zero(stack.back())) {
			stack.push_back(diffs(stack.back()));
		}

		p1 += predict(stack);
		p2 += reverse(stack);

		// stack.back().push_back(reverse(stack));
		// stack.back().push_back(predict(stack));
		// for (vector<long> v : stack) {
			// for (long i : v) {
				// cout << i << " ";
			// }
			// cout << endl;
		// }
	}

	cout << p1 << endl;
	cout << p2 << endl;
}
