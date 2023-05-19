#pragma once

#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <glm/glm.hpp>

class Plataforma
{
private:
	glm::vec2 posicao;
	glm::vec3 cor;
	float largura;
public:
	Plataforma(float y);
	bool isOut();
	void respawn();
	void desenha();
	void flow();
};

#endif

