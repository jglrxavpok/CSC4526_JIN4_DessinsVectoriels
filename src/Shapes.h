//
// Created by jglrxavpok on 30/04/2020.
//

#ifndef JIN4_SHAPES_H
#define JIN4_SHAPES_H

#include <vector>
#include <string>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
#include "Colors.h"
#include "CoordinateMap.h"

using namespace std;

enum ShapeType {
    GroupType,
    CircleType,
};

class Group;

class Shape {
protected:
    string label;
    int x;
    int y;
    ShapeType type;

public:
    explicit Shape(ShapeType type, string label, int x, int y): type(type), label(std::move(label)), x(x), y(y) {};

    virtual void render(vector<sf::Shape*>& shapes, const CoordinateMap<Shape>& coordinates) = 0;

    virtual bool renderImGuiComponents(CoordinateMap<Shape>& coordinates) = 0;

    virtual bool renderElement(Group* parent, CoordinateMap<Shape>& coordinates, bool& needRefresh);

    virtual unique_ptr<Shape> clone() = 0;

    virtual void toXML(pugi::xml_node& target) const;

    ShapeType getType() const {
        return type;
    };

    string getLabel() const {
        return label;
    };

    int getX() const {
        return x;
    };

    int getY() const {
        return y;
    };

    virtual ~Shape() = default;
};

#endif //JIN4_SHAPES_H
