#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define PI 3.1415926

GLUquadricObj *quadricObject;

GLint vehicule = 0; // (0) Carro # (1) Ônibus

// Ângulo de rotação das rodas
GLfloat angX = 0.0;

// Incremento da velocidade dos veículos
GLfloat inc = 0.04;
GLfloat incInitial = 0.04;

// Parâmetros de movimentação dos veículos
GLfloat theta = 0.0;
GLfloat right = -10.0;

// Array de Cores
GLfloat CL_BLACK[3]  = {0.00, 0.00, 0.00};
GLfloat CL_WHITE[3]  = {1.00, 1.00, 1.00};
GLfloat CL_RED[3]    = {1.00, 0.00, 0.00};
GLfloat CL_GREEN[3]  = {0.00, 1.00, 0.00};
GLfloat CL_BLUE[3]   = {0.00, 0.00, 1.00};
GLfloat CL_YELLOW[3] = {1.00, 1.00, 0.00};
GLfloat CL_PINK[3]   = {1.00, 0.40, 0.70};
GLfloat CL_ORANGE[3] = {1.00, 0.50, 0.00};
GLfloat CL_LILAC[3]  = {0.60, 0.40, 0.70};
GLfloat CL_BROWN[3]  = {0.50, 0.20, 0.00};
GLfloat CL_CYAN[3]   = {0.50, 1.00, 1.00};
GLfloat CL_GRAY[3]   = {0.88, 0.88, 0.88};

// Posição inicial do semáforo
GLint greenSignal  = 1;
GLint yellowSignal = 0;
GLint redSignal    = 0;

GLfloat *colorGreenSignal  = CL_GREEN;
GLfloat *colorYellowSignal = CL_BLACK;
GLfloat *colorRedSignal    = CL_BLACK;

// Parâmetros de iluminação
GLfloat diffuseColor = 0.75;

GLfloat lightX = -0.5f;
GLfloat lightY = +0.5f;

GLfloat light1X = +0.0f;
GLfloat light1Y = -0.5f;

GLfloat x_ortho; 
GLfloat y_ortho;

void init() 
{
    glClearColor(0.0,0.75,1.0,0.0);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 1, 1);
    
    gluLookAt(
        0.0, 0.0, 1.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    quadricObject = gluNewQuadric();
}

void lightning()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 1, 1);
    
    gluLookAt(
        0.0, 0.0, 1.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    GLfloat ambientlightPos[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffusePos[4] = {diffuseColor, diffuseColor, diffuseColor, 1.0};

    GLfloat lightZeroPos[4] = {lightX, lightY, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusePos);

    GLfloat lightOnePos[4] = {light1X, light1Y, 0.0, 0.8};

    glLightfv(GL_LIGHT1, GL_POSITION, lightOnePos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientlightPos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffusePos);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientlightPos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffusePos);
}

