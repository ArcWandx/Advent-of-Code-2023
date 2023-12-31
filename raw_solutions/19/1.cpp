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
#define vec vector
#define umap unordered_map
#define uset unordered_set
int DEBUG_COUNT = 0;
void debug(string s = "") { cerr << "DEBUG " << DEBUG_COUNT++ << ": " << s << endl; }

struct Part {
	umap<char, int> field;
	bool accepted;

	Part(int x, int m, int a, int s): accepted(false) {
		field['x'] = x;
		field['m'] = m;
		field['a'] = a;
		field['s'] = s;
	}
	Part() { Part(0, 0, 0, 0); }

	friend ostream& operator<<(ostream& os, const Part& p) {
		os << "{x: " << p.field.at('x')
			<< ", m: " << p.field.at('m')
			<< ", a: " << p.field.at('a')
			<< ", s: " << p.field.at('s')
			<< "}";
		return os;
	}
};

bool is_last_rule(string rule) {
	return rule.back() == '}';
}

function<string(Part&)> parse_rule(string rule) {
	stringstream ss(rule);
	char attrib, type;
	int num;
	char colon;
	string redirect;
	if (is_last_rule(rule)) {
		redirect = rule.substr(0, rule.size() - 1);
		return [redirect](Part&) {
			return redirect;
		};
	}

	ss >> attrib >> type >> num >> colon >> redirect;

	bool (*compare)(int, int);
	if (type == '>') {
		compare = [](int a, int b) { return a > b; };
	} else if (type == '<') {
		compare = [](int a, int b) { return a < b; };
	} else {
		cout << "Something has gone wrong" << endl;
		exit(1);
	}

	return [attrib, redirect, num, compare](Part& p) {
		if (attrib == 'A' || attrib == 'R') {
			return string(1, attrib);
		}
		if (compare(p.field.at(attrib), num)) return redirect;
		return string("pass");
	};
}

vec<function<string(Part&)>> parse_workflow(string line) {
	stringstream ss(line);
	string name;
	getline(ss, name, '{');

	vec<function<string(Part&)>> workflow;
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
	umap<string, vec<function<string(Part&)>>> workflows;
	vec<Part> parts;

	string line;
	// Fill workflows
	while (getline(cin, line)) {
		if (line.empty()) break;

		stringstream ss(line);
		string name;
		getline(ss, name, '{');

		workflows[name] = parse_workflow(line);
	}

	// Fill parts
	while (getline(cin, line)) {
		stringstream ss(line.substr(1, line.size() - 1));
		int x, m, a, s;
		char buf;
		ss >> buf >> buf >> x >> buf;
		ss >> buf >> buf >> m >> buf;
		ss >> buf >> buf >> a >> buf;
		ss >> buf >> buf >> s >> buf;
		parts.push_back(Part(x, m, a, s));
	}

	for (Part& p : parts) {
		string workflow = "in";
		string current = workflow;
		while (workflow != "A" && workflow != "R") {
			for (function<string(Part&)> f : workflows[workflow]) {
				workflow = f(p);
				if (workflow == "pass") continue;
				current = workflow;
				break;
			}
		}
		p.accepted = (workflow == "A");
	}

	int sum = 0;
	for (Part& p : parts) {
		if (p.accepted) {
			for (auto& [k, v] : p.field) {
				sum += v;
			}
		}
	}

	cout << sum << endl;
}
