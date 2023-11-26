// **********************************************************************
// PUCRS/Escola Polit�cnica
// COMPUTA��O GR�FICA
//
// Programa b�sico para criar aplicacoes 3D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include <glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "../include/LeitorObjeto3D.h"

#include "Temporizador.h"
#include "ListaDeCoresRGB.h"
#include "Ponto.h"
Temporizador T;
double AccumDeltaT = 0;

GLfloat AspectRatio, angulo = 0;

// Controle do modo de projecao
// 0: Projecao Paralela Ortografica; 1: Projecao Perspectiva
// A funcao "PosicUser" utiliza esta variavel. O valor dela eh alterado
// pela tecla 'p'
int ModoDeProjecao = 1;

// Controle do modo de projecao
// 0: Wireframe; 1: Faces preenchidas
// A funcao "Init" utiliza esta variavel. O valor dela eh alterado
// pela tecla 'e'
int ModoDeExibicao = 1;

double nFrames = 0;
double TempoTotal = 0;
Ponto CantoEsquerdo = Ponto(-20, -1, -10);
bool borda = false;

float variaPosX = -4.0f;

float cannonAngle = 0;
float cannonBodyAngle = 0;
Ponto posCannon = Ponto(-7.0f, 0, 35.0f);


#define inimigos 20
Objeto3D dog;
struct Dog {
    float x, y, z;
    bool inimigo, vivo;
};
Dog* dogsList;
// Ponto miniCannon = Ponto(posCannon.x + 5, posCannon.y - 2, posCannon.z + 2);

// **********************************************************************
//  void init(void)
//        Inicializa os parametros globais de OpenGL
// **********************************************************************
void init(void)
{
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // Fundo de tela preto

    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    // glShadeModel(GL_FLAT);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    if (ModoDeExibicao) // Faces Preenchidas??
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    dog = Objeto3D();
    dog.LeObjeto("../build/dog.tri");
    dogsList = new Dog[inimigos];
    for (int i=0; i<inimigos; i++) {
        Dog& d = dogsList[i];
        d.x = (posCannon.x - 10) + (rand() % 20);
        // d.x = posCannon.x;
        d.y = posCannon.y;
        d.z = posCannon.z - 43.5 + (rand() % 22);
        // d.z = posCannon.z;
        d.inimigo = i%2==0;
        d.vivo = true;
    }
}

// **********************************************************************
//
// **********************************************************************
void animate()
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;
    TempoTotal += dt;
    nFrames++;

    if (AccumDeltaT > 1.0 / 30) // fixa a atualiza��o da tela em 30
    {
        AccumDeltaT = 0;
        angulo += 1;
        glutPostRedisplay();
    }
    if (TempoTotal > 5.0)
    {
        cout << "Tempo Acumulado: " << TempoTotal << " segundos. ";
        cout << "Nros de Frames sem desenho: " << nFrames << endl;
        cout << "FPS(sem desenho): " << nFrames / TempoTotal << endl;
        TempoTotal = 0;
        nFrames = 0;
    }
}

