#include "Enemy.h"

#include <GL/glut.h>
#include <GL\freeglut.h>
#include<glm/glm.hpp>

#include "Formas.h"



Enemy::Enemy() {
    posicao = glm::vec2(4, 2);
    cor = glm::vec3(0, 1, 0);
    tamanho = 0.2;
    width = 0.2;
    height = 0.7;
    velocidade = 0;
    direcao = 1+ rand() % 3;
}



void Enemy::cair(float tempo) {
    float gravidade = 10;
    velocidade = velocidade + gravidade * tempo;
    posicao.y = posicao.y - velocidade * tempo;

    if (posicao.y < height) // colisao com o chao
        posicao.y = height;

}


void Enemy::mover() {
    velocidade = 0.02;

    if (posicao.x + (direcao * velocidade) + width > 6) { // quando bater na parede do lado direito ele muda a direçao
        direcao *= -1;
    }
    else if (posicao.x + (direcao * velocidade) < 0) { // quando bater na parede do lado esquerdo ele muda a direçao
        direcao *= -1;
    }

    posicao.x += direcao * velocidade; // movendo o inimigo

    glutPostRedisplay(); //Instrução que indica pra GLUT que o frame buffer deve ser atualizado
}
void Enemy::desenha() {
    glPushMatrix();

    glTranslatef(posicao.x, posicao.y, 0);
    glScalef(tamanho, tamanho, 1);
    glColor3f(cor.r, cor.g, cor.b);
    Formas::quadrado();

    glPopMatrix();
}