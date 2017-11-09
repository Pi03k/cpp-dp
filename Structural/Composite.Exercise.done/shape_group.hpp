#ifndef SHAPEGROUP_HPP
#define SHAPEGROUP_HPP

#include <memory>
#include <vector>

#include "shape.hpp"

namespace Drawing
{
  using ShapePtr = std::unique_ptr<Shape>;
  using ShapesContainer = std::vector<ShapePtr>;
  using iterator = std::vector<std::unique_ptr<Shape>>::iterator;
  using const_iterator = std::vector<std::unique_ptr<Shape>>::const_iterator;
  class ShapeGroup : public CloneableShape<ShapeGroup>
  {
    public:
      ShapeGroup() = default;
      ShapeGroup(const ShapeGroup&);
      ShapeGroup& operator=(const ShapeGroup&);
      void add(ShapePtr shape);
      void move(int dx, int dy) override;
      void draw() const override;
      int size() const;
      static auto constexpr id = "ShapeGroup";
      void swap(ShapeGroup& tmp);
    private:
      ShapesContainer shapes;
    public:
      iterator begin() { return shapes.begin(); }
      iterator end() { return shapes.end(); }
      const_iterator begin() const { return shapes.begin(); }
      const_iterator end() const { return shapes.end(); }
  };
}

#endif // SHAPEGROUP_HPP