void background() 
{
    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(90.0, 1.0, 1, 1);
        glOrtho(-7.0,7.0,-7.0,7.0,-7.0,7.0);

        gluLookAt(
            0.0, 0.0, 1.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );

        glViewport(0, 0, 800, 800);

        // Asfalto
        glPushMatrix();
            glTranslated(0, -5, -7);
            glColor3fv(CL_GRAY);
            glScaled(10.0,1.2,1.0);
            glutSolidCube(5);
        glPopMatrix();

        // Guia
        glPushMatrix();
            glTranslated(0, -2.0, -6.9);
            glColor3fv(CL_BLACK);
            glScaled(10.0,0.03,1.0);
            glutSolidCube(5);
        glPopMatrix();

        // Contorno 1 listra 1
        glPushMatrix();
            glTranslated(0, -4.15, -6.9);
            glColor3fv(CL_BLACK);
            glScaled(10.0,0.01,1.0);
            glutSolidCube(5);
        glPopMatrix();

        // Listra 1
        glPushMatrix();
            glTranslated(0, -4.25, -6.9);
            glColor3fv(CL_YELLOW);
            glScaled(10.0,0.03,1.0);
            glutSolidCube(5);
        glPopMatrix();

        // Contorno 2 listra 1
        glPushMatrix();
            glTranslated(0, -4.35, -6.9);
            glColor3fv(CL_BLACK);
            glScaled(10.0,0.01,1.0);
            glutSolidCube(5);
        glPopMatrix();

        // Contorno 1 listra 2
        glPushMatrix();
            glTranslated(0, -4.65, -6.9);
            glColor3fv(CL_BLACK);
            glScaled(10.0,0.01,1.0);
            glutSolidCube(5);
        glPopMatrix();

        // Listra 2
        glPushMatrix();
            glTranslated(0, -4.75, -6.9);
            glColor3fv(CL_YELLOW);
            glScaled(10.0,0.03,1.0);
            glutSolidCube(5);
        glPopMatrix();

        // Contorno 2 listra 2
        glPushMatrix();
            glTranslated(0, -4.85, -6.9);
            glColor3fv(CL_BLACK);
            glScaled(10.0,0.01,1.0);
            glutSolidCube(5);
        glPopMatrix();

        // Sol
        glPushMatrix();
            x_ortho = lightX * 7; y_ortho = lightY * 7;
            printf("(%.2f, %.2f)\n", x_ortho, y_ortho);

            glTranslatef(x_ortho, y_ortho, -6.5);

            // Raios
            glPushMatrix();
                glColor3fv(CL_YELLOW);
                glTranslated(0,0,1.0);
                glScaled(11.0,10.0,1.0);
                glutSolidCube(0.30);
                glRotatef(-30,0.0,0.0,1.0);
                glutSolidCube(0.30);
                glRotatef(-120,0.0,0.0,1.0);
                glutSolidCube(0.30);
            glPopMatrix();

            // Centro
            glPushMatrix();
                glColor3fv(CL_ORANGE);
                glScaled(1.0,1.0,1.0);
                glutSolidSphere(1.7, 50, 50);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void build_ap(GLfloat x_t, GLfloat y_t, GLfloat scale, GLfloat *color)
{
    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(90.0, 1.0, 1, 1);
        glOrtho(-7.0,7.0,-7.0,7.0,-7.0,7.0);

        gluLookAt(
            0.0, 0.0, 1.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );

        glViewport(0, 0, 800, 800);

        glPushMatrix();
            glTranslatef(x_t, y_t, 1.0);
            glScalef(scale, scale, scale);

            // Contorno da Torre
            glPushMatrix();
                glTranslated(5, 0.96, -5.5);
                glRotatef(30,0,1,0);
                glColor3fv(CL_BLACK);
                glScaled(0.7,1.3,0.3);
                glScalef(1.11,1.104,1);
                glutWireCube(4);
            glPopMatrix();

            // Torre
            glPushMatrix();
                glTranslated(5, 0.96, -5.5);
                glRotatef(30,0,1,0);
                glColor3fv(color);
                glScaled(0.7,1.3,0.3);
                glScalef(1.1,1.1,1);
                glutSolidCube(4);
            glPopMatrix();

            // Janelas
            glPushMatrix();
                glTranslated(0.26, 0.0, 0.0);
                glPushMatrix();
                    glTranslated(4.6, 2.7, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.21,0.107,0.1);
                    glutWireCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(4.6, 2.7, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_CYAN);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.2,0.1,0.1);
                    glutSolidCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(5.4, 2.7, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.21,0.107,0.1);
                    glutWireCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(5.4, 2.7, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_CYAN);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.2,0.1,0.1);
                    glutSolidCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(4.6, 0.8, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.21,0.107,0.1);
                    glutWireCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(4.6, 0.8, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_CYAN);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.2,0.1,0.1);
                    glutSolidCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(5.4, 0.8, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.21,0.107,0.1);
                    glutWireCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(5.4, 0.8, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_CYAN);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.2,0.1,0.1);
                    glutSolidCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(4.6, 1.7, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.21,0.107,0.1);
                    glutWireCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(4.6, 1.7, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_CYAN);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.2,0.1,0.1);
                    glutSolidCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(5.4, 1.7, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.21,0.107,0.1);
                    glutWireCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(5.4, 1.7, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_CYAN);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.2,0.1,0.1);
                    glutSolidCube(4);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(5, -0.95, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.21,0.301,0.1);
                    glutWireCube(4);
                glPopMatrix();

                // Porta
                glPushMatrix();
                    glTranslated(5, -0.95, -3.2);
                    glRotatef(30,0,1,0);
                    glColor3fv(CL_BROWN);
                    glScaled(0.8,1.6,0.3);
                    glScalef(0.2,0.3,0.1);
                    glutSolidCube(4);
                glPopMatrix();
            glPopMatrix();

            // Maçaneta
            glPushMatrix();
                glTranslated(5.1, -0.95, -3.05);
                glRotatef(30,0,1,0);
                glColor3fv(CL_BLACK);
                glutSolidSphere(0.08, 50, 50);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void build_semaphore() 
{
    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(90.0, 1.0, 1, 1);
        glOrtho(-7.0,7.0,-7.0,7.0,-7.0,7.0);
        glTranslatef(0,0,2.0);

        gluLookAt(
            0.0, 0.0, 1.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );

        glViewport(0, 0, 800, 800);

        glPushMatrix();
            glRotatef(30, 0, 1, 0);
            glTranslatef(-6.0, -1.2, -1.5);
            glScalef(0.6, 0.6, 0.6);

            // Haste semáforo
            glPushMatrix();
                glTranslatef(0, 1.0, -0.2);
                glColor3fv(CL_BROWN);
                glRotatef(90, 1, 0, 0);
                glScalef(1.2, 1.2, 1.32);
                gluCylinder(quadricObject, 0.15, 0.15, 5, 5, 30);
            glPopMatrix();

            // Caixa externa semáforo
            glPushMatrix();
                glTranslatef(0, 1.8, -0.2);
                glColor3fv(CL_BLACK);
                glScalef(0.71, 0.9507, 0.2);
                glutWireCube(3);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 1.8, -0.2);
                glColor3fv(CL_GRAY);
                glScalef(0.7, 0.95, 0.2);
                glutSolidCube(3);
            glPopMatrix();

            // Caixa interna semáforo
            glPushMatrix();
                glTranslatef(0, 1.8, 0.0001);
                glColor3fv(CL_BLACK);
                glScalef(0.41, 0.807, 0.2);
                glutWireCube(3);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 1.8, 0.0001);
                glColor3fv(CL_BROWN);
                glScalef(0.4, 0.8, 0.2);
                glutSolidCube(3);
            glPopMatrix();

            // Sinal vermelho
            glPushMatrix();
                glTranslatef(0, 2.5, 0.3);
                glColor3fv(colorRedSignal);
                glutSolidSphere(0.25, 50, 50);
            glPopMatrix();

            // Sinal amarelo
            glPushMatrix();
                glTranslatef(0, 1.8, 0.3);
                glColor3fv(colorYellowSignal);
                glutSolidSphere(0.25, 50, 50);
            glPopMatrix();

            // Sinal verde
            glPushMatrix();
                glTranslatef(0, 1.1, 0.3);
                glColor3fv(colorGreenSignal);
                glutSolidSphere(0.25, 50, 50);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void build_car() 
{
    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(90.0, 1.0, 1, 1);
        glOrtho(-7.0,7.0,-7.0,7.0,-7.0,7.0);
        glTranslatef(0,0,3.0);

        gluLookAt(
            0.0, 0.0, 1.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );

        glViewport(0, 0, 800, 800);

        glPushMatrix();
            glRotatef(180, 0, 1, 0);
            glRotatef(7, 0, 1, 0);
            glTranslatef(right, 0.0, 0);
            glScalef(2.0, 2.0, 2.0);

            // Carroceria
            glPushMatrix();
                glTranslatef(0, -2.8, -0.2);
                glColor3fv(CL_BLACK);
                glScalef(1.2001, 0.201, 0.5);
                glutWireCube(3);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, -2.8, -0.2);
                glColor3fv(CL_RED);
                glScalef(1.2, 0.2, 0.5);
                glutSolidCube(3);
            glPopMatrix();

            // Teto
            glPushMatrix();
                glTranslatef(0, -2.2, -0.2);
                glColor3fv(CL_BLACK);
                glScalef(0.6, 0.2, 0.5);
                glutSolidCube(3);
            glPopMatrix();

            // Farol esquerdo
            glPushMatrix();
                glRotatef(0,0,1,0);
                glTranslatef(1.7, -2.8, 0.2);
                glColor3fv(CL_WHITE);
                glScalef(0.5, 0.5, 0.5);
                glutSolidSphere(0.40, 50, 50);
            glPopMatrix();

            // Farol direito
            glPushMatrix();
                glRotatef(0,0,1,0);
                glTranslatef(1.7, -2.8, -0.7);
                glColor3fv(CL_WHITE);
                glScalef(0.5, 0.5, 0.5);
                glutSolidSphere(0.40, 50, 50);
            glPopMatrix();

            // Janela dianteira
            glPushMatrix();
                glTranslatef(-0.45, -2.2, -0.2);
                glColor3fv(CL_WHITE);
                glScalef(0.20, 0.10, 0.51);
                glutSolidCube(3);
            glPopMatrix();

            // Janela traseira
            glPushMatrix();
                glTranslatef(0.45, -2.2, -0.2);
                glColor3fv(CL_WHITE);
                glScalef(0.20, 0.10, 0.51);
                glutSolidCube(3);
            glPopMatrix();

            // Janelas frontal e traseira
            glPushMatrix();
                glTranslatef(0, -2.2, -0.2);
                glColor3fv(CL_WHITE);
                glScalef(0.61, 0.10, 0.42);
                glutSolidCube(3);
            glPopMatrix();

            // Roda frontal direita
            glPushMatrix();
                glTranslatef(0.90, -3.0, 0.55);
                glRotatef(90,1,0,0);
                glRotatef(90,0,0,1);
                glRotatef(angX,1,0,0);
                glRotatef(-90,0,1,0);
                glColor3fv(CL_BLACK);
                glScaled(0.5,0.5,0.5);
                glutWireTorus(0.28,0.40,40,40);
                glTranslatef(-0.90, +3.0, -0.55);
                glRotatef(theta, 0.0, 0.0, 1.0);
                glTranslatef(0.90, -3.0, 0.55);
            glPopMatrix();

            // Roda traseira direita
            glPushMatrix();
                glTranslatef(-0.90, -3.0, 0.55);
                glRotatef(90,1,0,0);
                glRotatef(90,0,0,1);
                glRotatef(angX,1,0,0);
                glRotatef(-90,0,1,0);
                glColor3fv(CL_BLACK);
                glScaled(0.5,0.5,0.5);
                glutWireTorus(0.28,0.40,40,40);
                glTranslatef(+0.90, +3.0, -0.55);
                glRotatef(theta, 0.0, 0.0, 1.0);
                glTranslatef(-0.90, -3.0, +0.55);
            glPopMatrix();

            // Roda frontal esquerda
            glPushMatrix();
                glTranslatef(0.90, -3.0, -0.95);
                glRotatef(90,1,0,0);
                glRotatef(90,0,0,1);
                glRotatef(angX,1,0,0);
                glRotatef(-90,0,1,0);
                glColor3fv(CL_BLACK);
                glScaled(0.5,0.5,0.5);
                glutWireTorus(0.28,0.40,40,40);
                glTranslatef(-0.90, +3.0, +0.95);
                glRotatef(theta, 0.0, 0.0, 1.0);
                glTranslatef(+0.90, -3.0, -0.95);
            glPopMatrix();

            // Roda traseira esquerda
            glPushMatrix();
                glTranslatef(-0.90, -3.0, -0.95);
                glRotatef(90,1,0,0);
                glRotatef(90,0,0,1);
                glRotatef(angX,1,0,0);
                glRotatef(-90,0,1,0);
                glColor3fv(CL_BLACK);
                glScaled(0.5,0.5,0.5);
                glutWireTorus(0.28,0.40,40,40);
                glTranslatef(+0.90, +3.0, +0.95);
                glRotatef(theta, 0.0, 0.0, 1.0);
                glTranslatef(-0.90, -3.0, -0.95);
            glPopMatrix();

            // Escapamento direito
            glPushMatrix();
                glRotatef(90, 0, 1, 0);
                glTranslatef(-0.3, -3, -2);
                glColor3fv(CL_GRAY);
                glScaled(0.5,0.5,0.5);
                gluCylinder(quadricObject, 0.15, 0.15, 5, 5, 30);
            glPopMatrix();

            // Escapamento esquerdo
            glPushMatrix();
                glRotatef(90, 0, 1, 0);
                glTranslatef(0.7, -3, -2);
                glColor3fv(CL_GRAY);
                glScaled(0.5,0.5,0.5);
                gluCylinder(quadricObject, 0.15, 0.15, 5, 5, 30);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void build_bus() 
{
    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(90.0, 1.0, 1, 1);
        glOrtho(-7.0,7.0,-7.0,7.0,-7.0,7.0);
        glTranslatef(0,0,1.5);

        gluLookAt(
            0.0, 0.0, 1.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );

        glViewport(0, 0, 800, 800);

        glPushMatrix();
            glRotatef(9, 0, 1, 0);
            glTranslatef(-right, 0.5, -1.0);
            glScalef(1.3, 1.3, 1.3);

            // Carroceria
            glPushMatrix();
                glTranslatef(0, -2.8, -0.2);
                glColor3fv(CL_BLACK);
                glScalef(2.3301, 0.2005, 0.5);
                glutWireCube(4);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, -2.8, -0.2);
                glColor3fv(CL_PINK);
                glScalef(2.33, 0.2, 0.5);
                glutSolidCube(4);
            glPopMatrix();

            // Teto
            glPushMatrix();
                glTranslatef(0, -1.6, -0.2);
                glColor3fv(CL_BLACK);
                glScalef(2.3301, 0.4005, 0.5);
                glutWireCube(4);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, -1.6, -0.2);
                glColor3fv(CL_BLUE);
                glScalef(2.33, 0.4, 0.5);
                glutSolidCube(4);
            glPopMatrix();

            // Farol esquerdo
            glPushMatrix();
                glRotatef(0,0,1,0);
                glTranslatef(-4.58, -2.8, 0.5);
                glColor3fv(CL_WHITE);
                glScalef(0.5, 0.5, 0.5);
                glutSolidSphere(0.40, 50, 50);
            glPopMatrix();

            // Farol direito
            glPushMatrix();
                glRotatef(0,0,1,0);
                glTranslatef(-4.58, -2.8, -0.9);
                glColor3fv(CL_WHITE);
                glScalef(0.5, 0.5, 0.5);
                glutSolidSphere(0.40, 50, 50);
            glPopMatrix();

            // Janelas frontal e traseira
            glPushMatrix();
                glTranslatef(0, -1.6, -0.2);
                glColor3fv(CL_WHITE);
                glScalef(2.34, 0.35, 0.45);
                glutSolidCube(4);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-0.25,0,0);
                // Janela 1
                glPushMatrix();
                    glTranslatef(-3.5, -1.6, -0.2);
                    glColor3fv(CL_BLACK);
                    glScalef(0.29, 0.29, 0.51);
                    glutSolidCube(4);
                glPopMatrix();

                // Janela 2
                glPushMatrix();
                    glTranslatef(-2.0, -1.6, -0.2);
                    glColor3fv(CL_BLACK);
                    glScalef(0.3, 0.3, 0.51);
                    glutSolidCube(4);
                glPopMatrix();

                // Janela 3
                glPushMatrix();
                    glTranslatef(-0.5, -1.6, -0.2);
                    glColor3fv(CL_BLACK);
                    glScalef(0.3, 0.3, 0.51);
                    glutSolidCube(4);
                glPopMatrix();

                // Janela 4
                glPushMatrix();
                    glTranslatef(1.0, -1.6, -0.2);
                    glColor3fv(CL_BLACK);
                    glScalef(0.3, 0.3, 0.51);
                    glutSolidCube(4);
                glPopMatrix();

                // Janela 5
                glPushMatrix();
                    glTranslatef(2.5, -1.6, -0.2);
                    glColor3fv(CL_BLACK);
                    glScalef(0.3, 0.3, 0.51);
                    glutSolidCube(4);
                glPopMatrix();

                // Janela 6
                glPushMatrix();
                    glTranslatef(4.0, -1.6, -0.2);
                    glColor3fv(CL_BLACK);
                    glScalef(0.3, 0.3, 0.51);
                    glutSolidCube(4);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix();
                // Roda frontal esquerda
                glPushMatrix();
                    glTranslatef(-3.70, -3.07, 0.78);
                    glRotatef(90,1,0,0);
                    glRotatef(90,0,0,1);
                    glRotatef(angX,1,0,0);
                    glRotatef(-90,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.63,0.63,0.63);
                    glutWireTorus(0.28,0.25,25,25);
                    glTranslatef(-0.90, +3.0, -0.55);
                    glRotatef(theta, 0.0, 0.0, 1.0);
                    glTranslatef(0.90, -3.0, 0.55);
                glPopMatrix();

                // Roda traseira 1 esquerda
                glPushMatrix();
                    glTranslatef(2.70, -3.09, 0.78);
                    glRotatef(90,1,0,0);
                    glRotatef(90,0,0,1);
                    glRotatef(angX,1,0,0);
                    glRotatef(-90,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.63,0.63,0.63);
                    glutWireTorus(0.28,0.25,25,25);
                    glTranslatef(-0.90, +3.0, -0.55);
                    glRotatef(theta, 0.0, 0.0, 1.0);
                    glTranslatef(0.90, -3.0, 0.55);
                glPopMatrix();

                // Roda traseira 2 esquerda
                glPushMatrix();
                    glTranslatef(3.70, -3.09, 0.78);
                    glRotatef(90,1,0,0);
                    glRotatef(90,0,0,1);
                    glRotatef(angX,1,0,0);
                    glRotatef(-90,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.63,0.63,0.63);
                    glutWireTorus(0.28,0.25,25,25);
                    glTranslatef(-0.90, +3.0, -0.55);
                    glRotatef(theta, 0.0, 0.0, 1.0);
                    glTranslatef(0.90, -3.0, 0.55);
                glPopMatrix();

                // Roda frontal direita
                glPushMatrix();
                    glTranslatef(-3.70, -3.07, -1.18);
                    glRotatef(90,1,0,0);
                    glRotatef(90,0,0,1);
                    glRotatef(angX,1,0,0);
                    glRotatef(-90,0,1,0);
                    glColor3fv(CL_BLACK);
                    glScaled(0.63,0.63,0.63);
                    glutWireTorus(0.28,0.25,25,25);
                    glTranslatef(-0.90, +3.0, -0.55);
                    glRotatef(theta, 0.0, 0.0, 1.0);
                    glTranslatef(0.90, -3.0, 0.55);
                glPopMatrix();

                // Roda traseira 1 direita
                glPushMatrix();
                    glTranslatef(2.70, -3.09, -1.18);
                    glRotatef(90,1,0,0);
                    glRotatef(90,0,0,1);
                    glRotatef(angX,1,0,0);
                    glRotatef(-90,0,1,0); 
                    glColor3fv(CL_BLACK);
                    glScaled(0.63,0.63,0.63);
                    glutWireTorus(0.28,0.25,25,25);
                    glTranslatef(-0.90, +3.0, -0.55);
                    glRotatef(theta, 0.0, 0.0, 1.0);
                    glTranslatef(0.90, -3.0, 0.55);
                glPopMatrix();

                // Roda traseira 2 direita
                glPushMatrix();
                    glTranslatef(3.70, -3.09, -1.18);
                    glRotatef(90,1,0,0);
                    glRotatef(90,0,0,1);
                    glRotatef(angX,1,0,0);
                    glRotatef(-90,0,1,0); 
                    glColor3fv(CL_BLACK);
                    glScaled(0.63,0.63,0.63);
                    glutWireTorus(0.28,0.25,25,25);
                    glTranslatef(-0.90, +3.0, -0.55);
                    glRotatef(theta, 0.0, 0.0, 1.0);
                    glTranslatef(0.90, -3.0, 0.55);
                glPopMatrix();
            glPopMatrix();

            // Escapamento
            glPushMatrix();
                glRotatef(90, 1, 0, 0); 
                glTranslatef(4.7, 0.67, 0.65);
                glColor3fv(CL_GRAY);
                glScaled(0.5,0.5,0.5);
                gluCylinder(quadricObject, 0.15, 0.15, 5, 5, 30);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    background();
    build_semaphore();
    build_ap(+0.0, +0.00, 1.0, CL_LILAC);
    build_ap(-1.4, -0.59, 0.7, CL_YELLOW);
    build_ap(-5.2, -0.20, 0.9, CL_BLUE);
    build_ap(-4.9, -1.15, 0.4, CL_RED);
    build_ap(-9.0, -0.40, 0.8, CL_GREEN);

    (vehicule == 0) ? build_car() : build_bus();
    
    lightning();
    glFlush();
}

