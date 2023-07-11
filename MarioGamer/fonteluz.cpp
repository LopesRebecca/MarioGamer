#include "fonteluz.h"


#include <GL/glut.h>
#include <GL\freeglut.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//construtor
FonteLuz::FonteLuz() {
    tipoLuz = PONTUAL;
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


TipoLuz FonteLuz::getTipoLuz() const {
    return tipoLuz;
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

// M�todos Get/Set para o tipo de luz
void FonteLuz::setTipoLuz(TipoLuz tipo) {
    tipoLuz = tipo;
}

// Ilumina��o de Phong
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

    return amb + dif + esp; //formula de phong
}


// M�todo para configurar a ilumina��o
void FonteLuz::configurarIluminacao() {
    // Configura��o das propriedades da luz
    GLenum luzGL;
    switch (tipoLuz) {
    case PONTUAL:
        luzGL = GL_LIGHT0;
        // Configura��o para uma fonte de luz pontual
        // Define a posi��o da luz
        glLightfv(luzGL, GL_POSITION, glm::value_ptr(glm::vec4(luzPos, 1.0f)));
        break;
    case DIRECIONAL:
        luzGL = GL_LIGHT1;
        // Configura��o para uma fonte de luz direcional
        // Define a dire��o da luz
        glLightfv(luzGL, GL_POSITION, glm::value_ptr(glm::vec4(luzPos, 0.0f)));
        break;
    }

    // Define as propriedades de cor da luz
    glLightfv(luzGL, GL_AMBIENT, glm::value_ptr(luzAmb));
    glLightfv(luzGL, GL_DIFFUSE, glm::value_ptr(luzDiff));
    glLightfv(luzGL, GL_SPECULAR, glm::value_ptr(luzSpec));

    // Habilita a luz
    glEnable(luzGL);
}


//m�todo que desenha a fonte de luz na tela
void FonteLuz::desenha() {
    glPointSize(5);
    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    glVertex3f(luzPos.x, luzPos.y, luzPos.z);
    glEnd();
}
