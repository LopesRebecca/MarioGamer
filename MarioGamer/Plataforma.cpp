#include "Plataforma.h"

#include "formas.h"

#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <glm.hpp>


Plataforma::Plataforma(float x) {
    posicao = glm::vec2(x, 1 + rand() % 3);
    velocidade = 1;
    largura = 0.25;
}

bool Plataforma::isOut() {
    return posicao.x < 0 - largura;
}

void Plataforma::move(float tempo) {
    posicao.x = posicao.x - velocidade * tempo; //movimentação uniforme constante (modifica apenas posição)
}

void Plataforma::respawn() {
    posicao.x = 6 + largura;
    posicao.y = 1 + rand() % 3;
}

void Plataforma::desenha() {
    //O pipe é um par de obstáculo (superior e inferior)
    //obstáculo inferior
    glPushMatrix();
    glTranslatef(posicao.x, (posicao.y - 0.5) / 2.0, 0);
    glScalef(largura, (posicao.y - 0.5) / 2.0, 1);
    Formas::quadrado();
    glPopMatrix();

    //obstaculo superior
    glPushMatrix();
    glTranslatef(posicao.x, (posicao.y + 4.5) / 2.0, 0);
    glScalef(largura, (3.5 - posicao.y) / 2.0, 1);
    Formas::quadrado();
    glPopMatrix();
}

