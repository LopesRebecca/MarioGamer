#pragma once

#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <glm.hpp>

class Plataforma
{
private:
	glm::vec2 posicao;
	glm::vec2 cor;
	float largura;
	float velocidade;
public:
	Plataforma(float x);
	bool isOut();
	void move(float tempo);
	void respawn();
	void desenha();
};

#endif