void timerFunc(GLint value)
{
    // Tratamento das alterações no semáforo
    if(redSignal == 1) 
    {
        if(vehicule == 1) 
        {
            if(right <= -2 || right >= -1) 
            {
                right += inc;
                angX += 25;
            } 
            else 
            {
                inc = incInitial;
            }
        }
        else if(right <= 0 || right >= 1.0) 
        {
            right += inc;
            angX += 25;
        } 
        else 
        {
            inc = incInitial;
        }
    } 
    else 
    {
        right += inc;
        angX += 25;
    }

    // Tratamento da mudança dos veículos
    if(right >= 15) {
        right = -15;
        vehicule = 1 - vehicule;
    }

    // Tratamento da iluminação
    if (y_ortho < -4) {
        diffuseColor = 0.5;
        glClearColor(0.0,0.45,1,0.0);
        light1Y = -5.0;
    }

    if (y_ortho >= -4 && y_ortho <= 1) {
        diffuseColor = 0.65;
        glClearColor(0.0,0.65,1.0,0.0);
        light1Y = -0.5;
    }

    if (y_ortho >= 1) {
        diffuseColor = 0.65;
        glClearColor(0.0,0.75,1.0,0.0);
        light1Y = -0.5;
    }

    glutPostRedisplay();
    glutTimerFunc(19,timerFunc, 1);
}

