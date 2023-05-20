#include "Plataforma.h"

#include "formas.h"

#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <glm/glm.hpp>


Plataforma::Plataforma(float y) {
    posicao = glm::vec2(1 + rand() % 3, y);
    cor = glm::vec3(1,0.46, 0.09);
    largura = 0.25;
}

bool Plataforma::isOut() {
    return posicao.x < 0 - largura;
}

void Plataforma::respawn() {
    posicao.x = 2 + rand() % 3;
    posicao.y = 1 + largura;
}

void Plataforma::desenha() {
    //obstaculo direito
    glPushMatrix();
    glTranslatef((posicao.x - 0.5) / 2.0, posicao.y, 0);
    glScalef((3.5 - posicao.y) / 2.0, largura, 1);
    glColor3f(cor.r, cor.g, cor.b);
    Formas::quadrado();
    glPopMatrix();

    //obstaculo esquerdo
    glPushMatrix();
    glTranslatef(posicao.x, (posicao.y - 4.5) / 2.0, 0);
    glScalef((3.5 - posicao.y) / 2.0, largura, 1);
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

