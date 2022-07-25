// #include "Shape2D.hpp"
#include "Angel.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <oglm.hpp>
#include <transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

Cube::Cube(unsigned int length, unsigned int thickness) : thickness(thickness) {
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
	Angel::set_perspective((float)M_PI_2, Angel::getWidth() / (float)Angel::getHeight(), 0.1, 100.0f);
	Angel::set_view(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
	for (auto &i : drawing_points) {
		glm::vec4 v(i.x, i.y, i.z, 1);
		v = Angel::pers *Angel::view* v;
		v /= v.w;
		i = oglm::vec3(v.x, v.y, v.z);
	}
	static int num = 0;
	for (auto &i : indices) {
		Line l(drawing_points[i.x].x, drawing_points[i.x].y, drawing_points[i.y].x, drawing_points[i.y].y);
		l.draw();
		// if (num == 0) {
		// 	std::cout << points[i.x] << "\t" << points[i.y] << std::endl;
		// }
	}
	if (num == 0)
		num = 1;
	drawing_points.clear();
}

void Cube::translate(float x, float y, float z) {}

void Cube::translate(oglm::vec3f factor) {
	oglm::mat4<float> trans_mat = oglm::translate(factor);
	for (auto &i : points) {
		oglm::vec4f v(i.x, i.y, i.z, 1);
		v = trans_mat * v;
		i = oglm::vec3f(v.x, v.y, v.z);
	}
}

void Cube::rotate(float degree, float x, float y, float z) {}
void Cube::rotate(float degree, oglm::vec3 factor) {
	oglm::mat4<float> scal = oglm::scale(oglm::vec3(1.0f, 1.0f, 1.0f));
	oglm::mat4<float> trans = oglm::translate(oglm::vec3(0.0f, 0.0f, 0.0f));
	oglm::mat4<float> rot = oglm::rotate(glfwGetTime()*30.0f,oglm::vec3(0.0f, 1.0f, 0.0f));
	// for(unsigned int i = 0; i < points.size(); i++)
 //  	  {
	// 	oglm::vec4 v(points[i].x, points[i].y, points[i].z, 1);
	// 	v = trans * rot * scal * v;
	// 	drawing_points[i] = oglm::vec3(v.x, v.y, v.z);
 //  	  }
	for (auto &i : points) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = trans * rot * scal * v;
		drawing_points.push_back(oglm::vec3(v.x, v.y, v.z));
	}
}

void Cube::scale(float x, float y, float z) {}
void Cube::scale(oglm::vec3 factor) {
	oglm::mat4<float> scale_mat = oglm::scale(factor);
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
