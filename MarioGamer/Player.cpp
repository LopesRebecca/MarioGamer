#include "Player.h"

#include <GL/glut.h>
#include <GL\freeglut.h>
#include<glm/glm.hpp>

#include "Formas.h"
#include "Plataforma.h"



Player::Player() {
    posicao = glm::vec3(0.25, 2, 8);
    cor = glm::vec3(1, 0, 0);
    tamanho = 0.2;
    width = 0.2;
    height = 0.2;
    velocidade = 0;
    direita;
    esquerda;
    vida = 100;
    pulos = 0;
}

//Maria Rebecca - 495703
void Player::flap() {
    
    velocidade = -4;
}

//Maria Rebecca  - 495703
void Player::mover(int tecla) {

    switch (tecla) {                                  //os códigos das teclas especiais são valores inteiros, então podem ser usados no switch
        case GLUT_KEY_LEFT:  posicao.x += 0.1;  break; //caso a seta direita seja pressionada, a coordenada x do ponto inferior esquerdo é reduzida, deslocando o quadrado pra esquerda
        case GLUT_KEY_RIGHT: posicao.x -= 0.1;  break; //caso a seta esquerda seja pressionada, a coordenada x do ponto inferior esquerdo é aumentada, deslocando o quadrado pra direita
            
        case GLUT_KEY_UP:  posicao.y -= 0.1; break; //caso a seta cima seja pressionada, a coordenada y do ponto inferior esquerdo é reduzida, deslocando o quadrado pra esquerda
        case GLUT_KEY_DOWN: posicao.y += 0.1; break; //caso a seta baixo seja pressionada, a coordenada y do ponto inferior esquerdo é aumentada, deslocando o quadrado pra direita
    }

    
    
    glutPostRedisplay(); //Instrução que indica pra GLUT que o frame buffer deve ser atualizado


    if (posicao.x + width < -9.75) // colisao pra nao sair da tela pela direita
        posicao.x = -9.75;

    if (posicao.x + width > 10) // colisao pra nao sair da tela pela esquerda
        posicao.x = 10 - width;

    if (posicao.y + height > 10)
        posicao.y = 10 - height;

    if (posicao.y < -9.75)
        posicao.y = -9.75;
}

//Alana Oliveira - 495702
void Player::cair(float tempo) {
    float gravidade = 10;
    velocidade = velocidade + gravidade * tempo;
    posicao.z = posicao.z - velocidade * tempo;

 
    if (posicao.z <= 0.2)
        posicao.z = 0.2;
    

}

//Pedro Henrique - 494569
void Player::desenha() {
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, posicao.z);
    glScalef(tamanho, tamanho, tamanho);
    glColor3f(cor.r, cor.g, cor.b);
    Formas::quadrado();
    glPopMatrix();
}


//Pedro Henrique - 494569
void Player::colisao(Player player, Enemy enemy) {
    if (player.posicao.x < enemy.posicao.x &&
        player.posicao.x + player.width > enemy.posicao.x &&
        player.posicao.y == enemy.posicao.y ) {
        vida--;
        if (vida < 0)
            exit(0);
        printf(" %d ", vida);
    }

   
}

//Pedro Henrique - 494569
bool Player::verificarColisao(Player player, Enemy enemy) {
    // Verifica se o jogador está em cima do inimigo
    if (player.posicao.x + player.width == enemy.posicao.x + enemy.width &&
        player.posicao.y + player.width > enemy.posicao.y + enemy.height) {
        return true; // Colisão ocorreu
    }
    return false; // Não houve colisão
}


//Maria Rebecca - 495703
void Player::colisaoPlataforma(Plataforma plataforma) {
    if (posicao.x < (plataforma.posicao.x + plataforma.width) &&
        posicao.x + width > (plataforma.posicao.x) &&
        posicao.y < (plataforma.posicao.y + plataforma.height) &&
        posicao.y + height > (plataforma.posicao.y)){
        posicao.y = plataforma.posicao.y + plataforma.height;
    }
}




