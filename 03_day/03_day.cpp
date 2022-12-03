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

ll prio(char c) {
  if (c >= 'a' && c <= 'z') return c - 'a' + 1;
  return c- 'A' + 27;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  ll sum = 0;
  while(in >> str) {
    string s = str.substr(0, str.size()/2), s2 = str.substr(str.size()/2);
    sort(s.begin(), s.end());
    sort(s2.begin(), s2.end());

    vector<char> v;
    set_intersection(s.begin(), s.end(), s2.begin(), s2.end(), back_inserter(v));
    sum += prio(v[0]);
  }

  cout << "Part 1: " << sum << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  ll gr = 0, i = 0, sum = 0;
  vector<char> v;
  while(in >> str) {
    vector<char> curr;
    sort(str.begin(), str.end());
    if (i++ == 0) v.insert(v.begin(), str.begin(), str.end());
    else {
      set_intersection(v.begin(), v.end(), str.begin(), str.end(), back_inserter(curr));
      swap(v, curr);
    }
    
    if (++gr == 3) {
      sum += prio(v[0]);
      gr = i = 0;
    }
  }

  cout << "Part 2: " << sum << endl;
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

