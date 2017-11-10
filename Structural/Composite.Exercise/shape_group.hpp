#ifndef SHAPEGROUP_HPP
#define SHAPEGROUP_HPP

#include <memory>
#include <vector>

#include "shape.hpp"

namespace Drawing
{
    using ShapePtr = std::unique_ptr<Shape>;

    // TODO
    class ShapeGroup : public CloneableShape<ShapeGroup>
    {
        std::vector<ShapePtr> shapes_;

    public:
        static constexpr const char* id = "ShapeGroup";

        using iterator = std::vector<ShapePtr>::iterator;
        using const_iterator = std::vector<ShapePtr>::const_iterator;

        ShapeGroup() = default;

        ShapeGroup(const ShapeGroup& source)
        {
            for (const auto& s : source.shapes_)
                shapes_.push_back(s->clone());
        }

        Shape& operator=(const ShapeGroup& source)
        {
            ShapeGroup temp(source);
            swap(temp);

            return *this;
        }

        ShapeGroup(ShapeGroup&&) = default;
        ShapeGroup& operator=(ShapeGroup&&) = default;

        void swap(ShapeGroup& other) noexcept
        {
            shapes_.swap(other.shapes_);
        }

        void add(ShapePtr shp)
        {
            shapes_.push_back(std::move(shp));
        }

        void draw() const override
        {
            for (const auto& s : shapes_)
                s->draw();
        }

        void move(int dx, int dy) override
        {
            for (const auto& s : shapes_)
                s->move(dx, dy);
        }

        size_t size() const
        {
            return shapes_.size();
        }

        iterator begin()
        {
            return shapes_.begin();
        }

        const_iterator begin() const
        {
            return shapes_.begin();
        }

        const_iterator cbegin()
        {
            return shapes_.cbegin();
        }

        const_iterator cbegin() const
        {
            return shapes_.cbegin();
        }

        iterator end()
        {
            return shapes_.end();
        }

        const_iterator end() const
        {
            return shapes_.end();
        }

        const_iterator cend()
        {
            return shapes_.cend();
        }

        const_iterator cend() const
        {
            return shapes_.cend();
        }
    };
}

// void overriding_begin_end()
// {
//      const std::vector<int> v1 = {1, 2, 3};

//     for (const auto& item : v1) // begin()
//         std::cout << item << " ";

//     // sugar syntax
//     for (auto it = v1.begin(); it != v1.end(); ++it)
//     {
//         const auto& item = *it;
//         std::cout << item << " ";
//     }
// }

#endif // SHAPEGROUP_HPP
