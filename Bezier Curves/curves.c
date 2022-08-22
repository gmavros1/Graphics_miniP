#include <GL/glut.h>
#include <math.h>
#include "dotVectorProd.h"

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


// Things to be drawn : Control Points - curves or surfaces points
struct point {
    float x;
    float y;
    float z;
};

// Matrices
float Mi[4][4] =
        {
                {1.0f, 0.0f, 0.0f, 0.0f},
                {-5.5f, 9.0f, -4.5f, 1.0f},
                {9.0f, -22.5f, 18.0f, -4.5f},
                {-4.5f, 13.5f, -13.5f, 4.5f}

        };


float Mb[4][4] =
        {
                {1.0f, 0.0f, 0.0f, 0.0f},
                {1.0f, 1.0f/3.0f, 0.0f, 0.0f},
                {1.0f, 2.0f/3.0f,1.0f/3.0f, 0.0f},
                {1.0f, 1.0f, 1.0f, 1.0f}

        };

int num_of_ctrl_points;
struct point ctrl_points[16];
int type = 1; // 1 cubic - 2 bezier - 3 bezier - 4 cubic surf
int max_control_points = 7;

//struct point curve_points[100]; // find 100 points maximum

void Multiply(float N[4][3], float M[4][4], float Result[4][3])
{
    for (int I = 0; I < 4; ++I)
    {
        for (int J = 0; J < 3; ++J)
        {
            float SumElements = 0.0f;
            for (int K = 0; K < 4; ++K)
            {
                SumElements += M[I][K] * N[K][J];
            }
            Result[I][J] = SumElements;
        }
    }
}

void captureControlPoints(float x, float y){

    if (num_of_ctrl_points == max_control_points)
        return;

    float wx,wy;

    wx = (2.0 *x )/(float)(width-1)-1.0;
    wy = (2.0 * (height-1-y))/(float)(height-1)-1.0;

    ctrl_points[num_of_ctrl_points].x = wx * 14;
    ctrl_points[num_of_ctrl_points].y = wy * 14;
    ctrl_points[num_of_ctrl_points].z = 0;

    num_of_ctrl_points ++;

    if (num_of_ctrl_points == max_control_points){
        change_projection();
    }

    glutPostRedisplay();
}

void draw_ctrl_points(){

    glColor3d(1.0, 0.0, 0.0);
    glPointSize(20);
    glBegin(GL_POINTS);
    for (int i = 0; i < num_of_ctrl_points; i++)
        glVertex3f(ctrl_points[i].x, ctrl_points[i].y, ctrl_points[i].z);
    glEnd();
}

