#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define vec vector
#define umap unordered_map
#define uset unordered_set

int HASH(string s) {
	int out = 0;
	FOR(i, s.size()) {
		out += (int)(char)s[i];
		out *= 17;
		out %= 256;
	}

	return out;
}

int main() {
	int sum = 0;
	string line;
	while (getline(cin, line)) {
	stringstream ss(line);
	string sub;
	while (getline(ss, sub, ',')) {
		FOR(i, sub.size()) {
			cout << (int)sub[i] << " ";
		}
		cout << endl;
		cout << sub << endl;
		cout << HASH(sub) << endl;
		sum += HASH(sub);
	}}

	cout << sum << endl;
}
