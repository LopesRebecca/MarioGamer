#include "Formas.h"


#include <cmath>
#include <GL/glut.h>


Formas::Formas() {

}

//Pedro Henrique - 494569
void Formas::circulo(int divisoes) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < divisoes; i++) {
        float ang = i * (2.0 * 3.14 / divisoes);
        float x = cos(ang);
        float y = sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}

//Maria Rebecca - 495703
void Formas::quadrado() {
    glBegin(GL_QUADS);

    // Lado frontal
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);

    // Lado traseiro
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, -1.0);

    // Lado superior
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);

    // Lado inferior
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);

    // Lado direito
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);

    // Lado esquerdo
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
    
    glEnd();
}
