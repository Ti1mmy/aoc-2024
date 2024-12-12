#include <bits/stdc++.h>

using namespace std;

class pos {
    public:
    int posX;
    int posY;
    int dir;

    pos(): posX{-1}, posY{-1}, dir{-1} {}
    pos(int x, int y, int dir): posX{x}, posY{y}, dir{dir} {}

    pos move(const vector<int>& direction, int dir) {
        return pos(this->posX + direction[0], this->posY + direction[1], dir);
    }
};

int main() {
    string s;
    vector<vector<char>> map;
    int posx = 0; int posy = 0;
    pos start;
    while (cin >> s) {
        vector<char> line;
        posx = 0;
        for (char x: s) {
            if (x == '^') start = pos(posx, posy, 0);
            line.emplace_back(x);
            ++posx;
        }
        ++posy;
        map.emplace_back(line);
    }

    vector<vector<int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    vector<string> dir_names = {"NORTH", "EAST", "SOUTH", "WEST"};
    int turns = 0;
    int ans = 0;

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] != '.') continue;
            int visited = 1;
            
            turns = 0;
            pos cur = start;
            // do search
            while(true) {
                if (visited > 4 * map.size() * map[0].size()) { // in a loop
                    ++ans;
                    break;
                }

                // cout << cur.posX << ", " << cur.posY << endl;
                bool out_of_bounds = (cur.posX >= map[0].size()) || (cur.posY >= map.size()) || (cur.posX == -1) || (cur.posY == -1);
                if (out_of_bounds) {
                    break;
                }

                bool obstacle = (map[cur.posY][cur.posX] == '#') || ((cur.posX == x) && (cur.posY == y));
                if (obstacle) {
                    cur = cur.move(directions[(turns + 2) % 4], turns % 4); // move back
                    turns++;
                } else {
                    ++visited;
                }
                cur = cur.move(directions[turns % 4], turns % 4);
                // cout << "moving: " << dir_names[turns % 4] << endl;
            }
        }
    }

    cout << "ans: " << ans << endl;
    return 0;
}
