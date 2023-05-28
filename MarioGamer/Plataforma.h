#pragma once

#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <glm/glm.hpp>

class Plataforma
{
public:
	glm::vec2 posicao;
	glm::vec3 cor;
	float largura;
	float width;
	float height;
public:
	Plataforma(float x, float y);
	void desenha();
	void flow();
	bool isColliding();
};

#endif

