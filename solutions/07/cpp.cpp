#include <bits/stdc++.h>
using namespace std;


#define FOR(i, a) for (int i=0; i<(a); i++)
#define FORR(i, a, b) for (int i=a; i<(b); i++)
#define umap unordered_map
#define uset unordered_set

#define P2 true
#define DEBUG false
#define CHECK 0b0000000000

int card_value(char c) {
	switch (c) {
		case 'A': return 14;
		case 'K': return 13;
		case 'Q': return 12;
		case 'J': return (!P2 ? 11 : 1);
		case 'T': return 10;
		default: return c - '0';
	}
}

class Hand {
public:
	int bid;
	char* hand;
	vector<int> counts;

	Hand(int bid, char hand[5]) {
		this->bid = bid;
		this->hand = hand;

		umap<char, int> m;
		FOR(i, 5) {
			m[hand[i]]++;
		}

		if (DEBUG) {
			cout << hand << endl;
			vector<int> v;
			for (auto p : m) {
				v.push_back(p.second);
			}
			sort(v.begin(), v.end(), greater<int>());
			for (int c : v) { cout << c << " "; }
			cout << endl;
		}

		for (auto p : m) {
			if (!P2 || (P2 && p.first != 'J')) {
				counts.push_back(p.second);
			}
		}
		sort(counts.begin(), counts.end(), greater<int>());
		if (P2) {
			if (counts.size() == 0) {
				counts.push_back(5);
			} else {
				counts[0] += m['J'];
			}
		}

	}

	friend bool operator<(const Hand& h1, const Hand& h2) {
		FOR(i, (int)min(h1.counts.size(), h2.counts.size())) {
			if (h1.counts[i] < h2.counts[i]) {
				return true;
			} else if (h1.counts[i] > h2.counts[i]) {
				return false;
			}
		}

		FOR(i, 5) {
			if (card_value(h1.hand[i]) < card_value(h2.hand[i])) {
				return true;
			} else if (card_value(h1.hand[i]) > card_value(h2.hand[i])) {
				return false;
			}
		}

		return false;
	}

	friend ostream& operator<<(ostream& os, const Hand& h) {
		os << h.hand << " " << h.bid << ": ";
		for (int c : h.counts) {
			os << c << " ";
		}
		return os;
	}
};

int main() {
	vector<Hand> v;
	string line;
	while (cin >> line) {
		char* hand = new char[6];
		FOR(i, 5) { hand[i] = line[i]; }
		hand[5] = '\0';
		int bid;
		cin >> bid;
		Hand h(bid, hand);
		v.push_back(h);
	}

	sort(v.begin(), v.end());

	if (DEBUG) {
		for (Hand h : v) {
			cout << h << endl;
		}
	}

	int sum = 0;
	FOR(i, (int)v.size()) {
		Hand h = v[i];
		sum += h.bid * (i+1);
	}
	cout << sum << endl;

	if (DEBUG) {
		srand(time(NULL));
		uset<int> s;
		while (s.size() < 10) {
			s.insert(rand() % 500);
		}
		vector<int> ranks;
		for (int r : s) {
			ranks.push_back(r);
		}
		sort(ranks.begin(), ranks.end());

		FOR(i, 20) {
			cout << ranks[i]+1 << ": " << v[ranks[i]] << endl;
		}
	}

	if (CHECK) {
		cout << CHECK << ": " << v[CHECK-1] << endl;
	}
}
