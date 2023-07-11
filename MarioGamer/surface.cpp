#include "surface.h"

#include <GL/glut.h>
#include <GL\freeglut.h>

//construtor
Surface::Surface() {

}

//M�todos privados
//m�todo que calcula a altura da superf�cie a partir da localiza��o no eixo x e y
float Surface::alturaSurface(float x, float y) {
    float d = glm::distance(glm::vec2(0, 0), glm::vec2(x, y)); //dist�ncia do ponto para o centro da superf�cie
    float z = ondaAltura * sin(onda + ondaComp * d);
    return z;
}

//m�todo que calcula o vetor normal de um tri�ngulo
glm::vec3 Surface::normalTriangle(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
    glm::vec3 n = glm::cross(B - A, C - A);
    n = glm::normalize(n);
    return n;
}

//Get's
float Surface::getLado() const {
    return lado;
}

int Surface::getDivisoes() const {
    return divisoes;
}

float Surface::getOndaAltura() const
{
    return ondaAltura;
}

float Surface::getOndaComp() const
{
    return ondaComp;
}

float Surface::getOndaVeloc() const
{
    return ondaVeloc;
}

const glm::vec3& Surface::getMatAmb() const
{
    return matAmb;
}

const glm::vec3& Surface::getMatDiff() const
{
    return matDiff;
}

const glm::vec3& Surface::getMatSpec() const
{
    return matSpec;
}

float Surface::getMatShine() const
{
    return matShine;
}

//Set's
void Surface::setLado(float newLado)
{
    lado = newLado;
}

void Surface::setDivisoes(int newDivisoes)
{
    divisoes = newDivisoes;
}

void Surface::setOndaAltura(float newOndaAltura)
{
    ondaAltura = newOndaAltura;
}

void Surface::setOndaComp(float newOndaComp)
{
    ondaComp = newOndaComp;
}

void Surface::setOndaVeloc(float newOndaVeloc)
{
    ondaVeloc = newOndaVeloc;
}

void Surface::setMatAmb(const glm::vec3& newMatAmb)
{
    matAmb = newMatAmb;
}

void Surface::setMatDiff(const glm::vec3& newMatDiff)
{
    matDiff = newMatDiff;
}

void Surface::setMatSpec(const glm::vec3& newMatSpec)
{
    matSpec = newMatSpec;
}

void Surface::setMatShine(float newMatShine)
{
    matShine = newMatShine;
}

//M�todo que modifica a vari�vel onda respons�vel por podificar o formato da onda
void Surface::move(float tempo) {
    onda += ondaVeloc * tempo; //alterar o �ngulo inicial da onda, far� ela "ondular"
}

//m�todo que desenha a superf�cie na tela
void Surface::desenha(glm::vec3 camPos, FonteLuz luz) {
    glm::vec3 P1, P2, P3, P4, PC, n;
    glm::vec3 corIluminada;
    float delta = lado / divisoes;

    // Define o modo de sombreamento para flat
    //glShadeModel(GL_FLAT);


    // Define o modo de sombreamento para Gouraud (padr�o)
    glShadeModel(GL_SMOOTH);

    //desenhando uma grade de tri�ngulos
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < divisoes; i++) {
        for (int j = 0; j < divisoes; j++) {
            //calculando os v�rtices do quadrado da grade (que ser� dividido em dois tri�ngulos)
            P1.x = -lado / 2 + i * delta;
            P1.y = -lado / 2 + j * delta;
            P1.z = alturaSurface(P1.x, P1.y);

            P2.x = -lado / 2 + (i + 1) * delta;
            P2.y = -lado / 2 + j * delta;
            P2.z = alturaSurface(P2.x, P2.y);

            P3.x = -lado / 2 + (i + 1) * delta;
            P3.y = -lado / 2 + (j + 1) * delta;
            P3.z = alturaSurface(P3.x, P3.y);

            P4.x = -lado / 2 + i * delta;
            P4.y = -lado / 2 + (j + 1) * delta;
            P4.z = alturaSurface(P4.x, P4.y);

            //Tri�ngulo 1 formado pelos pontos P1, P2 e P3
            PC = (1.0f / 3.0f) * (P1 + P2 + P3);  //calculando o ponto central do tri�ngulo
            n = normalTriangle(P1, P2, P3); //calculando o vetor normal do tri�ngulo
            corIluminada = luz.iluminacao(PC, camPos, matAmb, matDiff, matSpec, matShine, n); //calculando a ilumina��o da superficie no centro do tri�ngulo
            glColor3f(corIluminada.r, corIluminada.g, corIluminada.b); //aplicando a cor calculada para a face inteira (sombreamento flat)
            glVertex3f(P1.x, P1.y, P1.z);
            glVertex3f(P2.x, P2.y, P2.z);
            glVertex3f(P3.x, P3.y, P3.z);

            //Tri�ngulo 2 formado pelos pontos P1, P3 e P4 (repete todo o processo anterior)
            PC = (1.0f / 3.0f) * (P1 + P3 + P4);
            n = normalTriangle(P1, P3, P4);
            corIluminada = luz.iluminacao(PC, camPos, matAmb, matDiff, matSpec, matShine, n);
            glColor3f(corIluminada.r, corIluminada.g, corIluminada.b);
            glVertex3f(P1.x, P1.y, P1.z);
            glVertex3f(P3.x, P3.y, P3.z);
            glVertex3f(P4.x, P4.y, P4.z);
        }
    }
    glEnd();
}
