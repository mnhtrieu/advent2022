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

ll score(const vector<vector<ll>> & m, ll i, ll j) {
  ll cnt = 1, tmp = 0;
  for(int x = i-1; x >= 0; --x) {
    if (m[i][j] > m[x][j]) ++tmp;
    else { ++tmp; break; }
  }

  cnt *= tmp; tmp = 0;
  for(size_t x = i+1; x < m.size(); ++x) {
    if (m[i][j] > m[x][j]) ++tmp;
    else { ++tmp; break; }
  }

  cnt *= tmp; tmp = 0;
  for(int x = j-1; x >= 0; --x) {
    if (m[i][j] > m[i][x]) ++tmp;
    else { ++tmp; break; }
  }

  cnt *= tmp; tmp = 0;
  for(size_t x = j+1; x < m.size(); ++x) {
    if (m[i][j] > m[i][x]) ++tmp;
    else { ++tmp; break; }
  }

  cnt *= tmp; tmp = 0;
  return cnt;

}

bool is_visible(const vector<vector<ll>> & m, ll i, ll j) {
  bool visible = false, tmp = true;
  FOR(x, 0, i) if (m[x][j] >= m[i][j]) { tmp = false; break; }
  
  visible |= tmp; tmp = true;
  FOR(x, i+1, m.size()) if (m[x][j] >= m[i][j]) { tmp = false; break; } 

  visible |= tmp; tmp = true;
  FOR(x, 0, j) if (m[i][x] >= m[i][j]) { tmp = false; break; }

  visible |= tmp; tmp = true;
  FOR(x, j+1, m.size()) if (m[i][x] >= m[i][j]) { tmp = false; break; }
  
  return visible |= tmp;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<vector<ll>> m;
  while(getline(in, str)) {
    vector<ll> tmp;
    for (auto & c : str) tmp.emplace_back(c - '0');
    m.emplace_back(move(tmp));
  }

  ll cnt = 0;
  FOR(i, 1, m.size()-1) {
    FOR(j, 1, m[i].size()-1) {
      if (is_visible(m, i, j)) cnt ++;
    }
  }

  cout << "Part 1: " << cnt + m.size()*2 + (m.size()-2)*2 << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<vector<ll>> m;
  while(getline(in, str)) {
    vector<ll> tmp;
    for (auto & c : str) tmp.emplace_back(c - '0');
    m.emplace_back(move(tmp));
  }

  ll max_score = 0;
  FOR(i, 1, m.size()-1) {
    FOR(j, 1, m[i].size()-1) {
      max_score = max(max_score, score(m, i, j));
    }
  }

  cout << "Part 2: " << max_score << endl;
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

