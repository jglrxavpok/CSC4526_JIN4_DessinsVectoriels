//
// Created by jglrxavpok on 12/05/2020.
//

#include <utility>
#include <iostream>
#include <imgui.h>
#include "Circle.h"
#include "Group.h"

Circle::Circle(pugi::xml_node node): Circle(node.attribute("label").as_string(),
                                            node.attribute("x").as_int(),
                                            node.attribute("y").as_int(),
                                            node.attribute("r").as_int(),
                                            Color::fromName(node.attribute("color").as_string())) {}

Circle::Circle(string label, int x, int y, int radius, Color color): Shape(ShapeType::CircleType, std::move(label), x, y), radius(radius), color(color) {}

void Circle::toXML(pugi::xml_node& target) const {
    Shape::toXML(target);
    target.set_name("Circle");
    target.append_attribute("color").set_value(color.getName().c_str());
    target.append_attribute("r").set_value(radius);
}

void Circle::render(vector<sf::Shape*>& shapes, const CoordinateMap<Shape>& coordinates) {
    sf::CircleShape* circle = new sf::CircleShape(getRadius());
    const auto& coords = coordinates[this];
    circle->setPosition(coords.x-getRadius(), coords.y-getRadius());

    circle->setFillColor(getColor().toSFML());

    shapes.push_back(circle);
}

bool Circle::renderImGuiComponents(CoordinateMap<Shape>& coordinates) {
    using namespace ImGui;

    bool refresh = false;

    std::string colorName = color.getName();
    if(BeginCombo("Color", colorName.c_str())) {
        for(const auto& defaultColor : Color::defaultColors) {
            if(Selectable(defaultColor.getName().c_str())) {
                color = defaultColor;
            }
        }
        EndCombo();
    }

    InputInt("Radius", &radius);


    return refresh;
}

unique_ptr<Shape> Circle::clone() {
    return make_unique<Circle>(label+" (Copy)", x, y, radius, color);
}