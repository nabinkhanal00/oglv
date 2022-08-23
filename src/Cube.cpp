// #include "Shape2D.hpp"
#include "Angel.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <oglm.hpp>
#include <transform.hpp>
#include <unordered_map>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

oglm::vec3 fragPos;
Cube::Cube(unsigned int length, unsigned int thickness) : thickness(thickness) {
	points.push_back(oglm::vec3(-0.5f, -0.5f, -0.5f));
	points.push_back(oglm::vec3(0.5f, -0.5f, -0.5f));
	points.push_back(oglm::vec3(0.5f, 0.5f, -0.5f));
	points.push_back(oglm::vec3(-0.5f, 0.5f, -0.5f));
	points.push_back(oglm::vec3(-0.5f, -0.5f, 0.5f));
	points.push_back(oglm::vec3(0.5f, -0.5f, 0.5f));
	points.push_back(oglm::vec3(0.5f, 0.5f, 0.5f));
	points.push_back(oglm::vec3(-0.5f, 0.5f, 0.5f));

	// //front
	indices.push_back(oglm::vec2i(7, 4));
	indices.push_back(oglm::vec2i(4, 5));
	indices.push_back(oglm::vec2i(5, 6));
	indices.push_back(oglm::vec2i(6, 7));
	//
	// // back
	indices.push_back(oglm::vec2i(3, 2));
	indices.push_back(oglm::vec2i(2, 1));
	indices.push_back(oglm::vec2i(1, 0));
	indices.push_back(oglm::vec2i(0, 3));

	// top
	indices.push_back(oglm::vec2i(3, 7));
	indices.push_back(oglm::vec2i(7, 6));
	indices.push_back(oglm::vec2i(6, 2));
	indices.push_back(oglm::vec2i(2, 3));
	//
	// bottom
	indices.push_back(oglm::vec2i(0, 1));
	indices.push_back(oglm::vec2i(1, 5));
	indices.push_back(oglm::vec2i(5, 4));
	indices.push_back(oglm::vec2i(4, 0));

	// left
	indices.push_back(oglm::vec2i(7, 3));
	indices.push_back(oglm::vec2i(3, 0));
	indices.push_back(oglm::vec2i(0, 4));
	indices.push_back(oglm::vec2i(4, 7));

	// right
	indices.push_back(oglm::vec2i(6, 5));
	indices.push_back(oglm::vec2i(5, 1));
	indices.push_back(oglm::vec2i(1, 2));
	indices.push_back(oglm::vec2i(2, 6));
}

void Cube::rasterize() {
	float offset = 0.05f;
	for (auto &i : indices) {
		float x0 = points[i.x].x;
		float y0 = points[i.x].y;
		float z0 = points[i.x].z;
		float x1 = points[i.y].x;
		float y1 = points[i.y].y;
		float z1 = points[i.y].z;
		if (x0 == -x1) {
			float temp = y0;
			while (temp < 0.5) {
				vertexBuffer.push_back(oglm::vec3(x0, temp, z0));
				vertexBuffer.push_back(oglm::vec3(x1, temp, z1));
				temp += offset;
			}
			temp = z0;
			while (temp < 0.5) {
				vertexBuffer.push_back(oglm::vec3(x0, y0, temp));
				vertexBuffer.push_back(oglm::vec3(x1, y1, temp));
				temp += offset;
			}
		} else if (z0 == -z1) {
			float temp = y0;
			while (temp < 0.5) {
				vertexBuffer.push_back(oglm::vec3(x0, temp, z0));
				vertexBuffer.push_back(oglm::vec3(x1, temp, z1));
				temp += offset;
			}
		}
	}
}

void fillBottomFlatTriangle(const oglm::vec3 &_v1, const oglm::vec3 &_v2,
                            const oglm::vec3 &_v3, const oglm::vec4 &color) {
	oglm::vec3i v1 = Angel::map(_v1);
	oglm::vec3i v2 = Angel::map(_v2);
	oglm::vec3i v3 = Angel::map(_v3);
	float invslope1 = float(v2.x - v1.x) / (v2.y - v1.y);
	float invslope2 = float(v3.x - v1.x) / (v3.y - v1.y);


	float curx1 = v1.x;
	float curx2 = v1.x;

	for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++) {
		oglm::vec2 p0 = Angel::demap(curx1, scanlineY);
		oglm::vec2 p1 = Angel::demap(curx2, scanlineY);
		Line l(p0.x, p0.y, p1.x, p1.y);
		l.draw(color);
		curx1 += invslope1;
		curx2 += invslope2;
	}
}

