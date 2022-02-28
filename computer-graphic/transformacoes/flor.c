#include "standard.h"

/*
    Thiago Henrique Leite - 139920 - Flor

    Utilize as teclas abaixo para interagir com a figura:
    
    Setas [esquerda e direita]: Rotacionam a flor para esquerda e para direita, respectivamente.
    Setas [cima e baixo]: Movem a flor para cima e para baixo, respectivamente.
    'r' e 'l': Movem a flor inteira para direita e para esquerda, respectivamente.
    'i' e 'o': Ampliam e reduzem o tamanho da flor, respectivamente.
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

void buildFlower(float x, float y) 
{
    glTranslatef(x, y, 0);

    // Eixo X
    buildCircle(x-0.4, 0.0, 0.23, 0.23, CL_BLACK);
    buildCircle(x+0.4, 0.0, 0.23, 0.23, CL_BLACK);
    buildCircle(x-0.4, 0.0, 0.22, 0.22, CL_RED);
    buildCircle(x+0.4, 0.0, 0.22, 0.22, CL_RED);

    // Eixo Y
    buildCircle(x+0.0, +0.4, 0.23, 0.23, CL_BLACK);
    buildCircle(x+0.0, -0.4, 0.23, 0.23, CL_BLACK);
    buildCircle(x+0.0, +0.4, 0.22, 0.22, CL_RED);
    buildCircle(x+0.0, -0.4, 0.22, 0.22, CL_RED);

    // 1º quadrante
    buildCircle(x+0.25, +0.25, 0.25, 0.25, CL_BLACK);
    buildCircle(x+0.25, +0.25, 0.24, 0.24, CL_YELLOW);

    // 2º quadrante
    buildCircle(x-0.25, +0.25, 0.25, 0.25, CL_BLACK);
    buildCircle(x-0.25, +0.25, 0.24, 0.24, CL_YELLOW);
    
    // 3º quadrante
    buildCircle(x-0.25, -0.25, 0.25, 0.25, CL_BLACK);
    buildCircle(x-0.25, -0.25, 0.24, 0.24, CL_YELLOW);

    // 4º quadrante
    buildCircle(x+0.25, -0.25, 0.25, 0.25, CL_BLACK);
    buildCircle(x+0.25, -0.25, 0.24, 0.24, CL_YELLOW);
    
    // Origem
    buildCircle(x+0.0, 0.0, 0.23, 0.23, CL_BLACK);
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

        // Aplicação da translação
        glTranslatef(right, up, 0);

        // Aplica rotação da flor no seu próprio eixo (origem)
        glRotatef(theta, 0.0, 0.0, 1.0);

        buildFlower(0, 0.0);
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
            up += 0.01;
            break;
        case GLUT_KEY_DOWN:
            up -= 0.01;
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
    glutCreateWindow("Flor - Implementado por Thiago Leite");
    glutDisplayFunc(draw);
    glutSpecialFunc(specialKeyboard);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
