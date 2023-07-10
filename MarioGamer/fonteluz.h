#ifndef FONTELUZ_H
#define FONTELUZ_H

#include <glm/glm.hpp>

class FonteLuz {
private:
    glm::vec3 luzPos = glm::vec3(5, 5, 5);

    //propriedades de cor da fonte de luz
    glm::vec3 luzAmb = glm::vec3(0.1, 0.1, 0.1); //ambiente
    glm::vec3 luzDiff = glm::vec3(1, 1, 1);       //difusa
    glm::vec3 luzSpec = glm::vec3(1, 1, 1);       //especular
public:
    //construtor
    FonteLuz();

    //get's
    const glm::vec3& getLuzPos() const;
    const glm::vec3& getLuzAmb() const;
    const glm::vec3& getLuzDiff() const;
    const glm::vec3& getLuzSpec() const;

    //set's
    void setLuzPos(const glm::vec3& newLuzPos);
    void setLuzAmb(const glm::vec3& newLuzAmb);
    void setLuzDiff(const glm::vec3& newLuzDiff);
    void setLuzSpec(const glm::vec3& newLuzSpec);

    //métodos principais
    glm::vec3 iluminacao(glm::vec3 P, glm::vec3 camPos, glm::vec3 matAmb, glm::vec3 matDiff, glm::vec3 matSpec, float matShine, glm::vec3 n);
    void desenha();


};

#endif // FONTELUZ_H
