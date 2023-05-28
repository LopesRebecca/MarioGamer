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
    width = 2;
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
    glutPostRedisplay(); //Instrução que indica pra GLUT que o frame buffer deve ser atualizado


    //if (posicao.x < width) // colisao pra nao sair da tela pela direita
    //    posicao.x = width;

    //if (posicao.x + width > 6) // colisao pra nao sair da tela pela esquerda
    //    posicao.x = 6 - width;

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
    //Formas::quadrado();
    velocidade = 0;
    glPopMatrix();
}

void Player::colisao(Player player, Enemy enemy, GameOver gameOver) {
    if (player.posicao.x < enemy.posicao.x + enemy.width &&
        player.posicao.x + player.width > enemy.posicao.x &&
        player.posicao.y < enemy.posicao.y + enemy.height &&
        player.posicao.y + player.height > enemy.posicao.y){
        gameOver.gameOver(2.0, 2.0, -1.0, GLUT_BITMAP_TIMES_ROMAN_24, "Game Over");
        printf("AAAAAAAAA");
    }
   /* if (player.posicao.y + player.height > enemy.posicao.y) {
        enemy.desenha();
        printf("BBBBBBBBBBBBBBB");
    }*/
            
}


bool Player::colisaoPlataforma(Plataforma platform) {
    if (checkCollision(posicao.x, posicao.y, width, height,
                platform.posicao.x, platform.posicao.y, platform.width, platform.height)) {
                posicao.y = platform.posicao.y + platform.height; // Ajusta a posição do jogador na plataforma
    }

    return true;
       
}

//for (const auto& platform : platforms) {
//    if (checkCollision(playerX, playerY, playerWidth, playerHeight,
//        platform.x, platform.y, platform.width, platform.height)) {
//        playerY = platform.y + platform.height; // Ajusta a posição do jogador na plataforma
//        jumpSpeed = 0.0f; // Reinicia a velocidade de pulo
//        isJumping = false; // Desativa o pulo
//        break; // Não precisa verificar as outras plataformas
//    }
//}


bool Player:: checkCollision(float x1, float y1, float width1, float height1,
    float x2, float y2, float width2, float height2) {
    if (x1 + width1 >= x2 && x1 <= x2 + width2 &&
        y1 + height1 >= y2 && y1 <= y2 + height2) {
        return true; // Colisão detectada
    }
    return false; // Sem colisão
}
//
//void update(int value) {
//    // Verifica a colisão entre o jogador e o inimigo
//    if (checkCollision(playerX, playerY, playerWidth, playerHeight,
//        enemyX, enemyY, enemyWidth, enemyHeight)) {
//        std::cout << "Colisão detectada!" << std::endl;
//    }
//
//    glutTimerFunc(1000 / 60, update, 0); // Atualiza a cada 1/60 segundos (60 FPS)
//}



