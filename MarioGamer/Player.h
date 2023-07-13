#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include "Enemy.h"
#include "Plataforma.h"

//Maria Rebecca - 495703
class Player {
public:
    glm::vec3 posicao;
    glm::vec3 cor;
    float tamanho;
    float     width;
    float height;
    float     velocidade;
    int vida;
    int pulos;
public:
    Player();
    void flap();            
    void cair(float tempo); 
    void mover(int tecla);
    void desenha(unsigned char texturaId);
    void colisao(Player player, Enemy enemy);
    void colisaoPlataforma(Plataforma plataforma);
    unsigned int carregaTextura(const char fileName[]);
};
#endif 

