#include "Enemy.h"

#include <GL/glut.h>
#include <GL\freeglut.h>
#include<glm/glm.hpp>

#include "Formas.h"

Enemy::Enemy(float x, float y, float z) {
    posicao = glm::vec3(x, y, z);
    cor = glm::vec3(0, 1, 0);
    tamanho = 0.15;
    width = 0.2;
    height = 0.7;
    velocidade = 0;
    direcao = 1+ rand() % 3;
}

void Enemy::cair(float tempo) {
    float gravidade = 10;
    velocidade = velocidade + gravidade * tempo;
    posicao.y = posicao.y - velocidade * tempo;

    moverChao();
    

}

void Enemy::mover(Plataforma plataforma) {
    velocidade = 0.02;

    if (posicao.x + (direcao * velocidade) + width >= plataforma.posicao.x + 1) { // quando bater na parede do lado direito ele muda a direçao
        direcao *= -1;
    }
    else if (posicao.x + (direcao * velocidade) < plataforma.posicao.x ) { // quando bater na parede do lado esquerdo ele muda a direçao
        direcao *= -1;
    }

    posicao.x += direcao * velocidade; // movendo o inimigo

    glutPostRedisplay(); //Instrução que indica pra GLUT que o frame buffer deve ser atualizado
}


void Enemy::moverChao() {
    velocidade = 0.02;

    if (posicao.x + (direcao * velocidade) + width > 10) { // quando bater na parede do lado direito ele muda a direçao
        direcao *= -1;
    }
    else if (posicao.x + (direcao * velocidade) < -9.75) { // quando bater na parede do lado esquerdo ele muda a direçao
        direcao *= -1;
    }

 
    posicao.x += direcao * velocidade; // movendo o inimigo

    glutPostRedisplay(); //Instrução que indica pra GLUT que o frame buffer deve ser atualizado
}

void Enemy::desenha(unsigned int texturaId) {
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, posicao.z);
    glScalef(tamanho, tamanho, tamanho);
    glColor3f(cor.r, cor.g, cor.b);
    glBindTexture(GL_TEXTURE_2D, texturaId);
    Formas::quadrado();

    glPopMatrix();
}