#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
  private:
  vector<int> parse(string cmd)
  {
    vector<int> v;
    int acc = 0;
    for (auto iter = cmd.begin(); iter != cmd.end(); ++iter) {
      switch (*iter) {
      case 'i':
        ++acc;
        break;
      case 'd':
        --acc;
        break;
      case 's':
        acc *= acc;
        break;
      case 'o':
        v.push_back(acc);
        break;
      }
    }
    return v;
  }

  public:
  void parse_checker()
  {
    vector<int> expected({ 8, 64 });
    assert(expected == parse("iiisdoso"));
  }
  void run()
  {
    parse_checker();
  }
};

int main()
{
  Solution solution;
  solution.run();
  return 0;
}
