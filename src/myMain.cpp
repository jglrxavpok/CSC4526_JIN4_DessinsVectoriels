#include "myMain.h"
#include "Shapes.h"
#include "Group.h"
#include <pugixml.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

using namespace std;

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

bool renderImgui(std::unique_ptr<Group>&, CoordinateMap<Shape>& coordinates);

int myMain()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("drawing.xml");

    pugi::xml_node drawing = doc.root();
    std::unique_ptr<Group> visage = std::make_unique<Group>(drawing);
    CoordinateMap<Shape> coordinates;
    visage->computeAbsolute(coordinates, WIDTH/2, HEIGHT/2);

    vector<sf::Shape*> shapes;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "visage.xml");

    ImGui::SFML::Init(window);

    // inversion axe Y
    sf::View view = window.getDefaultView();
    view.setSize(WIDTH, -HEIGHT);
    window.setView(view);

    sf::Clock deltaClock;
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        if(renderImgui(visage, coordinates)) { // refresh
            coordinates.clear();
            visage->computeAbsolute(coordinates, WIDTH/2, HEIGHT/2);
        }

        shapes.clear();
        visage->render(shapes, coordinates);

        window.clear(sf::Color::White);
        for(const auto* shape : shapes) {
            window.draw(*shape);
        }
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
}

void save(unique_ptr<Group>& baseGroup) {
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("Drawing");
    baseGroup->toXML(root);

    doc.save(cout);

    cout << "Saving result: " << doc.save_file("drawing.xml") << endl;
}

bool renderImgui(std::unique_ptr<Group>& baseGroup, CoordinateMap<Shape>& coordinates) {
    ImGui::Begin("Hierarchy");
    if(ImGui::Button("Save to \"drawing.xml\"")) {
        save(baseGroup);
    }
    bool refresh = false;
    if(baseGroup->renderElement(nullptr, coordinates, refresh)) {
        ImGui::TreePop();
    }
    ImGui::End();
    return refresh;
}
