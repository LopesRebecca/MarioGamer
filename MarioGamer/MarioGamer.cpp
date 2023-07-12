
#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/ext.hpp>



#include <cmath>
#include <vector>

#include "fonteluz.h"
#include "Player.h"
#include "Enemy.h"
#include "Plataforma.h"
#include "surface.h"
#include "Textura.h"


using namespace std;

#define FPS 30
#define TEX_MARIO "texturas/mario.jpg"
#define TEX_PLATAFORMA "texturas/bloco.jpg"
#define TEX_INIMIGO "texturas/inimigo2.jpg"

float frameRate = 30;
bool isColiding = false;
float move = 0.4;

Player player;
Enemy enemy(3, 1, 1);
Plataforma flow(0, 0, 0);
Surface  surface;
FonteLuz luz;
Textura textura;

Plataforma pipe1(3, 1, 1);
Plataforma pipe2(0, 1, 1);

//vari�veis globais relacionadas a dimens�es da janela
int larguraJanela;
int alturaJanela;
float aspectRatio;

//variaveis globais textura
unsigned int texMario;
unsigned int texPlataforma;
unsigned int texInimigo;


//vari�veis globais relacionadas a c�mera
glm::vec3 camPos = glm::vec3(1, -10, 50);  //posi��o inicial da c�mera
glm::mat4 camRotacao = glm::rotate(glm::mat4(1), glm::radians(1.0f), glm::vec3(0, 1, 0)); //matriz de rota��o para girar a c�mera
bool      gira = true;

//� uma boa pr�tica criar uma fun��o para agrupar configura��es iniciais do OpenGL para o desenho a ser feito
void inicio() {
    glClearColor(0.0, 0.0, 0.0, 1.0); //cor de fundo (preto)
    glEnable(GL_DEPTH_TEST);          //habilitando a remo��o de faces que estejam atr�s de outras (ocultas)
    //glEnable(GL_MULTISAMPLE);         //habilita um tipo de antialiasing (melhora serrilhado)

    texMario = player.carregaTextura(TEX_MARIO); 
    texPlataforma = player.carregaTextura(TEX_PLATAFORMA);
    texInimigo = player.carregaTextura(TEX_INIMIGO);
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

    switch (tecla) {
        
    case 'f':
        luz.sombreamento = true;
            break;
    case 'g':
        luz.sombreamento = false;
            break;
   
    }
}

//Fun��o indicada pra GLUT que ser� executada ap�s uma certa quantidade de tempo
void timer(int v) {
    glutTimerFunc(1000.0 / frameRate, timer, 0);
    
    //alternando camera
    if (player.posicao.y < -3)
        camPos = glm::vec3(1, -10, 4); 
    else if(player.posicao.y > -3)
        camPos = glm::vec3(1, 6, 4);

    glm::mat4 R = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0, 0, 1)); //matriz de rota��o usada para girar a fonte de luz

    luz.setLuzPos(glm::vec3(R * glm::vec4(luz.getLuzPos(), 1.0f))); //girando a fonte de luz em torno do eixo Z
    player.cair(1.0 / frameRate); //a cada frame, o mario cai sob a��o da gravidade   
    enemy.mover();
    //player.colisaoPlataforma(pipe3);
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
    pipe1.desenha();
    pipe2.desenha();
    enemy.desenha();
    //player.desenha(TEX_MARIO);
    //pipe3.desenha(texPlataforma);
}

void projecaoPerspectiva(Player player) {
    //definindo o tipo de proje��o
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), //�ngulo de abertura do frustum
        (float)larguraJanela / alturaJanela, //aspect ratio da tela
        1.0f,                              //dist�ncia near
        100.0f);                           //dist�ncia far
    glMultMatrixf(glm::value_ptr(projectionMatrix));

    //definindo o posicionamento da c�mera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 cameraMatrix = glm::lookAt(camPos,            //posi��o da c�mera
        glm::vec3(player.posicao.x, player.posicao.y, 2),  //ponto para onde a c�mera est� olhando
        glm::vec3(0, 0, 2)); //dire��o para onde o topo da c�mera aponta
    glMultMatrixf(glm::value_ptr(cameraMatrix));


    
    //desenhando itens da cena
    cenario();
    eixos();
    surface.desenha(camPos, luz);
    luz.desenha();

}




void desenha() {
    glViewport(0, 0, larguraJanela, alturaJanela);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // glViewport(larguraJanela / 2, 0, larguraJanela / 2, alturaJanela); //reserva metada direita da janela para ser desenhada
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    projecaoPerspectiva(player);   //fun��o que desenha cen�rio usando proje��o em perspectiva
    
    luz.configurarIluminacao();
    //player.desenha(texMario);
    //enemy.desenha(); 
    //pipe3.desenha();
    //enemy.colisao(flow);
    
    
  
    glutSwapBuffers();
}




int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(larguraJanela, alturaJanela);
    glutCreateWindow("Mario Game - Computa��o Grafica");

    inicio();

    glutDisplayFunc(desenha);
    glutReshapeFunc(alteraJanela);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);
    glutTimerFunc(1000.0 / FPS, timer, 0);

    glutMainLoop();

    return 0;
}
