#pragma once

#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <glm/glm.hpp>

//Maria Rebecca - 495703
class Plataforma
{
public:
	glm::vec3 posicao;
	glm::vec3 cor;
	float largura;
	float width;
	float height;
public:
	Plataforma(float x, float y, float z);
	void desenha(unsigned int texturaId);
	void flow();
};

#endif

