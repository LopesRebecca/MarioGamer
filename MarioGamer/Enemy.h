#ifndef ENEMY_H
#define ENEMY_H

#include <glm/glm.hpp>
#include "Plataforma.h"

//Alana Oliveira - 495702
class Enemy {
public:
    glm::vec3 posicao;
    glm::vec3 cor;
    float tamanho;
    float     width;
    float height;
    float     velocidade;
    float direcao;
 
public:
    Enemy(float x, float y, float z);
    void cair(float tempo);
    void mover(Plataforma plataforma);
    void desenha(unsigned int texturaId);
    void moverChao();
};

#endif 

