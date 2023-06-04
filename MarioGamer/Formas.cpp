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
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();
}
