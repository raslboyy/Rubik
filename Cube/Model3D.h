#pragma once

#include <memory>

#include "Cube.h"

class Model3D {
 public:
  using SIDE = Side::SIDE;

  explicit Model3D(const Cube &);

  Model3D(const Model3D &) = delete;
  Model3D &operator=(const Model3D &) = delete;

 private:
  class Element {
   public:
    explicit Element(size_t n) : sides(n) {};
    [[nodiscard]] bool equals(const Element &, bool is_orientation) const;
    virtual ~Element() = default;
   protected:
    std::vector<SIDE> sides;
  };

  std::vector<std::vector<std::shared_ptr<Element>>> cube;
  size_t n_;

  struct CCenterElement : Element {
    explicit CCenterElement(SIDE side0) : Element(1) { Element::sides[0] = side0; }
  };
  struct CEdgeElement : Element {
    CEdgeElement(SIDE side0, SIDE side1) : Element(2) {
      Element::sides[0] = side0, Element::sides[1] = side1;
    }
  };
  struct CCornerElement : Element {
    CCornerElement(SIDE side0, SIDE side1, SIDE side2) : Element(3) {
      Element::sides[0] = side0, Element::sides[1] = side1, Element::sides[2] = side2;
    }
  };
};
