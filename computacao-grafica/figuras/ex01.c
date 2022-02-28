#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

const int WINDOW_WIDTH  = 400;
const int WINDOW_HEIGHT = 400;

float incX=0, incY=0;

void printPoint() {
    glPointSize(5);

    glBegin(GL_POINTS);
        glVertex2f(0+incX, 0+incY);
    glEnd();

    glutPostRedisplay();
}

void draw() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    printPoint();
    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
                incX = - ((float) (WINDOW_WIDTH  / 2) - x) / (float) (WINDOW_WIDTH  / 2);
                incY =   ((float) (WINDOW_HEIGHT / 2) - y) / (float) (WINDOW_HEIGHT / 2);

                printf("(%.1f, %.1f)\n", incX, incY);
            }
            break;
        
        default:
            break;
    }

    glutPostRedisplay();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50 ,100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("CG - Ex01");
    glutDisplayFunc(draw);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}
