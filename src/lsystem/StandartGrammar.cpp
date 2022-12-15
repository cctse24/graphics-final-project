#include "StandartGrammar.hpp"

void StandartGrammar::iterate(const int iterations = 1){
    vector<Rule> rul = getRules(rules);
    for (unsigned int i = 0; i < iterations ; ++i){
        string new_cond;
        for (unsigned int j = 0; j < condition.size(); ++j){
            string cur;
            cur += condition[j];
            string replacement = cur;
            for (auto r : rul){
                if(cur == r.var){
                    replacement = r.rule;
                    break;
                }
            }
            new_cond += replacement;
          }
        condition = new_cond;
    }
}


vector<Rule> StandartGrammar::getRules(vector<string> &rul){
  vector<Rule> v;
  for (auto r : rul){
      auto pos = r.find(" => ");
      if (pos != -1){
        Rule n(r.substr(0,pos), r.substr(pos+4));
        v.push_back(n);
      }
  }
  return v;
}


