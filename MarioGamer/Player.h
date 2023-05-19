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
    void flap();            
    void cair(float tempo); 
    void desenha();        
};

#endif 

