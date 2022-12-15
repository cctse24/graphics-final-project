#pragma once
#include <string>

using namespace std;

class Rule{
public:
  Rule(string variable, string rule):var(variable), rule(rule){}
  Rule(string variable, string rule, float pro):var(variable),
      rule(rule), pro(pro){}
  string var;
  string rule;
  float pro;
};
