#include <bits/stdc++.h>

#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define ALL(x) (x).begin(),(x).end()

using namespace std;

const vector<int> const_num = {5, 3, 2, 1};

int N;
vector<int> v;
string res;

vector<int> memo;
vector<string> memor;
set<pair<int,vector<int>>> se;

void dfs(int s, int c) {
  if (c + 1 < (int)v.size()) return;
  auto p = make_pair(c, v);
  if (se.find(p) != se.end()) return;
  se.insert(p);
  if (c < 0) return;
  if (c == 0 && (int)v.size() == 1) {
    int num = v[0];
    if (0 <= num && num <= N && memo[num] == -1) {
      memo[num] = s;
      memor[num] = res;
    }
    return;
  }
  auto const_process = [](int s, int c, char n, string& res, vector<int>& v){
    res.push_back(n);
    dfs(s, c);
    v.pop_back();
    res.pop_back();
  };
  for (int i : const_num) {
    v.push_back(i);
    const_process(s, c - i, '0' + i, res, v);
  }
  if (1 <= (int)v.size()) {
    int num = v.back();
    v.push_back(num);
    const_process(s, c - 1, 'd', res, v);
  }
  auto binary_pop = [](vector<int>& v) -> tuple<int, int> {
    int lhs = v[v.size() - 2];
    int rhs = v[v.size() - 1];
    v.pop_back();
    v.pop_back();
    return make_tuple(lhs, rhs);
  };
  auto binary_process = [](int s, int c, int n, char op, string& res, vector<int>& v){
    v.push_back(n);
    res.push_back(op);
    dfs(s, c);
  };
  auto binary_push = [](int lhs, int rhs, string& res, vector<int>& v){
    v.pop_back();
    v.push_back(lhs);
    v.push_back(rhs);
    res.pop_back();
  };
  if (2 <= (int)v.size()) {
    int lhs = 0, rhs = 0;
    tie(lhs, rhs) = binary_pop(v);
    binary_process(s, c - 1, lhs + rhs, '+', res, v);
    binary_push(lhs, rhs, res, v);

    tie(lhs, rhs) = binary_pop(v);
    binary_process(s, c - 1, lhs * rhs, '*', res, v);
    binary_push(lhs, rhs, res, v);

    tie(lhs, rhs) = binary_pop(v);
    binary_process(s, c - 1, lhs - rhs, '-', res, v);
    binary_push(lhs, rhs, res, v);

    tie(lhs, rhs) = binary_pop(v);
    binary_process(s, c - 1, rhs == 0 ? 0 : lhs / rhs, '/', res, v);
    binary_push(lhs, rhs, res, v);

    tie(lhs, rhs) = binary_pop(v);
    binary_process(s, c - 1, rhs == 0 ? 0 : lhs % rhs, '%', res, v);
    binary_push(lhs, rhs, res, v);
  }
}

int main() {
  N = 100000;
  memo.assign(N+1, -1);
  memor.resize(N+1);
  int depth = 0;
  for (int n = 1; n <= N; ++n) {
    while (memo[n] == -1) {
      cerr << "DEPTH : " << depth << endl;
      v.clear();
      res.clear();
      se.clear();
      dfs(depth, depth);
      ++depth;
    }
    cout << n << "\t";
    cout << "cost : " << memo[n] << "\t";
    cout << memor[n] << endl;
  }
  return 0;
}
