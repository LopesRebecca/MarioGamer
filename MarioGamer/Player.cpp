#include "Player.h"

#include <GL/glut.h>
#include <GL\freeglut.h>
#include<glm/glm.hpp>

#include "Formas.h"
#include "Plataforma.h"

Player::Player() {
    posicao = glm::vec2(0.25, 2);
    cor = glm::vec3(1, 0, 0);
    tamanho = 0.2;
    width = 0.2;
    height = 0.6;
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
    glutPostRedisplay(); //Instrução que indica pra GLUT que o frame buffer deve ser atualizado


    if (posicao.x < width) // colisao pra nao sair da tela pela direita
        posicao.x = width;

    if (posicao.x + width > 6) // colisao pra nao sair da tela pela esquerda
        posicao.x = 6 - width;

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

void Player::colisao(Player player, Enemy enemy) {
    if (player.posicao.x < enemy.posicao.x + enemy.width &&
        player.posicao.x + player.width > enemy.posicao.x &&
        player.posicao.y < enemy.posicao.y + enemy.height &&
        player.posicao.y + player.height > enemy.posicao.y) {
        //limpar a janela
        enemy.velocidade = 0;
        gameOver(2.0, 2.0, -1.0, GLUT_BITMAP_TIMES_ROMAN_24, "Game Over");
        //getc(stdin); para o jogo
    }
}

void Player::gameOver(float x, float y, float z, void* font, const char *string) {

        const unsigned char* str = reinterpret_cast<const unsigned char*>(string);
        glColor3f(0, 0, 0);
        glRasterPos3f(x, y, z);
        glutBitmapString(font, str);

        glPushMatrix();
        glTranslatef(posicao.x, posicao.y, 0);
        glScalef(tamanho, tamanho, 1);
        glColor3f(0, 0, 0);
        Formas::quadrado();
        velocidade = 0;
        glPopMatrix();    
}


