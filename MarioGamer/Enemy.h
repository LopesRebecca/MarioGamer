#ifndef ENEMY_H
#define ENEMY_H

#include <glm/glm.hpp>
#include "Plataforma.h"

//Alana Oliveira - 495702
class Enemy {
public:
    glm::vec2 posicao;
    glm::vec3 cor;
    float tamanho;
    float     width;
    float height;
    float     velocidade;
    float direcao;
 
public:
    Enemy(float x, float y, float z);
    void cair(float tempo);
    void colisaoPlataforma(Plataforma plataforma);
    void mover();
    void desenha();
    void moverChao();
};

#endif 

