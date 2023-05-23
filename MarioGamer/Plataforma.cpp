#include "Plataforma.h"

#include "formas.h"

#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <glm/glm.hpp>


Plataforma::Plataforma(float x, float y) {
    posicao = glm::vec2(x, y);
    cor = glm::vec3(1,0.46, 0.09);
    largura = 0.25;
}

void Plataforma::desenha() {

    //obstaculo esquerdo
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, 1);
    glScalef(1.2, 0.1, 1);
    glColor3f(cor.r, cor.g, cor.b);
    Formas::quadrado();
    glPopMatrix();
}

void Plataforma::flow() {
    glPushMatrix();
    glScalef(6, 0.4, 1);
    glColor3f(cor.r, cor.g, cor.b);
    Formas::quadrado();
    glPopMatrix();
}

