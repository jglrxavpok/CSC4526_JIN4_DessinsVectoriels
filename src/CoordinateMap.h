//
// Created by jglrxavpok on 14/05/2020.
//

#ifndef JIN4_COORDINATEMAP_H
#define JIN4_COORDINATEMAP_H
#include "SFML/System.hpp"

/// Classe d'aide pour accéder aux coordonnées absolues d'une Shape.
/// C'est probablement pas hyper propre comme façon de faire, donc on cache la misère dans une jolie abstraction
/// \tparam S
template<typename S>
class CoordinateMap {
private:
    map<const S*, sf::Vector2i> backingMap;

public:
    explicit CoordinateMap() = default;

    sf::Vector2i& operator[](const S* shape) {
        return backingMap[shape];
    }

    sf::Vector2i& operator[](S* shape) {
        return backingMap[shape];
    }

    sf::Vector2i& operator[](const std::unique_ptr<const S>& shape) {
        return backingMap[shape.get()];
    }

    sf::Vector2i& operator[](const std::unique_ptr<S>& shape) {
        return backingMap[shape.get()];
    }

    const sf::Vector2i& operator[](S * shape) const {
        return backingMap.at(shape);
    }

    const sf::Vector2i& operator[](const std::unique_ptr<S>& shape) const {
        return backingMap.at(shape.get());
    }

    const sf::Vector2i& operator[](const std::unique_ptr<const S>& shape) const {
        return backingMap.at(shape.get());
    }

    void clear() {
        backingMap.clear();
    }
};


#endif //JIN4_COORDINATEMAP_H
