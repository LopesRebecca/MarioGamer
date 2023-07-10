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

    glColor3f(1.0, 0.0, 0.0); // cor vermelha
    glVertex3f(-1.0, -1.0, 1.0); // canto inferior esquerdo
    glVertex3f(1.0, -1.0, 1.0);  // canto inferior direito
    glVertex3f(1.0, 1.0, 1.0);   // canto superior direito
    glVertex3f(-1.0, 1.0, 1.0);  // canto superior esquerdo

    // Face traseira
    glColor3f(0.0, 1.0, 0.0); // cor verde
    glVertex3f(1.0, -1.0, -1.0); // canto inferior direito
    glVertex3f(-1.0, -1.0, -1.0);  // canto inferior esquerdo
    glVertex3f(-1.0, 1.0, -1.0);   // canto superior esquerdo
    glVertex3f(1.0, 1.0, -1.0);  // canto superior direito

    // Face superior
    glColor3f(0.0, 0.0, 1.0); // cor azul
    glVertex3f(-1.0, 1.0, 1.0); // canto superior esquerdo
    glVertex3f(1.0, 1.0, 1.0);  // canto superior direito
    glVertex3f(1.0, 1.0, -1.0);   // canto inferior direito
    glVertex3f(-1.0, 1.0, -1.0);  // canto inferior esquerdo

    // Face inferior
    glColor3f(1.0, 1.0, 0.0); // cor amarela
    glVertex3f(-1.0, -1.0, -1.0); // canto inferior esquerdo
    glVertex3f(1.0, -1.0, -1.0);  // canto inferior direito
    glVertex3f(1.0, -1.0, 1.0);   // canto superior direito
    glVertex3f(-1.0, -1.0, 1.0);  // canto superior esquerdo

    // Face lateral esquerda
    glColor3f(1.0, 0.0, 1.0); // cor magenta
    glVertex3f(-1.0, -1.0, -1.0); // canto inferior esquerdo
    glVertex3f(-1.0, -1.0, 1.0);  // canto inferior direito
    glVertex3f(-1.0, 1.0, 1.0);   // canto superior direito
    glVertex3f(-1.0, 1.0, -1.0);  // canto superior esquerdo

    // Face lateral direita
    glColor3f(0.0, 1.0, 1.0); // cor ciano
    glVertex3f(1.0, -1.0, 1.0); // canto inferior esquerdo
    glVertex3f(1.0, -1.0, -1.0);  // canto inferior direito
    glVertex3f(1.0, 1.0, -1.0);   // canto superior direito
    glVertex3f(1.0, 1.0, 1.0);  // canto superior esquerdo 
    
    glEnd();
}
