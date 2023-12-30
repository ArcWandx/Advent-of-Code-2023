#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
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

class Module {
public:
	char type;
	string name;
	uset<string> inputs;
	vec<string> destinations;
	Module(char type): type(type) {}
	virtual void pulse(string, bool) = 0;
	virtual bool check() = 0;

	friend ostream& operator<<(ostream& os, const Module& m) {
		if (m.type != 'b') {
			os << m.type;
		}
		os << m.name << " -> ";
		if (m.type == 'b') {
			os << "BroadCaster";
		} else if (m.type == '&') {
			os << "Conjunction";
		} else if (m.type == '%') {
			os << "FlipFlop";
		} else {
			os << "N/A";
		}
		os << endl;
		os << "destinations: ";
		for (auto dest : m.destinations) {
			os << " " << dest;
		}
		os << endl;
		os << "inputs: ";
		for (auto input : m.inputs) {
			os << " " << input;
		}
		os << endl;
		return os;
	}
};

struct Pulse {
	bool signal;
	string from;
	string to;
};

umap<string, Module*> modules;
deque<Pulse> pulses;
long button_count = 0;
long low_count = 0;
long high_count = 0;

void send_pulse(bool signal, string from, string to) {
	if (signal) { high_count++; }
	else { low_count++; }

	if (modules.find(to) == modules.end()) { return; }
	pulses.push_back({signal, from, to});
}

class BroadCaster : public Module {
public:
	BroadCaster(): Module('b') {}

	void pulse(string, bool signal) {
		if (signal) return;
		for (string dest : destinations) {
			send_pulse(false, name, dest);
		}
	}

	bool check() { return false; }
};

class FlipFlop : public Module {
public:
	FlipFlop(): Module('%') {}

	bool state = false;

	void pulse(string, bool signal) {
		if (signal) return;

		state = !state;
		for (string dest : destinations) {
			send_pulse(state, name, dest);
		}
	}

	bool check() { return state; }
};

class Conjunction : public Module {
public:
	Conjunction(): Module('&') {}

	umap<string, bool> states;

	void pulse(string caller, bool signal) {
		states[caller] = signal;

		bool all_high = true;
		for (auto input : inputs) {
			if (!states[input]) {
				all_high = false;
				break;
			}
		}

		for (string dest : destinations) {
			send_pulse(!all_high, name, dest);
		}
	}

	bool check() {
		for (auto input : inputs) {
			if (!states[input]) { return false; }
		}
		return true;
	}
};

void parse_modules(string line) {
	stringstream ss(line);
	char type;
	string module;
	ss >> type >> module;
	if (type == 'b') {
		module = "broadcaster";
	}

	vec<string> destinations;
	string dest;
	ss >> dest;
	while (ss >> dest) {
		if (dest.back() == ',') {
			dest = dest.substr(0, dest.length() - 1);
		}
		destinations.push_back(dest);
	}

	Module* m = nullptr;
	if (type == 'b') {
		m = new BroadCaster();
	} else if (type == '%') {
		m = new FlipFlop();
	} else if (type == '&') {
		m = new Conjunction();
	}
	m->name = module;
	m->destinations = destinations;
	modules[module] = m;
}

void link_inputs() {
	for (auto m : modules) {
		for (auto dest : m.second->destinations) {
			if (modules.find(dest) == modules.end()) { continue; }
			modules[dest]->inputs.insert(m.first);
		}
	}
}

int main() {
	string line;
	while (getline(cin, line)) {
		parse_modules(line);
	}
	link_inputs();

	while (button_count < 1000) {
		button_count++;
		send_pulse(false, "button", "broadcaster");
		while (!pulses.empty()) {
			Pulse pulse = pulses.front();
			pulses.pop_front();
			modules[pulse.to]->pulse(pulse.from, pulse.signal);
		}
	}

	cout << "low:  " << low_count << endl;
	cout << "high: " << high_count << endl;
	cout << low_count * high_count << endl;

}
