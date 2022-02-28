#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TIME 100
#define MIN_TIME 5

float CL_BLACK[3]  = {0.00, 0.00, 0.00};
float CL_WHITE[3]  = {1.00, 1.00, 1.00};
float CL_RED[3]    = {1.00, 0.00, 0.00};
float CL_GREEN[3]  = {0.00, 0.36, 0.17};
float CL_BLUE[3]   = {0.00, 0.00, 1.00};
float CL_YELLOW[3] = {1.00, 0.84, 0.00};
float CL_PINK[3]   = {1.00, 0.40, 0.70};
float CL_ORANGE[3] = {1.00, 0.50, 0.00};

GLint start_rotation = 0, button_left = 0, button_right = 0;

GLint iteration_index = 0;

GLfloat rotation_angle = 0;

GLint time = 100;

void init();
void buildExternalTriangle(GLfloat, GLfloat*);
void buildInternalTriangle(GLfloat, GLfloat*);
void buildCircle();
void buildStick();
void buildCatavento();
void display();
void increase_time();
void decrease_time();
void start_catavento_rotation();
void stop_catavento_rotation();
void left_button();
void right_button(); 
void timer_function(int);
void timer_function(int);
void mouse_function(int, int, int, int);
void special_func(int, int, int);

void init()
{
     glClearColor(0.88, 0.88, 0.88, 0.00);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glOrtho(-7.0,7.0,-7.0,7.0,-7.0,7.0);
     glPushMatrix();
}

void buildExternalTriangle(GLfloat angle, GLfloat *color) 
{
    glPushMatrix();
        glRotatef(angle,0,0,1);
        glColor3fv(color);
        glBegin(GL_TRIANGLES);
            glVertex2f(+0.00, +0.00);
            glVertex2f(-0.25, +0.25);
            glVertex2f(+0.00, +0.50);
        glEnd();
    glPopMatrix();
}

void buildInternalTriangle(GLfloat angle, GLfloat *color) 
{
    glPushMatrix();
        glRotatef(angle,0,0,1);
        glColor3fv(color);
        glBegin(GL_TRIANGLES);
            glVertex2f(+0.00, +0.00);
            glVertex2f(-0.25, +0.00);
            glVertex2f(-0.25, +0.25);
        glEnd();
    glPopMatrix();
}

void buildCircle() 
{
    GLfloat ang = 0;

    glColor3fv(CL_BLACK);
    glBegin(GL_POLYGON);
        for(int i=0; i<50; i++){
            glVertex2f(0.03*cos(ang),0.03*sin(ang));
            ang = ang+(2*M_PI)/50;
        }
    glEnd();
}

void buildStick() 
{
    glColor3fv(CL_BLACK);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2f(+0.0, +0.0);
        glVertex2f(+0.0, -1.0);
    glEnd();
}

void buildCatavento() 
{
    buildStick();

    glPushMatrix();
        glRotatef(rotation_angle,0.0,0.0,1.0);
        glRotatef(20,0,0,1);
        buildExternalTriangle(0, CL_BLUE);
        buildExternalTriangle(-180, CL_GREEN);
        buildExternalTriangle(-90, CL_RED);
        buildExternalTriangle(90, CL_YELLOW);

        buildInternalTriangle(0, CL_GREEN);
        buildInternalTriangle(-180,CL_BLUE);
        buildInternalTriangle(-90, CL_YELLOW);
        buildInternalTriangle(90, CL_RED);
    glPopMatrix();

    buildCircle();
}

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.88, 0.88, 0.88, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    buildCatavento();

    glFlush();
}

void increase_time() 
{
    time *= 2;
}

void decrease_time() 
{
    time /= 2;
}

void start_catavento_rotation() 
{
    glutTimerFunc(MAX_TIME,timer_function,1); start_rotation = 1;
}

void stop_catavento_rotation() 
{
    time = MAX_TIME; start_rotation = 0; button_left = 0; button_right = 0;
}

void left_button() 
{  
    if(!start_rotation) start_catavento_rotation();

    if(iteration_index % 60 == 0) 
        if(time > MIN_TIME) decrease_time();

    iteration_index++;
}

void right_button() 
{
    if(iteration_index % 60 == 0)
        increase_time();

    if(time >= MAX_TIME) stop_catavento_rotation();

    iteration_index++;
}

void timer_function(int value)
{
    if(start_rotation) 
    {
        rotation_angle -= 5;

        if(button_left) left_button();
        if(button_right) right_button();
        
        glutPostRedisplay();
        glutTimerFunc(time,timer_function, 1);
    }

    printf("time: %d\n", time);
    printf("rotation_angle: %.2f\n", rotation_angle);
    printf("botão direito: %d\n", button_right);
    printf("botão esquerdo: %d\n", button_left);
    printf("start rotation: %d\n", start_rotation);
}

void mouse_function(int button, int state, int x, int y)
{
    switch(button) 
    {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) 
            {
                if(!start_rotation) start_catavento_rotation();

                button_left = 1; button_right = 0; iteration_index = 0;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN) 
            {
                button_right = 1; button_left = 0; iteration_index = 0;
            }
            break;
        default:
            break;
    }
}

void special_func(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_RIGHT:
            if(!start_rotation) start_catavento_rotation();
            if(time > MIN_TIME) decrease_time();
            break;
        case GLUT_KEY_LEFT:
            increase_time();
            if(time >= MAX_TIME) stop_catavento_rotation();
           break ;
        default:
           break;
     }
}

int main(int argc , char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(600,600);
    glutCreateWindow("Thiago Leite - Catavento 2D");
    glutDisplayFunc(display);
    glutSpecialFunc(special_func);
    glutTimerFunc(time,timer_function,1);
    glutMouseFunc(mouse_function);
    init();
    glutMainLoop();
}
