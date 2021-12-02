#pragma once
#include <vector>
#include <cmath>

struct vec3
{
    float x, y, z;
    vec3() :x(0.0), y(0.0), z(0.0) {}
    vec3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
};

/* assembly cube vertices */
void rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4, color color)
{
    glColor3fv(color);
    glBegin(GL_QUADS);
    glVertex3fv(&p1.x);
    glVertex3fv(&p2.x);
    glVertex3fv(&p3.x);
    glVertex3fv(&p4.x);
    glEnd();
}


/* draw cube */
void drawCube(GLuint id, float a, float b, float c)
{
    a = a / 2.0;
    b = b / 2.0;
    c = c / 2.0;

    vec3 v1(-a, b, c);
    vec3 v2(-a, -b, c);
    vec3 v3(a, -b, c);
    vec3 v4(a, b, c);

    vec3 v5(a, b, -c);
    vec3 v6(a, -b, -c);
    vec3 v7(-a, -b, -c);
    vec3 v8(-a, b, -c);

    glNewList(id, GL_COMPILE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (id == 3)
    {
        // front
        rect(v1, v2, v3, v4, red);

        // right
        rect(v4, v3, v6, v5, blue);

        // back
        rect(v5, v8, v7, v6, yellow);

        // left
        rect(v1, v8, v7, v2, green);

        // top
        rect(v1, v4, v5, v8, orange);

        // bottom
        rect(v2, v7, v6, v3, violet);
    }
    else if (id == 4)
    {
        // front
        rect(v1, v2, v3, v4, green);

        // right
        rect(v4, v3, v6, v5, blue);

        // back
        rect(v5, v8, v7, v6, red);

        // left
        rect(v1, v8, v7, v2, yellow);

        // top
        rect(v1, v4, v5, v8, orange);

        // bottom
        rect(v2, v7, v6, v3, violet);
    }
    else if (id == 5)
    {
        // front
        rect(v1, v2, v3, v4, blue);

        // right
        rect(v4, v3, v6, v5, yellow);

        // back
        rect(v5, v8, v7, v6, red);

        // left
        rect(v1, v8, v7, v2, green);

        // top
        rect(v1, v4, v5, v8, orange);

        // bottom
        rect(v2, v7, v6, v3, violet);
    }

    glEndList();
}

/* assembly cube vertices */
void rectPyramid(vec3 p1, vec3 p2, vec3 p3, color color)
{
    glColor3fv(color);
    glBegin(GL_TRIANGLES);
    glVertex3fv(&p1.x);
    glVertex3fv(&p2.x);
    glVertex3fv(&p3.x);
    glEnd();
}

/* draw cube */
void drawPyramid(GLuint id, float a, float b, float c)
{
    a = a / 2.0;
    b = b / 2.0;
    c = c / 2.0;

    vec3 v1(-b, a, b);
    vec3 v2(-b, a, -b);
    vec3 v3(b, a, b);
    vec3 v4(a, c, a);
    vec3 v5(b, a, -b);

    glNewList(id, GL_COMPILE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // base
    rect(v1, v2, v5, v3, red);

    // 1
    rectPyramid(v4, v1, v2, blue);

    // 2
    rectPyramid(v4, v2, v5, orange);

    // 3
    rectPyramid(v4, v5, v3, green);

    // 4
    rectPyramid(v4, v3, v1, yellow);

    glEndList();
}

void drawSphere(unsigned int& id, GLfloat ray, GLuint nStacks, GLuint nSectors)
{
    std::vector< std::vector<GLuint> > indexes;
    std::vector<vec3> points;

    const GLfloat PI = 3.14159265359;

    GLfloat deltaPhi = PI / nStacks;
    GLfloat deltaTheta = 2 * PI / nSectors;

    for (GLuint i = 0; i <= nStacks; i++)
    {
        GLfloat phi = -PI / 2.0 + i * deltaPhi;
        GLfloat temp = ray * cos(phi);
        GLfloat y = ray * sin(phi);

        std::vector<GLuint> pt;

        for (GLuint j = 0; j < nSectors; j++)
        {
            GLfloat theta = j * deltaTheta;
            GLfloat x = temp * sin(theta);
            GLfloat z = temp * cos(theta);

            points.push_back(vec3(x, y, z));
            GLuint index = points.size() - 1;
            pt.push_back(index);
        } // next j

        indexes.push_back(pt);
    } // next i

    glNewList(id, GL_COMPILE);

    for (GLuint i = 0; i < nStacks; i++)
    {
        if (i % 3 == 0)
            glColor3fv(yellow);
        else if (i % 3 == 1)
            glColor3fv(orange);
        else
            glColor3fv(yellow_dark);

        glBegin(GL_TRIANGLE_STRIP);

        for (GLuint j = 0; j < nSectors; j++)
        {
            GLuint index = indexes[i][j];
            glVertex3fv(&points[index].x);
            index = indexes[i + 1][j];
            glVertex3fv(&points[index].x);

            if (j == nSectors - 1)
            {
                index = indexes[i][0];
                glVertex3fv(&points[index].x);
                index = indexes[i + 1][0];
                glVertex3fv(&points[index].x);
            }
        }
        glEnd();
    }
    glEndList();
}

void drawTerrain(unsigned int id)
{
    float L = 500.0;
    float incr = 1.0;
    float y = -0.5;

    glNewList(id, GL_COMPILE);
    glColor3fv(white_ice);
    glBegin(GL_LINES);
    for (float i = -L; i <= L; i += incr)
    {
        // vertical
        glVertex3f(i, y, -L);
        glVertex3f(i, y, L);

        // horizontal
        glVertex3f(-L, y, i);
        glVertex3f(L, y, i);
    }
    glEnd();
    glEndList();
}