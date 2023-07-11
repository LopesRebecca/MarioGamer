#ifndef TEXTURA_H
#define TEXTURA_H

#include <glm/glm.hpp>

class Textura {
public:
    //const char texMario[];
public:
    Textura(); 
    unsigned int carregaTextura(const char fileName[]);
};
#endif 