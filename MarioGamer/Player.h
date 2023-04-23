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
    void flap();            //função que dá impulso para cima ao bird
    void cair(float tempo); //função que abaixo o bird sob ação da gravidade
    void desenha();         //função que desenha o bird na tela
};

#endif 

