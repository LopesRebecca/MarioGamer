#pragma once

#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <glm/glm.hpp>

class GameOver
{
public:
	glm::vec2 posicao;
	glm::vec3 cor;
public:
	GameOver();
	void gameOver(float x, float y, float z, void* font, const char* string);
};

#endif
