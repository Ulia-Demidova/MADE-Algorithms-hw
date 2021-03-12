#include <cctype>
#include <iostream>

using std::cin;
using std::cout;
using std::string;

class Lexer {
private:
  string s;
  int index;

public:
  Lexer(string &&s) : s(s), index(0) {}

  string next_token() {
    char symbol = s[index];
    string cur_token;
    cur_token += symbol;
    if (isdigit(symbol)) {
      while (isdigit(s[index + 1])) {
        ++index;
        cur_token += s[index];
      }
    }
    ++index;
    return cur_token;
  }
};

int main() {
  string expr;
  cin >> expr;
  Lexer lexer(std::move(expr));
  while (true) {
    string token = lexer.next_token();
    if (token == ".")
      break;
    else
      cout << token << '\n';
  }
  return 0;
}
