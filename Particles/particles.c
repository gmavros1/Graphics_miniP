//
// Created by gmavros on 23/2/22.
//

//
// Created by gmavros on 21/2/22.
//

#include <GL/glut.h>
#include <math.h>
#include "dotVectorProd.h"
#include <stdlib.h>
int counterIit = 0;

int width = 1000;
int height = 800;

// Camera rotation stuff
float eyePosition[3];
float rotationView_Left_Right;
float rotationView_Up_Down;
float rad;

// motion
float initialMousePositionX, initialMousePositionY;
int motionv;
int whichPoint;

// projection
void change_projection();
void myinit();


struct particles{
    float position[3];
    float previousPosition[3];
    float velocity[3];
    float m;
    float f[3];
};

const int numberOfPoints = 1000;
struct particles ps[1000];



void collision(){

    for (int i = 0; i < counterIit; ++i) {

        if (ps[i].position[1] < 0){
            ps[i].position[0] = ps[i].previousPosition[0];
            ps[i].position[1] = ps[i].previousPosition[1];
            ps[i].position[2] = ps[i].previousPosition[2];

            //ps[i].position[0] = 0.0f;
            //ps[i].position[1] = 0.0f;
            //ps[i].position[2] = 0.0f;

            //ps[i].velocity[0] = 0.0f;
            ps[i].velocity[1] = -ps[i].velocity[1];
            //ps[i].velocity[2] = 0.0f;


        }

    }

}

void update(){
    for (int j = 0; j < counterIit; ++j) {
        for (int i = 0; i < 3; ++i) {

            ps[j].previousPosition[i] = ps[j].position[i];

            ps[j].position[i] += 0.6f * ps[j].velocity[i];
        }
        //printf(" %f \n",ps[j].position[1]);

        for (int i = 0; i < 3; ++i) {
            ps[j].velocity[i] += 0.6f * (1.0f/ps[j].m) * ps[j].f[i];
        }
    }

    collision();
    glutPostRedisplay();

    //printf(" %f ",ps[2].position[1]);

}

void initialParticles(){
    for (int i = counterIit - 1; i < 3; i++) {
        float x = ((float)rand()/(float)(RAND_MAX)) * 0.05f - ((float)rand()/(float)(RAND_MAX)) * 0.05f;
        float y = ((float)rand()/(float)(RAND_MAX)) * 0.15f;
        float z = ((float)rand()/(float)(RAND_MAX)) * 0.1f - ((float)rand()/(float)(RAND_MAX)) * 0.1f;

        //printf(" %f \n",x);

        ps[i].position[0] = 0.01f;
        ps[i].position[1] = 0.01f;
        ps[i].position[2] = 0.01f;

        ps[i].previousPosition[0] = 0.0f;
        ps[i].previousPosition[1] = 0.0f;
        ps[i].previousPosition[2] = 0.0f;

        ps[i].velocity[0] = x;
        ps[i].velocity[1] = y;
        ps[i].velocity[2] = z;

        ps[i].m = 1.0f;

        ps[i].f[0] = 0;
        ps[i].f[1] = -0.001f * ps[i].m;
        ps[i].f[2] = 0;
    }
    counterIit = (counterIit + 3) % numberOfPoints;
    //update();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //draw_ctrl_points();

    glColor3d(0.0, 1.0, 0.0);

    glBegin(GL_POLYGON);
    glVertex3f(-12.0f, .0f, -20.0f);
    glVertex3f(12.0f, .0f, -20.0f);
    glVertex3f(12.0f, .0f, 20.0f);
    glVertex3f(-12.0f, .0f, 20.0f);
    glEnd();

    initialParticles();
    update();

    glColor3d(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < counterIit; ++i) {
        glVertex3f(ps[i].position[0], ps[i].position[1], ps[i].position[2]);
    }
    glEnd();


    glutSwapBuffers();
    glFlush();
}

void rotateCamera(int key, int x, int y ){
    switch ( key ){
        case GLUT_KEY_LEFT:
            rotationView_Left_Right -= 0.05f;
            break;
        case GLUT_KEY_RIGHT:
            rotationView_Left_Right += 0.05f;
            break;
        case GLUT_KEY_UP:
            rotationView_Up_Down += 0.05f;
            break;
        case GLUT_KEY_DOWN:
            rotationView_Up_Down -= 0.05f;
            break;
        default:
            break;
    }



    eyePosition[0] = rad * sinf(rotationView_Left_Right) * cosf(rotationView_Up_Down);
    eyePosition[1] = rad * sinf(rotationView_Up_Down);
    eyePosition[2] = rad * cosf(rotationView_Left_Right)* cosf(rotationView_Up_Down);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glutPostRedisplay();
}

void change_projection(){
    // Set up projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0f, 1.0f, -1.0, 1.0, 5.0, 170.0);

    eyePosition[0] = rad * sinf(rotationView_Left_Right) * cosf(rotationView_Up_Down);
    eyePosition[1] = rad * sinf(rotationView_Up_Down);
    eyePosition[2] = rad * cosf(rotationView_Left_Right)* cosf(rotationView_Up_Down);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}


void myinit()
{

    // later stuff
    // Camera rotation stuff
    eyePosition[0] = 70.0f;
    eyePosition[2] = 70.0f;
    eyePosition[1] = 70.0f;
    rotationView_Left_Right = 0.0f;
    rotationView_Up_Down = 0.3f;
    rad = 70.0f;

    change_projection();

    /*
    glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-14, 14, -14, 14);
    glMatrixMode(GL_MODELVIEW);//community.khronos.org/t/error-gl-gl-h-no-such-file-or-directory-even-tough-i-have-it-installed-debian/71888
    glLoadIdentity();
    */

    //initialParticles();
}

void mouse(int btn, int state, int x, int y){

    if (btn == 4) {

        // Zoom in
        eyePosition[0] = ++rad * sinf(rotationView_Left_Right) * cosf(rotationView_Up_Down);
        eyePosition[1] = ++rad * sinf(rotationView_Up_Down);
        eyePosition[2] = ++rad * cosf(rotationView_Left_Right) * cosf(rotationView_Up_Down);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        glutPostRedisplay();
    }
    if (btn == 3) {


        // Zoom in
        eyePosition[0] = --rad * sinf(rotationView_Left_Right) * cosf(rotationView_Up_Down);
        eyePosition[1] = --rad * sinf(rotationView_Up_Down);
        eyePosition[2] = --rad * cosf(rotationView_Left_Right) * cosf(rotationView_Up_Down);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        glutPostRedisplay();
    }


}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("To mikro spiti sto libadi");
    myinit();
    glPointSize(10);

    glutMouseFunc (mouse);
    glutAddMenuEntry("Cubic Curve", 1);
    glutAddMenuEntry("Closed Bezier", 2);
    glutAddMenuEntry("Two smooth cubic", 3);
    glutAddMenuEntry("Cubic surface", 4);

    glutDisplayFunc(display);
    //glutIdleFunc(initialParticles);
    //glutIdleFunc(update);
    glutSpecialFunc(rotateCamera);
    glutMainLoop();
}