// **********************************************************************
//  void DesenhaCubo()
// **********************************************************************
void DesenhaCubo(float tamAresta)
{
    glBegin(GL_QUADS);
    // Front Face
    glNormal3f(0, 0, 1);
    glVertex3f(-tamAresta / 2, -tamAresta / 2, tamAresta / 2);
    glVertex3f(tamAresta / 2, -tamAresta / 2, tamAresta / 2);
    glVertex3f(tamAresta / 2, tamAresta / 2, tamAresta / 2);
    glVertex3f(-tamAresta / 2, tamAresta / 2, tamAresta / 2);
    // Back Face
    glNormal3f(0, 0, -1);
    glVertex3f(-tamAresta / 2, -tamAresta / 2, -tamAresta / 2);
    glVertex3f(-tamAresta / 2, tamAresta / 2, -tamAresta / 2);
    glVertex3f(tamAresta / 2, tamAresta / 2, -tamAresta / 2);
    glVertex3f(tamAresta / 2, -tamAresta / 2, -tamAresta / 2);
    // Top Face
    glNormal3f(0, 1, 0);
    glVertex3f(-tamAresta / 2, tamAresta / 2, -tamAresta / 2);
    glVertex3f(-tamAresta / 2, tamAresta / 2, tamAresta / 2);
    glVertex3f(tamAresta / 2, tamAresta / 2, tamAresta / 2);
    glVertex3f(tamAresta / 2, tamAresta / 2, -tamAresta / 2);
    // Bottom Face
    glNormal3f(0, -1, 0);
    glVertex3f(-tamAresta / 2, -tamAresta / 2, -tamAresta / 2);
    glVertex3f(tamAresta / 2, -tamAresta / 2, -tamAresta / 2);
    glVertex3f(tamAresta / 2, -tamAresta / 2, tamAresta / 2);
    glVertex3f(-tamAresta / 2, -tamAresta / 2, tamAresta / 2);
    // Right face
    glNormal3f(1, 0, 0);
    glVertex3f(tamAresta / 2, -tamAresta / 2, -tamAresta / 2);
    glVertex3f(tamAresta / 2, tamAresta / 2, -tamAresta / 2);
    glVertex3f(tamAresta / 2, tamAresta / 2, tamAresta / 2);
    glVertex3f(tamAresta / 2, -tamAresta / 2, tamAresta / 2);
    // Left Face
    glNormal3f(-1, 0, 0);
    glVertex3f(-tamAresta / 2, -tamAresta / 2, -tamAresta / 2);
    glVertex3f(-tamAresta / 2, -tamAresta / 2, tamAresta / 2);
    glVertex3f(-tamAresta / 2, tamAresta / 2, tamAresta / 2);
    glVertex3f(-tamAresta / 2, tamAresta / 2, -tamAresta / 2);
    glEnd();
}
void DesenhaParalelepipedo(float x, float y, float z, float scaleX, float sca)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1, 1, 2);
    glutSolidCube(1);
    glPopMatrix();
}


void DesenhaCanhao(float cannonAngle, float cannonBodyAngle) {
    glPushMatrix();
        glColor3f(1,1,1);

        glTranslatef(posCannon.x, posCannon.y, posCannon.z);
        glRotatef(cannonBodyAngle, 0, 1, 0);
        glScalef(2, 1, 3);
        glutSolidCube(1);

    
        // printf("%f\n", miniCannon.x);
        glColor3f(0, 0.25f, 0.65f);
        glTranslatef(0, 0.5, -0.4);
        glRotatef(cannonAngle, 1, 0, 0);
        glScalef(0.3f, 0.3f, 0.7f);
        glutSolidCube(1);
    glPopMatrix();
}

// **********************************************************************
// void DesenhaLadrilho(int corBorda, int corDentro)
// Desenha uma c�lula do piso.
// Eh possivel definir a cor da borda e do interior do piso
// O ladrilho tem largula 1, centro no (0,0,0) e est� sobre o plano XZ
// **********************************************************************
void DesenhaLadrilho(int corBorda, int corDentro, bool borda)
{
    defineCor(corDentro); // desenha QUAD preenchido
    // glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glEnd();
    
    if (borda) {
        defineCor(corBorda);
    }
    // glColor3f(0, 1, 0);

    glBegin(GL_LINE_STRIP);
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glEnd();
}

// **********************************************************************
//
//
// **********************************************************************
void DesenhaPiso()
{
    srand(100); // usa uma semente fixa para gerar sempre as mesma cores no piso
    glPushMatrix();
    glTranslated(CantoEsquerdo.x, CantoEsquerdo.y, CantoEsquerdo.z);
    for (int x = 0; x < 25; x++)
    {
        glPushMatrix();
        for (int z = 0; z < 50; z++)
        {
            DesenhaLadrilho(DarkSlateBlue, SteelBlue, borda);
            glTranslated(0, 0, 1);
        }
        glPopMatrix();
        glTranslated(1, 0, 0);
    }
    glPopMatrix();
}

void DesenhaMuro()
{
    
    glRotated(90, 1, 0, 0);
    srand(100); // usa uma semente fixa para gerar sempre as mesma cores no piso
    glPushMatrix();
    glTranslated(CantoEsquerdo.x, CantoEsquerdo.y, CantoEsquerdo.z);
    for (int x = 0; x < 25; x++)
    {
        glPushMatrix();
        for (int y = 0; y < 15; y++)
        {
            DesenhaLadrilho(DarkSlateBlue, SteelBlue, borda);
            glTranslated(0, 0, 1);
        }
        glPopMatrix();
        glTranslated(1, 0, 0);
    }
    glPopMatrix();

}

