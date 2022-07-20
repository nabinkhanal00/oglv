#include "Shape2D.hpp"
#include "Angel.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include <iostream>

Cube::Cube(unsigned int length, unsigned int thickness):thickness(thickness){
    points.push_back(oglm::vec3<int>(0.0f, 0.0f, 0.0f));
    points.push_back(oglm::vec3<int>(100.0f, 0.0f, 0.0f));
    points.push_back(oglm::vec3<int>(0.0f, 100.0f, 0.0f));
    points.push_back(oglm::vec3<int>(0.0f, 0.0f, 100.0f));
    points.push_back(oglm::vec3<int>(0.0f, 100.0f, 100.0f));
    points.push_back(oglm::vec3<int>(100.0f, 100.0f, 0.0f));
    points.push_back(oglm::vec3<int>(100.0f, 0.0f, 100.0f));
    points.push_back(oglm::vec3<int>(100.0f, 100.0f, 100.0f));
}

void Cube::animate(){
    for(oglm::vec3<int> point : points){
       std::cout << "1"; 
    }
}

void Cube::draw(){
    
}
void Cube::translate(int x, int y, int z) {}
void Cube::translate(oglm::vec3<int> factor) {}
void Cube::rotate(int radians, int x, int y, int z) {}
void Cube::rotate(int radians, oglm::vec3<int> factor) {}
void Cube::scale(int x, int y, int z) {}
void Cube::scale(oglm::vec3<int> factor) {}
bool Cube::isCompleted() { return false; }
void Cube::pause() {}
void Cube::reset() {}
void Cube::increaseSpeed(int speed) {}
void Cube::decreaseSpeed(int speed) {}

Cube::~Cube(){}