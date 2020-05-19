//
// Created by jglrxavpok on 12/05/2020.
//

#ifndef JIN4_COLORS_H
#define JIN4_COLORS_H
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Color {
private:
    string name;
    sf::Color correspondingSFML;

    Color(string name, sf::Color color): name(std::move(name)), correspondingSFML(color) {}

public:
    string getName() const {
        return name;
    };

    const sf::Color toSFML() const {
        return correspondingSFML;
    };

    static Color fromName(string name) {
        if(name == "Red") {
            return Color(name, sf::Color::Red);
        }
        if(name == "Black") {
            return Color(name, sf::Color::Black);
        }
        if(name == "Magenta") {
            return Color(name, sf::Color::Magenta);
        }
        if(name == "White") {
            return Color(name, sf::Color::White);
        }
        if(name == "Yellow") {
            return Color(name, sf::Color::Yellow);
        }
        if(name == "Cyan") {
            return Color(name, sf::Color::Cyan);
        }
        if(name == "Green") {
            return Color(name, sf::Color::Green);
        }
        return Color("unknown", sf::Color::Transparent);
    };


    static std::vector<Color> defaultColors;
};



#endif //JIN4_COLORS_H
