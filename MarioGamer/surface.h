#ifndef SURFACE_H
#define SURFACE_H

#include <glm/glm.hpp>
#include "fonteluz.h"

class Surface {
private:
    //dimensões e divisões da superfície
    float     lado = 20.0f;
    int       divisoes = 100;
    //propriedades da onda
    float     onda = 0;   //ângulo no centro
    float     ondaAltura = 0.0; //altura da onda
    float     ondaComp = 1.0; //comprimento da onda
    float     ondaVeloc = 0.0; //velocidade da onda
    //propriedades de material
    glm::vec3 matAmb = glm::vec3(0.1, 0.1, 0.1); //ambiente
    glm::vec3 matDiff = glm::vec3(0, 1, 1);       //difusa
    glm::vec3 matSpec = glm::vec3(1, 1, 1);       //especular
    float     matShine = 64.0f;                  //especularidade
    //métodos privados
    float     alturaSurface(float x, float y);
    glm::vec3 normalTriangle(glm::vec3 A, glm::vec3 B, glm::vec3 C);
public:
    //Construtor
    Surface();

    //Get's
    float getLado() const;
    int   getDivisoes() const;
    float getOndaAltura() const;
    float getOndaComp() const;
    float getOndaVeloc() const;
    const glm::vec3& getMatAmb() const;
    const glm::vec3& getMatDiff() const;
    const glm::vec3& getMatSpec() const;
    float getMatShine() const;

    //Set's
    void setLado(float newLado);
    void setDivisoes(int newDivisoes);
    void setOndaAltura(float newOndaAltura);
    void setOndaComp(float newOndaComp);
    void setOndaVeloc(float newOndaVeloc);
    void setMatAmb(const glm::vec3& newMatAmb);
    void setMatDiff(const glm::vec3& newMatDiff);
    void setMatSpec(const glm::vec3& newMatSpec);
    void setMatShine(float newMatShine);

    //Métodos principais
    void move(float tempo);
    void desenha(glm::vec3 camPos, FonteLuz luz);
};

#endif // SURFACE_H
