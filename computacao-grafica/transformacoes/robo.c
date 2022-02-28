#include "standard.h"

/*
    Thiago Henrique Leite - 139920 - Robo

    Utilize as teclas abaixo para interagir com a figura:
    
    Setas [esquerda e direita]: Rotacionam o robô todo para esquerda e para direita, respectivamente.
    Setas [cima e baixo]: Movem os olhos do robô na largura de seu pescoço.
    'r' e 'l': Movem o robô todo para direita e esquerda, respectivamente.
    'i' e 'o': Ampliam e reduzem o tamanho do robô, respectivamente.
*/

void buildCircle(float x, float y, float sx, float sy, float* circleColor)
{
    float xAux;
    float yAux;
    float angulo = 0.0;

    glPushMatrix();
        glColor3fv(circleColor);

        glTranslatef(x, y, 0.0);
        
        glBegin(GL_POLYGON);
            for(int i = 0; i <= 60; i++)
            {
                xAux = sx*cos(angulo);
                yAux = sy*sin(angulo);

                glVertex2f(xAux*cos(theta)-yAux*sin(theta), xAux*sin(theta)+yAux*cos(theta));
                
                angulo += 2 * PI / 60;
            }
        glEnd();
    glPopMatrix();
}

void buildEyes(float x, float y) 
{
    glTranslatef(x, y, 0);

    // Constrói borda
    buildCircle(x-0.12, 0.25, -0.125, -0.125, CL_BLACK);
    buildCircle(x+0.12, 0.25, -0.125, -0.125, CL_BLACK);

    // Constrói branco dos olhos
    buildCircle(x-0.12, 0.25, -0.110, -0.110, CL_WHITE);
    buildCircle(x+0.12, 0.25, -0.110, -0.110, CL_WHITE);

    // Constrói íris
    buildCircle(x-0.12, 0.25, -0.060, -0.060, CL_BROWN);
    buildCircle(x+0.12, 0.25, -0.060, -0.060, CL_BROWN);

    // Constrói as pupilas
    buildCircle(x-0.12, 0.25, -0.020, -0.020, CL_BLACK);
    buildCircle(x+0.12, 0.25, -0.020, -0.020, CL_BLACK);
}

void buildRobot(float x, float y) 
{
    glPushMatrix();
        glTranslatef(x,y,0);

        glColor3fv(CL_BLUE);

        // Braço esquerdo
        glBegin(GL_POLYGON);
            glVertex2f(x-0.5, -0.1);    
            glVertex2f(x-0.3, -0.1);
            glVertex2f(x-0.2, -0.2);
            glVertex2f(x-0.4, -0.2);
        glEnd();


        // Braço direito
        glBegin(GL_POLYGON);
            glVertex2f(x+0.5, -0.1);
            glVertex2f(x+0.3, -0.1);
            glVertex2f(x+0.2, -0.2);
            glVertex2f(x+0.4, -0.2);
        glEnd();

        glColor3fv(CL_BROWN);

        // Corpo (parte inferior)
        glBegin(GL_POLYGON);
            glVertex2f(x-0.3, 0.0);
            glVertex2f(x+0.3, 0.0);
            glVertex2f(x+0.3, -0.5);
            glVertex2f(x-0.3, -0.5);
        glEnd();

        glColor3fv(CL_ORANGE);

        // Corpo (parte superior)
        glBegin(GL_POLYGON);
            glVertex2f(x-0.3, 0.0);
            glVertex2f(x+0.3, 0.0);
            glVertex2f(x+0.3, -0.15);
            glVertex2f(x-0.3, -0.15);
        glEnd();

        glColor3fv(CL_BLACK);

        // Pé esquerdo
        glBegin(GL_POLYGON);
            glVertex2f(x-0.25, -0.5);
            glVertex2f(x-0.25, -0.6);
            glVertex2f(x-0.05, -0.6);
            glVertex2f(x, -0.5);
        glEnd();
        
        // Pé direito
        glBegin(GL_POLYGON);
            glVertex2f(x, -0.5);
            glVertex2f(x+0.25, -0.5);
            glVertex2f(x+0.25, -0.6);
            glVertex2f(x+0.05, -0.6);
        glEnd();

        glColor3fv(CL_RED);

        // Pescoço
        glBegin(GL_POLYGON);
            glVertex2f(x-0.04, 0.0);
            glVertex2f(x+0.04, 0.0);
            glVertex2f(x+0.04, +0.25);
            glVertex2f(x-0.04, +0.25);
        glEnd();
    glPopMatrix();

    // Olhos
    glPushMatrix();
        glTranslatef(0, up, 0);
        buildEyes(x, y);
    glPopMatrix();
}

void draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0, 1.0, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        // Aplicação da escala
        glScaled(zoomIn, zoomIn, 1);

        // Ãplicação da translação
        glTranslatef(right, 0, 0);

        // Aplica rotação do robô no seu próprio eixo
        glTranslatef(0, -0.2, 0.0);
        glRotatef(theta, 0.0, 0.0, 1.0);
        glTranslatef(0, +0.2, 0.0);

        buildRobot(0, 0.2);
    glPopMatrix();

    glFlush();
}
/*
    Configuração das teclas especiais do teclado
*/
void specialKeyboard(int key, int x, int y)
{
    switch(key) 
    {
        case GLUT_KEY_RIGHT:
            theta -= 8;
            break;
        case GLUT_KEY_LEFT:
            theta += 8;
            break;
        case GLUT_KEY_UP:
            if(up < 0.03) up += 0.01;
            break;
        case GLUT_KEY_DOWN:
            if(up > -0.2) up -= 0.01;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

/*
    Configuração das teclas padrões do teclado
*/
void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'i':
            zoomIn += 0.01;
            break;
        case 'o':
            zoomIn -= 0.01;
            break;
        case 'r':
            right += 0.01;
            break;
        case 'l':
            right -= 0.01;
            break;
    }
    glutPostRedisplay();
}


int main(int argc , char** argv)
{
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50 ,100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Robo - Implementado por Thiago Leite");
    glutDisplayFunc(draw);
    glutSpecialFunc(specialKeyboard);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
