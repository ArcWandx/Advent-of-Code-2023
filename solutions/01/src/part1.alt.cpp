#include <bits/stdc++.h>
using namespace std;

int main() {
	string line;
	int sum = 0;
	while (getline(cin, line)) {
		int first = -1, last = -1;
		for (int i = 0; i < (int)line.size(); i++) {
			if (isdigit(line[i])) {
				first = line[i] - '0';
				break;
			}
		}
		for (int i = line.size() - 1; i >= 0; i--) {
			if (isdigit(line[i])) {
				last = line[i] - '0';
				break;
			}
		}

		int n = 10 * first + last;
		sum += n;
	}

	cout << sum << endl;
}