void closed_bezier(){
    float points [max_control_points][3];

    for (int i = 0; i < max_control_points; ++i) {
        points[i][0] = ctrl_points[i].x;
        points[i][1] = ctrl_points[i].y;
        points[i][2] = ctrl_points[i].z;
    }

    points[6][0] = ctrl_points[0].x;
    points[6][1] = ctrl_points[0].y;
    points[6][2] = ctrl_points[0].z;

    glMap1f(GL_MAP1_VERTEX_3, (float)0.0, 1, 3, max_control_points+1, &points[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    int NUM_STEPS = 50;

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= NUM_STEPS; i++)
        glEvalCoord1f((GLfloat)i/(float)NUM_STEPS);
    glEnd();

}

void cubic_curve(){
    float points [max_control_points][3];

    for (int i = 0; i < max_control_points; ++i) {
        points[i][0] = ctrl_points[i].x;
        points[i][1] = ctrl_points[i].y;
        points[i][2] = ctrl_points[i].z;
    }

    // ** first curve

    //  Mi * point (M*q)
    float resluts1[4][3];
    Multiply(points, Mi, resluts1);

    // Mb(-1) * results1
    float results2[4][3];
    Multiply(resluts1, Mb, results2);

    glMap1f(GL_MAP1_VERTEX_3, (float)0.0, 1, 3, 4, &results2[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    int NUM_STEPS = 50;

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= NUM_STEPS; i++)
        glEvalCoord1f((GLfloat)i/(float)NUM_STEPS);
    glEnd();

    // ** second curve

    //  Mi * point (M*q)
    float reslutsa1[4][3];
    Multiply(&points[3], Mi, reslutsa1);

    // Mb(-1) * results1
    float resultsa2[4][3];
    Multiply(reslutsa1, Mb, resultsa2);

    glMap1f(GL_MAP1_VERTEX_3, (float)0.0, 1, 3, 4, &resultsa2[0][0]);
    glEnable(GL_MAP1_VERTEX_3);


    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= NUM_STEPS; i++)
        glEvalCoord1f((GLfloat)i/(float)NUM_STEPS);
    glEnd();

}

void smooth_curve(){
    float points [4][3];

    for (int i = 0; i < 4; ++i) {
        points[i][0] = ctrl_points[i].x;
        points[i][1] = ctrl_points[i].y;
        points[i][2] = ctrl_points[i].z;
    }

    // ** first curve

    //  Mi * point (M*q)
    //float resluts1[4][3];
    //Multiply(points, Mi, resluts1);

    // Mb(-1) * results1
    //float results2[4][3];
    //Multiply(resluts1, Mb, results2);

    glMap1f(GL_MAP1_VERTEX_3, (float)0.0, 1, 3, 4, &points[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    int NUM_STEPS = 50;


    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= NUM_STEPS; i++)
        glEvalCoord1f((GLfloat)i/(float)NUM_STEPS);
    glEnd();

    // ** second curve
    float pointsA [4][3];

    pointsA[0][0] = ctrl_points[3].x;
    pointsA[0][1] = ctrl_points[3].y;
    pointsA[0][2] = ctrl_points[3].z;

    // oposite second point
    pointsA[1][0] = (ctrl_points[3].x - ctrl_points[2].x) + ctrl_points[3].x;
    pointsA[1][1] = (ctrl_points[3].y - ctrl_points[2].y) + ctrl_points[3].y;
    pointsA[1][2] = (ctrl_points[3].z - ctrl_points[2].z) + ctrl_points[3].z;

    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex3f(pointsA[1][0], pointsA[1][1], pointsA[1][2]);
    glEnd();

    pointsA[2][0] = ctrl_points[4].x;
    pointsA[2][1] = ctrl_points[4].y;
    pointsA[2][2] = ctrl_points[4].z;

    pointsA[3][0] = ctrl_points[5].x;
    pointsA[3][1] = ctrl_points[5].y;
    pointsA[3][2] = ctrl_points[5].z;


    //  Mi * point (M*q)
    //float reslutsa1[4][3];
    //Multiply(pointsA, Mi, reslutsa1);

    // Mb(-1) * results1
    //float resultsa2[4][3];
    //Multiply(reslutsa1, Mb, resultsa2);

    glMap1f(GL_MAP1_VERTEX_3, (float)0.0, 1, 3, 4, &pointsA[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= NUM_STEPS; i++)
        glEvalCoord1f((GLfloat)i/(float)NUM_STEPS);
    glEnd();

}

void bicubic_surface_2(){
    float pointsRow1 [4][3];
    float pointsRow2 [4][3];
    float pointsRow3 [4][3];
    float pointsRow4 [4][3];

    for (int i = 0; i < 4; ++i) {
        pointsRow1[i][0] = ctrl_points[i].x;
        pointsRow1[i][1] = ctrl_points[i].y;
        pointsRow1[i][2] = ctrl_points[i].z;

        pointsRow2[i][0] = ctrl_points[4 + i].x;
        pointsRow2[i][1] = ctrl_points[4 + i].y;
        pointsRow2[i][2] = ctrl_points[4 + i].z;

        pointsRow3[i][0] = ctrl_points[8 + i].x;
        pointsRow3[i][1] = ctrl_points[8 + i].y;
        pointsRow3[i][2] = ctrl_points[8 + i].z;

        pointsRow4[i][0] = ctrl_points[12 + i].x;
        pointsRow4[i][1] = ctrl_points[12 + i].y;
        pointsRow4[i][2] = ctrl_points[12 + i].z;
    }

    float results1a[4][3];
    float results1b[4][3];

    Multiply(pointsRow1, Mi, results1a);
    Multiply(results1a, Mb, results1b);

    float results2a[4][3];
    float results2b[4][3];

    Multiply(pointsRow2, Mi, results2a);
    Multiply(results2a, Mb, results2b);

    float results3a[4][3];
    float results3b[4][3];

    Multiply(pointsRow3, Mi, results3a);
    Multiply(results3a, Mb, results3b);

    float results4a[4][3];
    float results4b[4][3];

    Multiply(pointsRow4, Mi, results4a);
    Multiply(results4a, Mb, results4b);

    float results[16][3];

    for (int i = 0; i < 4; ++i) {
        results[i][0] = results1b[i][0];
        results[i][1] = results1b[i][1];
        results[i][2] = results1b[i][2];

        results[i + 4][0] = results2b[i][0];
        results[i + 4][1] = results2b[i][1];
        results[i + 4][2] = results2b[i][2];

        results[i + 8][0] = results3b[i][0];
        results[i + 8][1] = results3b[i][1];
        results[i + 8][2] = results3b[i][2];

        results[i + 12][0] = results4b[i][0];
        results[i + 12][1] = results4b[i][1];
        results[i + 12][2] = results4b[i][2];

    }

    float pointsCol1 [4][3];
    float pointsCol2 [4][3];
    float pointsCol3 [4][3];
    float pointsCol4 [4][3];

    for (int i = 0; i < 4; ++i) {
        pointsCol1[i][0] = results[i*4][0];
        pointsCol1[i][1] = results[i*4][1];
        pointsCol1[i][2] = results[i*4][2];

        pointsCol2[i][0] = results[(i*4)+1][0];
        pointsCol2[i][1] = results[(i*4)+1][1];
        pointsCol2[i][2] = results[(i*4)+1][2];

        pointsCol3[i][0] = results[(i*4)+2][0];
        pointsCol3[i][1] = results[(i*4)+2][1];
        pointsCol3[i][2] = results[(i*4)+2][2];

        pointsCol4[i][0] = results[(i*4)+3][0];
        pointsCol4[i][1] = results[(i*4)+3][1];
        pointsCol4[i][2] = results[(i*4)+3][2];

    }

    float results1A[4][3];
    float results1B[4][3];

    Multiply(pointsCol1, Mi, results1A);
    Multiply(results1A, Mb, results1B);

    float results2A[4][3];
    float results2B[4][3];

    Multiply(pointsCol2, Mi, results2A);
    Multiply(results2A, Mb, results2B);

    float results3A[4][3];
    float results3B[4][3];

    Multiply(pointsCol3, Mi, results3A);
    Multiply(results3A, Mb, results3B);

    float results4A[4][3];
    float results4B[4][3];

    Multiply(pointsCol4, Mi, results4A);
    Multiply(results4A, Mb, results4B);

    float resultsCol[16][3];

    for (int i = 0; i < 4; ++i) {
        resultsCol[i*4][0] = results1B[i][0];
        resultsCol[i*4][1] = results1B[i][1];
        resultsCol[i*4][2] = results1B[i][2];

        resultsCol[(i*4)+1][0] = results2B[i][0];
        resultsCol[(i*4)+1][1] = results2B[i][1];
        resultsCol[(i*4)+1][2] = results2B[i][2];

        resultsCol[(i*4)+2][0] = results3B[i][0];
        resultsCol[(i*4)+2][1] = results3B[i][1];
        resultsCol[(i*4)+2][2] = results3B[i][2];

        resultsCol[(i*4)+3][0] = results4B[i][0];
        resultsCol[(i*4)+3][1] = results4B[i][1];
        resultsCol[(i*4)+3][2] = results4B[i][2];

    }

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &resultsCol[0][0]);

    glEnable(GL_MAP2_VERTEX_3);

    for (int j = 0; j < 100; ++j) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 100; ++i) {
            glEvalCoord2f((float)i / 100, (float)j / 100);
        }
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 100; ++i) {
            glEvalCoord2f((float)j / 100, (float)i / 100);
        }
        glEnd();

    }

}

