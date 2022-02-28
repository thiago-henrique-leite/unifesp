#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define LINE 0
#define TRIANGLE 1

const int WINDOW_WIDTH  = 400;
const int WINDOW_HEIGHT = 400;

float cl_white[3]  = {1.0, 1.0, 1.0};
float cl_red[3]    = {1.0, 0.0, 0.0};
float cl_green[3]  = {0.0, 1.0, 0.0};
float cl_blue[3]   = {0.0, 0.0, 1.0};
float cl_yellow[3] = {1.0, 1.0, 0.0};
float cl_pink[3]   = {1.0, 0.4, 0.7};
float cl_orange[3] = {1.0, 0.5, 0.0};
float cl_lilac[3]  = {0.6, 0.4, 0.7};
float cl_brown[3]  = {0.5, 0.2, 0.0};
float cl_cyan[3]   = {0.5, 1.0, 1.0};

float *cl_current = cl_blue;

float incX1=0, incY1=0;
float incX2=0, incY2=0;
float incX3=0, incY3=0;

int currentPoint = 0;

int mode = LINE;

#define CHANGE_MODE(newMode) (mode = newMode)

void printLine() {
    glBegin(GL_LINES);
            glVertex2f(0+incX1, 0+incY1);
            glVertex2f(0+incX2, 0+incY2);
    glEnd();
}

void printTriangle() {
    glBegin(GL_TRIANGLES);
            glVertex2f(0+incX1, 0+incY1);
            glVertex2f(0+incX2, 0+incY2);
            glVertex2f(0+incX3, 0+incY3);
      glEnd();
}

void print() {
    glColor3fv(cl_current);

    if(mode == LINE && currentPoint == 0)
        printLine();
    else if(mode == TRIANGLE && currentPoint == 0)
      printTriangle();
}

void draw() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    print();
    glFlush();
}

void change_point() {
    if(mode == LINE && currentPoint > 0 || mode == TRIANGLE && currentPoint > 1) 
        currentPoint = 0;
    else
        currentPoint += 1;
}

void set_increment(int x, int y, float *incx, float *incy) {
    *incx = - ((float) (WINDOW_WIDTH  / 2) - x) / (float) (WINDOW_WIDTH  / 2);
    *incy =   ((float) (WINDOW_HEIGHT / 2) - y) / (float) (WINDOW_HEIGHT / 2);
}

void mouseClick(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
                if (currentPoint == 0)
                    set_increment(x, y, &incX1, &incY1);
                else if(currentPoint == 1)
                    set_increment(x, y, &incX2, &incY2);
                else if(mode == TRIANGLE && currentPoint == 2)
                    set_increment(x, y, &incX3, &incY3);
                
                change_point();
            }
            break;
        
        default:
            break;
    }

    glutPostRedisplay();
}

void lineMode() {
    CHANGE_MODE(0);
    incX1 = incX2 = incX3 = incY1 = incY2 = incY3 = currentPoint = 0;
}

void triangleMode() {
    CHANGE_MODE(1);
    incX1 = incX2 = incX3 = incY1 = incY2 = incY3 = currentPoint = 0;
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '0':
            cl_current = cl_white;
            break;
        case '1':
            cl_current = cl_red;
            break;
        case '2':
            cl_current = cl_green;
            break;
        case '3':
            cl_current = cl_blue;
            break;
        case '4':
            cl_current = cl_yellow;
            break;
        case '5':
            cl_current = cl_pink;
            break;
        case '6':
            cl_current = cl_orange;
            break;
        case '7':
            cl_current = cl_lilac;
            break;
        case '8':
            cl_current = cl_brown;
            break;
        case '9':
            cl_current = cl_cyan;
            break;
        case 'r':
            lineMode();
            break;
        case 'R':
            lineMode();
            break;
        case 't':
            triangleMode();
            break;
        case 'T':
            triangleMode();
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
    glutCreateWindow("CG - Ex05");
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}
