
#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>



#include <cmath>
#include <vector>

#include "Player.h"


using namespace std;

/*
 * Programa que simula uma parte do jogo Flappy Bird
 * O personagem (círculo) sofre influência da gravidade e se mantem no ar ao pressionar espaço ou a tecla 'a'
 */

 //Variáveis globais
float frameRate = 30;

//Um personagem  e três obstáculos em ciclo (pipes)
Player player;


//Função com configurações iniciais da aplicação
void inicio() {
    glClearColor(0.0, 1.0, 1.0, 1.0);

}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == 'w')
        player.flap(); //a cada pressionar da tecla, o bird recebe velocidade pra cima
}

//Função indicada pra GLUT que será executada após uma certa quantidade de tempo
void timer(int v) {
    glutTimerFunc(1000.0 / frameRate, timer, 0); //Controlando o desenho a cada 1000/30 significa que a tela será redesenhada 30 frames por segundo

    player.cair(1.0 / frameRate); //a cada frame, o bird cai sob ação da gravidade

    glutPostRedisplay();
}

//Função indicada na 'main' que será usada para redesenhar o conteúdo do frame buffer
void desenha() {
    glClear(GL_COLOR_BUFFER_BIT);

    //definição da área do sistema de coordenadas do mundo que será usado no jogo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 6, 0, 4, -1, 1);

    glMatrixMode(GL_MODELVIEW); //habilita o uso de matrizes de transformações geométricas
    glLoadIdentity();           //inicializa a matriz de trasnformação com a matriz identidade (não altera as coordenadas dos pontos)

    //desenha personagem e obstáculos
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
