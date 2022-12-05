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

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<deque<char>> v;
  char s, c;
  while (getline(in, str)) {
    if (str == "\n" || str.size() == 0) break;
    stringstream ss(str + " ");
    ll i = 0;

    if (v.size() == 0) v.resize(str.size() / 3);
    for (; ss >> noskipws >> s >> c >> s >> s; ++i) {
      if (c == ' ' || (c >= '1' && c <= '9')) continue;
      v[i].emplace_back(c);
    }

    i = 0;
  }

  regex r("move ([0-9]*?) from ([0-9]*?) to ([0-9]*?)");
  smatch m;
  while (getline(in, str)) {
    if (regex_match(str, m, r)) {
      F(stoi(m[1])) {
        v[stoi(m[3])-1].push_front(v[stoi(m[2])-1].front());
        v[stoi(m[2])-1].pop_front();
      }
    }
  }

  string res;
  F(v.size()) {
    if (v[i].empty()) continue;
    res += v[i].front();
  } 
  
  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<deque<char>> v;
  char s, c;
  while (getline(in, str)) {
    if (str == "\n" || str.size() == 0) break;
    stringstream ss(str + " ");
    ll i = 0;

    if (v.size() == 0) v.resize(str.size() / 3);
    for (; ss >> noskipws >> s >> c >> s >> s; ++i) {
      if (c == ' ' || (c >= '1' && c <= '9')) continue;
      v[i].emplace_back(c);
    }

    i = 0;
  }

  regex r("move ([0-9]*?) from ([0-9]*?) to ([0-9]*?)");
  smatch m;
  while (getline(in, str)) {
    if (regex_match(str, m, r)) {
      stack<char> ss;
      F(stoi(m[1])) {
        ss.push(v[stoi(m[2])-1].front());
        v[stoi(m[2])-1].pop_front();
      }

      while(!ss.empty()) {
        v[stoi(m[3])-1].push_front(ss.top());
        ss.pop();
      }
    }
  }

  string res;
  F(v.size()) {
    if (v[i].empty()) continue;
    res += v[i].front();
  }

  cout << "Part 2: " << res << endl;
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

