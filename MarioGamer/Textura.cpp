#include "Textura.h"

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <iostream> 
#include <string>

#include "stbi_image.h"

using namespace std;

Textura::Textura() {}

//função que carrega uma textura. Recebe o nome do arquivo e devolve o código identificador da textura
unsigned int Textura::carregaTextura(const char fileName[]) {
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
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //minificação - quando muitos texels cabem em um único pixel

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