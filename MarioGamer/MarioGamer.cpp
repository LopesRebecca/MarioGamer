
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
#define TEX_MARIO "imagens/mario.bmp"
#define TEX_PLATAFORMA "texturas/bloco.jpg"
#define TEX_INIMIGO "texturas/brickred.bmp"


float frameRate = 30;
bool isColiding = false;
float move = 0.4;

Player player;
static Enemy enemy;
Plataforma flow(0, 0);
Surface  surface;
FonteLuz luz;
Textura textura;

Plataforma pipe3(3,2);

//variáveis globais relacionadas a dimensões da janela
int larguraJanela;
int alturaJanela;
float aspectRatio;

//variaveis globais textura
unsigned int texMario;
unsigned int texPlataforma;
unsigned int texInimigo;


//variáveis globais relacionadas a câmera
glm::vec3 camPos = glm::vec3(1, -10, 4);  //posição inicial da câmera
glm::mat4 camRotacao = glm::rotate(glm::mat4(1), glm::radians(1.0f), glm::vec3(0, 1, 0)); //matriz de rotação para girar a câmera
bool      gira = true;

//É uma boa prática criar uma função para agrupar configurações iniciais do OpenGL para o desenho a ser feito
void inicio() {
    glClearColor(0.0, 0.0, 0.0, 1.0); //cor de fundo (preto)
    glEnable(GL_DEPTH_TEST);          //habilitando a remoção de faces que estejam atrás de outras (ocultas)
    //glEnable(GL_MULTISAMPLE);         //habilita um tipo de antialiasing (melhora serrilhado)

    texMario = textura.carregaTextura(TEX_MARIO); 
    texPlataforma = textura.carregaTextura(TEX_PLATAFORMA);
}


//função chamada sempre que a janela for modificada de tamanho
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
        
    case 'a':
        luz.setTipoLuz(PONTUAL);
            printf("Fonte de luz alterada para PONTUAL\n");
            break;
    case 's':
        luz.setTipoLuz(DIRECIONAL);
            printf("Fonte de luz alterada para DIRECIONAL\n");
            break;
    case 'f':
        // Define o modo de sombreamento para flat
        glShadeModel(GL_FLAT);
        break;

    case 'g':
        // Define o modo de sombreamento para Gouraud (padrão)
        glShadeModel(GL_SMOOTH);
        break;
    }
}

//Função indicada pra GLUT que será executada após uma certa quantidade de tempo
void timer(int v) {
    glutTimerFunc(1000.0 / frameRate, timer, 0);
    
    //alternando camera
    if (player.posicao.y < -3)
        camPos = glm::vec3(1, -10, 4); 
    else if(player.posicao.y > -3)
        camPos = glm::vec3(1, 6, 4);

    glm::mat4 R = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0, 0, 1)); //matriz de rotação usada para girar a fonte de luz

    luz.setLuzPos(glm::vec3(R * glm::vec4(luz.getLuzPos(), 1.0f))); //girando a fonte de luz em torno do eixo Z
    player.cair(1.0 / frameRate); //a cada frame, o mario cai sob ação da gravidade   

    player.colisaoPlataforma(pipe3);
    player.colisao(player, enemy);

    if (player.verificarColisao(player, enemy)) {
        enemy.posicao.x = -1;
        enemy.posicao.y = -1;
    }

    glutPostRedisplay();
}


//Pode remover depois, usar só pra se localizar msm
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
   

    //desenhando o chão no plano XZ
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

void projecaoPerspectiva(Player player) {
    //definindo o tipo de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), //ângulo de abertura do frustum
        (float)larguraJanela / alturaJanela, //aspect ratio da tela
        1.0f,                              //distância near
        100.0f);                           //distância far
    glMultMatrixf(glm::value_ptr(projectionMatrix));

    //definindo o posicionamento da câmera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 cameraMatrix = glm::lookAt(camPos,            //posição da câmera
        glm::vec3(player.posicao.x, player.posicao.y, player.posicao.z),  //posição para onde a câmera está direcionada
        glm::vec3(0, 0, 1)); //direção para onde o topo da câmera aponta
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
    projecaoPerspectiva(player);   //função que desenha cenário usando projeção em perspectiva
    
    luz.configurarIluminacao();
    player.desenha(texMario);
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
    glutCreateWindow("Mario Game - Computação Grafica");

    inicio();

    glutDisplayFunc(desenha);
    glutReshapeFunc(alteraJanela);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);
    glutTimerFunc(1000.0 / FPS, timer, 0);

    glutMainLoop();

    return 0;
}
