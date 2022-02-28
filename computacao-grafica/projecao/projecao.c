// Implementado por Thiago Henrique Leite - 139920

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.14159265

GLfloat inc = PI/360;

GLfloat angle = 0.0f;
GLfloat astep = 6.0f;

GLfloat k = -1.0f;
GLfloat kstep = 0.015f;

void init() 
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
}

void drawCube() 
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
    glEnd();
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.5,0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
    glEnd();
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
    glEnd();
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
    glEnd();
}

void displayFunc() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(270.0, 1.0, 0.6, 10.0);
        gluLookAt(
            -0.8, 0.9, -0.9,
            0.0, 0.0, 0.0,   
            0.0, 1.0, 0.0
        );
        glViewport(0, 300, 300, 300);
        drawCube();
    glPopMatrix();

    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(270.0, 1.0, 0.5, 10.0);
        gluLookAt(
            sin(angle*inc) + cos(angle*inc), 0.8, cos(angle*inc) - sin(angle*inc),
            0.0, 0.0, 0.0,   
            0.0, 1.0, 0.0
        );
        glViewport(300, 300, 300, 300);
        drawCube();
    glPopMatrix();

    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(300.0, 1.0, 0.5, 10.0);
        gluLookAt(
            -2.2, sin(angle*inc)+cos(angle*inc), -0.7,
            0.0, sin(angle*inc)+cos(angle*inc), 0.0,   
            0.0, 1.0, 0.0
        );
        glViewport(0, 0, 300, 300);
        drawCube();
    glPopMatrix();

    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 
        gluPerspective(300.0, 1.0, 0.5, 10.0);
        gluLookAt(
            k+k, k, k,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );
        glViewport(300, 0, 300, 300);
        drawCube();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void timerFunc(int value)
{
    if(k <= -4 || k > -0.8) kstep = kstep * (-1);
    k += kstep;
    angle -= astep;
    glutPostRedisplay();
    glutTimerFunc(1, timerFunc, 1);
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Proposta de Exercicios 02 - Parte Pratica");
    glutDisplayFunc(displayFunc);
    glutTimerFunc(10, timerFunc, 1);
    init();
    glutMainLoop();
    return 0;
}
