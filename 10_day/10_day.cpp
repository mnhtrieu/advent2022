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

  ll cycles[6] = {20, 60, 100, 140, 180, 220};
  ll x = 1, c = 1, i = 0, result = 0;
  while(getline(in, str)) {
    if (str == "noop") { c++; continue; }

    size_t pos = str.find_first_of(' ');
    string action = str.substr(0, pos);
    ll num = stoi(str.substr(pos+1));

    c += 2;
    x += num;

    if (c >= cycles[i]) {
      result += c == cycles[i] ? cycles[i]*x : cycles[i]*(x-num);
      i++;
    }
  }

  cout << "Part 1: " << result << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<vector<bool>> v(6);
  F(v.size()) v[i].resize(40);

  ll x = 1, i = 0, j = 0;
  while(getline(in, str)) {
    size_t pos = str.find_first_of(' ');
    ll num = pos != string::npos ? stoi(str.substr(pos+1)) : 0;
    ll cycles = pos != string::npos ? 2 : 1;
  
    FOR(c, 0, cycles) {
      FOR(z, -1, 2) if (j == x+z) { v[i][j] = true; break; } 
      if (j+1 >= 40) i++;
      j = (j+1) % 40;
    }

    x += num;
  }

  cout << "Part 2: " << endl;
  for (auto & v1: v) {
    for (const auto & b: v1) {
      cout << (b ? "#" : ".");
    }
    cout << endl;
  }
  
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