// **********************************************************************
//  void DefineLuz(void)
// **********************************************************************
void DefineLuz(void)
{
    // Define cores para um objeto dourado
    GLfloat LuzAmbiente[] = {0.4, 0.4, 0.4};
    GLfloat LuzDifusa[] = {0.7, 0.7, 0.7};
    GLfloat LuzEspecular[] = {0.9f, 0.9f, 0.9};
    GLfloat PosicaoLuz0[] = {0.0f, 3.0f, 5.0f}; // Posi��o da Luz
    GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f};

    // ****************  Fonte de Luz 0

    glEnable(GL_COLOR_MATERIAL);

    // Habilita o uso de ilumina��o
    glEnable(GL_LIGHTING);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
    // Define os parametros da luz n�mero Zero
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0);
    glEnable(GL_LIGHT0);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);

    // Define a reflectancia do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, Especularidade);

    // Define a concentra��oo do brilho.
    // Quanto maior o valor do Segundo parametro, mais
    // concentrado ser� o brilho. (Valores v�lidos: de 0 a 128)
    glMateriali(GL_FRONT, GL_SHININESS, 51);
}
// **********************************************************************

void MygluPerspective(float fieldOfView, float aspect, float zNear, float zFar)
{
    // https://stackoverflow.com/questions/2417697/gluperspective-was-removed-in-opengl-3-1-any-replacements/2417756#2417756
    //  The following code is a fancy bit of math that is equivilant to calling:
    //  gluPerspective( fieldOfView/2.0f, width/height , 0.1f, 255.0f )
    //  We do it this way simply to avoid requiring glu.h
    // GLfloat zNear = 0.1f;
    // GLfloat zFar = 255.0f;
    // GLfloat aspect = float(width)/float(height);
    GLfloat fH = tan(float(fieldOfView / 360.0f * 3.14159f)) * zNear;
    GLfloat fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}
// **********************************************************************
//  void PosicUser()
// **********************************************************************
void PosicUser()
{
    // Define os par�metros da proje��o Perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define o volume de visualiza��o sempre a partir da posicao do
    // observador
    if (ModoDeProjecao == 0)
        glOrtho(-10, 10, -10, 10, 0, 7); // Projecao paralela Orthografica
    else
        MygluPerspective(90, AspectRatio, 0.01, 50); // Projecao perspectiva

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-7, 5, 45, // Posi��o do Observador
              -7, 0, 0,   // Posi��o do Alvo
              0.0f, 1.0f, 0.0f);

    // gluLookAt(-12, 30 , 15 , -7,0,0, 0,1,0);

// Ponto CantoEsquerdo = Ponto(-20, -1, -10);
}
// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape(int w, int h)
{

    // Evita divis�o por zero, no caso de uam janela com largura 0.
    if (h == 0)
        h = 1;
    // Ajusta a rela��o entre largura e altura para evitar distor��o na imagem.
    // Veja fun��o "PosicUser".
    AspectRatio = 1.0f * w / h;
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Seta a viewport para ocupar toda a janela
    glViewport(0, 0, w, h);
    // cout << "Largura" << w << endl;

    PosicUser();
}

