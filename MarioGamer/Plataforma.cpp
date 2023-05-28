#include "Plataforma.h"

#include "formas.h"

#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <glm/glm.hpp>


Plataforma::Plataforma(float x, float y) {
    posicao = glm::vec2(x, y);
    cor = glm::vec3(1,0.46, 0.09);
    width = 1.2;
    height = 0.5;
}

void Plataforma::desenha() {
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, 1);
    glScalef(width, height, 1);
    glColor3f(cor.r, cor.g, cor.b);

    for (int i = 0; i < 3; i++) {
        Formas::quadrado(i, 0);
    }
    glPopMatrix();
}

void Plataforma::flow() {
    glPushMatrix();
    glScalef(width, height, 1);
    glColor3f(cor.r, cor.g, cor.b);

    for (int i = 0; i < 5; i++) {
        Formas::quadrado(i, 0);
    }
    glPopMatrix();
}
