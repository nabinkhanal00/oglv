// #include "Shape2D.hpp"
#include "Angel.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Cube::Cube() {
	points.push_back(oglm::vec3(-0.5f, -0.5f, -0.5f));
	points.push_back(oglm::vec3(0.5f, -0.5f, -0.5f));
	points.push_back(oglm::vec3(0.5f, 0.5f, -0.5f));
	points.push_back(oglm::vec3(-0.5f, 0.5f, -0.5f));
	points.push_back(oglm::vec3(-0.5f, -0.5f, 0.5f));
	points.push_back(oglm::vec3(0.5f, -0.5f, 0.5f));
	points.push_back(oglm::vec3(0.5f, 0.5f, 0.5f));
	points.push_back(oglm::vec3(-0.5f, 0.5f, 0.5f));

	indices.push_back(oglm::vec2i(0, 1));
	indices.push_back(oglm::vec2i(1, 2));
	indices.push_back(oglm::vec2i(2, 3));
	indices.push_back(oglm::vec2i(0, 3));

	indices.push_back(oglm::vec2i(0, 4));
	indices.push_back(oglm::vec2i(1, 5));
	indices.push_back(oglm::vec2i(2, 6));
	indices.push_back(oglm::vec2i(3, 7));

	indices.push_back(oglm::vec2i(4, 5));
	indices.push_back(oglm::vec2i(5, 6));
	indices.push_back(oglm::vec2i(6, 7));
	indices.push_back(oglm::vec2i(7, 4));
}

void Cube::animate() {}

void Cube::draw() {
	static int num = 0;
	for (auto &i : indices) {
		Line l(points[i.x].x, points[i.x].y, points[i.y].x, points[i.y].y);
		l.draw();
		if (num == 0) {
			std::cout << points[i.x] << "\t" << points[i.y] << std::endl;
		}
	}
	if (num == 0)
		num = 1;
}

void Cube::translate(float x, float y, float z) {}

void Cube::translate(oglm::vec3f factor) {
	oglm::mat4 trans_mat = oglm::translate(factor);
	for (auto &i : points) {
		oglm::vec4f v(i.x, i.y, i.z, 1);
		v = trans_mat * v;
		i = oglm::vec3f(v.x, v.y, v.z);
	}
}

void Cube::rotate(float degree, float x, float y, float z) {}
void Cube::rotate(float degree, oglm::vec3 factor) {
	oglm::mat4 scal = oglm::scale(oglm::vec3(1.0f, 1.0f, 1.0f));
	// std::cout << "Scale" << std::endl;
	// std::cout << scal << std::endl;

	oglm::mat4 rot = oglm::rotate(degree, factor);

	// std::cout << "Rotate" << std::endl;
	// std::cout << rot << std::endl;

	oglm::mat4 trans = oglm::translate(oglm::vec3(0.0f, 0.0f, 2.0f));

	// std::cout << "Translate" << std::endl;
	// std::cout << trans << std::endl;

	oglm::mat4 look = oglm::lookAt(oglm::vec3(0.0f, 0.0f, 0.0f),
	                               oglm::vec3(0.0f, 0.0f, -0.1f),
	                               oglm::vec3(0.0f, 1.0f, 0.0f));

	// std::cout << "Look At" << std::endl;
	// std::cout << look << std::endl;

	oglm::mat4 pers = oglm::perspective(
	    (float)M_PI_2, Angel::getWidth() / (float)Angel::getHeight(), 0.1f,
	    100.0f);

	// std::cout << "Perspective" << std::endl;
	// std::cout << pers << std::endl;

	for (auto &i : points) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = pers * look * trans * rot * scal * v;
		v /= v.w;
		i = oglm::vec3(v.x, v.y, v.z);
	}
}

void Cube::scale(float x, float y, float z) {}
void Cube::scale(oglm::vec3 factor) {
	oglm::mat4 scale_mat = oglm::scale(factor);
	for (auto &i : points) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = scale_mat * v;
		i = oglm::vec3f((v.x), (v.y), (v.z));
	}
}

bool Cube::isCompleted() { return false; }
void Cube::pause() {}
void Cube::reset() {}
void Cube::increaseSpeed(int speed) {}
void Cube::decreaseSpeed(int speed) {}

Cube::~Cube() {}
