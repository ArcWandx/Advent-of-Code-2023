#include <deque>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)(a); i++)
#define FORR(i, a, b) for (int i = a; i < (int)(b); i++)
#define len(a) ((int)a.size())
#define long long long
#define umap unordered_map
#define uset unordered_set
#define vec vector
int DEBUG_COUNT = 0;
void debug(string s = "") { cerr << "DEBUG " << DEBUG_COUNT++ << ": " << s << endl; }

struct Range{
	string workflow;
	int pos;

	umap<char, int> min;
	umap<char, int> max;

	Range(string workflow, int pos,
			long xmin, long xmax,
			long mmin, long mmax,
			long amin, long amax,
			long smin, long smax): workflow(workflow), pos(pos) {
		min['x'] = xmin;
		min['m'] = mmin;
		min['a'] = amin;
		min['s'] = smin;

		max['x'] = xmax;
		max['m'] = mmax;
		max['a'] = amax;
		max['s'] = smax;
	}

	friend ostream& operator<<(ostream& os, const Range& r) {
		os << r.workflow << " " << r.pos << "\n"
			<< "x: " << setw(4) << r.min.at('x') << ".." << setw(4) << r.max.at('x') << "\n"
			<< "m: " << setw(4) << r.min.at('m') << ".." << setw(4) << r.max.at('m') << "\n"
			<< "a: " << setw(4) << r.min.at('a') << ".." << setw(4) << r.max.at('a') << "\n"
			<< "s: " << setw(4) << r.min.at('s') << ".." << setw(4) << r.max.at('s') << "\n";
		return os;
	}
};

bool is_last_rule(string rule) {
	return rule.back() == '}';
}

tuple<char, bool, int, string> parse_rule(string rule) {
	stringstream ss(rule);
	char attrib, type;
	int num;
	char colon;
	string redirect;
	if (is_last_rule(rule)) {
		return make_tuple('A', false, 0, rule.substr(0, rule.size() - 1));
	}

	ss >> attrib >> type >> num >> colon >> redirect;
	return make_tuple(attrib, type == '<', num, redirect);
}

vec<tuple<char, bool, int, string>> parse_workflow(string line) {
	stringstream ss(line);
	string name;
	getline(ss, name, '{');

	vec<tuple<char, bool, int, string>> workflow;
	string rule;
	while (1) {
		getline(ss, rule, ',');
		if (is_last_rule(rule)) {
			workflow.push_back(parse_rule(rule));
			return workflow;
		}

		workflow.push_back(parse_rule(rule));
	}
}

int main() {
	// functions return the name of another workflow, or 'A' or 'R'
	umap<string, vec<tuple<char, bool, int, string>>> workflows;

	string line;
	// Fill workflows
	while (getline(cin, line)) {
		if (line.empty()) break;

		stringstream ss(line);
		string name;
		getline(ss, name, '{');

		workflows[name] = parse_workflow(line);
	}

	deque<Range> ranges;
	deque<Range> accepted;
	ranges.push_back(Range("in", 0, 1, 4000, 1, 4000, 1, 4000, 1, 4000));
	while (!ranges.empty()) {
		Range r = ranges.front();
		ranges.pop_front();

		char attrib;
		bool less;
		int num;
		string redirect;
		tie(attrib, less, num, redirect) = workflows[r.workflow][r.pos];

		if (attrib == 'A') {
			r.workflow = redirect;
			r.pos = 0;
			if (r.workflow == "A") {
				accepted.push_back(r);
			} else if (r.workflow != "R") {
				ranges.push_front(r);
			}
			continue;
		}

		Range s = r;
		if (less) {
			s.max[attrib] = min(s.max[attrib], num - 1);
			r.min[attrib] = max(r.min[attrib], num);
		} else {
			s.min[attrib] = max(s.min[attrib], num + 1);
			r.max[attrib] = min(r.max[attrib], num);
		}
		s.workflow = redirect;
		s.pos = 0;
		r.pos++;

		if (s.workflow == "A") {
			accepted.push_back(s);
		} else if (s.workflow != "R") {
			ranges.push_front(s);
		}
		ranges.push_front(r);
	}
	
	// count elements in accepted
	long sum = 0;
	for (Range r : accepted) {
		long x = r.max['x'] - r.min['x'] + 1;
		long m = r.max['m'] - r.min['m'] + 1;
		long a = r.max['a'] - r.min['a'] + 1;
		long s = r.max['s'] - r.min['s'] + 1;
		sum += x * m * a * s;
	}
	cout << sum << endl;
}
