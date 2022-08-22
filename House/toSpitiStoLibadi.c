#include <GL/glut.h>
#include <math.h>
#include "dotVectorProd.h"

float flag = 1;
float eyePosition[] = {00.0f, 40.0f, 70.0f};
float spotPos[] = {-5.0f, 10.0f, 10.0f, 1.0f};
GLfloat light_position[] = {0.0f, 0.0f, 0.0f};
GLfloat light_ambient[]={0.3f, 0.3f, 0.3f, 1.0f};
GLfloat light_diffuse[]={0.3f, 0.3f, 0.3f, 1.0f};
GLfloat light_specular[]={0.3f, 0.3f, 0.3f, 1.0f};
float rotationView_Left_Right = 0.0f;
float rotationSun = 0.0f;
int flagDivideGround = 0;

void initLight();

typedef float point[4];

void triangle( point a, point b, point c){

    GLfloat mat_ambient[]={1.0f, 1.0f, 0.0f, 0.5f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_ambient);


    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void normal(point p){
/* normalize a vector */

    double sqrt();
    float d =0.0f;
    int i;
    for(i=0; i<3; i++) d+=p[i]*p[i];
    d=sqrtf(d);
    if(d>0.0) for(i=0; i<3; i++) p[i]/=0.5f*d;
}

void normalForVector(Vector p){
/* normalize a vector */

    //double sqrt();
    float d =0.0f;
    d+=p.i*p.i;
    d+=p.j*p.j;
    d+=p.k*p.k;
    d=sqrtf(d);
    if(d>0.0) {
        p.i/=d;
        p.j/=d;
        p.k/=d;
    }
}

void divide_triangle(point a, point b, point c, int m){

/* triangle subdivision using vertex numbers
righthand rule applied to create outward pointing faces */

    point v1, v2, v3;
    int j;
    if(m>0)
    {
        for(j=0; j<3; j++) v1[j]=a[j]+b[j];
        normal(v1);
        for(j=0; j<3; j++) v2[j]=a[j]+c[j];
        normal(v2);
        for(j=0; j<3; j++) v3[j]=b[j]+c[j];
        normal(v3);
        divide_triangle(a, v1, v2, m-1);
        divide_triangle(c, v2, v3, m-1);
        divide_triangle(b, v3, v1, m-1);
        divide_triangle(v1, v3, v2, m-1);
    }
    else(triangle(a,b,c)); /* draw_ctrl_points triangle at end of recursion */
}

void mparmpoutsala(){

    GLfloat mat[]={0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat mat_shininess={120.0f};

    /* define material proerties for front face of all polygons */

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    //Door

    Vector door[4] = {
            {-1.5f, 6.0f, 10.001f},
            {1.5f, 6.0f, 10.001f,},
            {1.5f, 0.0f, 10.001f},
            {-1.5f, 0.0f, 10.001f}
    };

    Vector doorN[4] = {
            crossProduct(door[3], door[0], door[1]),
            crossProduct(door[0], door[1], door[2]),
            crossProduct(door[1], door[2], door[3]),
            crossProduct(door[2], door[3], door[0])
    };

    normalForVector(door[0]);
    normalForVector(door[1]);
    normalForVector(door[2]);
    normalForVector(door[3]);


    glBegin(GL_POLYGON);
    glNormal3f(doorN[0].i, doorN[0].j, doorN[0].k);
    glVertex3f(door[0].i, door[0].j, door[0].k);
    glNormal3f(doorN[1].i, doorN[1].j, doorN[1].k);
    glVertex3f(door[1].i, door[1].j, door[1].k);
    glNormal3f(doorN[2].i, doorN[2].j, doorN[2].k);
    glVertex3f(door[2].i, door[2].j, door[2].k);
    glNormal3f(doorN[3].i, doorN[3].j, doorN[3].k);
    glVertex3f(door[3].i, door[3].j, door[3].k);
    glEnd();


    //random balls

    GLfloat matc[]={0.0f, 0.7f, 0.0f, 1.0f};
    GLfloat matcs[]={0.0f, 0.0f, 0.0f, 0.0f};
    GLfloat mat_shininessc={30.0f};

    /* define material proerties for front face of all polygons */

    glMaterialfv(GL_FRONT, GL_AMBIENT, matc);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matcs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matcs);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininessc);

    glPushMatrix();
    glTranslatef(-12.0f, 0.0f, 10.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glEnable(GL_NORMALIZE);
    glutSolidCone(1.5,18,10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(12.0f, 0.0f, 10.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glEnable(GL_NORMALIZE);
    glutSolidCone(1.5,18,10, 10);
    glPopMatrix();

}

void drawSun(){

    point v[] = {{0.0f, 0.0f, 1.0f},
                 {0.0f, 0.942809f,-0.33333f},
                 {-0.816497f, -0.471405f, -0.333333f},
                 {0.816497f, -0.471405f, -0.333333f}
    };

    divide_triangle(v[0], v[1], v[2], 4);
    divide_triangle(v[3], v[2], v[1], 4);
    divide_triangle(v[0], v[3], v[1], 4);
    divide_triangle(v[0], v[2], v[3], 4);


}


void drawRoof(){
    GLfloat mat[]={0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess={100.0f};

    /* define material proerties for front face of all polygons */

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    Vector roof[6]={
            {5.0f, 10.0f, -10.0f},
            {-5.0f, 10.0f, -10.0f},
            {0.0f, 18.66f, -10.0f},
            {5.0f, 10.0f, 10.0f},
            {-5.0f, 10.0f, 10.0f},
            {0.0f, 18.66f, 10.0f}
    };

    Vector rooffN[4] = {
            crossProduct(roof[2], roof[0], roof[1]),
            crossProduct(roof[0], roof[1], roof[2]),
            crossProduct(roof[1], roof[2], roof[0]),
            crossProduct(roof[0], roof[0], roof[0]),
    };

    normalForVector(rooffN[0]);
    normalForVector(rooffN[1]);
    normalForVector(rooffN[2]);
    normalForVector(rooffN[3]);


    glBegin(GL_POLYGON);
    glNormal3f(rooffN[0].i, rooffN[0].j, rooffN[0].k);
    glVertex3f(roof[0].i, roof[0].j, roof[0].k);
    glNormal3f(rooffN[1].i, rooffN[1].j, rooffN[1].k);
    glVertex3f(roof[1].i, roof[1].j, roof[1].k);
    glNormal3f(rooffN[2].i, rooffN[2].j, rooffN[2].k);
    glVertex3f(roof[2].i, roof[2].j, roof[2].k);
    glEnd();

    rooffN[0] = crossProduct(roof[5], roof[3], roof[4]);
    rooffN[1] = crossProduct(roof[3], roof[4], roof[5]);
    rooffN[2] = crossProduct(roof[4], roof[5], roof[3]);
    rooffN[3] = crossProduct(roof[0], roof[0], roof[0]);


    normalForVector(rooffN[0]);
    normalForVector(rooffN[1]);
    normalForVector(rooffN[2]);
    normalForVector(rooffN[3]);

    glBegin(GL_POLYGON);
    glNormal3f(rooffN[0].i, rooffN[0].j, rooffN[0].k);
    glVertex3f(roof[3].i, roof[3].j, roof[3].k);
    glNormal3f(rooffN[1].i, rooffN[1].j, rooffN[1].k);
    glVertex3f(roof[4].i, roof[4].j, roof[4].k);
    glNormal3f(rooffN[2].i, rooffN[2].j, rooffN[2].k);
    glVertex3f(roof[5].i, roof[5].j, roof[5].k);
    glEnd();

    rooffN[0] = crossProduct(roof[2], roof[0], roof[3]);
    rooffN[1] = crossProduct(roof[5], roof[2], roof[0]);
    rooffN[2] = crossProduct(roof[3], roof[5], roof[2]);
    rooffN[3] = crossProduct(roof[0], roof[3], roof[5]);


    normalForVector(rooffN[0]);
    normalForVector(rooffN[1]);
    normalForVector(rooffN[2]);
    normalForVector(rooffN[3]);

    glBegin(GL_POLYGON);
    glNormal3f(rooffN[0].i, rooffN[0].j, rooffN[0].k);
    glVertex3f(roof[0].i, roof[0].j, roof[0].k);
    glNormal3f(rooffN[1].i, rooffN[1].j, rooffN[1].k);
    glVertex3f(roof[2].i, roof[2].j, roof[2].k);
    glNormal3f(rooffN[2].i, rooffN[2].j, rooffN[2].k);
    glVertex3f(roof[5].i, roof[5].j, roof[5].k);
    glNormal3f(rooffN[3].i, rooffN[3].j, rooffN[3].k);
    glVertex3f(roof[3].i, roof[3].j, roof[3].k);
    glEnd();

    rooffN[0] = crossProduct(roof[4], roof[1], roof[2]);
    rooffN[1] = crossProduct(roof[1], roof[2], roof[5]);
    rooffN[2] = crossProduct(roof[2], roof[5], roof[4]);
    rooffN[3] = crossProduct(roof[5], roof[4], roof[1]);

    normalForVector(rooffN[0]);
    normalForVector(rooffN[1]);
    normalForVector(rooffN[2]);
    normalForVector(rooffN[3]);

    glBegin(GL_POLYGON);
    glNormal3f(rooffN[0].i, rooffN[0].j, rooffN[0].k);
    glVertex3f(roof[1].i, roof[1].j, roof[1].k);
    glNormal3f(rooffN[1].i, rooffN[1].j, rooffN[1].k);
    glVertex3f(roof[2].i, roof[2].j, roof[2].k);
    glNormal3f(rooffN[2].i, rooffN[2].j, rooffN[2].k);
    glVertex3f(roof[5].i, roof[5].j, roof[5].k);
    glNormal3f(rooffN[3].i, rooffN[3].j, rooffN[3].k);
    glVertex3f(roof[4].i, roof[4].j, roof[4].k);
    glEnd();
}

void draw_ctrl_points(){

    GLfloat mat_diffuse[]={1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat mat_specular[]={0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat mat_ambiend[]={1.0f, 0.8f, 0.8f, 1.0f};
    GLfloat mat_shininess={20.0f};

    /* define material proerties for front face of all polygons */

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiend);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    Vector walls[8] = {
            {5.0f,  0.0f, -10.0f},
            {5.0f,  0.0f, 10.0f},
            {5.0f, 10.0f, 10.0f},
            {5.0f, 10.0f, -10.0f},
            {-5.0f, 0.0f, -10.0f},
            {-5.0f,  0.0f, 10.0f},
            {-5.0f, 10.0f, 10.0f},
            {-5.0f,  10.0f, -10.0f}
    };

    Vector wallzN[4] = {
            crossProduct( walls[3], walls[0], walls[4]),
            crossProduct( walls[7], walls[3], walls[0]),
            crossProduct( walls[4], walls[7], walls[3]),
            crossProduct( walls[0], walls[4], walls[7])
    };

    normalForVector(wallzN[0]);
    normalForVector(wallzN[1]);
    normalForVector(wallzN[2]);
    normalForVector(wallzN[3]);

    glBegin(GL_POLYGON);
    glNormal3f(wallzN[0].i, wallzN[0].j, wallzN[0].k);
    glVertex3f(walls[0].i, walls[0].j, walls[0].k);
    glNormal3f(wallzN[1].i, wallzN[1].j, wallzN[1].k);
    glVertex3f(walls[3].i, walls[3].j, walls[3].k);
    glNormal3f(wallzN[2].i, wallzN[2].j, wallzN[2].k);
    glVertex3f(walls[7].i, walls[7].j, walls[7].k);
    glNormal3f(wallzN[3].i, wallzN[3].j, wallzN[3].k);
    glVertex3f(walls[4].i, walls[4].j, walls[4].k);
    glEnd();

    wallzN[0] = crossProduct( walls[2], walls[1], walls[5]);
    wallzN[1] = crossProduct( walls[6], walls[2], walls[1]);
    wallzN[2] = crossProduct( walls[5], walls[6], walls[2]);
    wallzN[3] = crossProduct( walls[1], walls[5], walls[6]);


    normalForVector(wallzN[0]);
    normalForVector(wallzN[1]);
    normalForVector(wallzN[2]);
    normalForVector(wallzN[3]);


    glBegin(GL_POLYGON);
    glNormal3f(wallzN[0].i, wallzN[0].j, wallzN[0].k);
    glVertex3f(walls[1].i, walls[1].j, walls[1].k);
    glNormal3f(wallzN[1].i, wallzN[1].j, wallzN[1].k);
    glVertex3f(walls[2].i, walls[2].j, walls[2].k);
    glNormal3f(wallzN[2].i, wallzN[2].j, wallzN[2].k);
    glVertex3f(walls[6].i, walls[6].j, walls[6].k);
    glNormal3f(wallzN[3].i, wallzN[3].j, wallzN[3].k);
    glVertex3f(walls[5].i, walls[5].j, walls[5].k);
    glEnd();


    wallzN[0] = crossProduct( walls[3], walls[0], walls[1]);
    wallzN[1] = crossProduct( walls[2], walls[3], walls[0]);
    wallzN[2] = crossProduct( walls[1], walls[2], walls[3]);
    wallzN[3] = crossProduct( walls[0], walls[1], walls[2]);


    normalForVector(wallzN[0]);
    normalForVector(wallzN[1]);
    normalForVector(wallzN[2]);
    normalForVector(wallzN[3]);

    glBegin(GL_POLYGON);
    glNormal3f(wallzN[0].i, wallzN[0].j, wallzN[0].k);
    glVertex3f(walls[0].i, walls[0].j, walls[0].k);
    glNormal3f(wallzN[1].i, wallzN[1].j, wallzN[1].k);
    glVertex3f(walls[3].i, walls[3].j, walls[3].k);
    glNormal3f(wallzN[2].i, wallzN[2].j, wallzN[2].k);
    glVertex3f(walls[2].i, walls[2].j, walls[2].k);
    glNormal3f(wallzN[3].i, wallzN[3].j, wallzN[3].k);
    glVertex3f(walls[1].i, walls[1].j, walls[1].k);
    glEnd();

    wallzN[0] = crossProduct( walls[5], walls[4], walls[7]);
    wallzN[1] = crossProduct( walls[4], walls[7], walls[6]);
    wallzN[2] = crossProduct( walls[7], walls[6], walls[5]);
    wallzN[3] = crossProduct( walls[6], walls[5], walls[4]);


    normalForVector(wallzN[0]);
    normalForVector(wallzN[1]);
    normalForVector(wallzN[2]);
    normalForVector(wallzN[3]);

    glBegin(GL_POLYGON);
    glNormal3f(wallzN[0].i, wallzN[0].j, wallzN[0].k);
    glVertex3f(walls[4].i, walls[4].j, walls[4].k);
    glNormal3f(wallzN[1].i, wallzN[1].j, wallzN[1].k);
    glVertex3f(walls[7].i, walls[7].j, walls[7].k);
    glNormal3f(wallzN[2].i, wallzN[2].j, wallzN[2].k);
    glVertex3f(walls[6].i, walls[6].j, walls[6].k);
    glNormal3f(wallzN[3].i, wallzN[3].j, wallzN[3].k);
    glVertex3f(walls[5].i, walls[5].j, walls[5].k);
    glEnd();

}

void drawG(Vector v1, Vector v2, Vector v3, Vector v4){

    GLfloat mat[]={0.0f, 1.0f, 0.0f, 1.0f};
    GLfloat mat_shininess={50.0f};

    /* define material proerties for front face of all polygons */

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    Vector grndN[4] = {
            crossProduct(v4, v1, v2),
            crossProduct(v1, v2, v3),
            crossProduct(v2, v3, v4),
            crossProduct(v3, v4, v1)
    };

    normalForVector(grndN[0]);
    normalForVector(grndN[1]);
    normalForVector(grndN[2]);
    normalForVector(grndN[3]);


    glBegin(GL_POLYGON);
    glNormal3f(grndN[0].i, grndN[0].j, grndN[0].k);
    glVertex3f(v1.i, v1.j, v1.k);
    glNormal3f(grndN[1].i, grndN[1].j, grndN[1].k);
    glVertex3f(v2.i, v2.j, v2.k);
    glNormal3f(grndN[2].i, grndN[2].j, grndN[2].k);
    glVertex3f(v3.i, v3.j, v3.k);
    glNormal3f(grndN[3].i, grndN[3].j, grndN[3].k);
    glVertex3f(v4.i, v4.j, v4.k);
    glEnd();

}


void drawGround(){

    Vector ground[4] = {
            {-20.0f, 0.0f, -20.0f},
            {20.0f, 0.0f, -20.0f},
            {20.0f, 0.0f, 40.0f},
            {-20.0f, 0.0f, 40.0f}

    };

    double stepx = 40.0/20;
    double stepz = 60.0/20;
    if (!flagDivideGround)
        drawG(ground[0], ground[1], ground[2], ground[3]);
    else{
        float x1 = -20;
        float x2 = x1 + stepx;
        for (int i = 0; i < 20; i++) {
            ground[0].i = x1;
            ground[1].i = x2;
            ground[2].i = x2;
            ground[3].i = x1;

            float z1 = -20;
            float z2 = z1 + stepz;
            for (int j = 0; j < 20; j++) {
                ground[0].k = z1;
                ground[1].k = z1;
                ground[2].k = z2;
                ground[3].k = z2;

                z1 += stepz;
                z2 += stepz;

                drawG(ground[0], ground[1], ground[2], ground[3]);
            }
            x1 += stepx;
            x2 += stepx;
        }
    }


}



void display(void){


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(light_position[0], light_position[1], light_position[2]);
    drawSun();
    glPopMatrix();

    drawGround();
    draw_ctrl_points();
    drawRoof();
    mparmpoutsala();

    glFlush();
}

void sunMoving(){

    float step =  0.0005f;

    // Rotate
    rotationSun += step;

    if (light_position[0] >= 49.5f)
        rotationSun = 0.0f;

    light_position[0] = -50 * cosf(rotationSun);
    light_position[1] = 50 * sinf(rotationSun);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Change brightness
    //light_ambient[0] = 0.3f + sinf(rotationSun)*0.7f;
    //light_ambient[1] = 0.3f + sinf(rotationSun)*0.7f;
    //light_ambient[2] = 0.3f + sinf(rotationSun)*0.7f;

    light_diffuse[0] = 0.3f + sinf(rotationSun)*0.7f;
    light_diffuse[1] = 0.3f + sinf(rotationSun)*0.7f;
    light_diffuse[2] = 0.3f + sinf(rotationSun)*0.7f;

    light_specular[0] = 0.3f + sinf(rotationSun)*0.7f;
    light_specular[1] = 0.3f + sinf(rotationSun)*0.7f;
    light_specular[2] = 0.3f + sinf(rotationSun)*0.7f;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    glutPostRedisplay();
}

void rotateCamera(int key, int x, int y ){

    switch ( key ){
        case GLUT_KEY_LEFT:
            rotationView_Left_Right -= 0.05f;
            break;
        case GLUT_KEY_RIGHT:
            rotationView_Left_Right += 0.05f;
            break;
        default:
            break;
    }

    //if (rotationView_Left_Right >= -3.14)
    //    rotationView_Left_Right = -3.14f;

    //if (rotationView_Left_Right <= -3*3.14 )
    //    rotationView_Left_Right = -3*3.14;

    eyePosition[2] = 70 *cosf(rotationView_Left_Right);
    eyePosition[0] = 70 *sinf(rotationView_Left_Right);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2], 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    initLight();

    glutPostRedisplay();
}

void initLight(){
    // Spot light

    glLightfv(GL_LIGHT1, GL_POSITION, spotPos);
    float dir[] = {0.05f, -0.2f, 0.1f};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
    float white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_AMBIENT, white);
}

void myinit()
{


    //Sun
    glLightfv(GL_LIGHT0, GL_POSITION,light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_SMOOTH); /*enable smooth shading */
    glEnable(GL_LIGHTING); /* enable lighting */
    glEnable(GL_LIGHT0);  /* enable light 0 */
    glEnable(GL_DEPTH_TEST); /* enable z buffer */
    glEnable(GL_NORMALIZE);
    glShadeModel (GL_SMOOTH);

    glClearColor (0.0f, 0.0f, 0.0f, 1.0f);

    // Set up projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0f, 1.0f, -1.0, 1.0, 1.2, 170.0);

    // Set up camera view
    rotationView_Left_Right -= 2.0 * 3.14;
    eyePosition[2] = 70 *cosf(rotationView_Left_Right);
    eyePosition[0] = 70 *sinf(rotationView_Left_Right);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2], 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    initLight();
}

void mouse(int btn, int state, int x, int y){
    if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
        glutAttachMenu(GLUT_RIGHT_BUTTON);


}

void menuHandler(int choice) {

    switch (choice) {
        case 1:
            flagDivideGround = 1;
            break;
        case 2:
            flagDivideGround = 0;
            break;
        case 3:
            glDisable(GL_FLAT);
            glShadeModel (GL_SMOOTH);
            glEnable(GL_SMOOTH);
            break;
        case 4:
            glDisable(GL_SMOOTH);
            glShadeModel (GL_FLAT);
            glEnable(GL_FLAT);
            break;
        case 5:
            glEnable(GL_LIGHT1);
            break;
        case 6:
            glDisable(GL_LIGHT1);
            break;
        case 7:
            exit(0);
        default:
            break;
    }

    glutPostRedisplay();

}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("To mikro spiti sto libadi");
    myinit();

    glutMouseFunc (mouse);
    glutCreateMenu(menuHandler);
    glutAddMenuEntry("Divide Ground", 1);
    glutAddMenuEntry("Unify Ground", 2);
    glutAddMenuEntry("Smooth Shading", 3);
    glutAddMenuEntry("Flat Shading", 4);
    glutAddMenuEntry("Spotlight on", 5);
    glutAddMenuEntry("Spotlight off", 6);
    glutAddMenuEntry("EXIT", 7);

    glutDisplayFunc(display);
    glutSpecialFunc(rotateCamera);
    glutIdleFunc(sunMoving);
    glutMainLoop();
}


