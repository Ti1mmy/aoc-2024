#include <bits/stdc++.h>

using namespace std;

class pos {
    public:
    int posX;
    int posY;

    pos(): posX{-1}, posY{-1} {}
    pos(int x, int y): posX{x}, posY{y} {}

    pos move(const vector<int>& direction) {
        return pos(this->posX + direction[0], this->posY + direction[1]);
    }

    // pos(): posX(-1), posY(-1) {}
    bool operator==(const pos &other) const {
        return (this->posX == other.posX) && (this->posY == other.posY);
    }

    struct HashFunction {
        size_t operator()(const pos& point) const {
      size_t xHash = std::hash<int>()(point.posX);
      size_t yHash = std::hash<int>()(point.posY) << 1;
      return xHash ^ yHash;
    }
  };
};

int main() {
    string s;
    vector<vector<char>> map;
    unordered_set<pos, pos::HashFunction> visited;
    while (cin >> s) {
        vector<char> line;
        for (char x: s) {
            line.emplace_back(x);
        }
        map.emplace_back(line);
    }

    pos cur;
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == '^') {
                cur = pos(x, y);
            }
        }
    }
    

    vector<vector<int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    vector<string> dir_names = {"NORTH", "EAST", "SOUTH", "WEST"};
    int turns = 0;

    while(true) {
        // cout << cur.posX << ", " << cur.posY << endl;
        bool out_of_bounds = (cur.posX >= map[0].size()) || (cur.posY >= map.size()) || (cur.posX == -1) || (cur.posY == -1);
        if (out_of_bounds) {
            break;
        }

        bool obstacle = map[cur.posY][cur.posX] == '#';
        if (obstacle) {
            cur = cur.move(directions[(turns + 2) % 4]); // move back
            turns++;
        } else {
            visited.emplace(cur);
        }
        cur = cur.move(directions[turns % 4]);
        // cout << "moving: " << dir_names[turns % 4] << endl;
    }

    cout << "visited: " << visited.size() << endl;
    return 0;
}
