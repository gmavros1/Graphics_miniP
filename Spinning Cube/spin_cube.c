//
// Created by gmavros on 9/5/21.
//


#include <GL/glut.h>
#include <stdlib.h>

int m = 5;
float b = 90;
float a = 8;
int flag = 1;
int ChangeSpinTr = 0;

GLuint listName;

static void init (void){
    listName = glGenLists(1);
    glNewList (listName, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glEnd();
    glEndList ();
}

void myinit(void)
{

/* attributes */
    glEnable(GL_BLEND);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); /* white background */
    glColor3f(1.0f, 0.0f, 0.0f); /* draw_ctrl_points in red */
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20-70, 20+36, 20+36, -20-70, b-20-100, b+20);
    //gluLookAt(0,0,-100, 0, 0, -90, 0, 1, 0);
    //glTranslatef(0,0,-10);
    glMatrixMode(GL_MODELVIEW);
}

void display( void )
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //drawPoint();

    glPushMatrix();

    // Initial
    glTranslatef(0,0,-b);
    glTranslatef(0,0,(float) ChangeSpinTr);
    glRotatef((float) m,1,2,6);// main rotation
    glTranslatef(0,0,-(float) ChangeSpinTr);
    glTranslatef(0,0,-a/2);
    glScalef(a/2,a/2,0);
    glTranslatef(0,0,-1);
    glColor3f(0,1,1);
    glCallList(listName);

    // right
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-b);
    glTranslatef(0,0,(float) ChangeSpinTr);
    glRotatef((float) m,1,2,6);// main rotation
    glTranslatef(0,0,-(float) ChangeSpinTr);
    glTranslatef(a/2,0,0);
    glRotatef(90,0,1,0);
    glScalef(a/2,a/2,0);
    glTranslatef(0,0,-1);
    glColor3f(0,1,0);
    glCallList(listName);

    // opposite
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-b);
    glTranslatef(0,0,(float) ChangeSpinTr);
    glRotatef((float) m,1,2,6);// main rotation
    glTranslatef(0,0,-(float) ChangeSpinTr);
    glTranslatef(0,0,a/2);
    glRotatef(0,0,1,0);
    glScalef(a/2,a/2,0);
    glTranslatef(0,0,-1);
    glColor3f(1,0,0);
    glCallList(listName);

    // left
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-b);
    glTranslatef(0,0,(float) ChangeSpinTr);
    glRotatef((float) m,1,2,6);// main rotation
    glTranslatef(0,0,-(float) ChangeSpinTr);
    glTranslatef(-a/2,0,0);
    glRotatef(90,0,1,0);
    glScalef(a/2,a/2,0);
    glTranslatef(0,0,-1);
    glColor3f(0,0,1);
    glCallList(listName);

    // bottom
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-b);
    glTranslatef(0,0,(float) ChangeSpinTr);
    glRotatef((float) m,1,2,6);// main rotation
    glTranslatef(0,0,-(float) ChangeSpinTr);
    glTranslatef(0,a/2,0);
    glRotatef(90,1,0,0);
    glScalef(a/2,a/2,0);
    glTranslatef(0,0,-1);
    glColor3f(1,1,0);
    glCallList(listName);

    // top
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-b);
    glTranslatef(0,0,(float) ChangeSpinTr);
    glRotatef((float) m,1,2,6);// main rotation
    glTranslatef(0,0,-(float) ChangeSpinTr);
    glTranslatef(0,-a/2,0);
    glRotatef(90,1,0,0);
    glScalef(a/2,a/2,0);
    glTranslatef(0,0,-1);
    glColor3f(1,0,1);
    glCallList(listName);

    //glPopMatrix();
    //glRotatef((float) m,1,2,6);
    //glPushMatrix();

    glutSwapBuffers();
}

void spinCube(){

    m = (m+1) % 360;

    if (flag){
        a *= 1.01f;
        if (a>=24)
            flag = 0;
    }
    else{
        a /= 1.01f;
        if (a<=8)
            flag = 1;
    }



    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y){
    if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
        glutAttachMenu(GLUT_RIGHT_BUTTON);


}

void menuHandler(int choice) {

    switch (choice) {
        case 1:
            ChangeSpinTr = 0;
            break;
        case 2:
            ChangeSpinTr = 72;
            break;
        case 3:
            exit(0);
        default:
            break;
    }
}

int main(int argc, char** argv)
{

/* Standard GLUT initialization */

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); /* default, not needed */
    glutInitWindowSize(500,500); /* 500 x 500 pixel window */
    glutInitWindowPosition(1000,0); /* place window top left on display */
    glutCreateWindow("Spinning Cube"); /* window title */
    init();
    glutDisplayFunc(display); /* display callback invoked when window opened */
    myinit(); /* set attributes */

    glutMouseFunc (mouse);

    glutCreateMenu(menuHandler);
    glutAddMenuEntry("Cube Center", 1);
    glutAddMenuEntry("An other point", 2);
    glutAddMenuEntry("Exit", 3);

    glutIdleFunc(spinCube);

    glutMainLoop(); /* enter event loop */
}

