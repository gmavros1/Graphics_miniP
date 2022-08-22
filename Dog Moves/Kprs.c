//
// Created by gmavros on 22/2/22.
//

//#include "dog_parts1.h"
#include "dog_parts.h"
#include <math.h>

float upper_radius = 0.43f;
float lower_radius = 0.675f;
float head_radiousx = 0.5f;
float head_radiousy = 0.3f;

int start = 0;

int moveType = 0;

void traverse(struct treeNode* root);
void initial_nodes();
struct treeNode body, head;
struct treeNode front_right_upper, front_right_lower, back_right_upper, back_right_lower;
struct treeNode front_left_upper, front_left_lower, back_left_upper, back_left_lower;
int width = 1000;
int height = 800;

// Camera rotation stuff
float eyePosition[3];
float rotationView_Left_Right;
float rotationView_Up_Down;
float rad;

float theta[10];

// projection
void change_projection();
void myinit();

void rotateCamera(int key, int x, int y ){
    switch ( key ){
        case GLUT_KEY_LEFT:
            glMatrixMode(GL_PROJECTION);
            glRotatef(3.0f, 0.0f, 1.0f, 0.0f);
            glPushMatrix();
            glMatrixMode(GL_MODELVIEW);
            break;
        case GLUT_KEY_RIGHT:
            glMatrixMode(GL_PROJECTION);
            glRotatef(-3.0f, 0.0f, 1.0f, 0.0f);
            glPushMatrix();
            glMatrixMode(GL_MODELVIEW);
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
    glFrustum(-1.0f, 1.0f, -1.0, 1.0, 10.0, 170.0);

    eyePosition[0] = rad * sinf(rotationView_Left_Right) * cosf(rotationView_Up_Down);
    eyePosition[1] = rad * sinf(rotationView_Up_Down);
    eyePosition[2] = rad * cosf(rotationView_Left_Right)* cosf(rotationView_Up_Down);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}


void myinit()
{

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    eyePosition[0] = 70.0f;
    eyePosition[2] = 70.0f;
    eyePosition[1] = 70.0f;
    rotationView_Left_Right = 0.0f;
    rotationView_Up_Down = 0.0f;
    rad = 70.0f;

    glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    if (!start++) {
        glLoadIdentity();
        gluOrtho2D(-5, 7, -7, 7); // 14 14 14 14
        }
    else
        glPopMatrix();

    glMatrixMode(GL_MODELVIEW);//community.khronos.org/t/error-gl-gl-h-no-such-file-or-directory-even-tough-i-have-it-installed-debian/71888
    glLoadIdentity();

    initial_nodes();

}

void mouse(int btn, int state, int x, int y){

    if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
        glutAttachMenu(GLUT_RIGHT_BUTTON);

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

void move(){

    glPushMatrix();

    glLoadIdentity();
    //glTranslatef(2.695f, 2.695f, 0);
    //glTranslatef(2.695f, -lower_radius - upper_radius, 0);
    glRotatef(theta[0], 0.0f, 0.0f, 1.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,body.m);

    glLoadIdentity();
    glTranslatef(-2.45f, 0.925f, 0);
    glTranslatef(head_radiousx, -head_radiousy, 0);
    glRotatef(theta[1], 0.0f, 0.0f, 1.0f);
    glTranslatef(-head_radiousx, head_radiousy, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,head.m);

    glLoadIdentity();
    glTranslatef(-0.885f, -0.545f, 0.65f);
    glTranslatef(0, upper_radius, 0);
    glRotatef(theta[2], 0.0f, 0.0f, 1.0f);
    glTranslatef(0, -upper_radius, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,front_left_upper.m);

    glLoadIdentity();
    glTranslatef(0.035f, -0.955f, -0.05f);
    glTranslatef(0, (lower_radius), 0);
    glRotatef(theta[3], 0.0f, 0.0f, 1.0f);
    glTranslatef(0, -(lower_radius), 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,front_left_lower.m);

    glLoadIdentity();
    glTranslatef(-0.885f, -0.545f, -0.65f);
    glTranslatef(0, upper_radius, 0);
    glRotatef(theta[4], 0.0f, 0.0f, 1.0f);
    glTranslatef(0, -upper_radius, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,front_right_upper.m);

    glLoadIdentity();
    glTranslatef(0.035f, -0.955f, 0.05f);
    glTranslatef(0, (lower_radius), 0);
    glRotatef(theta[5], 0.0f, 0.0f, 1.0f);
    glTranslatef(0, -(lower_radius), 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,front_right_lower.m);

    glLoadIdentity();
    glTranslatef(1.095f, -0.545f, 0.65f);
    glTranslatef(0, upper_radius, 0);
    glRotatef(theta[6], 0.0f, 0.0f, 1.0f);
    glTranslatef(0, -upper_radius, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,back_left_upper.m);

    glLoadIdentity();
    glTranslatef(0.035f, -0.955f, 0.05f);
    glTranslatef(0, (lower_radius), 0);
    glRotatef(theta[7], 0.0f, 0.0f, 1.0f);
    glTranslatef(0, -(lower_radius), 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,back_left_lower.m);

    glLoadIdentity();
    glTranslatef(1.095f, -0.545f, -0.65f);
    glTranslatef(0, upper_radius, 0);
    glRotatef(theta[8], 0.0f, 0.0f, 1.0f);
    glTranslatef(0, -upper_radius, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,back_right_upper.m);

    glLoadIdentity();
    glTranslatef(0.035f, -0.955f, -0.05f);
    glTranslatef(0, (lower_radius), 0);
    glRotatef(theta[9], 0.0f, 0.0f, 1.0f);
    glTranslatef(0, -(lower_radius), 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,back_right_lower.m);

    glPopMatrix();

    glutPostRedisplay();
}

void move1_inverse(){
    if(theta[2] >= -70 && theta[2] <= -20) {
        theta[2] += 1.0f;
        theta[3] -= 1.4f;
    }
    else if(theta[2] < 0){
        theta[2] += 1.0f;
    }
}


void move1(){


    if (theta[2] > -20){
        theta[2] -= 1.0f;
    }
    else if(theta[2] <= -20 && theta[2] >= -70){
            theta[2] -= 1.0f;
            theta[3] += 1.4f;
    }


}

void move2_inverse(){

    if (theta[2] <=0){

        theta[0] += 1.0f;
        theta[6] -= 1.0f;
        theta[8] -= 1.0f;

        if(theta[2] >= -70 && theta[2] <= -20){
            theta[2] += 0.7f;
            theta[3] -= 2.0f;

            theta[4] += 0.7f;
            theta[5] -= 2.0f;
        }
        else if (theta[2] > -20){
            theta[2] += 1.0f;
            theta[4] += 1.0f;
        }
    }


}

void move2(){

    if (theta[0] > -70){


        theta[0] -= 1.0f;
        theta[6] += 1.0f;
        theta[8] += 1.0f;

        if (theta[2] > -20){
            theta[2] -= 1.0f;
            theta[4] -= 1.0f;
        }
        else if(theta[2] <= -20 && theta[2] >= -70){
            theta[2] -= 0.7f;
            theta[3] += 2.0f;

            theta[4] -= 0.7f;
            theta[5] += 2.0f;
        }

    }

}

void move3_inverse(){
    if (theta[1] <= 45 && theta[1] >=0) {
        theta[1] -= 1;
    }
}

void move3(){
    if (theta[1] < 45){
        theta[1] += 1;
    }
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glPushMatrix();

    //glTranslatef(1.6f, -0.225f, 0.0f);
    //glRotatef(-30, 0, 0, 1);
    //glTranslatef(-1.6f, 0.225f, 0.0f);
    //glPushMatrix();

    //glPushMatrix();
    glLoadIdentity();
    glLineWidth(6);
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glEnd();
    glPopMatrix();


    glLineWidth(1);
    glColor3d(0.0, 1.0, 0.0);
    move();
    traverse(&body);

    if (moveType ==1)
        move1();
    if (moveType ==2)
        move2();
    if (moveType ==3)
        move3();
    if (moveType ==-1)
        move1_inverse();
    if (moveType ==-2)
        move2_inverse();
    if (moveType ==-3)
        move3_inverse();


    glutSwapBuffers();
    glFlush();
}


void initial_nodes(){
    for (int i = 0; i < 10; ++i) {
        theta[i] = 0;
    }
    //theta[1] = -13;

    glLoadIdentity();
    //glTranslatef(2.45f, -0.925f, 0);
    glRotatef(theta[0], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,body.m);
    body.f = dog_body;
    body.sibling = NULL;
    body.child = &head;

    //theta[1]= 0;

    glLoadIdentity();
    glTranslatef(-2.45f, 0.925f, 0);
    glRotatef(theta[1], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,head.m);
    head.f = dog_head;
    head.sibling = &front_left_upper;
    head.child = NULL;

    glLoadIdentity();
    glTranslatef(-0.885f, -0.545f, 0.65f);
    glRotatef(theta[2], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,front_left_upper.m);
    front_left_upper.f = dog_front_upper_left;
    front_left_upper.sibling = &front_right_upper;
    front_left_upper.child = &front_left_lower;

    glLoadIdentity();
    glTranslatef(0.035f, -0.955f, -0.05f);
    glRotatef(theta[3], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,front_left_lower.m);
    front_left_lower.f = dog_front_lower_left;
    front_left_lower.sibling = NULL;
    front_left_lower.child = NULL;

    glLoadIdentity();
    glTranslatef(-0.885f, -0.545f, -0.65f);
    glRotatef(theta[4], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,front_right_upper.m);
    front_right_upper.f = dog_front_upper_right;
    front_right_upper.sibling = &back_left_upper;
    front_right_upper.child = &front_right_lower;

    glLoadIdentity();
    glTranslatef(0.035f, -0.955f, 0.05f);
    glRotatef(theta[5], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,front_right_lower.m);
    front_right_lower.f = dog_front_lower_right;
    front_right_lower.sibling = NULL;
    front_right_lower.child = NULL;

    glLoadIdentity();
    glTranslatef(1.095f, -0.545f, 0.65f);
    glRotatef(theta[6], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,back_left_upper.m);
    back_left_upper.f = dog_back_upper_left;
    back_left_upper.sibling = &back_right_upper;
    back_left_upper.child = &back_left_lower;

    glLoadIdentity();
    glTranslatef(0.035f, -0.955f, 0.05f);
    glRotatef(theta[7], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,back_left_lower.m);
    back_left_lower.f = dog_back_lower_left;
    back_left_lower.sibling = NULL;
    back_left_lower.child = NULL;

    glLoadIdentity();
    glTranslatef(1.095f, -0.545f, -0.65f);
    glRotatef(theta[8], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,back_right_upper.m);
    back_right_upper.f = dog_back_upper_right;
    back_right_upper.sibling = NULL;
    back_right_upper.child = &back_right_lower;

    glLoadIdentity();
    glTranslatef(0.035f, -0.955f, -0.05f);
    glRotatef(theta[9], 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX,back_right_lower.m);
    back_right_lower.f = dog_back_lower_right;
    back_right_lower.sibling = NULL;
    back_right_lower.child = NULL;
}

void traverse(struct treeNode* root){
    if (root == NULL)
        return;
    glPushMatrix();
    glMultMatrixf(root->m);
    root->f();
    if(root->child != NULL)
        traverse(root->child);
    glPopMatrix();
    if (root->sibling != NULL)
        traverse(root->sibling);

}

void menuHandler(int choice) {

    switch (choice) {
        case 1:
            moveType = 1;
            myinit();
            break;
        case 2:
            moveType = 2;
            myinit();
            break;
        case 3:
            moveType = 1;
            glLineWidth(7);
            myinit();
            break;
        case 4:
            moveType = - moveType;
            break;
        default:
            break;
    }


    glutPostRedisplay();

}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Kopros");
    myinit();
    glutDisplayFunc(display);

    glutMouseFunc (mouse);
    glutCreateMenu(menuHandler);
    glutAddMenuEntry("move1", 1);
    glutAddMenuEntry("move2", 2);
    glutAddMenuEntry("move3", 3);
    glutAddMenuEntry("inverse", 4);

    //glutIdleFunc(move2);


    glutSpecialFunc(rotateCamera);
    glutMainLoop();
}
