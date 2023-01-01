#include <bits/stdc++.h>
using namespace std;

struct Cube {
    /**
     * This is the face order
     * 0
     * 1 2 3 4
     * 5
     *
     * This is the pos order
     * 0 1 2
     * 3 4 5
     * 6 7 8
     */

    struct CubeInd {
        int face, pos;
    };

    std::string colors;
    Cube() {
        colors = string(9, 'Y') + string(9, 'R') + string(9, 'G') + string(9, 'O') +
                 string(9, 'B') + string(9, 'W');
    }
    Cube(const std::string& colors) : colors(colors) {}

    char& get(const CubeInd& cubeInd) {
        assert(0 <= cubeInd.face && cubeInd.face < 6);
        assert(0 <= cubeInd.pos && cubeInd.pos < 9);
        return colors[cubeInd.face * 9 + cubeInd.pos];
    }

    void rotate(const vector<CubeInd>& A, int k) {
        // This function mutates the cube and rotates the given faces by k inds
        auto B = A;  // make a copy
        std::rotate(B.begin(), B.begin() + k, B.end());

        // update the cube for each pos
        const int n = A.size();
        vector<char> old(n);
        for (int i = 0; i < n; i++) {
            old[i] = get(A[i]);
        }
        for (int i = 0; i < n; i++) {
            get(B[i]) = old[i];
        }
    }

    void print() {
        cout << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << get({0, i * 3 + j});
            }
            cout << endl;
        }

        for (int i = 0; i < 3; i++) {
            for (int face = 1; face <= 4; face++) {
                for (int j = 0; j < 3; j++) {
                    cout << get({face, i * 3 + j});
                }
                cout << ' ';
            }
            cout << endl;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << get({5, i * 3 + j});
            }
            cout << endl;
        }
    }

    void rotateFace(int face) {
        rotate({{face, 0},
                {face, 1},
                {face, 2},
                {face, 5},
                {face, 8},
                {face, 7},
                {face, 6},
                {face, 3}},
               2);
    }

    void F() {
        rotateFace(1);
        rotate({{0, 6},
                {0, 7},
                {0, 8},

                {2, 0},
                {2, 3},
                {2, 6},

                {5, 2},
                {5, 1},
                {5, 0},

                {4, 8},
                {4, 5},
                {4, 2}},
               3);
    }

    void R() {
        rotateFace(2);
        rotate({{0, 8},
                {0, 5},
                {0, 2},

                {3, 0},
                {3, 3},
                {3, 6},

                {5, 8},
                {5, 5},
                {5, 2},

                {1, 8},
                {1, 5},
                {1, 2}},
               3);
    }

    void U() {
        rotateFace(0);
        rotate({{3, 2},
                {3, 1},
                {3, 0},

                {2, 2},
                {2, 1},
                {2, 0},

                {1, 2},
                {1, 1},
                {1, 0},

                {4, 2},
                {4, 1},
                {4, 0}},
               3);
    }

    void B() {
        rotateFace(3);
        rotate({{0, 2},
                {0, 1},
                {0, 0},

                {4, 0},
                {4, 3},
                {4, 6},

                {5, 6},
                {5, 7},
                {5, 8},

                {2, 8},
                {2, 5},
                {2, 2}},
               3);
    }

    void L() {
        rotateFace(4);
        rotate({{0, 0},
                {0, 3},
                {0, 6},

                {1, 0},
                {1, 3},
                {1, 6},

                {5, 0},
                {5, 3},
                {5, 6},

                {3, 8},
                {3, 5},
                {3, 2}},
               3);
    }

    void D() {
        rotateFace(5);
        rotate({{1, 6},
                {1, 7},
                {1, 8},

                {2, 6},
                {2, 7},
                {2, 8},

                {3, 6},
                {3, 7},
                {3, 8},

                {4, 6},
                {4, 7},
                {4, 8}},
               3);
    }

    void M() {
        rotate({{0, 1},
                {0, 4},
                {0, 7},

                {1, 1},
                {1, 4},
                {1, 7},

                {5, 1},
                {5, 4},
                {5, 7},

                {3, 7},
                {3, 4},
                {3, 1}},
               3);
    }

    void E() {
        rotate({{1, 3},
                {1, 4},
                {1, 5},

                {2, 3},
                {2, 4},
                {2, 5},

                {3, 3},
                {3, 4},
                {3, 5},

                {4, 3},
                {4, 4},
                {4, 5}},
               3);
    }

    void S() {
        rotate({{0, 3},
                {0, 4},
                {0, 5},

                {2, 1},
                {2, 4},
                {2, 7},

                {5, 5},
                {5, 4},
                {5, 3},

                {4, 7},
                {4, 4},
                {4, 1}},
               3);
    }
};

int main() {
    printf("Hello World\n");

    Cube cube;
    cube.print();

    // cube.F();
    cube.M();
    cube.M();
    cube.S();
    cube.S();
    cube.E();
    cube.E();
    cube.print();
}
