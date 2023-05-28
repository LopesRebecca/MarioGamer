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

Plataforma pipe3(3,2);

void inicio() {
    glClearColor(0.0, 1.0, 1.0, 1.0);
}

void tecladoEspecial(int tecla, int x, int y) {
    player.mover(tecla);
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == ' ')
        player.flap(); //a cada pressionar da tecla, o mario recebe velocidade pra cima
}

//Função indicada pra GLUT que será executada após uma certa quantidade de tempo
void timer(int v) {
    glutTimerFunc(1000.0 / frameRate, timer, 0); //Controlando o desenho a cada 1000/30 significa que a tela será redesenhada 30 frames por segundo
    
    player.cair(1.0 / frameRate); //a cada frame, o mario cai sob ação da gravidade   

    enemy.cair(1.0 / frameRate);
    enemy.mover();

    //if (player.colisaoPlataforma(pipe3))
    

    glutPostRedisplay();
}

void desenha() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 6, 0, 4, -1, 1);

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.0, 0.0, 0.0);

    player.desenha();
    enemy.desenha(); 
    pipe3.desenha();
    //enemy.colisao(flow);
    
    flow.flow();
  
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 360);
    glutCreateWindow("Mario Game - Computação Grafica");

    inicio();

    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);

    glutTimerFunc(1000.0 / 30, timer, 0);

    glutMainLoop();

    return 0;
}
