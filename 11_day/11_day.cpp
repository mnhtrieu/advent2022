#include <bits/stdc++.h>
using namespace std;
using ll=unsigned long long;
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
string trim(const string& str, const string& whitespace);

struct monkey {
  queue<ll> items;
  function<ll(ll)> func;
  ll divisible;
  ll left;
  ll right;
};

void part_1(const string & file) {
  ifstream in(file);
  string str;

  regex items_expr ("\\s*Starting items: (.*?)");
  regex op_expr("\\s*Operation: new = old (.) (.*?)");
  regex test_expr("\\s*Test: divisible by ([0-9]*?)");
  regex true_expr("\\s*If true: throw to monkey ([0-9]*?)");
  regex false_expr("\\s*If false: throw to monkey ([0-9]*?)");

  vector<shared_ptr<monkey>> monkeys;

  getline(in, str); // ignore first line
  
  shared_ptr<monkey> m = shared_ptr<monkey>(new monkey());
  while(getline(in, str)) {
    if (str.starts_with("Monkey")) {
      monkeys.emplace_back(m);
      m = shared_ptr<monkey>(new monkey());
      continue;
    }

    smatch sm;
    if (regex_match(str, sm, items_expr)) {
      for (auto & i: explode(sm[1], ',')) m->items.push(i);
      continue;
    }

    if (regex_match(str, sm, op_expr)) {
      if (sm[1] == "+") {
        if (sm[2] == "old") m->func = [](ll i) -> ll { return i + i; };
        else {
          ll a = stoi(sm[2]);
          m->func = [a](ll i) -> ll { return i + a; };
        }
      }
      else if (sm[1] == "*") {
        if (sm[2] == "old") m->func = [](ll i) -> ll { return i * i; };
        else {
          ll a = stoi(sm[2]);
          m->func = [a](ll i) -> ll { return i * a; };
        }
      } 
      continue;
    }

    if (regex_match(str, sm, test_expr)) {
      m->divisible = stoi(sm[1]);
      continue;
    }

    if (regex_match(str, sm, true_expr)) {
      m->left = stoi(sm[1]);
      continue;
    }

    if (regex_match(str, sm, false_expr)) {
      m->right = stoi(sm[1]);
      continue;
    }
  }

  monkeys.emplace_back(m);
  vector<ll> results(monkeys.size(), 0);

  FOR(rounds, 0, 20) {
    F(monkeys.size()) {
      while(!monkeys[i]->items.empty()) {
        ll num = monkeys[i]->items.front(); monkeys[i]->items.pop();
        num = monkeys[i]->func(num);
        num /= 3;
        bool divisible = num % monkeys[i]->divisible == 0;
        if (divisible) monkeys[monkeys[i]->left]->items.push(num);
        else monkeys[monkeys[i]->right]->items.push(num);
        results[i] ++;
      }
    }
  }

  sort(results.begin(), results.end(), greater<int>());
  cout << "Part 1: " << results[0] * results[1] << endl;
}


void part_2(const string & file) {
  ifstream in(file);
  string str;

  regex items_expr ("\\s*Starting items: (.*?)");
  regex op_expr("\\s*Operation: new = old (.) (.*?)");
  regex test_expr("\\s*Test: divisible by ([0-9]*)");
  regex true_expr("\\s*If true: throw to monkey ([0-9]*)");
  regex false_expr("\\s*If false: throw to monkey ([0-9]*)");

  vector<shared_ptr<monkey>> monkeys;

  getline(in, str); // ignore first line
  
  shared_ptr<monkey> m = shared_ptr<monkey>(new monkey());
  ll product = 1;
  while(getline(in, str)) {
    if (str.starts_with("Monkey")) {
      monkeys.emplace_back(m);
      m = shared_ptr<monkey>(new monkey());
      continue;
    }

    smatch sm;
    if (regex_match(str, sm, items_expr)) {
      for (auto & i: explode(sm[1], ',')) m->items.push(i);
      continue;
    }

    if (regex_match(str, sm, op_expr)) {
      if (sm[1] == "+") {
        if (sm[2] == "old") m->func = [](ll i) -> ll { return i + i; };
        else {
          ll a = stoi(sm[2]); m->func = [a](ll i) -> ll { return i + a; };
        }
      }
      else if (sm[1] == "*") {
        if (sm[2] == "old") m->func = [](ll i) -> ll { return i * i; };
        else {
          ll a = stoi(sm[2]); m->func = [a](ll i) -> ll { return i * a; };
        }
      } 
      continue;
    }

    if (regex_match(str, sm, test_expr)) {
      m->divisible = stoi(sm[1]);
      product *= m->divisible;
      continue;
    }

    if (regex_match(str, sm, true_expr)) {
      m->left = stoi(sm[1]);
      continue;
    }

    if (regex_match(str, sm, false_expr)) {
      m->right = stoi(sm[1]);
      continue;
    }
  }

  monkeys.emplace_back(m);
  vector<ll> results(monkeys.size(), 0);

  FOR(rounds, 0, 10000) {
    F(monkeys.size()) {
      while(!monkeys[i]->items.empty()) {
        ll num = monkeys[i]->items.front(); monkeys[i]->items.pop();
        num = monkeys[i]->func(num);
        num %= product;
        bool divisible = num % monkeys[i]->divisible == 0;
        if (divisible) monkeys[monkeys[i]->left]->items.push(num);
        else monkeys[monkeys[i]->right]->items.push(num);
        results[i] ++;
      }
    }
  }

  sort(results.begin(), results.end(), greater<int>());
  cout << "Part 2: " << results[0] * results[1] << endl;
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


string trim(const string& str, const string& whitespace = " \t") {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos) return ""; // no content
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}