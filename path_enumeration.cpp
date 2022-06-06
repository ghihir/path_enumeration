#include<bits/stdc++.h>
using namespace std;

int main() {
  ifstream fin("input.txt");
  ofstream fout("output.txt");

  vector<vector<int>> connections;
  int s, e;
  int node_max = 0;
  while (fin >> s >> e) {
    if (s == e) continue;
    vector<int> tmp(2);
    tmp[0] = s, tmp[1] = e;
    connections.emplace_back(tmp);
    node_max = max({node_max, s, e});
  }

  fin.close();


  vector<vector<int>> adjacency_list(node_max + 1);
  for (int i = 0; i < connections.size(); i++) {
    adjacency_list[connections[i][0]].emplace_back(connections[i][1]);
  }

  for (int i = 0; i < adjacency_list.size(); i++) {
    sort(adjacency_list[i].begin(), adjacency_list[i].end());
    adjacency_list[i].erase(unique(adjacency_list[i].begin(), adjacency_list[i].end()), adjacency_list[i].end());
  }

  vector<vector<int>> path;
  int path_no = 0;
  while (adjacency_list[0].size() > 0) {
    path.emplace_back(vector<int>(1, 0));

    int current_vertex = 0;
    while (adjacency_list[current_vertex].size() > 0) {
      if (find(path[path_no].begin(), path[path_no].end(), adjacency_list[current_vertex][0]) == path[path_no].end()) {
        path[path_no].push_back(adjacency_list[current_vertex][0]);
        current_vertex = adjacency_list[current_vertex][0];
      } else {                                                  // ループする経路の場合は中断
        adjacency_list[current_vertex].erase(adjacency_list[current_vertex].begin());
        break;
      }
    }

    for (int i = path[path_no].size() - 1; i >= 1; i--) {     // 行き止まりまで行ったら、端へ続く辺は消去
      if (adjacency_list[path[path_no][i]].size() == 0) {
        adjacency_list[path[path_no][i - 1]].erase(adjacency_list[path[path_no][i - 1]].begin());
      }
    }

    path_no++;
  }

  for (int i = 0; i < path.size(); i++) {
    for (int j = 0; j < path[i].size(); j++) {
      if (j != path[i].size() - 1) {
        fout << path[i][j] << " -> ";
      } else {
        fout << path[i][j] << endl;
      }
    }
  }

  fout.close();
}