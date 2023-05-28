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
    int vida;
public:
    Player();
    void flap();            
    void cair(float tempo); 
    void mover(int tecla);
    void desenha();
    void over();
    void colisao(Player player, Enemy enemy, GameOver gameOver);
    void colisaoPlataforma(Plataforma plataforma);
    void colisaoEnemy(Enemy enemy);
};
#endif 

