#ifndef FORMAS_H
#define FORMAS_H

#include "glm/glm.hpp"

class Formas {
public :
    glm::vec2 posicao;
    float     width;
    float height;
public:
    Formas();
    void circulo(int divisoes);
    static void quadrado();
};

#endif // FORMAS_H
