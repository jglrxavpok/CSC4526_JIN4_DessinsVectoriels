#include <gtest/gtest.h>
#include "Shapes.h"
#include "Group.h"
#include "Circle.h"

namespace myNameSpace {

    TEST(TestReadXML, TestCircle) {
        std::string s = R"(<?xml version = "1.0"?>
            <Circle label="testCircle" x="0" y="1" r="2" color="Black"/>)";
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(s.c_str());
        EXPECT_NE(0, result);
        unique_ptr<Circle> circle = make_unique<Circle>(doc.child("Circle"));
        EXPECT_EQ("testCircle", circle->getLabel());
        EXPECT_EQ(0, circle->getX());
        EXPECT_EQ(1, circle->getY());
        EXPECT_EQ(2, circle->getRadius());
        EXPECT_EQ("Black", circle->getColor().getName());
    }

    TEST(TestReadXML, TestGroup) {
        std::string s = R"(<?xml version = "1.0"?>
                            <Group label="testGroup" x="0" y="1">
                                 <Circle label="testCircle1" x="2" y="3" r="4" color="Black"/>
                                 <Circle label="testCircle2" x="5" y="6" r="7" color="Black"/>
                            </Group>)";
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(s.c_str());
        EXPECT_NE(0, result);

        unique_ptr<Group> group = make_unique<Group>(doc.child("Group"));
        EXPECT_EQ("testGroup", group->getLabel());
        EXPECT_EQ(0, group->getX());
        EXPECT_EQ(1, group->getY());

        EXPECT_EQ(2, group->getElements().size());

        auto* circle1 = (Circle*) group->getElements()[0].get();
        EXPECT_EQ("testCircle1", circle1->getLabel());
        EXPECT_EQ(2, circle1->getX());
        EXPECT_EQ(3, circle1->getY());
        EXPECT_EQ(4, circle1->getRadius());
        EXPECT_EQ("Black", circle1->getColor().getName());

        auto* circle2 = (Circle*) group->getElements()[1].get();
        EXPECT_EQ("testCircle2", circle2->getLabel());
        EXPECT_EQ(5, circle2->getX());
        EXPECT_EQ(6, circle2->getY());
        EXPECT_EQ(7, circle2->getRadius());
        EXPECT_EQ("Black", circle2->getColor().getName());
    }

    TEST(TestReadXML, TestGroup1) {
        std::string s = R"(<?xml version = "1.0"?>
                                <Group label="testGroup1" x="0" y="1">
                                     <Circle label="testCircle" x="2" y="3" r="4" color="Black"/>
                                     <Group label="testGroup2" x="5" y="6"/>
                                </Group>)";
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(s.c_str());
        EXPECT_NE(0, result);

        unique_ptr<Group> group = make_unique<Group>(doc.child("Group"));
        EXPECT_EQ("testGroup1", group->getLabel());
        EXPECT_EQ(0, group->getX());
        EXPECT_EQ(1, group->getY());

        EXPECT_EQ(2, group->getElements().size());

        auto* circle1 = (Circle *) group->getElements()[0].get();
        EXPECT_EQ("testCircle", circle1->getLabel());
        EXPECT_EQ(2, circle1->getX());
        EXPECT_EQ(3, circle1->getY());
        EXPECT_EQ(4, circle1->getRadius());
        EXPECT_EQ("Black", circle1->getColor().getName());

        auto* testGroup2 = group->getElements()[1].get();
        EXPECT_EQ("testGroup2", testGroup2->getLabel());
        EXPECT_EQ(5, testGroup2->getX());
        EXPECT_EQ(6, testGroup2->getY());
    }

    TEST(TestAbsoluteCoord, Test1) {
        vector<std::unique_ptr<Shape>> g1Elements;
        vector<std::unique_ptr<Shape>> g2Elements;
        Circle* c21 = new Circle("C21", 4, 5, 1, Color::fromName("Black"));
        Circle* c22 = new Circle("C22", 7, 8, 1, Color::fromName("Black"));
        g2Elements.emplace_back(c21);
        g2Elements.emplace_back(c22);

        Group* g2 = new Group("G2", 2, 3, std::move(g2Elements));
        g1Elements.emplace_back(g2);

        Group* g1 = new Group("G1", 0, 1, std::move(g1Elements));

        CoordinateMap<Shape> coordinates;
        g1->computeAbsolute(coordinates);

        EXPECT_EQ(0, coordinates[g1].x);
        EXPECT_EQ(1, coordinates[g1].y);

        EXPECT_EQ(2+0, coordinates[g2].x);
        EXPECT_EQ(3+1, coordinates[g2].y);

        EXPECT_EQ(4+2+0, coordinates[c21].x);
        EXPECT_EQ(5+3+1, coordinates[c21].y);

        EXPECT_EQ(7+2+0, coordinates[c22].x);
        EXPECT_EQ(8+3+1, coordinates[c22].y);
    }
}
