#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.hpp"
#include <memory>

namespace Drawing
{
    class Shape
    {
    public:
        //virtual ~Shape() = default;
        virtual void move(int x, int y) = 0;
        virtual void draw() const = 0;
        virtual std::unique_ptr<Shape> clone() const;
    };


    // CRTP cloninig
    template <typename ShapeType, typename ShapeBase = Shape>
    class CloneableShape : public ShapeBase
    {
    public:
        std::unique_ptr<Shape> clone() const override
        {
            return std::make_unique<ShapeType>(static_cast<const ShapeType&>(*this));
        }
    };


    template <typename ShapeType>
    class ShapeBase : public CloneableShape<ShapeType>
    {
        Point coord_; // composition
    public:
        Point coord() const
        {
            return coord_;
        }

        void set_coord(const Point& pt)
        {
            coord_ = pt;
        }

        ShapeBase(int x = 0, int y = 0)
            : coord_{ x, y }
        {
        }

        void move(int dx, int dy) override
        {
            coord_.translate(dx, dy);
        }
    };
}

#endif // SHAPE_HPP
