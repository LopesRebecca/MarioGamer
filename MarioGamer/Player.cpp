#include "Player.h"

#include <GL/glut.h>
#include <GL\freeglut.h>
#include<glm/glm.hpp>

#include "Formas.h"
#include "Plataforma.h"
#include "Textura.h"
#include "stbi_image.h"


#include <iostream> 
using namespace std;
Player::Player() {
    posicao = glm::vec3(0.25, 2, 3);
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
void Player::desenha(unsigned char texturaId) {
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, posicao.z);
    glScalef(tamanho, tamanho, tamanho);
    glColor3f(cor.r, cor.g, cor.b);
    cubo(texturaId);

    glPopMatrix();
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

void Player::cubo(unsigned int texturaId) {
    glm::vec3 verticePos[8];
    glm::vec2 texturePos[12];

    //todas as posições dos vértices do cubo
    verticePos[0] = glm::vec3(-1, -1, -1);
    verticePos[1] = glm::vec3(-1, -1, 1);
    verticePos[2] = glm::vec3(-1, 1, -1);
    verticePos[3] = glm::vec3(-1, 1, 1);
    verticePos[4] = glm::vec3(1, -1, -1);
    verticePos[5] = glm::vec3(1, -1, 1);
    verticePos[6] = glm::vec3(1, 1, -1);
    verticePos[7] = glm::vec3(1, 1, 1);

    //todas as posições da textura que serão utilizadas para mapear nos vértices do cubo
    texturePos[0] = glm::vec2(0.00, 0.0);
    texturePos[1] = glm::vec2(0.33, 0.0);
    texturePos[2] = glm::vec2(0.67, 0.0);
    texturePos[3] = glm::vec2(1.00, 0.0);
    texturePos[4] = glm::vec2(0.00, 0.5);
    texturePos[5] = glm::vec2(0.33, 0.5);
    texturePos[6] = glm::vec2(0.67, 0.5);
    texturePos[7] = glm::vec2(1.00, 0.5);
    texturePos[8] = glm::vec2(0.00, 1.0);
    texturePos[9] = glm::vec2(0.33, 1.0);
    texturePos[10] = glm::vec2(0.67, 1.0);
    texturePos[11] = glm::vec2(1.00, 1.0);

    int facesVert[6][4];
    int facesTex[6][4];

    //Cada face conecta 4 vértices. Anotando os índices do vetor verticePos que cada face conecta.
    facesVert[0][0] = 0; facesVert[0][1] = 1; facesVert[0][2] = 3; facesVert[0][3] = 2;
    facesVert[1][0] = 0; facesVert[1][1] = 4; facesVert[1][2] = 5; facesVert[1][3] = 1;
    facesVert[2][0] = 4; facesVert[2][1] = 6; facesVert[2][2] = 7; facesVert[2][3] = 5;
    facesVert[3][0] = 6; facesVert[3][1] = 2; facesVert[3][2] = 3; facesVert[3][3] = 7;
    facesVert[4][0] = 1; facesVert[4][1] = 5; facesVert[4][2] = 7; facesVert[4][3] = 3;
    facesVert[5][0] = 0; facesVert[5][1] = 2; facesVert[5][2] = 6; facesVert[5][3] = 4;

    //Cada face precisa de 4 coordenadas de textura. Anotando os índices do vetor texturaPos que cada face irá precisar.
    facesTex[0][0] = 0; facesTex[0][1] = 1; facesTex[0][2] = 5;  facesTex[0][3] = 4;
    facesTex[1][0] = 1; facesTex[1][1] = 2; facesTex[1][2] = 6;  facesTex[1][3] = 5;
    facesTex[2][0] = 2; facesTex[2][1] = 3; facesTex[2][2] = 7;  facesTex[2][3] = 6;
    facesTex[3][0] = 4; facesTex[3][1] = 5; facesTex[3][2] = 9;  facesTex[3][3] = 8;
    facesTex[4][0] = 5; facesTex[4][1] = 6; facesTex[4][2] = 10; facesTex[4][3] = 9;
    facesTex[5][0] = 6; facesTex[5][1] = 7; facesTex[5][2] = 11; facesTex[5][3] = 10;

    //desenhando o cubo com a textura
    glBindTexture(GL_TEXTURE_2D, texturaId); //ativando a textura
    glBegin(GL_QUADS);                       //todas as faces são quadrados
    for (int i = 0; i < 6; i++) {            //desenhe um total de 6 faces
        for (int v = 0; v < 4; v++) {        //passando por cada um dos 4 vértices de cada face
            glTexCoord2f(texturePos[facesTex[i][v]].s, texturePos[facesTex[i][v]].t); //coordenada de textura localizada no índice armazenado naquela face
            glVertex3f(verticePos[facesVert[i][v]].x, verticePos[facesVert[i][v]].y, verticePos[facesVert[i][v]].z); //coordenada do vértice localizada no índice armazenado naquela face
        }
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0); //após terminar o desenho do objeto, desativa a textura
}

//função que carrega uma textura. Recebe o nome do arquivo e devolve o código identificador da textura
unsigned int Player::carregaTextura(const char fileName[]) {
    unsigned int texId;
    int largura, altura, nCanais;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imagem = stbi_load(fileName, &largura, &altura, &nCanais, 0); //qtd de pixels na largura e altura preenchidas automaticamente
    if (imagem == NULL) //verificação se o carregamento da imagem ocorreu com sucesso
        cout << "Erro, Imagem não carregada" << endl;
    else
        cout << "Imagem carregada com sucesso" << endl;

    glEnable(GL_TEXTURE_2D);             //habilitando o uso de texturas
    glGenTextures(1, &texId);            //gerando um objeto textura na máquina OpenGL
    glBindTexture(GL_TEXTURE_2D, texId); //ativando o objeto textura recém criado

    //parâmetros da textura caso coordenadas além do intervalo [0,1] seja utilizado
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //repetição espelhada no eixo S
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //repetição espelhada no eixo T

    //parâmetros da textura para filtragem quando tamanho de pixel e texel sejam diferentes (interpolação linear em ambos os casos)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnificação - quando um texel cobre vários pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //minificação - quando muitos texels cabem em um único pixel

    //parâmetros da textura para indicar se a textura deve-se combinar ou substituir a atual cor do objeto
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //GL_REPLACE = substitui, GL_COMBINE = combina (ou multiplica)

    //envio dos dados da textura para o OpenGL
    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB,
        largura,          //largura da textura
        altura,           //altura da textura (carregadas automaticamente pela função da biblioteca)
        0,
        GL_RGB,           //formato da cor da textura
        GL_UNSIGNED_BYTE, //tipos de dados de cada texel da textura
        imagem);          //ponteiro para os dados da textura

    glBindTexture(GL_TEXTURE_2D, 0); //desativando o objeto textura criado (ativa apenas quando for usar em algum objeto)

    stbi_image_free(imagem); //memória RAM pode ser liberada pois a imagem foi enviada ao OpenGL (memória gráfica)

    return texId; //retornando o identificador da textura (sem ele não há como acessar a textura carregada)
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


//Maria Rebecca - 495703
void Player::colisaoPlataforma(Plataforma plataforma) {
    if (posicao.x < (plataforma.posicao.x + plataforma.width) &&
        posicao.x + width > (plataforma.posicao.x) &&
        posicao.y < (plataforma.posicao.y + plataforma.height) &&
        posicao.y + height > (plataforma.posicao.y)){
        posicao.y = plataforma.posicao.y + plataforma.height;
    }
}




