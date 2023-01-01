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

void bfs() {
    // cube bfs
    // there is a start pos and a target
    // start pos is the starting cube
    // end pos is the shape (in any orientation)
    // max 9 moves to start
    // only allow the 6

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

    // const Cube target(
    //     "YY?YY?Y??"
    //     "?Y?RRRRRR"
    //     "YYYGGGGGG"
    //     "???OOOOOO"
    //     "???BBBBBB"
    //     "WWWWWWWWW");

    const vector<string> moves = {"U", "R", "L", "D", "B", "F", "U'", "R'", "L'", "D'", "B'", "F'"};
    const int maxNumMoves = 9;

    // find a way to go from source to target
    queue<Cube> Q;
    unordered_map<string, int> dist;
    Q.push(source);
    dist[source.colors] = 0;
    while (Q.size()) {
        auto at = Q.front();
        Q.pop();

        const auto curDist = dist[at.colors];

        if (partialMatch(at.colors, target.colors)) {
            cout << "woo! " << curDist << endl;
            break;
        }

        if (curDist >= maxNumMoves) {
            continue;
        }

        for (const auto& move : moves) {
            auto next = at;
            next.parseOne(move);
            if (!dist.count(next.colors)) {
                dist[next.colors] = curDist + 1;
                Q.push(next);
            }
        }
    }

    cout << " done?" << endl;

    // extra fun - question marks are wild
}

int main() {
    printf("Hello World\n");

    bfs();
}
