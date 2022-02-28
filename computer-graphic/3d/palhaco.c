#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Setas rotacionam o palhaço;
// 's' para a rotação;

float angX = 0.0, angY = 0.0;
float sx = 1.0, sy = 1.0;

int opcao = 0, aumenta = 0;

float CL_BLACK[3]  = {0.00, 0.00, 0.00};
float CL_WHITE[3]  = {1.00, 1.00, 1.00};
float CL_RED[3]    = {1.00, 0.00, 0.00};
float CL_GREEN[3]  = {0.00, 1.00, 0.00};
float CL_BLUE[3]   = {0.00, 0.00, 1.00};
float CL_YELLOW[3] = {1.00, 1.00, 0.00};
float CL_PINK[3]   = {1.00, 0.40, 0.70};
float CL_ORANGE[3] = {1.00, 0.50, 0.00};
float CL_LILAC[3]  = {0.60, 0.40, 0.70};
float CL_BROWN[3]  = {0.50, 0.20, 0.00};
float CL_CYAN[3]   = {0.50, 1.00, 1.00};
float CL_GRAY[3]  = {0.88, 0.88, 0.88};

void init(){
     glClearColor(0.45, 0.23, 0.27, 0.0);;
     glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glOrtho(-7.0,7.0,-7.0,7.0,-7.0,7.0);
     glPushMatrix();
}

void build_palhaco() {
  // Cabelo Direito
   glPushMatrix();
      glScalef(sx, sy, 1);
      glTranslatef(-2.6, 1, -0.2);
      glColor3fv(CL_YELLOW);
      glutSolidSphere(1,50,50);
	 glPopMatrix();

  // Cabelo Esquerdo
  glPushMatrix();
    glScalef(sx, sy, 1);
    glTranslatef(2.6, 1, -0.2);
    glColor3fv(CL_ORANGE);
    glutSolidSphere(1,50,50);
  glPopMatrix();

  // Cabelo Médio Direito
  glPushMatrix();
    glScalef(sx, sy, 1);
    glTranslatef(1.5, 2.5, -0.2);
    glColor3fv(CL_BLUE);
    glutSolidSphere(1,50,50);
  glPopMatrix();

  // Cabelo Médio Esquerdo
  glPushMatrix();
    glScalef(sx, sy, 1);
    glTranslatef(-1.5, 2.5, -0.2);
    glColor3fv(CL_GREEN);
    glutSolidSphere(1,50,50);
  glPopMatrix();

  // Cabelo Central
  glPushMatrix();
    glScalef(sx, sy, 1);
    glTranslatef(0, 3, -0.2);
    glColor3fv(CL_PINK);
    glutSolidSphere(1,50,50);
  glPopMatrix();

  // Rosto
  glPushMatrix();
    glColor3fv(CL_GRAY);
    glutSolidSphere(3,50,50);
  glPopMatrix();

  // Nariz
  glPushMatrix();
    glTranslatef(0, 0.2, 3.3);
    glColor3fv(CL_RED);
    glutSolidSphere(0.5,50,50);
  glPopMatrix();

  // Olho Esquerdo
  glPushMatrix();
    glTranslatef(-0.8, 1.5, 3.0);
    glColor3fv(CL_BLACK);
    glutSolidSphere(0.5,50,50);
  glPopMatrix();

  // Olho Direito
  glPushMatrix();
    glTranslatef(0.8, 1.5, 3.0);
    glColor3fv(CL_BLACK);
    glutSolidSphere(0.5,50,50);
  glPopMatrix();

  // Íris Esquerda
  glPushMatrix();
    glTranslatef(-0.8, 1.5, 3.5);
    glColor3fv(CL_WHITE);
    glutSolidSphere(0.17,50,50);
  glPopMatrix();

  // Íris Direita
  glPushMatrix();
    glTranslatef(0.8, 1.5, 3.5);
    glColor3fv(CL_WHITE);
    glutSolidSphere(0.17,50,50);
  glPopMatrix();

  // Retina do olho esquerdo
  glPushMatrix();
    glTranslatef(-0.8, 1.5, 3.7);
    glColor3fv(CL_BLACK);
    glutSolidSphere(0.08,50,50);
  glPopMatrix();

  // Retina do olho direito
  glPushMatrix();
    glTranslatef(0.8, 1.5, 3.7);
    glColor3fv(CL_BLACK);
    glutSolidSphere(0.08,50,50);
  glPopMatrix();

  // Boca
  glPushMatrix();
    glTranslatef(0.0, -1.3, 2.4);
    glColor3fv(CL_RED);
    glScaled(2,0.5,1);
    glutSolidTorus(0.28,0.40,50,50);
  glPopMatrix();
}

void display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glPopMatrix();
     glPushMatrix();
     glRotatef(angX,1.0,0.0,0.0);
     glRotatef(angY,0.0,1.0,0.0);
     build_palhaco();
     glFlush();
}

void timerFunc(int value)
{
    switch (opcao) {
        case 1:
            angX+=1;
            break;
        case 2:
            angX-=1;
            break;
        case 3:
            angY+=1;
            break;
        case 4:
            angY-=1;
            break;
        default:
            break;
    }

    if(aumenta) {
      sx += 0.005;
      sy += 0.005;

      if(sx > 1.2) aumenta = 0;
    } else {
      sx -= 0.005;
      sy -= 0.005;

      if(sx < 0.9) aumenta = 1;
    }

    glutPostRedisplay();
    glutTimerFunc(10,timerFunc, 1);
}

void rotacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           opcao = 1;
           break ;
        case GLUT_KEY_DOWN :
           opcao = 2;
           break ;
        case GLUT_KEY_LEFT :
           opcao = 3;
           break ;
        case GLUT_KEY_RIGHT :
           opcao = 4;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
       case 's':
          opcao = 5;
          break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50,50);
     glutInitWindowSize(600,600);
     glutCreateWindow("Thiago Henrique - Palhaço 3D");
     glutDisplayFunc(display);
     glutSpecialFunc(rotacoes);
     glutKeyboardFunc(keyboard);
     glutTimerFunc(10,timerFunc,1);
     init();
     glutMainLoop();
}
