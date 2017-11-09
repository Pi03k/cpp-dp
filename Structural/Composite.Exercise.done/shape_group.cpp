#include "shape_group.hpp"
#include "shape_factories.hpp"
#include <algorithm>

using namespace std;
using namespace Drawing;

namespace
{
    bool is_registered = SingletonShapeFactory::instance()
                             .register_creator(ShapeGroup::id, &make_unique<ShapeGroup>);
}
ShapeGroup::ShapeGroup(const ShapeGroup& shapeGroup)
{
    for(auto& shape: shapeGroup.shapes)
    {
      add(shape->clone());
    }
}

ShapeGroup& ShapeGroup::operator=(const ShapeGroup& shapeGroup)
{
  ShapeGroup tmp(shapeGroup);
  swap(tmp);
  return *this;
}

void ShapeGroup::swap(ShapeGroup& tmp)
{
  shapes.swap(tmp.shapes);
}

void ShapeGroup::move(int dx, int dy)
{
  for(auto &shape : shapes)
  {
    shape->move(dx, dy);
  }
}

void ShapeGroup::draw() const
{
  for(auto &shape : shapes)
  {
    shape->draw();
  }
}

void ShapeGroup::add(ShapePtr shape)
{
  shapes.push_back(std::move(shape));
}

int ShapeGroup::size() const
{
  return shapes.size();
}
