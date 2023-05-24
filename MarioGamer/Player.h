#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "Enemy.h"

class Player {
public:
    glm::vec2 posicao;
    glm::vec3 cor;
    float tamanho;
    float     width;
    float height;
    float     velocidade;
    bool direita;
    bool esquerda;
public:
    Player();
    void flap();            
    void cair(float tempo); 
    void mover(int tecla);
    void desenha();
    void over();
    void gameOver(float x, float y, float z, void* font, const char* string);
    void colisao(Player player, Enemy enemy);
};
#endif 

