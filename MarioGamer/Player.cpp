#include "Player.h"

#include <GL/glut.h>
#include <GL\freeglut.h>
#include<glm/glm.hpp>

#include "Formas.h"
#include "Plataforma.h"
#include "GameOver.h"

Player::Player() {
    posicao = glm::vec2(0.25, 2);
    cor = glm::vec3(1, 0, 0);
    tamanho = 0.2;
    width = 0.2;
    height = 0.7 ;
    velocidade = 0;
    direita;
    esquerda;
}



void Player::flap() {
    velocidade = -4; 
}

void Player::mover(int tecla) {

    switch (tecla) {                                  //os códigos das teclas especiais são valores inteiros, então podem ser usados no switch
        case GLUT_KEY_LEFT:  posicao.x -= 0.1; break; //caso a seta esquerda seja pressionada, a coordenada x do ponto inferior esquerdo é reduzida, deslocando o quadrado pra esquerda
        case GLUT_KEY_RIGHT: posicao.x += 0.1; break; //caso a seta direita seja pressionada, a coordenada x do ponto inferior esquerdo é aumentada, deslocando o quadrado pra direita
    }
    


    if (posicao.x < width) // colisao pra nao sair da tela pela direita
        posicao.x = width;

    if (posicao.x + width > 6) // colisao pra nao sair da tela pela esquerda
        posicao.x = 6 - width;

    if (posicao.x + width > 2 ) { // colisao lateral com a plataforma do centro esquerda
        posicao.x = 2 - width;      
    }
   

    
   
    glutPostRedisplay(); //Instrução que indica pra GLUT que o frame buffer deve ser atualizado


}

void Player::cair(float tempo) {
    float gravidade = 10;
    velocidade = velocidade + gravidade * tempo;
    posicao.y = posicao.y - velocidade * tempo;

    if (posicao.y < height) // colisao com o chao
        posicao.y = height;

   
}


void Player::desenha() {
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, 0);
    glScalef(tamanho, tamanho, 1);
    glColor3f(cor.r, cor.g, cor.b);
    Formas::quadrado();
    glPopMatrix();
}

void Player::over() {
    glPushMatrix();

    glTranslatef(posicao.x, posicao.y, 0);
    glScalef(tamanho, tamanho, 1);
    glColor3f(0, 0, 0);
    Formas::quadrado();
    velocidade = 0;
    glPopMatrix();
}

void Player::colisao(Player player, Enemy enemy, GameOver gameOver) {
    if (posicao.y < height + 0.4) { // colisao com a plataforma
        posicao.y = height + 0.4;
    }
}