int spot_control_points(float x, float y){
    float wx, wy;
    wx = (float) ((2.0 *x )/(float)(width-1)-1.0) * (float)14;
    wy = (float) ((2.0 * (height-1-y))/(float)(height-1)-1.0) * (float)14;

    float min = 2.0f;
    int index = -1;
    for (int i = 0; i < max_control_points; ++i) {
        float distance;
        distance = sqrtf(powf((wx - ctrl_points[i].x), 2) + powf((wy - ctrl_points[i].y), 2));
        if (distance <= min){
            min = distance;
            index = i;
        }
    }

    return index;

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //draw_ctrl_points();

    glColor3d(0.0, 1.0, 0.0);
    if (num_of_ctrl_points == max_control_points) {
        if (type == 1)
            cubic_curve();
        if (type == 2) {
            closed_bezier();
        }
        if (type == 3) {
            smooth_curve();
        }
        if (type == 4) {
            bicubic_surface_2();
        }
    }

    draw_ctrl_points();
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

void motion(int x, int y){
    float movex, movey; // motion metric
    if(motionv){

        movex = (float)(((2.0 *x )/(float)(width-1)-1.0) * 14.0f) - initialMousePositionX ;
        movey = (float)(((2.0 * (height-1-y))/(float)(height-1)-1.0) * 14.0f) - initialMousePositionY ;
        //movex = (float) ((2.0 *movex )/(float)(width-1)-1.0);
        //movey = (float) ((2.0 * (height-1-movey))/(float)(height-1)-1.0);

        float newX = ctrl_points[whichPoint].x + movex;
        float newY = ctrl_points[whichPoint].y + movey;

        ctrl_points[whichPoint].x = newX;
        ctrl_points[whichPoint].y = newY;


    }

    initialMousePositionX = (float)(((2.0 *x )/(float)(width-1)-1.0) * 14.0f);
    initialMousePositionY = (float)(((2.0 * (height-1-y))/(float)(height-1)-1.0) * 14.0f);

    glutPostRedisplay();

}

void mouse(int btn, int state, int x, int y){

    if (num_of_ctrl_points >= max_control_points){
        if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
            motionv = 1;
            //initialMousePositionX = x;
            //initialMousePositionY = y;
            initialMousePositionX =  ((2.0f *(float)x )/(float)(width-1)-1.0f) * 14.0f;
            initialMousePositionY = ((2.0f * ((float)height-1-(float)y))/(float)(height-1)-1.0f) * 14.0f;

            whichPoint = spot_control_points((float)x, (float)y);
            if (whichPoint == -1)
                return;
        }
        //glutPostRedisplay();
        if(btn==GLUT_LEFT_BUTTON&&state==GLUT_UP)
            motionv = 0;

    }

    if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
        captureControlPoints((float)x, (float)y);


    if (btn == 4) {

        if (motionv == 1){
            ctrl_points[whichPoint].z = ctrl_points[whichPoint].z + 0.1;
            glutPostRedisplay();
            return;
        }

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

        if (motionv == 1){
            ctrl_points[whichPoint].z = ctrl_points[whichPoint].z - 0.1;
            glutPostRedisplay();
            return;
        }

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

void menuHandler(int choice) {

    switch (choice) {
        case 1:
            type = choice;
            max_control_points = 7;
            glLineWidth(7);
            myinit();
            break;
        case 2:
            type = choice;
            max_control_points = 6;
            glLineWidth(7);
            myinit();
            break;
        case 3:
            type = 3;
            max_control_points = 6;
            glLineWidth(7);
            myinit();
            break;
        case 4:
            type = choice;
            max_control_points = 16;
            glLineWidth(1);
            myinit();
            break;
        default:
            break;
    }


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
    rotationView_Up_Down = 0.0f;
    rad = 70.0f;

    num_of_ctrl_points = 0;

    for (int i = 0; i < 16; ++i) {
        ctrl_points[i].x = 0.0f;
        ctrl_points[i].y = 0.0f;
        ctrl_points[i].z = 0.0f;
    }

    change_projection();

    /*
    glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-14, 14, -14, 14);
    glMatrixMode(GL_MODELVIEW);//community.khronos.org/t/error-gl-gl-h-no-such-file-or-directory-even-tough-i-have-it-installed-debian/71888
    glLoadIdentity();
    */
     }

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("To mikro spiti sto libadi");
    myinit();
    glLineWidth(7);

    glutMotionFunc(motion);
    glutMouseFunc (mouse);
    glutCreateMenu(menuHandler);
    glutAddMenuEntry("Cubic Curve", 1);
    glutAddMenuEntry("Closed Bezier", 2);
    glutAddMenuEntry("Two smooth cubic", 3);
    glutAddMenuEntry("Cubic surface", 4);

    glutDisplayFunc(display);
    glutSpecialFunc(rotateCamera);
    glutMainLoop();
}


