#include <exception>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

enum token {
  Plus,
  Minus,
  Mul,
  Open,
  Close,
  End,
  Num,
};

class Parser;

class Lexer {
private:
  string s;
  int index;
  int64_t value;
  token cur_token;

public:
  friend Parser;

  explicit Lexer(string &&s) : s(s), index(0), value(0), cur_token(Num) {}

  void parse_number() {
    value = 0;
    while (isdigit(s[index])) {
      value = value * 10 + (s[index] - '0');
      ++index;
    }
    --index;
  }

  void next_token() {
    char symbol = s[index];

    if (isdigit(symbol)) {
      parse_number();
      cur_token = Num;
    } else if (symbol == '+')
      cur_token = Plus;
    else if (symbol == '-')
      cur_token = Minus;
    else if (symbol == '*')
      cur_token = Mul;
    else if (symbol == '(')
      cur_token = Open;
    else if (symbol == ')')
      cur_token = Close;
    else if (symbol == '.')
      cur_token = End;
    else
      throw std::runtime_error("Wrong symbol when lexer works");
    ++index;
  }
};

struct Expression {
  token token;
  int64_t value;
  vector<Expression> args;

  explicit Expression(int64_t value) : value(value), token(Num) {}
  explicit Expression(enum ::token token) : token(token), value(0) {}
  Expression(enum ::token token, Expression a, Expression b)
      : token(token), args({a, b}), value(0) {}

  int64_t evaluate() {
    if (token == Num)
      return value;
    else if (token == Mul)
      return args[0].evaluate() * args[1].evaluate();
    else
      throw std::runtime_error("Can't evaluate single expression");
  }
};

class Parser {
  Lexer lexer;

public:
  explicit Parser(Lexer &lexer) : lexer(lexer) {}

  Expression parseTerm() {
    if (lexer.cur_token == Open) {
      Expression answer = parseExpr();
      if (lexer.cur_token != Close)
        throw std::runtime_error("Expected ')'");
      return answer;
    } else if (lexer.cur_token == Num) {
      Expression answer(lexer.value);
      return answer;
    }
    throw std::runtime_error("Can't parse term");
  }

  Expression parseProduct() {
    lexer.next_token();
    Expression answer = parseTerm();
    lexer.next_token();
    if (lexer.cur_token == Mul) {
      token c = lexer.cur_token;
      answer = Expression(c, answer, parseProduct());
    }
    return answer;
  }

  Expression parseExpr() {
    vector<Expression> expr;
    Expression answer = parseProduct();
    expr.push_back(answer);
    while (lexer.cur_token == Plus || lexer.cur_token == Minus) {
      expr.emplace_back(Expression(lexer.cur_token));
      answer = parseProduct();
      expr.push_back(answer);
    }
    return Expression(evaluate(expr));
  }

  int64_t evaluate(vector<Expression> &expr) {
    int64_t res = expr[0].evaluate();
    int i = 1;
    while (i < expr.size()) {
      if (expr[i].token == Plus) {
        ++i;
        res += expr[i].evaluate();
      } else if (expr[i].token == Minus) {
        ++i;
        res -= expr[i].evaluate();
      }
      ++i;
    }
    return res;
  }

  int64_t parse() {
    Expression result = parseExpr();
    if (lexer.cur_token == End)
      return result.value;
    else
      throw std::runtime_error("Can't evaluate expression");
  }
};

int main() {
  string s;
  cin >> s;
  Lexer lexer(std::move(s));
  Parser parser(lexer);
  try {
    cout << parser.parse();
  } catch (std::exception &e) {
    cout << "WRONG";
  }
  return 0;
}
