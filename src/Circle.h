//
// Created by jglrxavpok on 14/05/2020.
//

#ifndef JIN4_CIRCLE_H
#define JIN4_CIRCLE_H
#include "Shapes.h"
#include "CoordinateMap.h"

class Circle: public Shape {
private:
    int radius;
    Color color;

public:
    explicit Circle(string label, int x, int y, int radius, Color color);
    explicit Circle(pugi::xml_node node);

    void render(vector<sf::Shape*> &shapes, const CoordinateMap<Shape>& coordinates) override;
    bool renderImGuiComponents(CoordinateMap<Shape>& coordinates) override;
    unique_ptr<Shape> clone() override;
    void toXML(pugi::xml_node& target) const override;

    const Color getColor() const {
        return color;
    };

    int getRadius() const {
        return radius;
    };
};
#endif //JIN4_CIRCLE_H
