#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define len(a) ((int)a.size())
#define long long long
#define vec vector
#define umap unordered_map
#define uset unordered_set
int DEBUG_COUNT = 0;
void debug(string s = "") { cerr << "DEBUG " << DEBUG_COUNT++ << ": " << s << endl; }
#define DEBUG 0
#define REPLACE false

vec<string> records;
vec<vec<int>> chunks_list;

enum Status {
	EMPTY, // 0
	UNDAMAGED, // 1
	DAMAGED, // 2
	CERTAIN, // 3
	UNCERTAIN, // 4
	MAYBE_UNDMGD, // 5
	MAYBE_DMGD, // 6
	MIXED, // 7
};
Status status(string& record, int ind) {
	int charset = 0;
	FORR(i, ind, len(record)) {
		char c = record[i];
		if (charset == 7) {
			break;
		} if (c == '.') {
			charset |= 1;
		} else if (c == '#') {
			charset |= 2;
		} else if (c == '?') {
			charset |= 4;
		}
	}
	return (Status)charset;
}

bool is_certainly_damaged(string& record, int ind) {
	return status(record, ind) & 2;
}

string to_string(string& record, int ind, vec<int>& chunks, int chunk_ind, int cont) {
	stringstream ss;
	FOR(i, len(record)) {
		if (i == ind) { ss << "["; }
		else if (i == ind + 1) { ss << "]"; }
		else { ss << " "; }
		ss << record[i];
	}
	if (ind == len(record)) { ss << "$ "; }
	else if (ind == len(record) - 1) { ss << "] "; }
	else { ss << "  "; }

	ss << ": [" << chunk_ind << "] - " << cont << " | ";
	FOR(i, len(chunks)) {
		if (i == chunk_ind) { ss << "["; }
		else if (i == chunk_ind + 1) { ss << "]"; }
		else { ss << " "; }
		ss << chunks[i];
	}
	if (chunk_ind == len(chunks)) { ss << "[] "; }
	else if (chunk_ind == len(chunks) - 1) { ss << "]  "; }
	else { ss << "   "; }
	return ss.str();
}

vec<int> decrement(vec<int> chunks) {
	chunks[0]--;
	return chunks;
}

umap<string, long> cache;
long count(string& record, int ind, vec<int>& chunks, int chunk_ind, int cont) {
	string key = to_string(record, ind, chunks, chunk_ind, cont);
	if (DEBUG) cout << key << endl;
	if (cache.count(key)) {
		if (DEBUG) cout << "--- return: cache ---" << endl;
		return cache[key];
	}

	// Base cases
	// Tried to do too many contiguous
	if (cont > chunks[chunk_ind]) {
		if (DEBUG) cout << "--- return: too many contiguous ---" << endl;
		return 0;
	}
	// No more chunks of damaged
	if (chunk_ind == len(chunks) - 1 && chunks[chunk_ind] == cont) {
		if (DEBUG) cout << "--- return: no more chunks: " << !is_certainly_damaged(record, ind) << " ---" << endl;
		return !is_certainly_damaged(record, ind);
	}
	// End of record
	if (ind == len(record)) {
		if (DEBUG) cout << "--- return: end of record ---" << endl;
		return 0;
	}

	// Recursive cases
	switch (record[ind]) {
	case '.':
		if (cont == 0) {
			cache[key] = count(record, ind+1, chunks, chunk_ind, 0);
		} else if (cont == chunks[chunk_ind]) {
			cache[key] = count(record, ind+1, chunks, chunk_ind + 1, 0);
		} else {
			if (DEBUG) cout << "------ too short ------" << endl;
			cache[key] = 0;
		}
		break;
	case '#':
		cache[key] = count(record, ind+1, chunks, chunk_ind, cont+1);
		break;
	case '?':
		if (REPLACE) record[ind] = '#';
		cache[key] = count(record, ind+1, chunks, chunk_ind, cont+1);

		if (REPLACE) record[ind] = '.';
		if (cont == 0) {
			cache[key] += count(record, ind+1, chunks, chunk_ind, 0);
		} else if (cont == chunks[chunk_ind]) {
			cache[key] += count(record, ind+1, chunks, chunk_ind + 1, 0);
		} else {
			if (DEBUG) cout << "------ too short ------" << endl;
			cache[key] += 0;
		}

		if (REPLACE) record[ind] = '?';
		break;
	default:
		throw "Invalid character in \"" + record + "\"";
		return -(1l << 60);
	}
	if (DEBUG) cout << "--- return: " << cache[key] << " ---" << endl;
	return cache[key];
}

void unfold() {
	FOR(i, records.size()) {
		string line = records[i];
		string new_line = line;
		FOR(j, 4) {
			new_line += '?' + line;
		}
		records[i] = new_line;
	}

	FOR(i, chunks_list.size()) {
		vec<int> new_check;
		// multiply by 5
		FOR(k, 5) {
			FOR(j, chunks_list[i].size()) {
				new_check.push_back(chunks_list[i][j]);
			}
		}
		chunks_list[i] = new_check;
	}
}

void compress() {
	// replace any contiguous blocks of '.' in rec[i] with single '.'
	FOR(i, records.size()) {
		string line = records[i];
		string new_line = "";
		FOR(j, len(line)) {
			if (line[j] == '.') {
				if (j == 0 || line[j - 1] != '.') {
					new_line += '.';
				}
			} else {
				new_line += line[j];
			}
		}
		records[i] = new_line;
	}

	// Remove start and end '.'
	FOR(i, records.size()) {
		string line = records[i];
		string new_line = "";
		FOR(j, len(line)) {
			if (line[j] == '.') {
				if (j == 0 || j == len(line) - 1) {
					continue;
				}
			}
			new_line += line[j];
		}
		records[i] = new_line;
	}
}

int main() {
	cout << left;
	string line;
	while (getline(cin, line)) {
		stringstream ss(line);
		string record;
		ss >> record;
		records.push_back(record);
		chunks_list.push_back(vec<int>());
		int n;
		char c;
		do {
			ss >> n;
			chunks_list.back().push_back(n);
		} while (ss >> c);
	}

	// compress();
	unfold();

	if (DEBUG) {
		FOR(i, DEBUG-1) {
			records.erase(records.begin());
			chunks_list.erase(chunks_list.begin());
		}
		for (int i = len(chunks_list); i > DEBUG; i--) {
			records.pop_back();
			chunks_list.pop_back();
		}
	}

	long sum = 0;
	FOR(i, len(records)) {
		long part = 0;
		if (DEBUG) cout << "=== record: " << records[i] << " ===" << endl;
		long n = count(records[i], 0, chunks_list[i], 0, 0);
		part += n;
		sum += part;
	}

	cout << sum << endl;

}
