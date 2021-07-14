#pragma once

#include <memory>
#include <vector>
#include "IAction.h"

class Scramble : public IAction {
 public:
  explicit Scramble(size_t n, size_t = std::numeric_limits<size_t>::infinity());
  explicit Scramble(size_t n, const std::string &);
  // проверка n
  Scramble(const Scramble &) = default;

  const IAction &operator()(Cube &) const override;
  [[nodiscard]] std::string to_string() const override;
  [[nodiscard]] size_t len() const { return scramble.size(); }

  Scramble &operator+=(const Scramble &);
  friend Scramble operator+(Scramble, const Scramble &);
 private:
  size_t n_;
  std::vector<std::shared_ptr<IAction>> scramble;
};
