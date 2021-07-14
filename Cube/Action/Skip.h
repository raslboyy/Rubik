#pragma once

#include "IAction.h"

class Skip : public IAction {
 public:
  const IAction &operator()(Cube &) const override { return *this; };
  [[nodiscard]] std::string to_string() const override { return "-"; }
};