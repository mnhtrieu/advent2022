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

struct folder {
  map<string, shared_ptr<folder>> folders;
  shared_ptr<folder> parent;
  map<string, ll> files; 
};

ll crawl(shared_ptr<folder> curr, vector<ll> & m) {
  ll size = 0;
  for(auto & [k,v]: curr->files) size += v;
  for(auto & [k,v] : curr->folders) size += m.emplace_back(crawl(v, m));
  return size;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  shared_ptr<folder> root(new folder());
  shared_ptr<folder> curr = root;

  while(getline(in, str)) {
    if (str.starts_with("$ cd")) {
      string f = str.substr(5);
      if (f == "/") curr = root;
      else if (f == "..") curr = curr->parent;
      else curr = curr->folders[f];
    }
    else if (str.starts_with("$ ls")) {
      continue;
    }
    else if (str.starts_with("dir")) {
      string f = str.substr(4);
      curr->folders[f] = shared_ptr<folder>(new folder());
      curr->folders[f]->parent = curr;
    }
    else {
      string::size_type pos = str.find_first_of(' ');
      ll size = stoi(str.substr(0, pos));
      string filename = str.substr(pos+1);
      curr->files[filename] = size;
    }
  }

  vector<ll> sizes;
  sizes.emplace_back(crawl(root, sizes));

  ll sum = 0;
  for (auto & s : sizes) if (s <= 100000) sum += s;
  
  cout << "Part 1: " << sum << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  shared_ptr<folder> root(new folder());
  shared_ptr<folder> curr = root;

  while(getline(in, str)) {
    if (str.starts_with("$ cd")) {
      string f = str.substr(5);
      if (f == "/") curr = root;
      else if (f == "..") curr = curr->parent;
      else curr = curr->folders[f];
    }
    else if (str.starts_with("$ ls")) {
      continue;
    }
    else if (str.starts_with("dir")) {
      string f = str.substr(4);
      curr->folders[f] = shared_ptr<folder>(new folder());
      curr->folders[f]->parent = curr;
    }
    else {
      string::size_type pos = str.find_first_of(' ');
      ll size = stoi(str.substr(0, pos));
      string filename = str.substr(pos+1);
      curr->files[filename] = size;
    }
  }

  ll space = 70000000;
  vector<ll> sizes;
  ll rootsize = crawl(root, sizes);
  sizes.emplace_back(rootsize);
  sort(sizes.begin(), sizes.end());
  auto lower = lower_bound(sizes.begin(), sizes.end(), 30000000 - (space - rootsize));
  cout << "Part 2: " << *lower << endl;
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

