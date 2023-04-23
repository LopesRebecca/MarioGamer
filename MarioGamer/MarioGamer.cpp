
#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>



#include <cmath>
#include <vector>

#include "Player.h"


using namespace std;

/*
 * Programa que simula uma parte do jogo Flappy Bird
 * O personagem (c�rculo) sofre influ�ncia da gravidade e se mantem no ar ao pressionar espa�o ou a tecla 'a'
 */

 //Vari�veis globais
float frameRate = 30;

//Um personagem  e tr�s obst�culos em ciclo (pipes)
Player player;


//Fun��o com configura��es iniciais da aplica��o
void inicio() {
    glClearColor(0.0, 1.0, 1.0, 1.0);

}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == 'w')
        player.flap(); //a cada pressionar da tecla, o bird recebe velocidade pra cima
}

//Fun��o indicada pra GLUT que ser� executada ap�s uma certa quantidade de tempo
void timer(int v) {
    glutTimerFunc(1000.0 / frameRate, timer, 0); //Controlando o desenho a cada 1000/30 significa que a tela ser� redesenhada 30 frames por segundo

    player.cair(1.0 / frameRate); //a cada frame, o bird cai sob a��o da gravidade

    glutPostRedisplay();
}

//Fun��o indicada na 'main' que ser� usada para redesenhar o conte�do do frame buffer
void desenha() {
    glClear(GL_COLOR_BUFFER_BIT);

    //defini��o da �rea do sistema de coordenadas do mundo que ser� usado no jogo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 6, 0, 4, -1, 1);

    glMatrixMode(GL_MODELVIEW); //habilita o uso de matrizes de transforma��es geom�tricas
    glLoadIdentity();           //inicializa a matriz de trasnforma��o com a matriz identidade (n�o altera as coordenadas dos pontos)

    //desenha personagem e obst�culos
    player.desenha();


    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 360);
    glutCreateWindow("Transformacoes Geometricas 2D - OpenGL Classico");

    inicio();

    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    glutTimerFunc(1000.0 / 30, timer, 0);

    glutMainLoop();

    return 0;
}
