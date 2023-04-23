#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

class Player {
private:
    glm::vec2 posicao;
    glm::vec3 cor;
    float     tamanho;
    float     velocidade;
public:
    Player();
    void flap();            //função que dá impulso para cima ao bird
    void cair(float tempo); //função que abaixo o bird sob ação da gravidade
    void desenha();         //função que desenha o bird na tela
};

#endif 

