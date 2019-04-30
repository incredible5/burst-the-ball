#include<GL/glut.h> 
#include<unistd.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#define SCREEN_WIDTH 1855
#define SCREEN_HEIGHT 934

int x, y, radius = 70, score= 0, j = 0, k = 0, centerx = 0, centery = 0;
char msg[] = "SCORE:";
float mx, my, i;

void init() 
{ 
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0); 
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
}

void text() //for text display of score
{
    char p[2];
    sprintf(p, "%d", score);
    glColor3f(0,1,1);
    glRasterPos2f(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 100);
    for(int iqa=0;iqa<strlen(p);iqa++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,p[iqa]);
    }
    glRasterPos2f(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 70);
    for(int iqa=0;iqa<strlen(msg);iqa++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg[iqa]);
    }
}

void blast(int x, int y) // blast image
{
    score++;
    x -= 100;
    y -= 140;
    glClear(GL_COLOR_BUFFER_BIT);
    text();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x+72.4,y+35.0);
    glVertex2f(x+52.0,y+0.0);
    glVertex2f(x+36.0,y+59.5);
    glVertex2f(x+12.0,y+70.0);
    glVertex2f(x+15.2,y+129.5);
    glVertex2f(x+0.8,y+157.5);
    glVertex2f(x+15.2,y+192.5);
    glVertex2f(x+20.0,y+245.0);
    glVertex2f(x+47.2,y+234.5);
    glVertex2f(x+64.8,y+280.0);
    glVertex2f(x+84.0,y+245.0);
    glVertex2f(x+108.0,y+262.5);
    glVertex2f(x+120.8,y+227.5);
    glVertex2f(x+140.0,y+227.5);
    glVertex2f(x+143.2,y+185.5);
    glVertex2f(x+156.0,y+157.5);
    glVertex2f(x+156.0,y+119.0);
    glVertex2f(x+138.0,y+87.5);
    glVertex2f(x+143.2,y+52.5);
    glVertex2f(x+132.0,y+21.0);
    glVertex2f(x+112.8,y+35.0);
    glVertex2f(x+93.6,y+0.0);
    glVertex2f(x+72.8,y+35.0);
    glEnd();
    glFlush();
}

int randValue()
{
    return rand()%1000;
}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        mx = mousex;
        my = SCREEN_HEIGHT-mousey; // since y-axiz is from top to bottom
        int eq = ((mx - centerx)*(mx - centerx)) + ((my - centery)*(my - centery)) - (radius*radius);
        if(eq <= 0)
        {
            glEnd();
            glFlush();
            glClear(GL_COLOR_BUFFER_BIT);
            blast(x / 2 + j, y / 2 + k);
            sleep(1);
            j = randValue();
            k = 0;
            centerx = j;
            centery = k;
        }
    }
}
  
void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    text();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (i = 0;i < 6.29;i += 0.001) // generates a circle by highlighting pixels from 0 to 2pi (2pi ~ 6.29)
    {
        x = radius * cos(i);
        y = radius * sin(i);
        glVertex2i(x + j, y + k);
        if((x / 2 + j) >= SCREEN_WIDTH || (y / 2 + k) >= SCREEN_HEIGHT)
        {
            glEnd();
            glFlush();
            glClear(GL_COLOR_BUFFER_BIT);
            j = randValue();
            k = 0;
            centerx = j;
            centery = k;
        }
    }
    j = j + 3;
    k = k + 5;
    centerx = j;
    centery = k;
    for(int sl = 0; sl < 9999999; sl++)
    {}
    glEnd();
    glFlush();
    glutPostRedisplay(); // To call the display function again and again
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("{Project}");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}