void fillTopFlatTriangle(const oglm::vec3 &_v1, const oglm::vec3 &_v2,
                         const oglm::vec3 &_v3, const oglm::vec4 &color) {

	oglm::vec3i v1 = Angel::map(_v1);
	oglm::vec3i v2 = Angel::map(_v2);
	oglm::vec3i v3 = Angel::map(_v3);
	float invslope1 = float(v3.x - v1.x) / (v3.y - v1.y);
	float invslope2 = float(v3.x - v2.x) / (v3.y - v2.y);

	float curx1 = v3.x;
	float curx2 = v3.x;

	for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--) {
		oglm::vec2 p0 = Angel::demap(curx1, scanlineY);
		oglm::vec2 p1 = Angel::demap(curx2, scanlineY);
		Line l(p0.x, p0.y, p1.x, p1.y);
		l.draw(color);
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}

void drawTriangle(std::vector<oglm::vec3> &points, const oglm::vec4 &color) {
	std::sort(points.begin(), points.end(),
	          [](oglm::vec3 a, oglm::vec3 b) { return a.y < b.y; });
	oglm::vec3 v1 = points.at(0);
	oglm::vec3 v2 = points.at(1);
	oglm::vec3 v3 = points.at(2);
	Line l1(v1.x, v1.y, v2.x, v2.y);
	l1.draw(color);
	Line l2(v2.x, v2.y, v3.x, v3.y);
	l2.draw(color);
	Line l3(v3.x, v3.y, v1.x, v1.y);
	l3.draw(color);
}
void fillTriangle(std::vector<oglm::vec3> &points, const oglm::vec4 &color) {
	std::sort(points.begin(), points.end(),
	          [](oglm::vec3 a, oglm::vec3 b) { return a.y < b.y; });
	oglm::vec3 v1 = points.at(0);
	oglm::vec3 v2 = points.at(1);
	oglm::vec3 v3 = points.at(2);

	/* here we know that v1.y <= v2.y <= v3.y */
	/* check for trivial case of bottom-flat triangle */
	if (fabs(v2.y - v3.y) <= 0.005) {
		fillBottomFlatTriangle(v1, v2, v3, color);
	}
	/* check for trivial case of top-flat triangle */
	else if (fabs(v1.y - v2.y) <= 0.005) {
		fillTopFlatTriangle(v1, v2, v3, color);
	} else {
		/* general case - split the triangle in a topflat and bottom-flat
		 * one */
		oglm::vec3 *v4 = new oglm::vec3(
		    (v1.x +
		     ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x)),
		    v2.y, v2.z);
		fillBottomFlatTriangle(v1, v2, *v4, color);
		fillTopFlatTriangle(v2, *v4, v3, color);
	}
}
oglm::vec3 calculateNormal(std::vector<oglm::vec3> &points) {
	oglm::vec3 p1 = points.at(0);
	oglm::vec3 p2 = points.at(1);
	oglm::vec3 p3 = points.at(2);
	oglm::vec3 p1p2 = p2 - p1;
	oglm::vec3 p1p3 = p3 - p1;
	float x1 = p1p2.x;
	float y1 = p1p2.y;
	float z1 = p1p2.z;
	float x2 = p1p3.x;
	float y2 = p1p3.y;
	float z2 = p1p3.z;
	oglm::vec3 norm((y1 * z2 - y2 * z1), (x2 * z1 - x1 * z2),
	                (x1 * y2 - x2 * y1));
	return norm;
}
inline oglm::vec3 reflect(const oglm::vec3 &I, const oglm::vec3 &N) {
	return I - 2.0f * oglm::dot(N, I) * N;
}

oglm::vec4 phong(const oglm::vec3 &frag, const oglm::vec3 &normal,
                 const oglm::vec3 &lightPos, const oglm::vec4 &lightColor,
                 const oglm::vec4 &objectColor) {
	oglm::vec3 lc = oglm::vec3(lightColor.x, lightColor.y, lightColor.z);

	oglm::vec3 oc = oglm::vec3(objectColor.x, objectColor.y, objectColor.z);
	float ambientStrength = 0.1;
	oglm::vec3 ambient = ambientStrength * lc;
	// diffuse
	oglm::vec3 norm = oglm::normalize(normal);
	oglm::vec3 lightDir = normalize(lightPos - fragPos);
	float diff = std::max(oglm::dot(norm, lightDir), 0.0f);
	oglm::vec3 diffuse = diff * lc;
	oglm::vec3 result = (ambient + diffuse) * oc;
	return oglm::vec4(result.x, result.y, result.z, 1.0f);
}

