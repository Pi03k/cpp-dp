#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>
#include <typeindex>

#include "rectangle.hpp"
#include "shape.hpp"
#include "shape_readers_writers/rectangle_reader_writer.hpp"
#include "shape_readers_writers/square_reader_writer.hpp"
#include "square.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

// unique_ptr<Shape> create_shape(const string& id)
// {
//     if (id == Rectangle::id)
//         return make_unique<Rectangle>();
//     else if (id == Square::id)
//         return make_unique<Square>();

//     throw runtime_error("Unknown shape id");
// }

// unique_ptr<ShapeReaderWriter> create_shape_rw(Shape& shape)
// {
//     if (typeid(shape) == typeid(Rectangle))
//         return make_unique<RectangleReaderWriter>();
//     else if (typeid(shape) == typeid(Square))
//         return make_unique<SquareReaderWriter>();

//     throw runtime_error("Unknown shape id");
// }

namespace Draft
{    
    template <
        typename Product, 
        typename Key = std::string, 
        typename Creator = std::function<std::unique_ptr<Product>()>
    >
    class GenericFactory
    {
        std::unordered_map<Key, Creator> creators_;
    public:
        bool register_creator(const Key& id, Creator creator)
        {
            return creators_.insert(make_pair(id, creator)).second;
        }

        std::unique_ptr<Product> create(const Key& id)
        {
            auto& creator = creators_.at(id);
            return creator();
        }
    };

    using ShapeFactory = GenericFactory<Shape>;
    using ShapeReaderWriterFactory = GenericFactory<ShapeReaderWriter, std::type_index>; 

    template <typename T>
    type_index make_type_index(const T& obj)
    {
        return type_index{typeid(obj)};
    }

    template <typename T>
    type_index make_type_index()
    {
        return type_index{typeid(T)};
    }
}

class GraphicsDoc
{
    vector<unique_ptr<Shape>> shapes_;
    Draft::ShapeFactory& shape_factory_;
    Draft::ShapeReaderWriterFactory& shape_rw_factory_;

public:
    GraphicsDoc(Draft::ShapeFactory& sf, Draft::ShapeReaderWriterFactory& srwf) 
        : shape_factory_{sf}, shape_rw_factory_{srwf}
    {}

    void add(unique_ptr<Shape> shp)
    {
        shapes_.push_back(move(shp));
    }

    void render()
    {
        for (const auto& shp : shapes_)
            shp->draw();
    }

    void load(const string& filename)
    {
        ifstream file_in{filename};

        if (!file_in)
        {
            cout << "File not found!" << endl;
            exit(1);
        }

        while (file_in)
        {
            string shape_id;
            file_in >> shape_id;

            if (!file_in)
                return;

            cout << "Loading " << shape_id << "..." << endl;

            auto shape = shape_factory_.create(shape_id);
            auto shape_rw = shape_rw_factory_.create(Draft::make_type_index(*shape));

            shape_rw->read(*shape, file_in);

            shapes_.push_back(move(shape));
        }
    }

    void save(const string& filename)
    {
        ofstream file_out{filename};

        for (const auto& shp : shapes_)
        {
            auto shape_rw = create_shape_rw(*shp);
            shape_rw->write(*shp, file_out);
        }
    }
};



int main()
{
    // bootstraping
    Draft::ShapeFactory shape_factory;
    
    shape_factory.register_creator(Square::id, &make_unique<Square>);

    Draft::ShapeReaderWriterFactory shape_rw_factory;
    shape_rw_factory.register_creator(Draft::make_type_index<Rectangle>(), &make_unique<RectangleReaderWriter>);
    shape_rw_factory.register_creator(Draft::make_type_index<Square>(), &make_unique<SquareReaderWriter>);

    cout << "Start..." << endl;

    GraphicsDoc doc{shape_factory, shape_rw_factory};

    doc.load("drawing.txt");

    cout << "\n";

    doc.render();

    doc.save("new_drawing.txt");
}
