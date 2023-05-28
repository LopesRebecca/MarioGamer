#include "Formas.h"


#include <cmath>
#include <GL/glut.h>


Formas::Formas() {

}

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

void Formas::quadrado(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x +1 , y);
    glVertex2f(x+1, y+1);
    glVertex2f(x, y + 1);
    glEnd();
}
