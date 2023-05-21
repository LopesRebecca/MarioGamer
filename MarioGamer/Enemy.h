#ifndef ENEMY_H
#define ENEMY_H

#include <glm/glm.hpp>

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
    Enemy();
    void cair(float tempo);
    void mover();
    void desenha();
};

#endif 

