/**
 * Copyright 2014 Andrew Brinker
 */

#include "./Grammar.h"
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#define EOI_STR      "$"
#define EOI_CHAR     '$'
#define EPSILON_STR  "e"
#define EPSILON_CHAR 'e'


Grammar::Grammar() {}


int Grammar::load(std::string file_name) {
  std::ifstream input_file(file_name);
  // The terminals section
  for (std::string line; getline(input_file, line);) {
    if (line == EOI_STR) break;
    _terminals.insert(line[0]);
  }
  // The productions section
  for (std::string line; getline(input_file, line);) {
    if (line == "$") break;
    _non_terminals.insert(line[0]);
    _productions.insert(line);
  }
  return 0;
}


int Grammar::parse() {
  bool failed = findFirst();
  if (failed) return 1;
  failed = findFollow();
  return failed;
}


bool Grammar::findFirst() {
  firstRuleOne();
  firstRuleTwo();
  firstRuleThree();
  return false;
}


void Grammar::firstRuleOne() {
  for (auto it = _terminals.begin(); it != _terminals.end(); ++it) _first[*it].insert(*it);
}


void Grammar::firstRuleTwo() {
  for (auto it = _productions.begin(); it != _productions.end(); ++it) {
    if (it->substr(3) == EPSILON_STR) _first[it->substr(0,3)[0]].insert(EPSILON_CHAR);
  }
}


void Grammar::firstRuleThree() {
  bool changed;
  do {
    changed = false;
    for (auto it = _productions.begin(); it != _productions.end(); ++it) {
      std::string rhs = it->substr(3);
      size_t i = 1;
      while (i <= rhs.length()) {
        std::set<char> current_first = _first[rhs[i]];
        if (current_first.find(EPSILON_CHAR) != current_first.end()) {
          ++i;
        } else {
          std::string lhs = it->substr(0,3);
          _first[lhs[0]].insert(current_first.begin(), current_first.end());
          changed = true;
          break;
        }
        if (i > rhs.length()) {
          std::cout << "Past the end!" << std::endl;
          std::string lhs = it->substr(0,3);
          _first[lhs[0]].insert(EPSILON_CHAR);
          changed = true;
        }
      }
    }
  } while(changed);
}


bool Grammar::findFollow() {
  return false;
}


mapset Grammar::first() const {
  return _first;
}


mapset Grammar::follow() const {
  return _follow;
}