void Cube::draw(bool lineFill, bool isLightedObject, const oglm::vec4 &color,
                const oglm::vec3 &lightPos, const oglm::vec4 &lightColor) {
	float val = 0.0f;

	std::vector<oglm::vec3> triangle;
	std::vector<oglm::vec3> fragPos;
	for (auto &i : vertexBuffer) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = model * v;
		fragPos.push_back(oglm::vec3(v.x, v.y, v.z));

		v = Angel::pers * Angel::view * v;
		if (v.w > val) {
			v.x /= v.w;
			v.y /= v.w;
			v.z /= v.w;
		}
		currentBuffer.push_back(oglm::vec4(v.x, v.y, v.z, v.w));

	}

	int c = 0;
	oglm::vec3 frag0, frag1, frag2;
	for (size_t i = 0; i < currentBuffer.size() - 1; i = i + 2) {
		float x0 = currentBuffer[i].x;
		float y0 = currentBuffer[i].y;
		float z0 = (currentBuffer[i].z);
		float x1 = currentBuffer[i + 1].x;
		float y1 = currentBuffer[i + 1].y;
		float z1 = (currentBuffer[i + 1].z);
		float slope = (y1 - y0) / (x1 - x0);
		// std::cout << clipping << std::endl;
		if (clipping) {
			if (z1 >= val && z0 < val) {
				z0 = val;
				if (x0 < 0) {
					x0 = -1.0f;
					y0 = y1 + slope * (x0 - x1);
				} else {
					x0 = 1.0f;
					y0 = y1 + slope * (x0 - x1);
				}
			} else if (z0 >= val && z1 < val) {

				if (x1 < 0) {
					x1 = -1.0f;
					y1 = y0 + slope * (x1 - x0);
				} else {
					x1 = 1.0f;
					y1 = y0 + slope * (x1 - x0);
				}
				z1 = val;
			}
			int precision = 1000;
			if (y0 < -precision)
				y0 = -1;
			if (y0 > precision)
				y0 = 1;
			if (y1 < -precision)
				y1 = -1;
			if (y1 > precision)
				y1 = 1;
			if (z0 >= val && z1 >= val && x0 > -1.0 && x1 < 1.0) {
				Line l(x0, y0, x1, y1, 5);
				l.draw();
			}
		} else {

			c++;

			if (c % 2 == 0) {
				frag2 = fragPos[i + 1];
				triangle.push_back(oglm::vec3(x1, y1, z1));
				oglm::vec3 normal = calculateNormal(triangle);
				oglm::vec3 camDir = Angel::camFocus - Angel::camPos;
				float dotProduct = oglm::dot(normal, camDir);
				float angle = acos(dotProduct) * 180.0 / M_PI;
				oglm::vec3 frag = (frag0 + frag1 + frag2) / 3;
				if (angle >= 90) {
					if (isLightedObject) {
						oglm::vec4 c =
						    phong(frag, normal, lightPos, lightColor, color);
						if (lineFill)
							drawTriangle(triangle, color);
						else
							fillTriangle(triangle, c);
					} else {
						if (lineFill) {
							drawTriangle(triangle, color);
						} else {
							fillTriangle(triangle, color);
						}
					}
				}
				triangle.clear();

			} else {
				frag0 = fragPos[i];
				frag1 = fragPos[i + 1];
				triangle.push_back(oglm::vec3(x0, y0, z0));
				triangle.push_back(oglm::vec3(x1, y1, z1));
			}
		}
	}
	currentBuffer.clear();
}


void Cube::set_model(const oglm::vec3 &tFactor, const oglm::vec3 &sFactor,
                     float rotAng, const oglm::vec3 &rotAxis) {
	oglm::mat4 trans = oglm::translate(tFactor);
	oglm::mat4 scal = oglm::scale(sFactor);
	oglm::mat4 rot = oglm::rotate(rotAng, oglm::normalize(rotAxis));
	model = trans * rot * scal;
}
void Cube::load(bool doRasterize) {
	for (auto &i : indices) {
		float x0 = points[i.x].x;
		float y0 = points[i.x].y;
		float z0 = points[i.x].z;
		float x1 = points[i.y].x;
		float y1 = points[i.y].y;
		float z1 = points[i.y].z;
		vertexBuffer.push_back(oglm::vec3(x0, y0, z0));
		vertexBuffer.push_back(oglm::vec3(x1, y1, z1));
	}
	if (doRasterize) {
		clipping = true;
		rasterize();
	}
}