void keyboard(unsigned char key, GLint x, GLint y)
{
    switch(key)
    {
        case 's':
            if(yellowSignal == 1)
            {
                redSignal = 1; yellowSignal = 0; greenSignal = 0;
                colorRedSignal = CL_RED; colorYellowSignal = CL_BLACK; colorGreenSignal = CL_BLACK;
            } 
            else if(redSignal == 1) 
            {
                redSignal = 0; yellowSignal = 0; greenSignal = 1;
                colorRedSignal = CL_BLACK; colorYellowSignal = CL_BLACK; colorGreenSignal = CL_GREEN;
            }
            else if(greenSignal == 1)
            {
                redSignal = 0; yellowSignal = 1; greenSignal = 0;
                colorRedSignal = CL_BLACK; colorYellowSignal = CL_YELLOW; colorGreenSignal = CL_BLACK;
            }
            break;
        case 'a':
            if(inc < 0.3) inc += 0.05;
            break;
    }
    glutPostRedisplay();
}

void mouseFunction(GLint button, GLint state, GLint x, GLint y)
{
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) {
                lightX = - ((GLfloat) (800/2) - x) / (GLfloat) (800/2);
                lightY =   ((GLfloat) (800/2) - y) / (GLfloat) (800/2);
            }
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(GLint argc, char **argv)
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50,50);
     glutInitWindowSize(800,800);
     glutCreateWindow("Thiago Henrique - Trabalho Final");
     glutDisplayFunc(display);
     glutKeyboardFunc(keyboard);
     glutTimerFunc(10,timerFunc,1);
     glutMouseFunc(mouseFunction);
     init();
     glutMainLoop();
}