#include "Player.h"

#include <GL/glut.h>
#include <GL\freeglut.h>
#include <glm.hpp>

#include "Formas.h"

Player::Player() {
    posicao = glm::vec2(0.25, 2);
    cor = glm::vec3(1, 0, 0);
    tamanho = 0.2;
    velocidade = 0.2;
}

void Player::flap() {
    velocidade = -3; 
}

void Player::cair(float tempo) {
    float gravidade = 10;
    velocidade = velocidade + gravidade * tempo;
    posicao[0] = posicao[0] - velocidade * tempo;
}

void Player::desenha() {
    glPushMatrix();

    glTranslatef(0.25, 2, 0);
    glScalef(tamanho, tamanho, 1);
    glColor3f(cor[0], cor[1], cor[2]);
    Formas::circulo(36); 

    glPopMatrix();
}


