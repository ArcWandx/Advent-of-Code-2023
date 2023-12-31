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

void print_modules() {
	for (auto m : modules) {
		Module* module = m.second;
		cout << module->name << " -> " << typeid(*module).name() << endl;
		cout << "destinations: ";
		for (auto dest : module->destinations) {
			cout << dest << " ";
		}
		cout << endl;
		cout << "inputs: ";
		for (auto input : module->inputs) {
			cout << input << " ";
		}
		cout << endl;
		cout << endl;
	}
}

umap<string, vec<bool>> initialize_states() {
	umap<string, vec<bool>> states;
	for (auto m : modules) {
		if (m.second->name == "rx") { continue; }
		states[m.first] = {false};
	}
	return states;
}

void record_states(umap<string, vec<bool>>& states) {
	for (auto m : modules) {
		Module* module = m.second;
		if (modules.find(module->name) == modules.end()) { continue; }
		states[module->name].push_back(module->check());
	}
}

umap<string, vec<long>> consolidate_states(umap<string, vec<bool>>& states) {
	umap<string, vec<long>> consolidated;
	for (auto s : states) {
		vec<long> consolidated_states;
		bool last_state = s.second[0];
		long count = 1;
		FORR(i, 1, len(s.second)) {
			if (s.second[i] == last_state) {
				count++;
			} else {
				consolidated_states.push_back(count);
				count = 1;
				last_state = s.second[i];
			}
		}
		consolidated_states.push_back(count);
		consolidated[s.first] = consolidated_states;
	}
	return consolidated;
}

void print_states(umap<string, vec<bool>>& states, umap<string, vec<long>>& consolidated, umap<string, long>& cycles) {
	map<long, map<int, string>> sort_by_cycle;
	for (auto c : cycles) {
		sort_by_cycle[c.second][consolidated[c.first][0]] = c.first;
	}

	for (pair p : sort_by_cycle) {
		int cycle = p.first;
		for (pair p2 : p.second) {
			string str = p2.second;
			cout << modules[str]->type << str << ": " << cycle << " [";
			for (auto state : states[str]) {
				cout << ((state) ? 'X' : '.');
			}
			cout << "]" << endl;
		}
	}
}

void print_consolidated_states(umap<string, vec<long>>& consolidated, umap<string, long>& cycles) {
	map<long, map<int, string>> sort_by_cycle;
	for (auto c : cycles) {
		sort_by_cycle[c.second][consolidated[c.first][0]] = c.first;
	}

	for (pair s : sort_by_cycle) {
		for (pair p : s.second) {
			string str = p.second;
			cout << modules[str]->type << str << ": " << s.first << " [";
			for (auto state : consolidated[str]) {
				cout << state << ", ";
			}
			cout << "]" << endl;
		}
	}
}

umap<string, long> find_cycles(umap<string, vec<long>> consolidated) {
	umap<string, long> cycles;
	for (auto s : consolidated) {
		string m = s.first;
		if (modules[m]->type != '%') { continue; }
		vec<long> states = s.second;

		long cycle = 0;
		for (long i = 0; i < len(states); i++) {
			cycle += states[i];
			if (states[i] > states[0]) { cycle -= states[0]; }
			if (states[i] != states[0]) { break; }
		}
		cycles[m] = cycle;
	}
	return cycles;
}

void print_parsed(umap<string, vec<long>>& consolidated, umap<string, long>& cycles) {
	string last;
	// linear search for a module that has destination "rx"
	for (pair p : modules) {
		Module* m = p.second;
		if (m->destinations[0] == "rx") {
			last = m->name;
			break;
		}
	}

	map<long, map<int, string>> sort_by_cycle;
	for (auto c : cycles) {
		sort_by_cycle[c.second][consolidated[c.first][0]] = c.first;
	}

	map<int, string> controllers;
	for (string s : modules[last]->inputs) {
		s = *(modules[s]->inputs.begin());
		int cycle = cycles[*(modules[s]->inputs.begin())];
		controllers[cycle] = s;
	}

	cout << *modules["broadcaster"] << endl;
	cout << *modules[last] << endl;
	for (pair p : controllers) {
		cout << "==============================" << endl;

		string s = p.second;
		// find module that is destination of s, and input of last
		string inv;
		set<string> dests(modules[s]->destinations.begin(), modules[s]->destinations.end());
		set<string> inputs(modules[last]->inputs.begin(), modules[last]->inputs.end());
		for (string dest : dests) {
			if (inputs.find(dest) != inputs.end()) {
				inv = dest;
				break;
			}
		}
		cout << *modules[inv] << endl;
		cout << *modules[s] << endl;

		int cycle = p.first;
		for (pair p2 : sort_by_cycle[cycle]) {
			cout << *modules[p2.second] << endl;
		}
	}
	cout << "==============================" << endl;
	return;

}

int main() {
	string line;
	while (getline(cin, line)) {
		parse_modules(line);
	}
	link_inputs();

	umap<string, vec<bool>> states = initialize_states();

	while (button_count < 10000) {
		button_count++;
		send_pulse(false, "button", "broadcaster");
		while (!pulses.empty()) {
			Pulse pulse = pulses.front();
			pulses.pop_front();
			modules[pulse.to]->pulse(pulse.from, pulse.signal);
		}

		record_states(states);
	}

	umap<string, vec<long>> consolidated = consolidate_states(states);
	umap<string, long> cycles = find_cycles(consolidated);
	print_states(states, consolidated, cycles);
	// print_consolidated_states(consolidated, cycles);
	// print_parsed(consolidated, cycles);

	uset<long> cycle_set;
	for (auto c : cycles) {
		cycle_set.insert(c.second);
	}

	// subtract 1 from each, and lcm
	long out = 1;
	for (long c : cycle_set) {
		cout << c << endl;
		out = lcm(out, c);
	}

	cout << out << endl;

}
