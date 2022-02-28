#include "standard.h"

/*
    Thiago Henrique Leite - 139920 - Carro

    Utilize as teclas abaixo para interagir com a figura:
    
    Setas [esquerda e direita]: Movem o carro para esquerda e para direita, respectivamente.
    Setas [cima e baixo]: Movem o carro para cima e para baixo, respectivamente.
    'i' e 'o': Ampliam e reduzem o tamanho do carro, respectivamente.
*/

/* 
    Função para construir as rodas do carro
    x e y: fornecem a posição de onde será o centro das rodas
    sx e sy: fornecem informações a respeito do tamanho das calotas
    tireColor e wheelColor: fornecem as cores do pneu e calota, respectivamente
*/
void buildWheel(float x, float y, float sx, float sy, float *tireColor, float *wheelColor)
{
    float xAux;
    float yAux;
    float angulo = 0.0;

    glPushMatrix();
        glTranslatef(x, y, 0.0);

        glColor3fv(tireColor);
        
        // Construção do pneu 
        glBegin(GL_POLYGON);
            for(int i = 0; i <= N; i++)
            {
                xAux = sx*cos(angulo);
                yAux = sy*sin(angulo);
                
                glVertex2f(xAux*cos(theta)-yAux*sin(theta), xAux*sin(theta)+yAux*cos(theta));

                angulo += 2 * PI / N;
            }
        glEnd();

        glColor3fv(wheelColor);

        // Construção da calota
        glBegin(GL_POLYGON);
            for(int i = 0; i <= N; i++)
            {
                xAux = (sx-0.045)*cos(angulo);
                yAux = (sy-0.045)*sin(angulo);

                glVertex2f(xAux*cos(theta)-yAux*sin(theta), xAux*sin(theta)+yAux*cos(theta));
                
                angulo += 2 * PI / N;
            }
        glEnd();
    glPopMatrix();
}

/* 
    Função para construir a estrutura do carro
    xinit e xend: fornecem a posição x de ínicio e término da estrutura
    y: indica a posição y onde iniciaremos a construção
    height: informa qual será a altura da estrutura
    structureColor: indica a cor do carro

    A estrutura do carro é retangular, com os pontos (xinit, y) e (xend, y) 
    temos a linha superior de nosso retângulo. Seu lado é determinado pela altura height
*/
void buildStructure(float xinit, float xend, float y, float height, float *structureColor) 
{
    glPushMatrix();
        glColor3fv(structureColor);

        // Constrói estrutura inferior
        glBegin(GL_POLYGON);
            glVertex2f(xinit, y);
            glVertex2f(xend, y);
            glVertex2f(xend, y-height);
            glVertex2f(xinit, y-height);
        glEnd();

        // Constrói estrutura superior
        glColor3fv(CL_BROWN);

        glBegin(GL_POLYGON);
            glVertex2f(xinit+0.3, y);
            glVertex2f(xend-0.3, y);
            glVertex2f(xend-0.3, y+height-0.1);
            glVertex2f(xinit+0.3, y+height-0.1);
        glEnd();

        // Constrói janelas
        glColor3fv(CL_CYAN);

        glBegin(GL_POLYGON);
            glVertex2f(xinit+0.33, y);
            glVertex2f(xend-0.33, y);
            glVertex2f(xend-0.33, y+height-0.13);
            glVertex2f(xinit+0.33, y+height-0.13);
        glEnd();


        // Constrói divisória das portas
        glColor3fv(CL_BLACK);
        glLineWidth(10);

        glBegin(GL_LINES);
            glVertex2f(0.0, 0.47);
            glVertex2f(0.0, height-0.45);
        glEnd();

        // Constrói as 2 maçanetas das portas
        glBegin(GL_LINES);
            glVertex2f(-0.20, height-0.15);
            glVertex2f(-0.10, height-0.15);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(+0.20, height-0.15);
            glVertex2f(+0.10, height-0.15);
        glEnd();

        // Constrói os dois escapamentos
        glBegin(GL_LINES);
            glVertex2f(xinit, height-0.35);
            glVertex2f(xinit-0.05, height-0.35);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(xinit, height-0.37);
            glVertex2f(xinit-0.05, height-0.37);
        glEnd();
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
        // Aplicação da translação
        glTranslatef(right, up, 0);

        buildStructure(-0.70, 0.70, 0.25, 0.35, CL_RED);
    glPopMatrix();
    
    glPushMatrix();
        glScaled(zoomIn, zoomIn, 1);
        glTranslatef(right, up, 0);
        buildWheel(-0.35, -0.10, 0.125, 0.125, CL_BLACK, CL_WHITE);
        buildWheel(+0.35, -0.10, 0.125, 0.125, CL_BLACK, CL_WHITE);
        // Aplica rotação das rodas no seu próprio eixo
        glTranslatef(+0.35, +0.10, 0.0);
        glRotatef(theta, 0.0, 0.0, 1.0);
        glTranslatef(-0.35, -0.10, 0.0);
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
            right += 0.01;
            theta += 8;
            break;
        case GLUT_KEY_LEFT:
            right -= 0.01;
            theta -= 8;
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
void keyboard(unsigned char key, int x, int y)
{
    switch(key){
       case 'i':
          zoomIn += 0.01;
          break;
       case 'o':
          zoomIn -= 0.01;
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
    glutCreateWindow("Carro - Implementado por Thiago Leite");
    glutDisplayFunc(draw);
    glutSpecialFunc(specialKeyboard);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
