#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=double;
#define FOR(i,a,b) for(ll i=a;i<(ll)b;++i)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define aa first
#define bb second
#define PB push_back
#define EQ(a,b) (fabs(a-b)<=(fabs(a+b)*EPS))
#define MOD ((ll)(1e9+7))

#define FILE "demo.in"
//#define FILE "input.in"

void part_1(const string & file);
void part_2(const string & file);
vector<ll> explode(string const & s, char delim);

struct step {
  ll step;
  ll x;
  ll y;
};

bool moveable(char s, const vector<string> & m, ll x, ll y) {
  if (x < 0 || y < 0) return false;
  if (x >= m.size() || y >= m[0].size()) return false;
  if (m[x][y] == 'S') return false;
  if (m[x][y] == 'E' && s == 'z') return true;
  if (s == 'S' && m[x][y] == 'a') return true;
  return m[x][y] <= s + 1;
}


void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<string> m;
  ll i=0,j=0;

  queue<step> q;
  set<pair<ll,ll>> visited;

  while(getline(in, str)) {
    m.emplace_back(str);
    size_t idx = str.find_first_of('S');
    if (idx != string::npos) {
      q.push({0, i, j});
      visited.insert({i, j});
    }
    ++i;
  }

  ll result = 0;

  while(!q.empty()) {
    step s = q.front(); q.pop();
    if (m[s.x][s.y] == 'E') { result = s.step; break; }
    if (moveable(m[s.x][s.y], m, s.x-1, s.y) && !visited.contains({s.x-1, s.y})) { 
      q.push({s.step+1, s.x-1, s.y}); 
      visited.insert({s.x-1, s.y}); 
    }
    if (moveable(m[s.x][s.y], m, s.x+1, s.y) && !visited.contains({s.x+1, s.y})) {
      q.push({s.step+1, s.x+1, s.y});
      visited.insert({s.x+1, s.y}); 
    }
    if (moveable(m[s.x][s.y], m, s.x, s.y-1) && !visited.contains({s.x, s.y-1})) {
      q.push({s.step+1, s.x, s.y-1});
      visited.insert({s.x, s.y-1}); 
    }
    if (moveable(m[s.x][s.y], m, s.x, s.y+1) && !visited.contains({s.x, s.y+1})) {
      q.push({s.step+1, s.x, s.y+1});
      visited.insert({s.x, s.y+1}); 
    }
  }

  cout << "Part 1: " << result << endl;
}




void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<string> m;
  ll i=0,j=0;

  vector<queue<step>> q;
  vector<set<pair<ll,ll>>> visited;

  while(getline(in, str)) {
    m.emplace_back(str);
    FOR(a, 0, str.size()) {
      if (str[a] == 'S' || str[a] == 'a') {
        queue<step> q1;
        set<pair<ll,ll>> v1;
        q1.push({0, i, a});  
        q.emplace_back(q1);
        v1.insert({i, a});
        visited.emplace_back(v1);
      }
    }
    ++i;
  }

  ll result = INT_MAX;

  F(q.size()) {
    while(!q[i].empty()) {
      step s = q[i].front(); q[i].pop();
      if (m[s.x][s.y] == 'E') { result = min(s.step, result); break; }
      if (moveable(m[s.x][s.y], m, s.x-1, s.y) && !visited[i].contains({s.x-1, s.y})) { 
        q[i].push({s.step+1, s.x-1, s.y}); 
        visited[i].insert({s.x-1, s.y}); 
      }
      if (moveable(m[s.x][s.y], m, s.x+1, s.y) && !visited[i].contains({s.x+1, s.y})) {
        q[i].push({s.step+1, s.x+1, s.y});
        visited[i].insert({s.x+1, s.y}); 
      }
      if (moveable(m[s.x][s.y], m, s.x, s.y-1) && !visited[i].contains({s.x, s.y-1})) {
        q[i].push({s.step+1, s.x, s.y-1});
        visited[i].insert({s.x, s.y-1}); 
      }
      if (moveable(m[s.x][s.y], m, s.x, s.y+1) && !visited[i].contains({s.x, s.y+1})) {
        q[i].push({s.step+1, s.x, s.y+1});
        visited[i].insert({s.x, s.y+1}); 
      }
    }
  }


  cout << "Part 2: " << result << endl;
}

vector<ll> explode(string const & s, char delim)
{
    vector<ll> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);){
      if (token == "x") res.PB(1);
      else res.PB(stoi(token));
    }

    return res;
}

int main(int argc, const char ** argv){
  ios::sync_with_stdio(0);cin.tie(0);
  
  string file = FILE;
  if (argc > 1) {
    file = argv[1];
  }

  part_1(file);
  part_2(file);
  return 0;
}

