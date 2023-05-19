
#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>



#include <cmath>
#include <vector>

#include "Player.h"
#include "Plataforma.h"


using namespace std;

float frameRate = 30;

Player player;
Plataforma flow(0);
Plataforma pipe1(7);
Plataforma pipe2(9);
Plataforma pipe3(11);
std::vector<Plataforma> pipes;



void inicio() {
    glClearColor(0.0, 1.0, 1.0, 1.0);
    pipes.push_back(pipe1);
    pipes.push_back(pipe2);
    pipes.push_back(pipe3);
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == 'd')
        player.flap(); //a cada pressionar da tecla, o bird recebe velocidade pra cima
}

//Função indicada pra GLUT que será executada após uma certa quantidade de tempo
void timer(int v) {
    glutTimerFunc(1000.0 / frameRate, timer, 0); //Controlando o desenho a cada 1000/30 significa que a tela será redesenhada 30 frames por segundo

    player.cair(1.0 / frameRate); //a cada frame, o bird cai sob ação da gravidade

    glutPostRedisplay();
}


void desenha() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 6, 0, 6, -1, 1);

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();           

    for (unsigned int i = 0; i < pipes.size(); i++) pipes[i].desenha();
    player.desenha();
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
    glutTimerFunc(1000.0 / 30, timer, 0);

    glutMainLoop();

    return 0;
}
