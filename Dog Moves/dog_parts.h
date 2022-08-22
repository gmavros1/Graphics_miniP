//
// Created by gmavros on 22/2/22.
//

#ifndef GRAPHICS_AUTH_DOG_PARTS_H
#define GRAPHICS_AUTH_DOG_PARTS_H

#endif //GRAPHICS_AUTH_DOG_PARTS_H

#include <GL/glut.h>

struct point {
    float x;
    float y;
    float z;
};

struct treeNode{
    float m[16]; // right position with father node
    void (*f)(); // draw to initial position
    struct treeNode *child; // pointer to child struct
    struct treeNode *sibling; // pointer to sibling struct
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

void bicubic_surface_2(struct point ctrl_points[16]){
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

    //glDisable(GL_MAP2_VERTEX_3);
    glEnable(GL_MAP2_VERTEX_3);

    for (int j = 0; j < 25; ++j) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 25; ++i) {
            glEvalCoord2f((float)i / 25, (float)j / 25);
        }
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 25; ++i) {
            glEvalCoord2f((float)j / 25, (float)i / 25);
        }
        glEnd();

    }

}

void dog_body(){

    glPushMatrix();
    glTranslatef(-1.6f, 0.225f, 0.0f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    // 1
    ctrl_points1[0].x = -0.4f;
    ctrl_points1[0].y = -0.1f;
    ctrl_points1[0].z = 0.0f;

    ctrl_points1[1].x = 0.9f;
    ctrl_points1[1].y = -0.95f;
    ctrl_points1[1].z = 0.0f;

    ctrl_points1[2].x = 2.35f;
    ctrl_points1[2].y = -0.6f;
    ctrl_points1[2].z = 0.0f;

    ctrl_points1[3].x = 3.3f;
    ctrl_points1[3].y = -0.5f;
    ctrl_points1[3].z = 0.0f;

    // 2
    ctrl_points1[4].x = 0.0f;
    ctrl_points1[4].y = 0.0f;
    ctrl_points1[4].z = 0.25f;

    ctrl_points1[5].x = 0.9f;
    ctrl_points1[5].y = -0.4f;
    ctrl_points1[5].z = 0.75f;

    ctrl_points1[6].x = 2.2f;
    ctrl_points1[6].y = -0.2f;
    ctrl_points1[6].z = 0.4f;

    ctrl_points1[7].x = 3.6f;
    ctrl_points1[7].y = 0.1f;
    ctrl_points1[7].z = 0.0f;

    // 3
    ctrl_points1[8].x = 0.2f;
    ctrl_points1[8].y = 0.2f;
    ctrl_points1[8].z = 0.3f;

    ctrl_points1[9].x = 1.0f;
    ctrl_points1[9].y = 0.0f;
    ctrl_points1[9].z = 0.6f;

    ctrl_points1[10].x = 2.4f;
    ctrl_points1[10].y = -0.05f;
    ctrl_points1[10].z = 0.6f;

    ctrl_points1[11].x = 3.5f;
    ctrl_points1[11].y = 0.2f;
    ctrl_points1[11].z = 0.0f;

    // 4
    ctrl_points1[12].x = 0.3f;
    ctrl_points1[12].y = 0.5f;
    ctrl_points1[12].z = 0.0f;

    ctrl_points1[13].x = 1.2f;
    ctrl_points1[13].y = 0.4f;
    ctrl_points1[13].z = 0.0f;

    ctrl_points1[14].x = 2.5f;
    ctrl_points1[14].y = 0.5f;
    ctrl_points1[14].z = 0.0f;

    ctrl_points1[15].x = 3.3f;
    ctrl_points1[15].y = 0.3f;
    ctrl_points1[15].z = 0.0f;


    //semi
    // 1
    ctrl_points2[0].x = -0.4f;
    ctrl_points2[0].y = -0.1f;
    ctrl_points2[0].z = 0.0f;

    ctrl_points2[1].x = 0.9f;
    ctrl_points2[1].y = -0.95f;
    ctrl_points2[1].z = 0.0f;

    ctrl_points2[2].x = 2.35f;
    ctrl_points2[2].y = -0.6f;
    ctrl_points2[2].z = 0.0f;

    ctrl_points2[3].x = 3.3f;
    ctrl_points2[3].y = -0.5f;
    ctrl_points2[3].z = 0.0f;

    // 2
    ctrl_points2[4].x = 0.0f;
    ctrl_points2[4].y = 0.0f;
    ctrl_points2[4].z = -0.25f;

    ctrl_points2[5].x = 0.9f;
    ctrl_points2[5].y = -0.4f;
    ctrl_points2[5].z = -0.75f;

    ctrl_points2[6].x = 2.2f;
    ctrl_points2[6].y = -0.2f;
    ctrl_points2[6].z = -0.4f;

    ctrl_points2[7].x = 3.6f;
    ctrl_points2[7].y = 0.1f;
    ctrl_points2[7].z = 0.0f;

    // 3
    ctrl_points2[8].x = 0.2f;
    ctrl_points2[8].y = 0.2f;
    ctrl_points2[8].z = -0.3f;

    ctrl_points2[9].x = 1.0f;
    ctrl_points2[9].y = 0.0f;
    ctrl_points2[9].z = -0.6f;

    ctrl_points2[10].x = 2.4f;
    ctrl_points2[10].y = -0.05f;
    ctrl_points2[10].z = -0.6f;

    ctrl_points2[11].x = 3.5f;
    ctrl_points2[11].y = 0.2f;
    ctrl_points2[11].z = 0.0f;

    // 4
    ctrl_points2[12].x = 0.3f;
    ctrl_points2[12].y = 0.5f;
    ctrl_points2[12].z = 0.0f;

    ctrl_points2[13].x = 1.2f;
    ctrl_points2[13].y = 0.4f;
    ctrl_points2[13].z = 0.0f;

    ctrl_points2[14].x = 2.5f;
    ctrl_points2[14].y = 0.5f;
    ctrl_points2[14].z = 0.0f;

    ctrl_points2[15].x = 3.3f;
    ctrl_points2[15].y = 0.3f;
    ctrl_points2[15].z = 0.0f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();
}

void dog_head(){

    glPushMatrix();
    glTranslatef(0.85f, -0.7f, 0.0f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    //1
    ctrl_points1[0].x = -1.7f;
    ctrl_points1[0].y = 0.1f;
    ctrl_points1[0].z = 0.0f;

    ctrl_points1[1].x = -1.4f;
    ctrl_points1[1].y = 0.0f;
    ctrl_points1[1].z = 0.0f;

    ctrl_points1[2].x = -0.7f;
    ctrl_points1[2].y = 0.2f;
    ctrl_points1[2].z = 0.0f;

    ctrl_points1[3].x = -0.4f;
    ctrl_points1[3].y = -0.1f;
    ctrl_points1[3].z = 0.0f;

    //2
    ctrl_points1[4].x = -1.7f;
    ctrl_points1[4].y = 0.5f;
    ctrl_points1[4].z = 0.0f;

    ctrl_points1[5].x = -1.4f;
    ctrl_points1[5].y = 0.2f;
    ctrl_points1[5].z = 0.1f;

    ctrl_points1[6].x = -0.9f;
    ctrl_points1[6].y = 0.35f;
    ctrl_points1[6].z = 0.15f;

    ctrl_points1[7].x = 0.0f;
    ctrl_points1[7].y = 0.0f;
    ctrl_points1[7].z = 0.25f;

    //3
    ctrl_points1[8].x = -2.0f;
    ctrl_points1[8].y = 0.7f;
    ctrl_points1[8].z = 0.0f;

    ctrl_points1[9].x = -1.7f;
    ctrl_points1[9].y = 0.5f;
    ctrl_points1[9].z = 0.12f;

    ctrl_points1[10].x = -1.0f;
    ctrl_points1[10].y = 0.5f;
    ctrl_points1[10].z = 0.2f;

    ctrl_points1[11].x = 0.2f;
    ctrl_points1[11].y = 0.2f;
    ctrl_points1[11].z = 0.3f;

    //4
    ctrl_points1[12].x = -1.3f;
    ctrl_points1[12].y = 0.9f;
    ctrl_points1[12].z = 0.0f;

    ctrl_points1[13].x = -1.0f;
    ctrl_points1[13].y = 1.4f;
    ctrl_points1[13].z = 0.0f;

    ctrl_points1[14].x = -0.5f;
    ctrl_points1[14].y = 1.5f;
    ctrl_points1[14].z = 0.0f;

    ctrl_points1[15].x = 0.3f;
    ctrl_points1[15].y = 0.5f;
    ctrl_points1[15].z = 0.0f;

    // semi
    //1
    ctrl_points2[0].x = -1.7f;
    ctrl_points2[0].y = 0.1f;
    ctrl_points2[0].z = 0.0f;

    ctrl_points2[1].x = -1.4f;
    ctrl_points2[1].y = 0.0f;
    ctrl_points2[1].z = 0.0f;

    ctrl_points2[2].x = -0.7f;
    ctrl_points2[2].y = 0.2f;
    ctrl_points2[2].z = 0.0f;

    ctrl_points2[3].x = -0.4f;
    ctrl_points2[3].y = -0.1f;
    ctrl_points2[3].z = 0.0f;

    //2
    ctrl_points2[4].x = -1.7f;
    ctrl_points2[4].y = 0.5f;
    ctrl_points2[4].z = 0.0f;

    ctrl_points2[5].x = -1.4f;
    ctrl_points2[5].y = 0.2f;
    ctrl_points2[5].z = -0.1f;

    ctrl_points2[6].x = -0.9f;
    ctrl_points2[6].y = 0.35f;
    ctrl_points2[6].z = -0.15f;

    ctrl_points2[7].x = 0.0f;
    ctrl_points2[7].y = 0.0f;
    ctrl_points2[7].z = -0.25f;

    //3
    ctrl_points2[8].x = -2.0f;
    ctrl_points2[8].y = 0.7f;
    ctrl_points2[8].z = 0.0f;

    ctrl_points2[9].x = -1.7f;
    ctrl_points2[9].y = 0.5f;
    ctrl_points2[9].z = -0.12f;

    ctrl_points2[10].x = -1.0f;
    ctrl_points2[10].y = 0.5f;
    ctrl_points2[10].z = -0.2f;

    ctrl_points2[11].x = 0.2f;
    ctrl_points2[11].y = 0.2f;
    ctrl_points2[11].z = -0.3f;

    //4
    ctrl_points2[12].x = -1.3f;
    ctrl_points2[12].y = 0.9f;
    ctrl_points2[12].z = 0.0f;

    ctrl_points2[13].x = -1.0f;
    ctrl_points2[13].y = 1.4f;
    ctrl_points2[13].z = 0.0f;

    ctrl_points2[14].x = -0.5f;
    ctrl_points2[14].y = 1.5f;
    ctrl_points2[14].z = 0.0f;

    ctrl_points2[15].x = 0.3f;
    ctrl_points2[15].y = 0.5f;
    ctrl_points2[15].z = 0.0f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();
}

void dog_front_upper_left(){

    glPushMatrix();
    glTranslatef(-0.715f, 0.77f, -0.65f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    // 1
    ctrl_points1[0].x = 0.5f;
    ctrl_points1[0].y = -1.2f;
    ctrl_points1[0].z = 0.75f;

    ctrl_points1[1].x = 0.7f;
    ctrl_points1[1].y = -1.2f;
    ctrl_points1[1].z = 0.75f;

    ctrl_points1[2].x = 0.9f;
    ctrl_points1[2].y = -1.1f;
    ctrl_points1[2].z = 0.75f;

    ctrl_points1[3].x = 1.1f;
    ctrl_points1[3].y = -1.05f;
    ctrl_points1[3].z = 0.75f;

    // 2
    ctrl_points1[4].x = 0.5f;
    ctrl_points1[4].y = -0.9f;
    ctrl_points1[4].z = 0.75f;

    ctrl_points1[5].x = 0.68f;
    ctrl_points1[5].y = -0.9f;
    ctrl_points1[5].z = 0.8f;

    ctrl_points1[6].x = 0.86f;
    ctrl_points1[6].y = -0.89f;
    ctrl_points1[6].z = 0.7f;

    ctrl_points1[7].x = 1.03f;
    ctrl_points1[7].y = -0.83f;
    ctrl_points1[7].z = 0.75f;

    // 3
    ctrl_points1[8].x = 0.31f;
    ctrl_points1[8].y = -0.53f;
    ctrl_points1[8].z = 0.75f;

    ctrl_points1[9].x = 0.53f;
    ctrl_points1[9].y = -0.53f;
    ctrl_points1[9].z = 0.9f;

    ctrl_points1[10].x = 0.79f;
    ctrl_points1[10].y = -0.45f;
    ctrl_points1[10].z = 0.8f;

    ctrl_points1[11].x = 1.05f;
    ctrl_points1[11].y = -0.45f;
    ctrl_points1[11].z = 0.75f;

    // 4
    ctrl_points1[12].x = 0.37f;
    ctrl_points1[12].y = -0.26f;
    ctrl_points1[12].z = 0.75f;

    ctrl_points1[13].x = 0.55f;
    ctrl_points1[13].y = -0.32f;
    ctrl_points1[13].z = 0.8f;

    ctrl_points1[14].x = 0.79f;
    ctrl_points1[14].y = -0.34f;
    ctrl_points1[14].z = 0.8f;

    ctrl_points1[15].x = 1.12f;
    ctrl_points1[15].y = -0.4f;
    ctrl_points1[15].z = 0.75f;

    // semi
    // 1
    ctrl_points2[0].x = 0.5f;
    ctrl_points2[0].y = -1.2f;
    ctrl_points2[0].z = 0.75f;

    ctrl_points2[1].x = 0.7f;
    ctrl_points2[1].y = -1.2f;
    ctrl_points2[1].z = 0.5f;

    ctrl_points2[2].x = 0.9f;
    ctrl_points2[2].y = -1.1f;
    ctrl_points2[2].z = 0.4f;

    ctrl_points2[3].x = 1.1f;
    ctrl_points2[3].y = -1.05f;
    ctrl_points2[3].z = 0.75f;

    // 2
    ctrl_points2[4].x = 0.5f;
    ctrl_points2[4].y = -0.9f;
    ctrl_points2[4].z = 0.75f;

    ctrl_points2[5].x = 0.68f;
    ctrl_points2[5].y = -0.9f;
    ctrl_points2[5].z = 0.6f;

    ctrl_points2[6].x = 0.86f;
    ctrl_points2[6].y = -0.89f;
    ctrl_points2[6].z = 0.5f;

    ctrl_points2[7].x = 1.03f;
    ctrl_points2[7].y = -0.83f;
    ctrl_points2[7].z = 0.75f;

    // 3
    ctrl_points2[8].x = 0.31f;
    ctrl_points2[8].y = -0.53f;
    ctrl_points2[8].z = 0.75f;

    ctrl_points2[9].x = 0.53f;
    ctrl_points2[9].y = -0.53f;
    ctrl_points2[9].z = 0.7f;

    ctrl_points2[10].x = 0.79f;
    ctrl_points2[10].y = -0.45f;
    ctrl_points2[10].z = 0.6f;

    ctrl_points2[11].x = 1.05f;
    ctrl_points2[11].y = -0.45f;
    ctrl_points2[11].z = 0.75f;

    // 4
    ctrl_points2[12].x = 0.37f;
    ctrl_points2[12].y = -0.26f;
    ctrl_points2[12].z = 0.75f;

    ctrl_points2[13].x = 0.55f;
    ctrl_points2[13].y = -0.32f;
    ctrl_points2[13].z = 0.6f;

    ctrl_points2[14].x = 0.79f;
    ctrl_points2[14].y = -0.34f;
    ctrl_points2[14].z = 0.6f;

    ctrl_points2[15].x = 1.12f;
    ctrl_points2[15].y = -0.4f;
    ctrl_points2[15].z = 0.75f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();

}

void dog_front_upper_right(){

    glPushMatrix();
    glTranslatef(-0.715f, 0.77f, 0.65f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    // 1
    ctrl_points1[0].x = 0.5f;
    ctrl_points1[0].y = -1.2f;
    ctrl_points1[0].z = -0.75f;

    ctrl_points1[1].x = 0.7f;
    ctrl_points1[1].y = -1.2f;
    ctrl_points1[1].z = -0.75f;

    ctrl_points1[2].x = 0.9f;
    ctrl_points1[2].y = -1.1f;
    ctrl_points1[2].z = -0.75f;

    ctrl_points1[3].x = 1.1f;
    ctrl_points1[3].y = -1.05f;
    ctrl_points1[3].z = -0.75f;

    // 2
    ctrl_points1[4].x = 0.5f;
    ctrl_points1[4].y = -0.9f;
    ctrl_points1[4].z = -0.75f;

    ctrl_points1[5].x = 0.68f;
    ctrl_points1[5].y = -0.9f;
    ctrl_points1[5].z = -0.8f;

    ctrl_points1[6].x = 0.86f;
    ctrl_points1[6].y = -0.89f;
    ctrl_points1[6].z = -0.7f;

    ctrl_points1[7].x = 1.03f;
    ctrl_points1[7].y = -0.83f;
    ctrl_points1[7].z = -0.75f;

    // 3
    ctrl_points1[8].x = 0.31f;
    ctrl_points1[8].y = -0.53f;
    ctrl_points1[8].z = -0.75f;

    ctrl_points1[9].x = 0.53f;
    ctrl_points1[9].y = -0.53f;
    ctrl_points1[9].z = -0.9f;

    ctrl_points1[10].x = 0.79f;
    ctrl_points1[10].y = -0.45f;
    ctrl_points1[10].z = -0.8f;

    ctrl_points1[11].x = 1.05f;
    ctrl_points1[11].y = -0.45f;
    ctrl_points1[11].z = -0.75f;

    // 4
    ctrl_points1[12].x = 0.37f;
    ctrl_points1[12].y = -0.26f;
    ctrl_points1[12].z = -0.75f;

    ctrl_points1[13].x = 0.55f;
    ctrl_points1[13].y = -0.32f;
    ctrl_points1[13].z = -0.8f;

    ctrl_points1[14].x = 0.79f;
    ctrl_points1[14].y = -0.34f;
    ctrl_points1[14].z = -0.8f;

    ctrl_points1[15].x = 1.12f;
    ctrl_points1[15].y = -0.4f;
    ctrl_points1[15].z = -0.75f;

    // semi
    // 1
    ctrl_points2[0].x = 0.5f;
    ctrl_points2[0].y = -1.2f;
    ctrl_points2[0].z = -0.75f;

    ctrl_points2[1].x = 0.7f;
    ctrl_points2[1].y = -1.2f;
    ctrl_points2[1].z = -0.5f;

    ctrl_points2[2].x = 0.9f;
    ctrl_points2[2].y = -1.1f;
    ctrl_points2[2].z = -0.4f;

    ctrl_points2[3].x = 1.1f;
    ctrl_points2[3].y = -1.05f;
    ctrl_points2[3].z = -0.75f;

    // 2
    ctrl_points2[4].x = 0.5f;
    ctrl_points2[4].y = -0.9f;
    ctrl_points2[4].z = -0.75f;

    ctrl_points2[5].x = 0.68f;
    ctrl_points2[5].y = -0.9f;
    ctrl_points2[5].z = -0.6f;

    ctrl_points2[6].x = 0.86f;
    ctrl_points2[6].y = -0.89f;
    ctrl_points2[6].z = -0.5f;

    ctrl_points2[7].x = 1.03f;
    ctrl_points2[7].y = -0.83f;
    ctrl_points2[7].z = -0.75f;

    // 3
    ctrl_points2[8].x = 0.31f;
    ctrl_points2[8].y = -0.53f;
    ctrl_points2[8].z = -0.75f;

    ctrl_points2[9].x = 0.53f;
    ctrl_points2[9].y = -0.53f;
    ctrl_points2[9].z = -0.7f;

    ctrl_points2[10].x = 0.79f;
    ctrl_points2[10].y = -0.45f;
    ctrl_points2[10].z = -0.6f;

    ctrl_points2[11].x = 1.05f;
    ctrl_points2[11].y = -0.45f;
    ctrl_points2[11].z = -0.75f;

    // 4
    ctrl_points2[12].x = 0.37f;
    ctrl_points2[12].y = -0.26f;
    ctrl_points2[12].z = -0.75f;

    ctrl_points2[13].x = 0.55f;
    ctrl_points2[13].y = -0.32f;
    ctrl_points2[13].z = -0.6f;

    ctrl_points2[14].x = 0.79f;
    ctrl_points2[14].y = -0.34f;
    ctrl_points2[14].z = -0.6f;

    ctrl_points2[15].x = 1.12f;
    ctrl_points2[15].y = -0.4f;
    ctrl_points2[15].z = -0.75f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();
}

void dog_back_upper_left(){

    glPushMatrix();
    glTranslatef(-2.695f, 0.77f, -0.65f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    // 1
    ctrl_points1[0].x = 0.5f + 1.98f;
    ctrl_points1[0].y = -1.2f;
    ctrl_points1[0].z = 0.45f;

    ctrl_points1[1].x = 0.7f + 1.98f;
    ctrl_points1[1].y = -1.2f;
    ctrl_points1[1].z = 0.5f;

    ctrl_points1[2].x = 0.9f + 1.98f;
    ctrl_points1[2].y = -1.1f;
    ctrl_points1[2].z = 0.5f;

    ctrl_points1[3].x = 1.1f + 1.98f;
    ctrl_points1[3].y = -1.05f;
    ctrl_points1[3].z = 0.45f;

    // 2
    ctrl_points1[4].x = 0.5f + 1.98f;
    ctrl_points1[4].y = -0.9f;
    ctrl_points1[4].z = 0.45f;

    ctrl_points1[5].x = 0.68f + 1.98f;
    ctrl_points1[5].y = -0.9f;
    ctrl_points1[5].z = 0.5f;

    ctrl_points1[6].x = 0.86f + 1.98f;
    ctrl_points1[6].y = -0.89f;
    ctrl_points1[6].z = 0.5f;

    ctrl_points1[7].x = 1.03f + 1.98f;
    ctrl_points1[7].y = -0.83f;
    ctrl_points1[7].z = 0.45f;

    // 3
    ctrl_points1[8].x = 0.31f + 1.98f;
    ctrl_points1[8].y = -0.53f;
    ctrl_points1[8].z = 0.45f;

    ctrl_points1[9].x = 0.53f + 1.98f;
    ctrl_points1[9].y = -0.53f;
    ctrl_points1[9].z = 0.5f;

    ctrl_points1[10].x = 0.79f + 1.98f;
    ctrl_points1[10].y = -0.45f;
    ctrl_points1[10].z = 0.5f;

    ctrl_points1[11].x = 1.05f + 1.98f;
    ctrl_points1[11].y = -0.45f;
    ctrl_points1[11].z = 0.45f;

    // 4
    ctrl_points1[12].x = 0.37f + 1.98f;
    ctrl_points1[12].y = -0.26f;
    ctrl_points1[12].z = 0.45f;

    ctrl_points1[13].x = 0.55f + 1.98f;
    ctrl_points1[13].y = -0.32f;
    ctrl_points1[13].z = 0.5f;

    ctrl_points1[14].x = 0.79f + 1.98f;
    ctrl_points1[14].y = -0.34f;
    ctrl_points1[14].z = 0.5f;

    ctrl_points1[15].x = 1.12f + 1.98f;
    ctrl_points1[15].y = -0.4f;
    ctrl_points1[15].z = 0.45f;

    // semi
    // 1
    ctrl_points2[0].x = 0.5f + 1.98f;
    ctrl_points2[0].y = -1.2f;
    ctrl_points2[0].z = 0.35f;

    ctrl_points2[1].x = 0.7f + 1.98f;
    ctrl_points2[1].y = -1.2f;
    ctrl_points2[1].z = 0.35f;

    ctrl_points2[2].x = 0.9f + 1.98f;
    ctrl_points2[2].y = -1.1f;
    ctrl_points2[2].z = 0.5f;

    ctrl_points2[3].x = 1.1f + 1.98f;
    ctrl_points2[3].y = -1.05f;
    ctrl_points2[3].z = 0.3f;

    // 2
    ctrl_points2[4].x = 0.5f + 1.98f;
    ctrl_points2[4].y = -0.9f;
    ctrl_points2[4].z = 0.3f;

    ctrl_points2[5].x = 0.68f + 1.98f;
    ctrl_points2[5].y = -0.9f;
    ctrl_points2[5].z = 0.35f;

    ctrl_points2[6].x = 0.86f + 1.98f;
    ctrl_points2[6].y = -0.89f;
    ctrl_points2[6].z = 0.35f;

    ctrl_points2[7].x = 1.03f + 1.98f;
    ctrl_points2[7].y = -0.83f;
    ctrl_points2[7].z = 0.3f;

    // 3
    ctrl_points2[8].x = 0.31f + 1.98f;
    ctrl_points2[8].y = -0.53f;
    ctrl_points2[8].z = 0.3f;

    ctrl_points2[9].x = 0.53f + 1.98f;
    ctrl_points2[9].y = -0.53f;
    ctrl_points2[9].z = 0.35f;

    ctrl_points2[10].x = 0.79f + 1.98f;
    ctrl_points2[10].y = -0.45f;
    ctrl_points2[10].z = 0.35f;

    ctrl_points2[11].x = 1.05f + 1.98f;
    ctrl_points2[11].y = -0.45f;
    ctrl_points2[11].z = 0.3f;

    // 4
    ctrl_points2[12].x = 0.37f + 1.98f;
    ctrl_points2[12].y = -0.26f;
    ctrl_points2[12].z = 0.3f;

    ctrl_points2[13].x = 0.55f + 1.98f;
    ctrl_points2[13].y = -0.32f;
    ctrl_points2[13].z = 0.35f;

    ctrl_points2[14].x = 0.79f + 1.98f;
    ctrl_points2[14].y = -0.34f;
    ctrl_points2[14].z = 0.35f;

    ctrl_points2[15].x = 1.12f + 1.98f;
    ctrl_points2[15].y = -0.4f;
    ctrl_points2[15].z = 0.3f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();
}

void dog_back_upper_right(){

    glPushMatrix();
    glTranslatef(-2.695f, 0.77f, 0.65f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    // 1
    ctrl_points1[0].x = 0.5f + 1.98f;
    ctrl_points1[0].y = -1.2f;
    ctrl_points1[0].z = -0.45f;

    ctrl_points1[1].x = 0.7f + 1.98f;
    ctrl_points1[1].y = -1.2f;
    ctrl_points1[1].z = -0.5f;

    ctrl_points1[2].x = 0.9f + 1.98f;
    ctrl_points1[2].y = -1.1f;
    ctrl_points1[2].z = -0.5f;

    ctrl_points1[3].x = 1.1f + 1.98f;
    ctrl_points1[3].y = -1.05f;
    ctrl_points1[3].z = -0.45f;

    // 2
    ctrl_points1[4].x = 0.5f + 1.98f;
    ctrl_points1[4].y = -0.9f;
    ctrl_points1[4].z = -0.45f;

    ctrl_points1[5].x = 0.68f + 1.98f;
    ctrl_points1[5].y = -0.9f;
    ctrl_points1[5].z = -0.5f;

    ctrl_points1[6].x = 0.86f + 1.98f;
    ctrl_points1[6].y = -0.89f;
    ctrl_points1[6].z = -0.5f;

    ctrl_points1[7].x = 1.03f + 1.98f;
    ctrl_points1[7].y = -0.83f;
    ctrl_points1[7].z = -0.45f;

    // 3
    ctrl_points1[8].x = 0.31f + 1.98f;
    ctrl_points1[8].y = -0.53f;
    ctrl_points1[8].z = -0.45f;

    ctrl_points1[9].x = 0.53f + 1.98f;
    ctrl_points1[9].y = -0.53f;
    ctrl_points1[9].z = -0.5f;

    ctrl_points1[10].x = 0.79f + 1.98f;
    ctrl_points1[10].y = -0.45f;
    ctrl_points1[10].z = -0.5f;

    ctrl_points1[11].x = 1.05f + 1.98f;
    ctrl_points1[11].y = -0.45f;
    ctrl_points1[11].z = -0.45f;

    // 4
    ctrl_points1[12].x = 0.37f + 1.98f;
    ctrl_points1[12].y = -0.26f;
    ctrl_points1[12].z = -0.45f;

    ctrl_points1[13].x = 0.55f + 1.98f;
    ctrl_points1[13].y = -0.32f;
    ctrl_points1[13].z = -0.5f;

    ctrl_points1[14].x = 0.79f + 1.98f;
    ctrl_points1[14].y = -0.34f;
    ctrl_points1[14].z = -0.5f;

    ctrl_points1[15].x = 1.12f + 1.98f;
    ctrl_points1[15].y = -0.4f;
    ctrl_points1[15].z = -0.45f;

    // semi
    // 1
    ctrl_points2[0].x = 0.5f + 1.98f;
    ctrl_points2[0].y = -1.2f;
    ctrl_points2[0].z = -0.35f;

    ctrl_points2[1].x = 0.7f + 1.98f;
    ctrl_points2[1].y = -1.2f;
    ctrl_points2[1].z = -0.35f;

    ctrl_points2[2].x = 0.9f + 1.98f;
    ctrl_points2[2].y = -1.1f;
    ctrl_points2[2].z = -0.5f;

    ctrl_points2[3].x = 1.1f + 1.98f;
    ctrl_points2[3].y = -1.05f;
    ctrl_points2[3].z = -0.3f;

    // 2
    ctrl_points2[4].x = 0.5f + 1.98f;
    ctrl_points2[4].y = -0.9f;
    ctrl_points2[4].z = -0.3f;

    ctrl_points2[5].x = 0.68f + 1.98f;
    ctrl_points2[5].y = -0.9f;
    ctrl_points2[5].z = -0.35f;

    ctrl_points2[6].x = 0.86f + 1.98f;
    ctrl_points2[6].y = -0.89f;
    ctrl_points2[6].z = -0.35f;

    ctrl_points2[7].x = 1.03f + 1.98f;
    ctrl_points2[7].y = -0.83f;
    ctrl_points2[7].z = -0.3f;

    // 3
    ctrl_points2[8].x = 0.31f + 1.98f;
    ctrl_points2[8].y = -0.53f;
    ctrl_points2[8].z = -0.3f;

    ctrl_points2[9].x = 0.53f + 1.98f;
    ctrl_points2[9].y = -0.53f;
    ctrl_points2[9].z = -0.35f;

    ctrl_points2[10].x = 0.79f + 1.98f;
    ctrl_points2[10].y = -0.45f;
    ctrl_points2[10].z = -0.35f;

    ctrl_points2[11].x = 1.05f + 1.98f;
    ctrl_points2[11].y = -0.45f;
    ctrl_points2[11].z = -0.3f;

    // 4
    ctrl_points2[12].x = 0.37f + 1.98f;
    ctrl_points2[12].y = -0.26f;
    ctrl_points2[12].z = -0.3f;

    ctrl_points2[13].x = 0.55f + 1.98f;
    ctrl_points2[13].y = -0.32f;
    ctrl_points2[13].z = -0.35f;

    ctrl_points2[14].x = 0.79f + 1.98f;
    ctrl_points2[14].y = -0.34f;
    ctrl_points2[14].z = -0.35f;

    ctrl_points2[15].x = 1.12f + 1.98f;
    ctrl_points2[15].y = -0.4f;
    ctrl_points2[15].z = -0.3f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();
}

void dog_front_lower_left(){

    glPushMatrix();
    glTranslatef(-0.75f, 1.725f, -0.6f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    // 1
    ctrl_points1[0].x = 0.4f;
    ctrl_points1[0].y = -2.29f;
    ctrl_points1[0].z = 0.75f;

    ctrl_points1[1].x = 0.48f;
    ctrl_points1[1].y = -2.33f;
    ctrl_points1[1].z = 0.6f;

    ctrl_points1[2].x = 0.56f;
    ctrl_points1[2].y = -2.35f;
    ctrl_points1[2].z = 0.6f;

    ctrl_points1[3].x = 0.65f;
    ctrl_points1[3].y = -2.4f;
    ctrl_points1[3].z = 0.75f;

    // 2
    ctrl_points1[4].x = 0.54f;
    ctrl_points1[4].y = -1.85f;
    ctrl_points1[4].z = 0.75f;

    ctrl_points1[5].x = 0.67f;
    ctrl_points1[5].y = -1.9f;
    ctrl_points1[5].z = 0.8f;

    ctrl_points1[6].x = 0.78f;
    ctrl_points1[6].y = -1.93f;
    ctrl_points1[6].z = 0.8f;

    ctrl_points1[7].x = 0.92f;
    ctrl_points1[7].y = -1.94f;
    ctrl_points1[7].z = 0.75f;

    // 3
    ctrl_points1[8].x = 0.56f;
    ctrl_points1[8].y = -1.57f;
    ctrl_points1[8].z = 0.75f;

    ctrl_points1[9].x = 0.68f;
    ctrl_points1[9].y = -1.6f;
    ctrl_points1[9].z = 0.8f;

    ctrl_points1[10].x = 0.84f;
    ctrl_points1[10].y = -1.58f;
    ctrl_points1[10].z = 0.8f;

    ctrl_points1[11].x = 1.01f;
    ctrl_points1[11].y = -1.54f;
    ctrl_points1[11].z = 0.75f;

    // 1
    ctrl_points1[12].x = 0.5f;
    ctrl_points1[12].y = -1.2f;
    ctrl_points1[12].z = 0.75f;

    ctrl_points1[13].x = 0.7f;
    ctrl_points1[13].y = -1.2f;
    ctrl_points1[13].z = 0.75f;

    ctrl_points1[14].x = 0.9f;
    ctrl_points1[14].y = -1.1f;
    ctrl_points1[14].z = 0.75f;

    ctrl_points1[15].x = 1.1f;
    ctrl_points1[15].y = -1.05f;
    ctrl_points1[15].z = 0.75f;

    // semi
    // 1
    ctrl_points2[0].x = 0.4f;
    ctrl_points2[0].y = -2.29f;
    ctrl_points2[0].z = 0.75f;

    ctrl_points2[1].x = 0.48f;
    ctrl_points2[1].y = -2.33f;
    ctrl_points2[1].z = 0.6f;

    ctrl_points2[2].x = 0.56f;
    ctrl_points2[2].y = -2.35f;
    ctrl_points2[2].z = 0.6f;

    ctrl_points2[3].x = 0.65f;
    ctrl_points2[3].y = -2.4f;
    ctrl_points2[3].z = 0.75f;

    // 2
    ctrl_points2[4].x = 0.54f;
    ctrl_points2[4].y = -1.85f;
    ctrl_points2[4].z = 0.75f;

    ctrl_points2[5].x = 0.67f;
    ctrl_points2[5].y = -1.9f;
    ctrl_points2[5].z = 0.6f;

    ctrl_points2[6].x = 0.78f;
    ctrl_points2[6].y = -1.93f;
    ctrl_points2[6].z = 0.6f;

    ctrl_points2[7].x = 0.92f;
    ctrl_points2[7].y = -1.94f;
    ctrl_points2[7].z = 0.75f;

    // 3
    ctrl_points2[8].x = 0.56f;
    ctrl_points2[8].y = -1.57f;
    ctrl_points2[8].z = 0.75f;

    ctrl_points2[9].x = 0.68f;
    ctrl_points2[9].y = -1.6f;
    ctrl_points2[9].z = 0.55f;

    ctrl_points2[10].x = 0.84f;
    ctrl_points2[10].y = -1.58f;
    ctrl_points2[10].z = 0.55f;

    ctrl_points2[11].x = 1.01f;
    ctrl_points2[11].y = -1.54f;
    ctrl_points2[11].z = 0.75f;

    // 4
    ctrl_points2[12].x = 0.5f;
    ctrl_points2[12].y = -1.2f;
    ctrl_points2[12].z = 0.75f;

    ctrl_points2[13].x = 0.7f;
    ctrl_points2[13].y = -1.2f;
    ctrl_points2[13].z = 0.5f;

    ctrl_points2[14].x = 0.9f;
    ctrl_points2[14].y = -1.1f;
    ctrl_points2[14].z = 0.4f;

    ctrl_points2[15].x = 1.1f;
    ctrl_points2[15].y = -1.05f;
    ctrl_points2[15].z = 0.75f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();
}

void dog_front_lower_right(){

    glPushMatrix();
    glTranslatef(-0.75f, 1.725f, 0.6f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    // 1
    ctrl_points1[0].x = 0.4f;
    ctrl_points1[0].y = -2.29f;
    ctrl_points1[0].z = -0.75f;

    ctrl_points1[1].x = 0.48f;
    ctrl_points1[1].y = -2.33f;
    ctrl_points1[1].z = -0.6f;

    ctrl_points1[2].x = 0.56f;
    ctrl_points1[2].y = -2.35f;
    ctrl_points1[2].z = -0.6f;

    ctrl_points1[3].x = 0.65f;
    ctrl_points1[3].y = -2.4f;
    ctrl_points1[3].z = -0.75f;

    // 2
    ctrl_points1[4].x = 0.54f;
    ctrl_points1[4].y = -1.85f;
    ctrl_points1[4].z = -0.75f;

    ctrl_points1[5].x = 0.67f;
    ctrl_points1[5].y = -1.9f;
    ctrl_points1[5].z = -0.8f;

    ctrl_points1[6].x = 0.78f;
    ctrl_points1[6].y = -1.93f;
    ctrl_points1[6].z = -0.8f;

    ctrl_points1[7].x = 0.92f;
    ctrl_points1[7].y = -1.94f;
    ctrl_points1[7].z = -0.75f;

    // 3
    ctrl_points1[8].x = 0.56f;
    ctrl_points1[8].y = -1.57f;
    ctrl_points1[8].z = -0.75f;

    ctrl_points1[9].x = 0.68f;
    ctrl_points1[9].y = -1.6f;
    ctrl_points1[9].z = -0.8f;

    ctrl_points1[10].x = 0.84f;
    ctrl_points1[10].y = -1.58f;
    ctrl_points1[10].z = -0.8f;

    ctrl_points1[11].x = 1.01f;
    ctrl_points1[11].y = -1.54f;
    ctrl_points1[11].z = -0.75f;

    // 1
    ctrl_points1[12].x = 0.5f;
    ctrl_points1[12].y = -1.2f;
    ctrl_points1[12].z = -0.75f;

    ctrl_points1[13].x = 0.7f;
    ctrl_points1[13].y = -1.2f;
    ctrl_points1[13].z = -0.75f;

    ctrl_points1[14].x = 0.9f;
    ctrl_points1[14].y = -1.1f;
    ctrl_points1[14].z = -0.75f;

    ctrl_points1[15].x = 1.1f;
    ctrl_points1[15].y = -1.05f;
    ctrl_points1[15].z = -0.75f;

    // semi
    // 1
    ctrl_points2[0].x = 0.4f;
    ctrl_points2[0].y = -2.29f;
    ctrl_points2[0].z = -0.75f;

    ctrl_points2[1].x = 0.48f;
    ctrl_points2[1].y = -2.33f;
    ctrl_points2[1].z = -0.6f;

    ctrl_points2[2].x = 0.56f;
    ctrl_points2[2].y = -2.35f;
    ctrl_points2[2].z = -0.6f;

    ctrl_points2[3].x = 0.65f;
    ctrl_points2[3].y = -2.4f;
    ctrl_points2[3].z = -0.75f;

    // 2
    ctrl_points2[4].x = 0.54f;
    ctrl_points2[4].y = -1.85f;
    ctrl_points2[4].z = -0.75f;

    ctrl_points2[5].x = 0.67f;
    ctrl_points2[5].y = -1.9f;
    ctrl_points2[5].z = -0.6f;

    ctrl_points2[6].x = 0.78f;
    ctrl_points2[6].y = -1.93f;
    ctrl_points2[6].z = -0.6f;

    ctrl_points2[7].x = 0.92f;
    ctrl_points2[7].y = -1.94f;
    ctrl_points2[7].z = -0.75f;

    // 3
    ctrl_points2[8].x = 0.56f;
    ctrl_points2[8].y = -1.57f;
    ctrl_points2[8].z = -0.75f;

    ctrl_points2[9].x = 0.68f;
    ctrl_points2[9].y = -1.6f;
    ctrl_points2[9].z = -0.55f;

    ctrl_points2[10].x = 0.84f;
    ctrl_points2[10].y = -1.58f;
    ctrl_points2[10].z = -0.55f;

    ctrl_points2[11].x = 1.01f;
    ctrl_points2[11].y = -1.54f;
    ctrl_points2[11].z = -0.75f;

    // 4
    ctrl_points2[12].x = 0.5f;
    ctrl_points2[12].y = -1.2f;
    ctrl_points2[12].z = -0.75f;

    ctrl_points2[13].x = 0.7f;
    ctrl_points2[13].y = -1.2f;
    ctrl_points2[13].z = -0.5f;

    ctrl_points2[14].x = 0.9f;
    ctrl_points2[14].y = -1.1f;
    ctrl_points2[14].z = -0.4f;

    ctrl_points2[15].x = 1.1f;
    ctrl_points2[15].y = -1.05f;
    ctrl_points2[15].z = -0.75f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();
}

void dog_back_lower_left(){

    glPushMatrix();
    glTranslatef(-2.73f, 1.725f, -0.6f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    // 1
    ctrl_points1[0].x = 0.4f + 1.98f;
    ctrl_points1[0].y = -2.29f;
    ctrl_points1[0].z = 0.45f;

    ctrl_points1[1].x = 0.48f + 1.98f;
    ctrl_points1[1].y = -2.33f;
    ctrl_points1[1].z = 0.5f;

    ctrl_points1[2].x = 0.56f + 1.98f;
    ctrl_points1[2].y = -2.35f;
    ctrl_points1[2].z = 0.5f;

    ctrl_points1[3].x = 0.65f + 1.98f;
    ctrl_points1[3].y = -2.4f;
    ctrl_points1[3].z = 0.45f;

    // 2
    ctrl_points1[4].x = 0.54f + 1.98f;
    ctrl_points1[4].y = -1.85f;
    ctrl_points1[4].z = 0.45f;

    ctrl_points1[5].x = 0.67f + 1.98f;
    ctrl_points1[5].y = -1.9f;
    ctrl_points1[5].z = 0.5f;

    ctrl_points1[6].x = 0.78f + 1.98f;
    ctrl_points1[6].y = -1.93f;
    ctrl_points1[6].z = 0.5f;

    ctrl_points1[7].x = 0.92f + 1.98f;
    ctrl_points1[7].y = -1.94f;
    ctrl_points1[7].z = 0.45f;

    // 3
    ctrl_points1[8].x = 0.56f + 1.98f;
    ctrl_points1[8].y = -1.57f;
    ctrl_points1[8].z = 0.45f;

    ctrl_points1[9].x = 0.68f + 1.98f;
    ctrl_points1[9].y = -1.6f;
    ctrl_points1[9].z = 0.5f;

    ctrl_points1[10].x = 0.84f + 1.98f;
    ctrl_points1[10].y = -1.58f;
    ctrl_points1[10].z = 0.5f;

    ctrl_points1[11].x = 1.01f + 1.98f;
    ctrl_points1[11].y = -1.54f;
    ctrl_points1[11].z = 0.45f;

    // 4
    ctrl_points1[12].x = 0.5f + 1.98f;
    ctrl_points1[12].y = -1.2f;
    ctrl_points1[12].z = 0.45f;

    ctrl_points1[13].x = 0.7f + 1.98f;
    ctrl_points1[13].y = -1.2f;
    ctrl_points1[13].z = 0.5f;

    ctrl_points1[14].x = 0.9f + 1.98f;
    ctrl_points1[14].y = -1.1f;
    ctrl_points1[14].z = 0.5f;

    ctrl_points1[15].x = 1.1f + 1.98f;
    ctrl_points1[15].y = -1.05f;
    ctrl_points1[15].z = 0.45f;

    // semi
    // 1
    ctrl_points2[0].x = 0.4f + 1.98f;
    ctrl_points2[0].y = -2.29f;
    ctrl_points2[0].z = 0.3f;

    ctrl_points2[1].x = 0.48f + 1.98f;
    ctrl_points2[1].y = -2.33f;
    ctrl_points2[1].z = 0.35f;

    ctrl_points2[2].x = 0.56f + 1.98f;
    ctrl_points2[2].y = -2.35f;
    ctrl_points2[2].z = 0.35f;

    ctrl_points2[3].x = 0.65f + 1.98f;
    ctrl_points2[3].y = -2.4f;
    ctrl_points2[3].z = 0.3f;

    // 2
    ctrl_points2[4].x = 0.54f + 1.98f;
    ctrl_points2[4].y = -1.85f;
    ctrl_points2[4].z = 0.3f;

    ctrl_points2[5].x = 0.67f + 1.98f;
    ctrl_points2[5].y = -1.9f;
    ctrl_points2[5].z = 0.35f;

    ctrl_points2[6].x = 0.78f + 1.98f;
    ctrl_points2[6].y = -1.93f;
    ctrl_points2[6].z = 0.35f;

    ctrl_points2[7].x = 0.92f + 1.98f;
    ctrl_points2[7].y = -1.94f;
    ctrl_points2[7].z = 0.3f;

    // 3
    ctrl_points2[8].x = 0.56f + 1.98f;
    ctrl_points2[8].y = -1.57f;
    ctrl_points2[8].z = 0.3f;

    ctrl_points2[9].x = 0.68f + 1.98f;
    ctrl_points2[9].y = -1.6f;
    ctrl_points2[9].z = 0.35f;

    ctrl_points2[10].x = 0.84f + 1.98f;
    ctrl_points2[10].y = -1.58f;
    ctrl_points2[10].z = 0.35f;

    ctrl_points2[11].x = 1.01f + 1.98f;
    ctrl_points2[11].y = -1.54f;
    ctrl_points2[11].z = 0.3f;

    // 4
    ctrl_points2[12].x = 0.5f + 1.98f;
    ctrl_points2[12].y = -1.2f;
    ctrl_points2[12].z = 0.3f;

    ctrl_points2[13].x = 0.7f + 1.98f;
    ctrl_points2[13].y = -1.2f;
    ctrl_points2[13].z = 0.35f;

    ctrl_points2[14].x = 0.9f + 1.98f;
    ctrl_points2[14].y = -1.1f;
    ctrl_points2[14].z = 0.35f;

    ctrl_points2[15].x = 1.1f + 1.98f;
    ctrl_points2[15].y = -1.05f;
    ctrl_points2[15].z = 0.3f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();
}

void dog_back_lower_right(){

    glPushMatrix();
    glTranslatef(-2.73f, 1.725f, 0.6f);

    struct point ctrl_points1[16]; // change
    struct point ctrl_points2[16]; // change

    // 1
    ctrl_points1[0].x = 0.4f + 1.98f;
    ctrl_points1[0].y = -2.29f;
    ctrl_points1[0].z = -0.45f;

    ctrl_points1[1].x = 0.48f + 1.98f;
    ctrl_points1[1].y = -2.33f;
    ctrl_points1[1].z = -0.5f;

    ctrl_points1[2].x = 0.56f + 1.98f;
    ctrl_points1[2].y = -2.35f;
    ctrl_points1[2].z = -0.5f;

    ctrl_points1[3].x = 0.65f + 1.98f;
    ctrl_points1[3].y = -2.4f;
    ctrl_points1[3].z = -0.45f;

    // 2
    ctrl_points1[4].x = 0.54f + 1.98f;
    ctrl_points1[4].y = -1.85f;
    ctrl_points1[4].z = -0.45f;

    ctrl_points1[5].x = 0.67f + 1.98f;
    ctrl_points1[5].y = -1.9f;
    ctrl_points1[5].z = -0.5f;

    ctrl_points1[6].x = 0.78f + 1.98f;
    ctrl_points1[6].y = -1.93f;
    ctrl_points1[6].z = -0.5f;

    ctrl_points1[7].x = 0.92f + 1.98f;
    ctrl_points1[7].y = -1.94f;
    ctrl_points1[7].z = -0.45f;

    // 3
    ctrl_points1[8].x = 0.56f + 1.98f;
    ctrl_points1[8].y = -1.57f;
    ctrl_points1[8].z = -0.45f;

    ctrl_points1[9].x = 0.68f + 1.98f;
    ctrl_points1[9].y = -1.6f;
    ctrl_points1[9].z = -0.5f;

    ctrl_points1[10].x = 0.84f + 1.98f;
    ctrl_points1[10].y = -1.58f;
    ctrl_points1[10].z = -0.5f;

    ctrl_points1[11].x = 1.01f + 1.98f;
    ctrl_points1[11].y = -1.54f;
    ctrl_points1[11].z = -0.45f;

    // 4
    ctrl_points1[12].x = 0.5f + 1.98f;
    ctrl_points1[12].y = -1.2f;
    ctrl_points1[12].z = -0.45f;

    ctrl_points1[13].x = 0.7f + 1.98f;
    ctrl_points1[13].y = -1.2f;
    ctrl_points1[13].z = -0.5f;

    ctrl_points1[14].x = 0.9f + 1.98f;
    ctrl_points1[14].y = -1.1f;
    ctrl_points1[14].z = -0.5f;

    ctrl_points1[15].x = 1.1f + 1.98f;
    ctrl_points1[15].y = -1.05f;
    ctrl_points1[15].z = -0.45f;

    // semi
    // 1
    ctrl_points2[0].x = 0.4f + 1.98f;
    ctrl_points2[0].y = -2.29f;
    ctrl_points2[0].z = -0.3f;

    ctrl_points2[1].x = 0.48f + 1.98f;
    ctrl_points2[1].y = -2.33f;
    ctrl_points2[1].z = -0.35f;

    ctrl_points2[2].x = 0.56f + 1.98f;
    ctrl_points2[2].y = -2.35f;
    ctrl_points2[2].z = -0.35f;

    ctrl_points2[3].x = 0.65f + 1.98f;
    ctrl_points2[3].y = -2.4f;
    ctrl_points2[3].z = -0.3f;

    // 2
    ctrl_points2[4].x = 0.54f + 1.98f;
    ctrl_points2[4].y = -1.85f;
    ctrl_points2[4].z = -0.3f;

    ctrl_points2[5].x = 0.67f + 1.98f;
    ctrl_points2[5].y = -1.9f;
    ctrl_points2[5].z = -0.35f;

    ctrl_points2[6].x = 0.78f + 1.98f;
    ctrl_points2[6].y = -1.93f;
    ctrl_points2[6].z = -0.35f;

    ctrl_points2[7].x = 0.92f + 1.98f;
    ctrl_points2[7].y = -1.94f;
    ctrl_points2[7].z = -0.3f;

    // 3
    ctrl_points2[8].x = 0.56f + 1.98f;
    ctrl_points2[8].y = -1.57f;
    ctrl_points2[8].z = -0.3f;

    ctrl_points2[9].x = 0.68f + 1.98f;
    ctrl_points2[9].y = -1.6f;
    ctrl_points2[9].z = -0.35f;

    ctrl_points2[10].x = 0.84f + 1.98f;
    ctrl_points2[10].y = -1.58f;
    ctrl_points2[10].z = -0.35f;

    ctrl_points2[11].x = 1.01f + 1.98f;
    ctrl_points2[11].y = -1.54f;
    ctrl_points2[11].z = -0.3f;

    // 4
    ctrl_points2[12].x = 0.5f + 1.98f;
    ctrl_points2[12].y = -1.2f;
    ctrl_points2[12].z = -0.3f;

    ctrl_points2[13].x = 0.7f + 1.98f;
    ctrl_points2[13].y = -1.2f;
    ctrl_points2[13].z = -0.35f;

    ctrl_points2[14].x = 0.9f + 1.98f;
    ctrl_points2[14].y = -1.1f;
    ctrl_points2[14].z = -0.35f;

    ctrl_points2[15].x = 1.1f + 1.98f;
    ctrl_points2[15].y = -1.05f;
    ctrl_points2[15].z = -0.3f;

    bicubic_surface_2(ctrl_points1);
    bicubic_surface_2(ctrl_points2);

    glPopMatrix();
}