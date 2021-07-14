#pragma once

#include "IAction.h"
#include "../Side.h"

class Cube;

class Move : public IAction {
 public:
  using SIDE = Side::SIDE;
  explicit Move(size_t n);
  Move(unsigned deep, unsigned count, SIDE side);
  explicit Move(const std::string &);

  const IAction &operator()(Cube &) const override;
  [[nodiscard]] std::string to_string() const override;

 private:
  unsigned deep_{};
  unsigned count_{};
  SIDE side_{};

  static auto &GetOrder();
  static auto &GetIsRow();
  static auto &GetIsNormalDeep();
  static auto &GetIsReverse();
  void operator()(Cube &cube, SIDE side, unsigned deep) const;
};
