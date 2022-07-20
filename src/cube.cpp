#include "Shape2D.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include "Angel.hpp"
#include <iostream>

Cube::Cube(unsigned int thickness, unsigned int windowWidth, unsigned int windowHeight):angel(windowWidth, windowHeight){
    lines[0] = Line(0, 0, 200, 200, thickness, windowWidth, windowHeight);
}

void Cube::animate(){
    for(Line l : lines){
        l.animate();
    }
}

int main(){
    return 0;
}