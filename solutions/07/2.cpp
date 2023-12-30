#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a) for (int i=0; i<(a); i++)
#define FORR(i, a, b) for (int i=a; i<(b); i++)

class Hand {
public:
	int bid;
	char* hand;
	map<char, int> m;
	vector<int> counts;
	long value;

	Hand(int bid, char hand[5]) {
		this->bid = bid;
		this->hand = hand;

		FOR(i, 5) {
			m[hand[i]]++;
		}
		for (auto p : m) {
			counts.push_back(p.second);
		}
		sort(counts.begin(), counts.end());

		value = calc_value();
	}

	bool five_of_a_kind() {
		for (auto p : m) {
			if (p.first != 'J') {
				if (p.second + m['J'] == 5) return true;
			} else {
				if (p.second == 5) return true;
			}
		}
		return false;
	}

	bool four_of_a_kind() {
		for (auto p : m) {
			if (p.first != 'J') {
				if (p.second + m['J'] == 4) return true;
			} else {
				if (p.second == 4) return true;
			}
		}
		return false;
	}

	bool full_house() {
		switch (m['J']) {
			case 5:
			case 4:
			case 3:
				return true;
			case 2:
				// valid counts: [2,3], [1, 2, 2]
				if (counts[0] == 2 && counts[1] == 3) return true;
				if (counts[0] == 1 && counts[1] == 2 && counts[2] == 2) return true;
				return false;
			case 1:
				// valid counts: [1,1,3], [1, 2, 2]
				if (counts[0] == 1 && counts[1] == 1 && counts[2] == 3) return true;
				if (counts[0] == 1 && counts[1] == 2 && counts[2] == 2) return true;
				return false;
			default:
				bool three = false;
				bool two = false;
				for (auto p : m) {
					if (p.second == 3) three = true;
					if (p.second == 2) two = true;
				}
				return three && two;
		}
	}

	bool three_of_a_kind() {
		for (auto p : m) {
			if (p.first != 'J') {
				if (p.second + m['J'] == 3) return true;
			} else {
				if (p.second == 3) return true;
			}
		}
		return false;
	}

	bool two_pair() {
		switch (m['J']) {
			case 5:
			case 4:
			case 3:
			case 2:
				return true;
			case 1:
				// valid counts: [1,1,1,2]
				return counts[0] == 1 && counts[1] == 1 && counts[2] == 1 && counts[3] == 2;
			default:
				int count = 0;
				for (auto p : m) {
					if (p.second == 2) count++;
				}
				return count == 2;
		}
	}

	bool one_pair() {
		for (auto p : m) {
			if (p.first != 'J') {
				if (p.second + m['J'] == 2) return true;
			} else {
				if (p.second == 2) return true;
			}
		}
		return false;
	}

	int card_value(char c) {
		switch (c) {
			case 'A': return 14;
			case 'K': return 13;
			case 'Q': return 12;
			case 'J': return 1;
			case 'T': return 10;
			default: return c - '0';
		}
	}

	int type_value() {
		if (five_of_a_kind()) return 7;
		if (four_of_a_kind()) return 6;
		if (full_house()) return 5;
		if (three_of_a_kind()) return 4;
		if (two_pair()) return 3;
		if (one_pair()) return 2;
		return 1;
	}

	long calc_value() {
		long out = type_value();
		FOR(i, 5) {
			out *= 100;
			out += card_value(hand[i]);
		}
		return out;
	}
};

int main() {
	vector<Hand> v;
	string line;
	while (cin >> line) {
		char* hand = new char[5];
		FOR(i, 5) { hand[i] = line[i]; }
		int bid;
		cin >> bid;
		Hand h(bid, hand);
		v.push_back(h);
	}

	sort(v.begin(), v.end(), [](Hand h1, Hand h2) { return h1.value < h2.value; });

	// for (Hand h : v) {
		// cout << h.hand << " " << setw(4) << h.bid << ": " << h.value << endl;
	// }

	int sum = 0;
	FOR(i, int(v.size())) {
		Hand h = v[i];
		sum += h.bid * (i+1);
	}
	cout << sum << endl;
}
