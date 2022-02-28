#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>

GLfloat YELLOW[4] = {1,1,0,1};
GLfloat WHITE[4]  = {1,1,1,1};
GLfloat BLACK[4]  = {0,0,0,1};
GLfloat GREEN[4]  = {0,1,0,1};
GLfloat BLUE[4]   = {0,0,1,1};
GLfloat RED[4]    = {1,0,0,1};

GLfloat angleRotation = 0.0f;

GLfloat lightX = 0.0f;
GLfloat lightY = 0.0f;

GLfloat lightDir[3] = {0,0,-1};

void lightning() {
    GLfloat initialPositionLight[4] = {lightX, lightY, 5.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION, initialPositionLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, WHITE);
    glLightfv(GL_LIGHT0,GL_SPECULAR, WHITE);
    glLightfv(GL_LIGHT0,GL_AMBIENT, BLACK);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, lightDir);
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF, 17.0f);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 0.3f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
    glEnable(GL_DEPTH_TEST); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
    gluLookAt(0.0, 0.0, 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);  
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2, 2);
    glViewport(0, 0, 500, 500);
    glPushMatrix();
}

void mouseClick(int button, int state, int x, int y) {
    switch(button) 
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN) {
            lightX = - ((float) (500/2) - x) / (float) (500/2);
            lightY =   ((float) (500/2) - y) / (float) (500/2);

            printf("(%.1f, %.1f)\n", lightX, lightY);
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void sphere(GLfloat t_x, GLfloat t_y, GLfloat t_z, GLfloat color[]) {
    glPushMatrix();
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
        glRotatef(angleRotation,0.0,0.0,1.0);
        glTranslatef(t_x,t_y,t_z);
        glutSolidSphere(0.25,40,40);
    glPopMatrix();
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();

    sphere(-1.5,+0.0,+0.0,RED);
    sphere(+1.5,+0.0,+0.0,BLUE);
    sphere(+0.0,-1.5,+0.0,GREEN);
    sphere(+0.0,+1.5,+0.0,YELLOW);

    lightning();
    glFlush();
}

void timerFunc(int value)
{
    angleRotation += 0.05;
    glutPostRedisplay();
    glutTimerFunc(1, timerFunc, 1);
}

int main(int argc, char **argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
    glutCreateWindow("Thiago Leite - Iluminacao");
    init();
    glutDisplayFunc(displayFunc);
    glutMouseFunc(mouseClick);
    glutTimerFunc(1,timerFunc,1);
    glutMainLoop();
    return 0;
}
