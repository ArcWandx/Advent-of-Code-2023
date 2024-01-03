#include <bits/stdc++.h>
using namespace std;

int digit_length(int n) {
	// Return the length of n in english
	switch (n) {
		case 1: return 3;
		case 2: return 3;
		case 3: return 5;
		case 4: return 4;
		case 5: return 4;
		case 6: return 3;
		case 7: return 5;
		case 8: return 5;
		case 9: return 4;
		default: return -1;
	}
}

char to_digit(string line, int i) {
	// If substring starting at i matches "one", "two", etc., return the corresponding digit
	// Otherwise, return -1
	for (int j = 1; j <= 9; j++) {
		string s = line.substr(i, digit_length(j));
		if (s == "one") return '1';
		if (s == "two") return '2';
		if (s == "three") return '3';
		if (s == "four") return '4';
		if (s == "five") return '5';
		if (s == "six") return '6';
		if (s == "seven") return '7';
		if (s == "eight") return '8';
		if (s == "nine") return '9';
	}
	return '\0';
}

int main() {
	string line;
	int sum = 0;
	while (getline(cin, line)) {
		int first = -1, last = -1;
		for (size_t i = 0; i < line.size(); i++) {
			char c = to_digit(line, i);
			if (c == 0) c = line[i];
			if (!isdigit(c)) { continue; }

			if (first == -1) first = c - '0';
			last = c - '0';
		}
		int n = 10 * first + last;
		sum += n;
	}

	cout << sum << endl;
}
