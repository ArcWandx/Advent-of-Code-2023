#include <bits/stdc++.h>
using namespace std;

#define s 141

class num {
public:
	int n;

	int i;
	int j;

	num(int i, int j) {
		n = 0;
		this->i = i;
		this->j = j;
	}
	num() { num(-1, -1); }
	void add_digit(char c) {
		n = n * 10 + (c - '0');
	}
};

int main() {
	num arr[s][s];
	num n;

	bool parts[s][s];
	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++)
			parts[i][j] = false;

	char c;
	int i = 0, j = 0, start;
	while (cin >> c) {
		if (n.n == 0) {
			start = j;
		}
		if (c >= '0' && c <= '9') {
			n.add_digit(c);
			j++;
		} else if (c != '.' && c != '\n') {
			// mark the parts of the path
			for (int k = -1; k <= 1; k++) {
				if (i + k < 0 || i + k >= s) continue;
				for (int l = -1; l <= 1; l++) {
					if (j + l < 0 || j + l >= s) continue;
					parts[i + k][j + l] = true;
				}
			}
		}

		if (c < '0' || c > '9') {
			for (int k = start; k < j; k++) {
				arr[i][k] = n;
			}
			n = num(i, j);
			j++;
		}
		if (j == s) {
			i++;
			j = 0;
		}
	}

	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++)
			cout << arr[i][j].n << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++)
			if (parts[i][j])
				cout << "X";
			else
				cout << ".";
		cout << endl;
	}

	// Add all nums adjacent to parts to set
	set<int> nums;
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			if (!parts[i][j]) continue;
			nums.insert(arr[i][j].n);
		}
	}

	int sum = 0;
	for (int n : nums) {
		sum += n;
	}

	cout << sum << endl;
}
