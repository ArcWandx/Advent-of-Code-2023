#include <bits/stdc++.h>
using namespace std;

int main() {
	string line;
	int sum = 0;
	while (getline(cin, line)) {
		int first = -1, last = -1;
		for (size_t i = 0; i < line.size(); i++) {
			char c = line[i];
			if (isdigit(c)) {
				if (first == -1) first = c - '0';
				last = c - '0';
			}
		}
		int n = 10 * first + last;
		sum += n;
	}

	cout << sum << endl;
}
