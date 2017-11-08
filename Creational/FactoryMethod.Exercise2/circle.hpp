#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"

namespace Drawing
{
    class Circle : public ShapeBase
    {
        int radius_;
    public:
        static constexpr const char* id = "Circle";

        Circle(int x = 0, int y = 0, int r = 0)
            : ShapeBase{x, y}, radius_{r}
        {}

        void draw() const override
        {
            std::cout << "Drawing a circle at " << coord() << " with r: " << radius_ << std::endl;
        }

        int radius() const
        {
            return radius_;
        }

        void set_radius(int r)
        {
            radius_ = r;
        }

    };
}

#endif // CIRCLE_H
