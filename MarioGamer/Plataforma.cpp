#include "Plataforma.h"

#include "formas.h"

#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <glm/glm.hpp>

//Maria Rebecca - 495703
Plataforma::Plataforma(float x, float y) {
    posicao = glm::vec2(x, y);
    cor = glm::vec3(1,0.46, 0.09);
    largura = 0.25;
    width = 1.2;
    height = 0.5;
}

//Maria Rebecca - 495703
void Plataforma::desenha() {
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, 1);
    glScalef(1, 0.2, -4);
    glColor3f(cor.r, cor.g, cor.b);
    Formas::quadrado();
    glPopMatrix();
}

//Maria Rebecca - 495703
void Plataforma::flow() {
    //desenhando o chão no plano XZ
    glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);
    glScalef(3, 1, 3);
    glBegin(GL_QUADS);
    glVertex3f(-1, 0, -1);
    glVertex3f(1, 0, -1);
    glVertex3f(1, 0, 1);
    glVertex3f(-1, 0, 1);
    glEnd();
    glPopMatrix();
}
