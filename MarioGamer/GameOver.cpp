#include "GameOver.h"

#include <GL/glut.h>
#include <GL\freeglut.h>
#include<glm/glm.hpp>

#include "Formas.h"


GameOver::GameOver() {
    posicao = glm::vec2(0.25, 2);
    cor = glm::vec3(1, 0, 1);
}

void GameOver::gameOver(float x, float y, float z, void* font, const char* string) {
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, 0);
    glScalef(6, 4, 1);
    glColor3f(cor.r, cor.b, cor.g); 
    //Formas::quadrado(2,2);
    glPopMatrix();

    const unsigned char* str = reinterpret_cast<const unsigned char*>(string);
    glColor3f(0, 0, 0);
    glRasterPos3f(x, y, z);
    glutBitmapString(font, str);

    return;
}
