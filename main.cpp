#include <bits/stdc++.h>

#include "cube.h"

bool partialMatch(const string& s, const string& t) {
    int n = s.size();
    if (n != t.size()) return false;

    for (int i = 0; i < n; i++) {
        if (s[i] == '?' || t[i] == '?') continue;
        if (s[i] != t[i]) return false;
    }
    return true;
}

const vector<string> moves = {"U", "R", "L", "D", "B", "F", "U'", "R'", "L'", "D'", "B'", "F'"};

// i need a new data structure
struct StringMatcher {
    struct Node {
        unordered_map<char, unique_ptr<Node>> children;
    };

    unique_ptr<Node> root;

    StringMatcher() : root(make_unique<Node>()) {}

    // data structure will be able to check whether some normal string
    void insert(const std::string& s) {
        // you can insert normal chars and ?
        Node* cur = root.get();
        for (char c : s) {
            if (!cur->children.count(c)) {
                cur->children[c] = make_unique<Node>();
            }
            cur = cur->children[c].get();
        }
    }

    optional<string> lookup(const string& s) {
        // currently only look up non-? chars
        string path;
        auto res = lookup(s, 0, root.get(), path);
        return res;
    }

    optional<string> lookup(const string& s, int ind, Node* cur, string& path) {
        if (ind == s.size()) return path;

        if (cur->children.count(s[ind])) {
            path.push_back(s[ind]);

            auto res = lookup(s, ind + 1, cur->children[s[ind]].get(), path);
            if (res) return res;
            path.pop_back();
        }
        if (cur->children.count('?')) {
            path.push_back('?');
            auto res = lookup(s, ind + 1, cur->children['?'].get(), path);
            if (res) return res;
            path.pop_back();
        }
        return nullopt;
    }
};

void middle() {
    // meet in the middle strategy
    // do bfs from both ways

    const Cube source(
        "YYYYYYYYY"
        "RRRRRRRRR"
        "GGGGGGGGG"
        "OOOOOOOOO"
        "BBBBBBBBB"
        "WWWWWWWWW");
    const Cube target(
        "YY?YY???Y"
        "YY?RRRRRR"
        "?YYGGGGGG"
        "???OOOOOO"
        "???BBBBBB"
        "WWWWWWWWW");

    StringMatcher matcher;

    // 1: wildcards to middle
    queue<Cube> Q1;
    unordered_map<string, int> dist1;
    unordered_map<string, vector<string>> pathToHere1;
    matcher.insert(target.colors);
    Q1.push(target);
    dist1[target.colors] = 0;
    pathToHere1[target.colors] = {};

    while (Q1.size()) {
        auto at = Q1.front();
        Q1.pop();

        const auto curDist = dist1[at.colors];
        const auto path = pathToHere1[at.colors];

        if (curDist >= 5) {
            continue;
        }

        for (const auto& move : moves) {
            auto next = at;
            next.parseOne(move);
            if (!dist1.count(next.colors)) {
                dist1[next.colors] = curDist + 1;

                Q1.push(next);
                matcher.insert(next.colors);

                auto nextPath = path;
                nextPath.push_back(move);
                pathToHere1[next.colors] = nextPath;
            }
        }
    }

    // 2: source to middle
    queue<Cube> Q2;
    unordered_map<string, int> dist2;
    unordered_map<string, vector<string>> pathToHere2;
    Q2.push(source);
    dist2[source.colors] = 0;
    pathToHere1[target.colors] = {};
    while (Q2.size()) {
        auto at = Q2.front();
        Q2.pop();

        const auto curDist = dist2[at.colors];
        const auto path = pathToHere2[at.colors];

        // check if matcher here
        optional<string> matchResult = matcher.lookup(at.colors);
        if (matchResult) {
            cout << *matchResult << endl;
            cout << "woo hoo" << endl;

            cout << "other side" << endl;
            for (auto s : pathToHere1[*matchResult]) {
                cout << s << ' ';
            }
            cout << endl;

            for (auto s : pathToHere2[at.colors]) {
                cout << s << ' ';
            }
            cout << endl;
            break;
        }

        if (curDist >= 5) {
            continue;
        }

        for (const auto& move : moves) {
            auto next = at;
            next.parseOne(move);
            if (!dist2.count(next.colors)) {
                dist2[next.colors] = curDist + 1;
                Q2.push(next);

                auto nextPath = path;
                nextPath.push_back(move);
                pathToHere2[next.colors] = nextPath;
            }
        }
    }
}

int main() {
    printf("Hello World\n");

    middle();
    return 0;
}
