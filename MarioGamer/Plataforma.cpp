#include "Plataforma.h"

#include "formas.h"

#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <glm/glm.hpp>


unsigned int plataformaImgId;

//Maria Rebecca - 495703
Plataforma::Plataforma(float x, float y, float z) {
    posicao = glm::vec3(x, y, z);
    cor = glm::vec3(1,0.46, 0.09);
    largura = 1;
    width = 0.2;
    height = 0.1;
}

//Maria Rebecca - 495703
void Plataforma::desenha(unsigned int texturaId) {
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, 3);
    glScalef(largura, width, height);
    glColor3f(cor.r, cor.g, cor.b);
    glBindTexture(GL_TEXTURE_2D, texturaId);
    Formas::quadrado();
    glPopMatrix();
}

//Maria Rebecca - 495703
void Plataforma::flow() {
    //desenhando o chão no plano XZ

    // aplicar textura no chão
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
