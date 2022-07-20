#include "Shape2D.hpp"
#include "Angel.hpp"
#include "Cube.hpp"
#include <iostream>

Cube::Cube(unsigned int thickness){
    //lines[0] = Line(0, 0, 1, 1, thickness);
    std::cout <<"asdf" << std::endl;
}

void Cube::translate(int x, int y) {}
void Cube::translate(oglm::vec2<int> factor) {}
void Cube::rotate(int radians, int x, int y) {}
void Cube::rotate(int radians, oglm::vec2<int> factor) {}
void Cube::scale(int x, int y) {}
void Cube::scale(oglm::vec2<int> factor) {}
bool Cube::isCompleted() { return false; }
void Cube::pause() {}
void Cube::reset() {}
void Cube::increaseSpeed(int speed) {}
void Cube::decreaseSpeed(int speed) {}

Cube::~Cube(){}