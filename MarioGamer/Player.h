#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

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
};

#endif 

