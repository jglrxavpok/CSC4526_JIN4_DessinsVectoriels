//
// Created by jglrxavpok on 12/05/2020.
//

#include "Group.h"
#include "Circle.h"
#include <cstring>
#include <iostream>
#include "imgui.h"

vector<std::unique_ptr<Shape>> loadShapes(const pugi::xml_node node) {
    std::vector<std::unique_ptr<Shape>> elements(0);
    for(const auto& node : node.children()) {
        if(strcmp(node.name(), "Circle") == 0) {
            elements.emplace_back(new Circle(node));
        } else if(strcmp(node.name(), "Group") == 0) {
            elements.emplace_back(new Group(node));
        }
    }
    return elements;
}

Group::Group(pugi::xml_node node): Group(node.attribute("label").as_string(),
                                         node.attribute("x").as_int(),
                                         node.attribute("y").as_int(),
                                         std::move(loadShapes(node))) {}

Group::Group(string label, int x, int y, vector<std::unique_ptr<Shape>> elements): Shape(ShapeType::GroupType, std::move(label), x, y), elements(std::move(elements)) {}

void Group::toXML(pugi::xml_node& target) const {
    Shape::toXML(target);
    target.set_name("Group");
    for(const auto& shape : getElements()) {
        pugi::xml_node shapeNode = target.append_child(":unnamed");
        shape->toXML(shapeNode);
    }
}

void Group::computeAbsolute(CoordinateMap<Shape>& coordinates, int absoluteX, int absoluteY) const {
    coordinates[this] = sf::Vector2i(getX()+absoluteX, getY()+absoluteY);

    for(const auto& child : getElements()) {
        if(child->getType() == ShapeType::GroupType) {
            if(Group* group = dynamic_cast<Group*>(child.get())) {
                group->computeAbsolute(coordinates, getX()+absoluteX, getY()+absoluteY);
            }
        } else {
            int childAbsoluteX = child->getX() + getX() + absoluteX;
            int childAbsoluteY = child->getY() + getY() + absoluteY;
            coordinates[child] = sf::Vector2i(childAbsoluteX, childAbsoluteY);
        }
    }
}

void Group::render(vector<sf::Shape*>& shapes, const CoordinateMap<Shape>& coordinates) {
    for(const auto& child : getElements()) {
        child->render(shapes, coordinates);
    }
}

bool Group::renderImGuiComponents(CoordinateMap<Shape>& coordinates) {
    return false;
}

bool Group::renderHierarchy(CoordinateMap<Shape>& coordinates) const {
    bool needRefresh = false;
    for(auto& shape : getElements()) {
        if(shape->renderElement(const_cast<Group *>(this), coordinates, needRefresh)) {
            ImGui::TreePop();
        }
    }

    return needRefresh;
}

bool Group::renderElement(Group* parent, CoordinateMap<Shape> &coordinates, bool &needRefresh) {
    if(Shape::renderElement(parent, coordinates, needRefresh)) {
        needRefresh |= renderHierarchy(coordinates);
        return true;
    }
    return false;
}

std::unique_ptr<Shape> Group::clone() {
    vector<unique_ptr<Shape>> cloneElements;
    Group* clone = new Group(label+" (Copy)", x, y, std::move(cloneElements));
    for(const auto& shape : getElements()) {
        clone->add(shape->clone());
    }
    return unique_ptr<Group>(clone);
}

void Group::add(Shape* shape) {
    elements.emplace_back(shape);
}

void Group::add(unique_ptr<Shape>&& shape) {
    elements.emplace_back(std::move(shape));
}
