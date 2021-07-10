#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Side.h"
#include "../Random.h"

class Cube {
 public:

  explicit Cube(size_t = 3);
  explicit Cube(std::vector<Side> &);

  class IAction;

  std::string random_scramble(size_t = std::numeric_limits<size_t>::infinity());
  void apply_scramble(const std::string &);
  [[nodiscard]] std::string get_scramble() const;

  [[nodiscard]] unsigned stupidFitness() const;
  [[nodiscard]] unsigned layerFitness() const;

  friend std::ostream &operator<<(std::ostream &os, const Cube &c);
//  friend std::istream &operator>>(std::istream &is, Cube &c);

 private:
  size_t n_;
  std::vector<Side> sides;

 public:
  enum SIDE : size_t { UP = 0, DOWN, LEFT, RIGHT, FRONT, BACK };

  Cube(const Cube &) = default;
  Cube &operator=(const Cube &) = default;

  [[nodiscard]] size_t n() const { return n_; }

 private:
  Side &get(SIDE face) { return sides[face]; }

 public:
  class IAction {
   public:
    virtual ~IAction() = default;
    virtual const IAction &operator()(Cube &) const = 0;
    [[nodiscard]] virtual std::string to_string() const = 0;
  };
 private:
  class Move : public IAction {
   public:
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
  class Rotate;
  class Skip;
  class Scramble : public IAction {
    public:
    explicit Scramble(size_t n, size_t = std::numeric_limits<size_t>::infinity());
    explicit Scramble(size_t n, const std::string &);
    // проверка n
    Scramble(const Scramble &) = default;

    const IAction &operator()(Cube &) const override;
    [[nodiscard]] std::string to_string() const override;

    Scramble &operator+=(const Scramble &);
    private:
    size_t n_;
    std::vector<std::shared_ptr<IAction>> scramble;
  };
  friend Scramble operator+(Scramble, const Scramble &);
  Scramble scramble_;
 public:
  void R(size_t deep = 0) { Move(deep, 1, RIGHT).operator()(*this); }
  void L(size_t deep = 0) { Move(deep, 1, LEFT) .operator()(*this); }
  void U(size_t deep = 0) { Move(deep, 1, UP)   .operator()(*this); }
  void D(size_t deep = 0) { Move(deep, 1, DOWN) .operator()(*this); }
  void F(size_t deep = 0) { Move(deep, 1, FRONT).operator()(*this); }
  void B(size_t deep = 0) { Move(deep, 1, BACK) .operator()(*this); }
};


class Cube::Rotate : public IAction {
 public:
  Rotate() : type_(static_cast<SIDE>(Random::randU32(4))) {};
  explicit Rotate(SIDE type) : type_(type) {};
  explicit Rotate(const std::string &s) : type_(static_cast<SIDE>(s[0] - '0')) {}

  const IAction &operator()(Cube &) const override;
  [[nodiscard]] std::string to_string() const override;

 private:
  SIDE type_{};

  static auto &GetOrder();
};

class Cube::Skip : public IAction {
 public:
  const IAction &operator()(Cube &) const override { return *this; };
  [[nodiscard]] std::string to_string() const override { return "-"; }
};