
#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <cstdio>



#include <cmath>
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "Plataforma.h"
#include "GameOver.h"


using namespace std;

float frameRate = 30;
bool isColiding = false;
float move = 0.4;

Player player;
static Enemy enemy;
Plataforma flow(0, 0);
GameOver gameOver;

Plataforma pipe1(0,3);
Plataforma pipe2(3, 2);
Plataforma pipe3(6,1.2);
Plataforma pipe4(0, 1.2);
Plataforma pipe5(4, 3);

std::vector<Plataforma> pipes;


void inicio() {
    glClearColor(0.0, 1.0, 1.0, 1.0);
    pipes.push_back(pipe1);
    pipes.push_back(pipe2); 
    pipes.push_back(pipe3);
    pipes.push_back(pipe4);
    pipes.push_back(pipe5);
}

void tecladoEspecial(int tecla, int x, int y) {
    player.mover(tecla);
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == ' ')
        player.flap(); //a cada pressionar da tecla, o mario recebe velocidade pra cima
}

//Fun��o indicada pra GLUT que ser� executada ap�s uma certa quantidade de tempo
void timer(int v) {
    glutTimerFunc(1000.0 / frameRate, timer, 0); //Controlando o desenho a cada 1000/30 significa que a tela ser� redesenhada 30 frames por segundo
    
    player.cair(1.0 / frameRate); //a cada frame, o mario cai sob a��o da gravidade   

    enemy.cair(1.0 / frameRate);
    enemy.mover();

    glutPostRedisplay();
}

void desenha() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 6, 0, 4, -1, 1);

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();

    player.desenha();
    enemy.desenha(0,3);
    player.colisao(player, enemy, gameOver);
    enemy.desenha(6, 1.2);
    
    for (unsigned int i = 0; i < pipes.size(); i++) pipes[i].desenha();
    
    enemy.colisao(flow);
    
    flow.flow();
  
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 360);
    glutCreateWindow("Mario Game - Computa��o Grafica");

    inicio();

    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);
    glutTimerFunc(1000.0 / 30, timer, 0);

    glutMainLoop();

    return 0;
}
