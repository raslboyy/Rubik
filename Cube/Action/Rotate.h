#pragma once

#include "IAction.h"
#include "../../Random.h"
#include "../Side.h"

class Rotate : public IAction {
 public:
  using SIDE = Side::SIDE;
  Rotate() : type_(static_cast<SIDE>(Random::randU32(4))) {};
  explicit Rotate(SIDE type) : type_(type) {};
  explicit Rotate(const std::string &s) : type_(static_cast<SIDE>(s[0] - '0')) {}

  const IAction &operator()(Cube &) const override;
  [[nodiscard]] std::string to_string() const override;

 private:
  SIDE type_{};

  static auto &GetOrder();
  static auto &GetRotate();
};
