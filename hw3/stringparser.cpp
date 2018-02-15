#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <iostream>
#include <cstdlib>

using namespace std;

bool check_valid(string str, stack<string> &mystack) {
  stringstream exp(str);
  char a;
  while (exp >> a){
    if (!isalpha(a)){
      if (a == '+') {
        exp >> a;
        while (isalpha(a))
          exp >> a;
        if (a == '-'){
          cout << "Malformed, mixed operators" << endl;
          return false;
        }
      }

      else if (a == '-') { 
        exp >> a;
        while (isalpha(a))
          exp >> a;
        if (a == '+'){
          cout << "Malformed, mixed operators" << endl;
          return false;
        }
      }

      if (a == '(') {
        string s(1,a);
        mystack.push(s);
      }

      else if (a == ')')
        mystack.pop();

    }
  }

  if (!mystack.empty()){
    cout << "Malformed, parentheses dont match" << endl;
    return false;
  }

  return true;
}

int make_stack(stringstream& exp, stack<string> &mystack){
  char a;
  while (exp >> a){
    if (isalpha(a) && islower(a)) {
      string s(1,a);
      while (exp >> a && (isalpha(a) && islower(a))) {
        s.push_back(a);
      }

      if (mystack.size() > 0 && ((mystack.top() == "<") || (mystack.top() == ">"))){
        while (mystack.size() > 0 && (mystack.top() == "<" || mystack.top() == ">") && s.length() > 1){
          if (mystack.top() == "<")
            s.pop_back();
          else
            s.erase(0,1);
          mystack.pop();
        }   
      }
      //cout << s;
      mystack.push(s);
    }

    if (exp.fail())
      return -2;

    if (a == '(' || a == '+' || a == '-' || a == '<' || a == '>'){
      string s(1,a);
      mystack.push(s);
    }

    else if (a == ')')
      break;

    else if (!isspace(a)){
      cout << "Malformed, nonexpression chars" << endl;
      return -1;
    }
  }
  return 0;
}

int operate(stack<string> &mystack){
  string t = mystack.top();

  if (t == "(" || t == "+" || t == "-" || t == "<" || t == ">"){
      cout << "Malformed, operator immediately before parentheses" << endl;
      return -1;
  }

string s = mystack.top();
string q = t;
  while (mystack.size() > 1) {
    mystack.pop();
    s = mystack.top();
    
    /*if (s == "<" || s == ">") {
      while (s == "<" || s == ">"){
        if (s == "<")
          ++back;
        else
          ++front;
        mystack.pop();
        s = mystack.top(); 
      }

      if (back > 0){
        for (int i = 0; i < back; i++)
          s.pop_back();
      }

      if (front > 0){
        for (int i = 0; i < front; i++)
          s.erase(0,1);
      }
    }*/

    if (s == "+"){
      mystack.pop();
      s = mystack.top();
      if (s == "(" || s == "+" || s == "-" || s == "<" || s == ">"){
        cout << "Malformed, operator immediately before parentheses" << endl;
        return -1;
      }
      else
        q = s + q;
    }

    else if (s == "-"){
      mystack.pop();
      s = mystack.top();
      if (s == "(" || s == "+" || s == "-" || s == "<" || s == ">"){
        cout << "Malformed, operator immediately before parentheses" << endl;
        return -1;
      }
      else {
        if (s.find(t,0) != string::npos)
          q = s.erase(s.find(t,0), q.length());
        else
          q = s;
      }
    }

    if (s == "("){
      mystack.pop();
      break;
    }
  }
 
  if (mystack.size() > 1 && q.length() > 1){
    if (mystack.top() == "<" || mystack.top() == ">"){
      while ((mystack.size() > 0) && (mystack.top() == "<" || mystack.top() == ">")){
        if (mystack.top() == "<")
          q.pop_back();
        else
          q.erase(0,1);
        mystack.pop();
      }

        
    }
  }

  mystack.push(q);
  return 0;
}

int main(int argc, char* argv[])
{
  if (argc < 3) {
   cerr << "Please provide an input and output file" << endl;
   return -1;
  }

  ifstream input(argv[1]);
  ofstream output(argv[2]);

  if(input.fail()) {
     cerr << "Invalid file" << endl;
     return -1;
  }

  while (!input.fail() && !input.eof()){
    stack<string> mystack;
    string str;
    getline(input, str);

    if (str.length() == 0){
      cout << "Empty string" << endl;
      continue;
    }

    stringstream exp(str);
    bool valid = check_valid(str, mystack);
    if (!valid)
      continue;

    int made = make_stack(exp, mystack);
    if(made == -2){
      cout << mystack.top() << endl;
      continue;
    }
    int form;
    while ((mystack.size() > 1) && valid == true && made != -1){
      form = operate(mystack);

      if(form == -1)
        break;

      made = make_stack(exp, mystack);

      if(made == -1)
        break;
    }
    if(mystack.size() == 1 && form != -1 && made != -1)
      cout << mystack.top() << endl;
  }
}