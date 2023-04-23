
#include <iostream>
#include <GL/glut.h>
#include <GL\freeglut.h>


void inicio() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
}



void desenha() {
    glClear(GL_COLOR_BUFFER_BIT); 

    glColor3f(1.0, 0.0, 0.0);   
    glBegin(GL_TRIANGLES);       
    glVertex2f(-0.5, -0.5);  
    glVertex2f(0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                         
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowPosition(200, 200);              
    glutInitWindowSize(300, 300);                  
    glutCreateWindow("00 - Ola Mundo");            

    inicio();

    glutDisplayFunc(desenha);   

    glutMainLoop();            

    return 0;
}