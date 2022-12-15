#include "StochasticGrammar.hpp"

void StochasticGrammar::iterate(int iterations = 1){
    vector<Rule> r = getRules(rules);
    map<float, Rule> rul = buildRuleRange(r);
    srand(time(NULL));
    for (unsigned int i = 0; i < iterations ; ++i){
        string new_cond;
        float random = ((float)rand()/(float)RAND_MAX);
        auto randomRule = rul.lower_bound(random);
        for (unsigned int j = 0; j < condition.size(); ++j){
            string cur;
            cur += condition[j];
            string replacement = cur;
            if(randomRule->second.var == cur){
              replacement = randomRule->second.rule;
            }
            new_cond += replacement;
          }
        condition = new_cond;
    }
}

vector<Rule> StochasticGrammar::getRules(vector<string> &rul){
  vector<Rule> v;
  for (auto r : rul){
      auto pos1 = r.find(" => ");
      auto pos2 = r.find(" (");
      auto pos3 = r.find(")");
      if (pos1 != -1 && pos2 != -1){
        string p = r.substr(pos2+3, pos3);
        Rule n(r.substr(0,pos1), r.substr(pos1+4, pos2 - pos1 - 4),stof(p));
        v.push_back(n);
      }
  }
  return v;
}

map<float, Rule> StochasticGrammar::buildRuleRange(const vector<Rule> &rules){
    map<float, Rule> rulesWithProbability;
    float probability = 0.0;
    for (auto r : rules){
        probability += r.pro;
        rulesWithProbability.insert(make_pair(probability,r));
    }
    return rulesWithProbability;
}
