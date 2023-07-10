#include "fonteluz.h"


#include <GL/glut.h>
#include <GL\freeglut.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//construtor
FonteLuz::FonteLuz() {

}

//Get's
const glm::vec3& FonteLuz::getLuzPos() const
{
    return luzPos;
}

const glm::vec3& FonteLuz::getLuzAmb() const
{
    return luzAmb;
}

const glm::vec3& FonteLuz::getLuzDiff() const
{
    return luzDiff;
}

const glm::vec3& FonteLuz::getLuzSpec() const
{
    return luzSpec;
}

//Set's
void FonteLuz::setLuzPos(const glm::vec3& newLuzPos)
{
    luzPos = newLuzPos;
}

void FonteLuz::setLuzAmb(const glm::vec3& newLuzAmb)
{
    luzAmb = newLuzAmb;
}

void FonteLuz::setLuzDiff(const glm::vec3& newLuzDiff)
{
    luzDiff = newLuzDiff;
}

void FonteLuz::setLuzSpec(const glm::vec3& newLuzSpec)
{
    luzSpec = newLuzSpec;
}

//M�todos principais
//m�todo que calcula a cor que um ponto ir� possuir ap�s ser iluminado pela fonte de luz usando Modelo de Ilumina��o de Phong
glm::vec3 FonteLuz::iluminacao(glm::vec3 P, glm::vec3 camPos, glm::vec3 matAmb, glm::vec3 matDiff, glm::vec3 matSpec, float matShine, glm::vec3 n) {
    //reflex�o ambiente
    glm::vec3 amb = luzAmb * matAmb;

    //reflex�o difusa
    glm::vec3 l = glm::vec3(luzPos) - P;
    l = glm::normalize(l);
    n = glm::normalize(n);
    glm::vec3 dif = luzDiff * matDiff * glm::max(0.0f, glm::dot(l, n));

    //reflex�o especular
    glm::vec3 v = glm::vec3(camPos) - P;
    v = glm::normalize(v);
    glm::vec3 r = 2 * glm::dot(n, l) * n - l;
    glm::vec3 esp = luzSpec * matSpec * (float)(pow(glm::max(0.0f, glm::dot(v, r)), matShine));

    return amb + dif + esp;
}

//m�todo que desenha a fonte de luz na tela
void FonteLuz::desenha() {
    glPointSize(5);
    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    glVertex3f(luzPos.x, luzPos.y, luzPos.z);
    glEnd();
}
