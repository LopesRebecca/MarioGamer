
#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/ext.hpp>



#include <cmath>
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "Plataforma.h"


using namespace std;

float frameRate = 30;
bool isColiding = false;
float move = 0.4;

Player player;
static Enemy enemy;
Plataforma flow(0, 0);

Plataforma pipe3(3,2);

//vari�veis globais relacionadas a dimens�es da janela
int larguraJanela, alturaJanela;
float aspectRatio;

//vari�veis globais relacionadas a c�mera
glm::vec4 camPos(3, 3, 3, 1);  //posi��o inicial da c�mera
glm::mat4 camRotacao = glm::rotate(glm::mat4(1), glm::radians(1.0f), glm::vec3(0, 1, 0)); //matriz de rota��o para girar a c�mera
bool      gira = true;

//� uma boa pr�tica criar uma fun��o para agrupar configura��es iniciais do OpenGL para o desenho a ser feito
void inicio() {
    glClearColor(0.0, 0.0, 0.0, 1.0); //cor de fundo (preto)
    glEnable(GL_DEPTH_TEST);          //habilitando a remo��o de faces que estejam atr�s de outras (ocultas)
    //glEnable(GL_MULTISAMPLE);         //habilita um tipo de antialiasing (melhora serrilhado)
}


//fun��o chamada sempre que a janela for modificada de tamanho
void alteraJanela(int largura, int altura) {
    larguraJanela = largura;
    alturaJanela = altura;
    aspectRatio = (float)larguraJanela / alturaJanela;
    glutPostRedisplay();
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
    glutTimerFunc(1000.0 / frameRate, timer, 0);
    
    if (gira)
        camPos = camRotacao * camPos; //a cada frame, a posi��o da c�mera � rotacionada usando a matriz de rota��o camRotacao


    player.cair(1.0 / frameRate); //a cada frame, o mario cai sob a��o da gravidade   

    enemy.cair(1.0 / frameRate);

    player.colisaoPlataforma(pipe3);
    enemy.colisaoPlataforma(pipe3);
    player.colisao(player, enemy);

    if (player.verificarColisao(player, enemy)) {
        enemy.posicao.x = -1;
        enemy.posicao.y = -1;
    }

    glutPostRedisplay();
}


//Pode remover depois, usar s� pra se localizar msm
void eixos() {
    glLineWidth(3); //altera a largura das linhas para 3 pixels
    glBegin(GL_LINES);
    //eixo x em vermelho
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);
    //eixo y em verde
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);
    //eixo z em azul
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100);
    glEnd();
}

void cenario() {
   

    //desenhando o ch�o no plano XZ
    glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);
    glScalef(3, 1, 3);
    glBegin(GL_QUADS);
    glVertex3f(-1, 0, -1);
    glVertex3f(1, 0, -1);
    glVertex3f(1, 0, 1);
    glVertex3f(-1, 0, 1);
    glEnd();
    glPopMatrix();
}

//Fun��o que desenha cen�rio usando proje��o em perspectiva
void projecaoPerspectiva(Player player) {
    //definindo o tipo de proje��o
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 matrizProjecao = glm::frustum(-1, 1,   //left e right (limites na largura do plano de proje��o)
        -1, 1,   //bottom e top (limites na altura do plano de proje��o)
        1, 100); //near e far (limites na profundidade do volume de visualiza��o)
    glMultMatrixf(glm::value_ptr(matrizProjecao));
   

    //definindo o posicionamento da c�mera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 matrizCamera = glm::lookAt(glm::vec3(camPos), //eye = posi��o da c�mera
        glm::vec3(player.posicao.x, player.posicao.y, 0),  //at  = para onde a c�mera aponta
        glm::vec3(0, 1, 0)); //up  = para onde o topo da c�mera aponta
    glMultMatrixf(glm::value_ptr(matrizCamera)); //criada a matriz usando GLM, deve-se envi�-la para OpenGL

    //desenhando cen�rio (ch�o e objeto) e eixos
    cenario();
    eixos();
}


void desenha() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // glViewport(larguraJanela / 2, 0, larguraJanela / 2, alturaJanela); //reserva metada direita da janela para ser desenhada
    projecaoPerspectiva(player);   //fun��o que desenha cen�rio usando proje��o em perspectiva

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 6, 0, 4, -1, 1);

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    eixos();
    

    player.desenha();
    enemy.desenha(); 
    pipe3.desenha();
    //enemy.colisao(flow);
    
    
  
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

    glutReshapeFunc(alteraJanela);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);
    glutTimerFunc(1000.0 / 30, timer, 0);

    glutMainLoop();

    return 0;
}
