#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <winuser.h>
#pragma warning(disable : 4996)

GLfloat window_width = 500;
GLfloat window_height = 500;

GLfloat Xmin_orgin = -2; GLfloat Xmax_orgin = 2;
GLfloat Ymin_orgin = -2; GLfloat Ymax_orgin = 2;



void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(Xmin_orgin, Xmax_orgin, Ymin_orgin, Ymax_orgin);
    glMatrixMode(GL_MODELVIEW);
}

void ball()
{
    glColor3f(1, 0, 0);
    glutWireSphere(0.2, 25, 25);
}
void basket()
{
    glColor3f(0, 1, 0);
    glutWireCone(0.3, 0.5, 25, 25);
}
void poll()
{
    glColor3f(0, 0, 1);
    glutSolidCube(2);
}
float ballX = 0.0, ballY = 1.8, basketX = 0.0, basketY = -1.5, pollX = 0.9, pollY = 1.8;
int rand(), r, flagout = 0, count = 0, countScore = 0;
float ballSpeed = 0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    printf("ballX=%f\n", ballX);
    printf("ballY=%f\n", ballY);
    printf("basketX=%f\n", basketX);
    printf("basketY=%f\n", basketY);

    if (count == 3)
    {
        ballSpeed += 0.008;
        count = 0;
    }

    if (ballY < -1.5 && (ballX > basketX - 0.3 && ballX < basketX + 0.3))
    {
        count++;
        countScore++;
        ballY = 1.8;
        r = rand() % 4;
        if (r == 0)
        {
            ballX = -1.8;
            pollX = -1.8 + 0.9;
        }
        if (r == 1)
        {
            ballX = -1;
            pollX = -1 + 0.9;
        }
        if (r == 2)
        {
            ballX = 1;
            pollX = 1 + 0.9;
        }
        if (r == 3)
        {
            ballX = 1.8;
            pollX = 1.8 + 0.9;
        }
    }

    if (flagout == 0)
        ballY -= 0.01 + ballSpeed;

    if (ballY < -2)
    {
        flagout = 1;
        char TheScore[10];
        _itoa_s(countScore, TheScore, 10);
        char text[50] = "";
        strcat(text, TheScore);
        MessageBox(NULL, (LPCWSTR)text, L"YOUR SCORE IS :   ", 0);
        exit(0);
    }

    glPushMatrix();
    glTranslatef(ballX, ballY, 0);
    ball();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(basketX, basketY, 0);
    glRotatef(90, 1, 0, 0);
    basket();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pollX, pollY, 0);
    glScalef(1.5, 0.4, 1);
    poll();
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

void skeys(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
        basketX -= 0.5;
    if (key == GLUT_KEY_RIGHT)
        basketX += 0.5;
}
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    GLdouble aspect = (GLdouble)w / (GLdouble)h;
    glLoadIdentity();
    if (w >= h) {
        gluOrtho2D(Xmin_orgin * aspect, Xmax_orgin * aspect, Ymin_orgin, Ymax_orgin);
    }
    else {
        gluOrtho2D(Xmin_orgin, Xmax_orgin, Ymin_orgin / aspect, Ymax_orgin / aspect);
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Game basket ball");
    glutPositionWindow(400, 100);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(skeys);
    glutMainLoop();
    return 0;
}