/**
 * Copyright 2014 Andrew Brinker
 */

#include <string>
#include <Grammar/Grammar.h>

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&);


class Preprocessor {
 public:
  explicit Preprocessor(std::string);
  Grammar run();

 private:
  Grammar load();
  Grammar expand();
  void sanityCheck();

  std::string name;
  Grammar file;
  bool _is_expanded;

  DISALLOW_COPY_AND_ASSIGN(Preprocessor);
};

#endif  // PREPROCESSOR_H
