//
// Created by jglrxavpok on 14/05/2020.
//

#include "Shapes.h"
#include "imgui.h"
#include "Group.h"

bool Shape::renderElement(Group* parent, CoordinateMap<Shape> &coordinates, bool &needRefresh) {
    bool open = ImGui::TreeNode(this->getLabel().c_str());
    if(open) {
        if(parent) {
            if(ImGui::Button("Copy")) {
                parent->add(clone());
                needRefresh |= true;
            }
        }

        if(ImGui::TreeNode("Absolute position")) {
            ImGui::InputInt("X", &coordinates[this].x);
            ImGui::InputInt("Y", &coordinates[this].y);
            ImGui::TreePop();
        }

        if(ImGui::TreeNode("Relative position")) {
            needRefresh |= ImGui::InputInt("X", &x);
            needRefresh |= ImGui::InputInt("Y", &y);
            ImGui::TreePop();
        }

        needRefresh |= renderImGuiComponents(coordinates);
    }
    return open;
}

void Shape::toXML(pugi::xml_node& target) const {
    target.append_attribute("label").set_value(label.c_str());
    target.append_attribute("x").set_value(x);
    target.append_attribute("y").set_value(y);
}