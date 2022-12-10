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

ll sgn(ll val) {
    return (0 < val) - (val < 0);
}

bool is_far(pair<ll, ll> h, pair<ll, ll> t) {
  return abs(h.first-t.first) > 1 || abs(h.second-t.second) > 1;
}

pair<ll,ll> move(pair<ll,ll> h, pair<ll,ll> t) {
  return {sgn(h.first-t.first), sgn(h.second-t.second)};
}

pair<ll,ll> operator+(const pair<ll,ll> &a ,const pair<ll,ll> &b) {
  return make_pair(a.first+b.first,a.second+b.second);
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  char c;
  ll i;
  set<pair<ll,ll>> moves;
  pair<ll,ll> h = {0,0}, t = {0,0};
  moves.insert(t);
  while(in >> c >> i) {
    if (c == 'R') {
      FOR(j, 0, i) { 
        h = {h.aa, h.bb+1};
        if (is_far(h, t)) moves.insert(t = t + move(h, t));
      }
    }
    else if (c == 'L') {
      FOR(j, 0, i) { 
        h = {h.aa, h.bb-1};
        if (is_far(h, t)) moves.insert(t = t + move(h, t));
      }
    }
    else if (c == 'D') {
      FOR(j, 0, i) { 
        h = {h.aa-1, h.bb};
        if (is_far(h, t)) moves.insert(t = t + move(h, t));
      }
    }
    else if (c == 'U') {
      FOR(j, 0, i) { 
        h = {h.aa+1, h.bb};
        if (is_far(h, t)) moves.insert(t = t + move(h, t));
      }
    }
  }

  cout << "Part 1: " << moves.size() << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  pair<ll,ll> h = {0,0};
  vector<pair<ll,ll>> v(9, {0,0});

  char c;
  ll i, x = 0, y = 0;
  set<pair<ll,ll>> moves;
  moves.insert({0,0});
  while(in >> c >> i) {
    if (c == 'R') {
      FOR(j, 0, i) { 
        pair<ll, ll> prev = h = {y, ++x};
        FOR(z, 0, 9) {
          if (is_far(prev, v[z])) v[z] = v[z] + move(prev, v[z]);
          prev = v[z];
          moves.insert(v[8]);
        }
      }
    }
    else if (c == 'L') {
      FOR(j, 0, i) { 
        pair<ll, ll> prev = h = {y, --x};
        FOR(z, 0, 9) {
          if (is_far(prev, v[z])) v[z] = v[z] + move(prev, v[z]); 
          prev = v[z];
          moves.insert(v[8]);
        }
      }
    }
    else if (c == 'D') {
      FOR(j, 0, i) { 
        pair<ll, ll> prev = h = {--y, x};
        FOR(z, 0, 9) {
          if (is_far(prev, v[z])) v[z] = v[z] + move(prev, v[z]);
          
          prev = v[z];
          moves.insert(v[8]);
        }
      }
    }
    else if (c == 'U') {
      FOR(j, 0, i) { 
        pair<ll, ll> prev = h = {++y, x};
        FOR(z, 0, 9) {
          if (is_far(prev, v[z])) v[z] = v[z] + move(prev, v[z]);
          prev = v[z];
          moves.insert(v[8]);
        }
      }
    }
  }

  cout << "Part 2: " << moves.size() << endl;
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

