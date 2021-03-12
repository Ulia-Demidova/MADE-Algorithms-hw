#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
using std::vector;

struct cell {
  int x;
  int y;
  cell() : x(0), y(0) {}
  cell(int x, int y) : x(x), y(y) {}
};

void bfs(size_t n, cell &&start, cell &&end) {
  vector<vector<bool>> used(n, vector<bool>(n, false));
  vector<vector<size_t>> distance(n, vector<size_t>(n));
  vector<vector<cell>> prev(n, vector<cell>(n));
  queue<cell> q;
  distance[start.x][start.y] = 0;
  used[start.x][start.y] = true;
  prev[start.x][start.y] = start;
  q.push(start);
  vector<cell> steps({
      {1, -2},
      {1, 2},
      {-1, -2},
      {-1, 2},
      {2, -1},
      {2, 1},
      {-2, -1},
      {-2, 1},
  });

  while (!q.empty()) {
    cell cur = q.front();
    q.pop();

    for (auto &step : steps) {
      if (cur.x + step.x >= 0 && cur.x + step.x < n && cur.y + step.y >= 0 &&
          cur.y + step.y < n && !used[cur.x + step.x][cur.y + step.y]) {
        cell next({cur.x + step.x, cur.y + step.y});
        used[next.x][next.y] = true;
        q.push(next);
        distance[next.x][next.y] = distance[cur.x][cur.y] + 1;
        prev[next.x][next.y] = cur;
      }
    }
  }

  cout << distance[end.x][end.y] + 1 << '\n';
  vector<cell> res({end});
  while (end.x != start.x || end.y != start.y) {
    res.push_back(prev[end.x][end.y]);
    end = prev[end.x][end.y];
  }
  for (auto it = res.rbegin(); it != res.rend(); ++it) {
    cout << it->x + 1 << ' ' << it->y + 1 << '\n';
  }
}

int main() {
  size_t n;
  cin >> n;
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  --x1;
  --x2;
  --y1;
  --y2;
  bfs(n, cell(x1, y1), cell(x2, y2));
  return 0;
}
