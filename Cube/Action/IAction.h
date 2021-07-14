#pragma once

#include <string>

class Cube;

class IAction {
 public:
  virtual ~IAction() = default;
  virtual const IAction &operator()(Cube &) const = 0;
  [[nodiscard]] virtual std::string to_string() const = 0;
};