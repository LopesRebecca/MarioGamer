#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include "Enemy.h"
#include "GameOver.h"
#include "Plataforma.h"

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
    void colisao(Player player, Enemy enemy, GameOver gameOver);
    bool colisaoPlataforma(Plataforma plataforma);
    bool checkCollision(float x1, float y1, float width1, float height1,
        float x2, float y2, float width2, float height2);
};
#endif 

