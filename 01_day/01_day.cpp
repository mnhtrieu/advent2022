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

//#define FILE "demo.in"
#define FILE "input.in"

void part_1(const string & file);
void part_2(const string & file);
vector<ll> explode(string const & s, char delim);

void part_1(const string & file) {
  ifstream in(file);
  string str;
  ll sum = 0, max = 0;
  while(getline(in, str)) {
    if (str == "\n" || str.size() == 0) {
      if (sum > max) max = sum;
      sum = 0;
      continue;
    }
    
    sum += stoi(str);
  }

  cout << "Part 1: " << max << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<ll> calories;
  ll sum = 0;
  while(getline(in, str)) {
    if (str == "\n" || str.size() == 0) {
      calories.emplace_back(sum);
      sum = 0;
      continue;
    }

    sum += stoi(str);
  }

  sort(calories.begin(), calories.end(), greater<int>());
  ll result = 0;
  F(3) result += calories[i];

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

