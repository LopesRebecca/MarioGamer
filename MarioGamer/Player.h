#ifndef PLAYER_H
#define PLAYER_H

//#include <glm/glm.hpp>

class Player {
private:
    float posicao[2];
    float cor[3];
    float     tamanho;
    float     velocidade;
public:
    Player();
    void flap();            //fun��o que d� impulso para cima ao bird
    void cair(float tempo); //fun��o que abaixo o bird sob a��o da gravidade
    void desenha();         //fun��o que desenha o bird na tela
};

#endif 

