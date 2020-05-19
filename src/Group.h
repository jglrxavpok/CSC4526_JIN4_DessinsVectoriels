//
// Created by jglrxavpok on 14/05/2020.
//

#ifndef JIN4_GROUP_H
#define JIN4_GROUP_H
#include "Shapes.h"
#include "CoordinateMap.h"

class Group: public Shape {
private:
    std::vector<std::unique_ptr<Shape>> elements;
    bool renderHierarchy(CoordinateMap<Shape>& coordinates) const;

public:
    explicit Group(string label, int x, int y, vector<std::unique_ptr<Shape>> elements);
    explicit Group(pugi::xml_node node);

    void computeAbsolute(CoordinateMap<Shape>& coordinates, int absoluteX = 0, int absoluteY = 0) const;
    void render(vector<sf::Shape*> &shapes, const CoordinateMap<Shape>& coordinates) override;
    bool renderImGuiComponents(CoordinateMap<Shape>& coordinates) override;
    unique_ptr<Shape> clone() override;
    void toXML(pugi::xml_node& target) const override;

    void add(Shape* shape);
    void add(unique_ptr<Shape>&& shape);

    const vector<std::unique_ptr<Shape>>& getElements() const {
        return elements;
    }

    bool renderElement(Group* parent, CoordinateMap<Shape> &coordinates, bool &needRefresh) override;
};
#endif //JIN4_GROUP_H