// **********************************************************************
//  void display( void )
// **********************************************************************
float PosicaoZ = -30;
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DefineLuz();

    PosicUser();

    glMatrixMode(GL_MODELVIEW);

    // glPushMatrix();
    // glTranslatef(5.0f, 0.0f, 3.0f);
    // glRotatef(angulo, 0, 1, 0);
    // glColor3f(0.5f, 0.0f, 0.0f); // Vermelho
    // glutSolidCube(2);
    // // DesenhaCubo(1);
    // glPopMatrix();

    // glPushMatrix();
    // glTranslatef(variaPosX, 0.0f, 2.0f);
    // glRotatef(angulo, 0, 1, 0);
    // glColor3f(0.6156862745, 0.8980392157, 0.9803921569); // Azul claro
    // glutSolidCube(2);
    // // DesenhaCubo(1);
    // glPopMatrix();

    glPushMatrix();
        DesenhaPiso();
        glTranslatef(0, 3.5f, 15.5f);
        DesenhaMuro();
    glPopMatrix();

    // glRotated(180, 0, 1, 0);
    DesenhaCanhao(cannonAngle, cannonBodyAngle);

    // DesenhaCanhao(-7.0f, 0, 30.0f, cannonAngle);

    for (int i=0; i<inimigos; i++) {
        Dog& d = dogsList[i];
        printf("Dog(%.2f, %.2f, %.2f)\n", d.x, d.y, d.z);
        glPushMatrix();
            glTranslatef(d.x, d.y, d.z);
            glRotatef(-90, 0, 1, 0);
            glScalef(0.2,0.2,0.2);
            if (d.inimigo) glColor3f(1.0f,0.0f,0.0f); //mudar, mto parecido com o deles
            else           glColor3f(0.0f, 1.0f, 0.0f);

            dog.ExibeObjeto();
        glPopMatrix();
    }
    

    // // exibir as vacas
    // for (int i=0; i<N_AMIGOS_INIMIGOS; i++)
    // {
    //     Vaca& v = vacas[i];
    //     //printf("Vaca(%.2f, %.2f, %.2f)\n", v.posX, v.posY, v.posZ);
    //     glPushMatrix();
    //         glTranslatef(v.posX, v.posY, v.posZ);
    //         glRotatef(-100, 1, 0, 0);
    //         glRotatef(60, 0, 0, 1);
    //         //glScalef(0.05, 0.05, 0.05);
    //         glScalef(0.07, 0.07, 0.07);
    //         if (v.inimigo) glColor3f(1.0f,0.0f,0.0f);
    //         else           glColor3f(0.0f, 0.0f, 1.0f);
    //         vacaModel.ExibeObjeto();
    //     glPopMatrix();
    // }

    glutSwapBuffers();
}

// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
//
// **********************************************************************
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:     // Termina o programa qdo
        exit(0); // a tecla ESC for pressionada
        break;
    case 'p':
        ModoDeProjecao = !ModoDeProjecao;
        glutPostRedisplay();
        break;
    case 'e':
        ModoDeExibicao = !ModoDeExibicao;
        init();
        glutPostRedisplay();
        break;
    case 'b':
        borda = !borda;
        break;
    case 'd':
        printf("\n%f",posCannon.x);
        if (posCannon.x < 2.75f)
            posCannon.x+=0.25;
        break;
    case 'a':
        printf("\n%f",posCannon.x);
        if (posCannon.x > -18.50f)
            posCannon.x-=0.25;
        break;
    case 'w':
        // variaY++;
        // printf("\n%f",posCannon.z);
        if (posCannon.z > 25)
            posCannon.z-=0.25f;
        break;
    case 's':
        // variaY--;
        // printf("\n%f",posCannon.z);
        if (posCannon.z < 38.5f) 
            posCannon.z+=0.25f;
        break;
    case 'q':
        variaPosX++;
        break;
    case ' ':
        printf("TIRO\n");
        break;
    default:
        cout << key;
        break;
    }
}

// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys(int a_keys, int x, int y)
{
    switch (a_keys)
    {
    case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
        // glutFullScreen(); // Go Into Full Screen Mode
        if (cannonAngle < 45) 
            cannonAngle+=3;  
        
        break;
    case GLUT_KEY_DOWN: // When Down Arrow Is Pressed...
        // glutInitWindowSize(700, 500);
        // if (cannonAngle >  )
        // printf("%f\n", cannonAngle);
        if (cannonAngle > -10) 
            cannonAngle-=3;
        break;  
    case GLUT_KEY_RIGHT:
        if (cannonBodyAngle-3 > -45.0) 
            cannonBodyAngle-=3;
        break;
    case GLUT_KEY_LEFT:
        if (cannonBodyAngle+3 < 45.0) 
            cannonBodyAngle+=3;
        break;  
    default:
        break;
    }
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Computacao Grafica - Exemplo Basico 3D");

    init();
    // system("pwd");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);
    glutIdleFunc(animate);

    glutMainLoop();
    return 0;
}
