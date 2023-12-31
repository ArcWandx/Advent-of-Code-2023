#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <iomanip>
#include <map>
#include <numeric>
#include <set>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <string>
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

vec<string> grid;
struct Node {
	map<Node*, int> adj;
	int r, c;
	Node(int r, int c): r(r), c(c) {}

	void add(Node* node, int dist) {
		node->adj[this] = dist;
	}

	friend ostream& operator<<(ostream& os, const Node& node) {
		os << "Node((" << node.r << ", " << node.c << "), {";
		for (auto [n, d] : node.adj) {
			os << "(" << n->r << ", " << n->c << "): " << d << ", ";
		}
		os << "})";
		return os;
	}

	friend bool operator==(const Node& a, const Node& b) {
		return a.r == b.r && a.c == b.c;
	}
};

bool in_bounds(int i, int j) {
	return i >= 0 && i < len(grid) && j >= 0 && j < len(grid[i]);
}

bool is_path(int i, int j) {
	return in_bounds(i, j) && grid[i][j] != '#';
}

bool is_intersection(int i, int j) {
	if (i == 0 && j == 1) return true;
	if (i == len(grid)-1 && j == len(grid[0])-2) return true;
	if (!is_path(i, j)) return false;

	int count = 0;
	if (is_path(i - 1, j)) count++;
	if (is_path(i + 1, j)) count++;
	if (is_path(i, j - 1)) count++;
	if (is_path(i, j + 1)) count++;

	return count >= 3;
}

// bool visited[23][23];
// void print_grid(int, int);
umap<Node*, bool> nodes;
void find_intersections(Node* root, Node* end) {
	map<pair<int, int>, Node*> intersections;
	intersections.emplace(make_pair(0, 1), root);
	FORR(i, 1, len(grid)) {
		FORR(j, 1, len(grid[i])) {
			if (is_intersection(i, j)) {
				intersections.emplace(make_pair(i, j), new Node(i, j));
				nodes[intersections.at(make_pair(i, j))] = false;
			}
		}
	}
	intersections.emplace(make_pair(end->r, end->c), end);

	// loop over all intersections
	bool visited[len(grid)][len(grid[0])];
	for (auto [_, node] : intersections) {
		// cout << "=============================================" << endl;
		// cout << "(" << node->r << ", " << node->c << ")" << endl;
		// cout << "=============================================" << endl;

		// find adjacent intersections
		memset(visited, 0, sizeof(visited));
		deque<pair<int, int>> q;
		deque<pair<int, int>> next;
		q.emplace_back(node->r, node->c);

		for (int dist = 0; !q.empty(); dist++) {
			// if (dist % 5 == 0) { print_grid(node->r, node->c); }

			while (!q.empty()) {
				auto [i, j] = q.front();
				q.pop_front();

				if (!is_path(i, j)) continue;
				if (visited[i][j]) continue;
				visited[i][j] = true;

				if (is_intersection(i, j) &&
						make_pair(i, j) != make_pair(node->r, node->c)) {
					node->add(intersections.at(make_pair(i, j)), dist);
					continue;
				}

				next.emplace_back(i - 1, j);
				next.emplace_back(i, j + 1);
				next.emplace_back(i + 1, j);
				next.emplace_back(i, j - 1);
			}
			swap(q, next);
		}
	}
}

void print_grid(int r, int c) {
	FOR(i, len(grid)) {
		FOR(j, len(grid[i])) {
			if (i == r && j == c) {
				cout << 'X';
			} else if (is_intersection(i, j)) {
				cout << 'x';
			// } else if (visited[i][j]) {
				// cout << '-';
			} else if (grid[i][j] == '#') {
				cout << ' ';
			} else {
				cout << '.';
			}
		}
		cout << endl;
	}
	cout << endl;
}

void print_nodes(Node* root) {
	deque<Node*> level;
	set<Node*> seen;
	level.push_back(root);
	int count = 0;
	while (!level.empty()) {
		Node* node = level.front();
		level.pop_front();

		if (seen.count(node)) continue;
		seen.insert(node);

		cout << *node << endl;
		count++;
		for (auto [n, d] : node->adj) {
			level.push_back(n);
		}
	}

	cout << count << endl;
}

int path_length(vec<Node*> path) {
	int dist = 0;
	FORR(i, 1, len(path)) {
		dist += path[i]->adj.at(path[i-1]);
	}
	return dist;
}

bool vec_contains(vec<Node*> path, Node* node) {
	for (Node* n : path) {
		if (n == node) return true;
	}
	return false;
}

// try every path from start to end recursively. return the longest
int dfs(Node* start, Node* end, int dist) {
	if (*start == *end) {
		return dist;
	}
	if (nodes[start]) { return -1; }

	int out = 0;
	for (auto [n, d] : start->adj) {
		// cout << "(" << start->r << ", " << start->c << ") -> (" << n->r << ", " << n->c << ")" << endl;
		nodes[start] = true;
		out = max(out, dfs(n, end, dist + d));
		nodes[start] = false;
	}

	return out;

}

void print_path(vec<Node*> path) {
	FOR(i, len(path)-1) {
		cout << "(" << path[i]->r << ", " << path[i]->c << ") + ";
		cout << path[i+1]->adj.at(path[i]) << endl;
	}
	cout << "(" << path[len(path)-1]->r << ", " << path[len(path)-1]->c << ")" << endl;
}

int main() {
	string line;
	while (getline(cin, line)) {
		grid.push_back(line);
	}

	Node* root = new Node(0, 1);
	Node* end = new Node(len(grid)-1, len(grid[0])-2);
	find_intersections(root, end);

	// print best path and best path length
	// print_grid(-1, -1);
	cout << dfs(root, end, 0) << endl;

}
