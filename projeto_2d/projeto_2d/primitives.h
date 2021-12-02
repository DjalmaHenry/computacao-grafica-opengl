#pragma once
#include <vector>
#include <cmath>

struct vec3
{
    float x, y;
    vec3() :x(0.0), y(0.0) {}
    vec3(float x_, float y_) :x(x_), y(y_) {}
};

void drawCircle(float ray, color color1, color color2) {
    int i;
    float angle = 0.0;
    
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 50; i++) {
        if(i <= 25)
            glColor3fv(color1);
        else
            glColor3fv(color2);
        angle = (2 * 3.14 * i) / 50.0;
        glVertex2f(ray * cos(angle), ray * sin(angle));
    }
    glEnd();
}

void drawSquare(float a, float b, color color1, color color2)
{
    glBegin(GL_QUADS);
        glColor3fv(color1);
        glVertex2f(-0.25 * a, 0.25 * a);
        glVertex2f(0.25 * b, 0.25 * a);
        glColor3fv(color2);
        glVertex2f(0.25 * b, -0.25 * a);
        glVertex2f(-0.25 * a, -0.25 * a);
    glEnd();
}

void drawSquareDoor(float a, float b, color color1, color color2)
{
    glBegin(GL_QUADS);
        glColor3fv(color1);
        glVertex2f(-0.75 * a, -0.25 * a);
        glVertex2f(-0.25 * b, -0.25 * a);
        glColor3fv(color2);
        glVertex2f(-0.25 * b, -0.75 * a);
        glVertex2f(-0.75 * a, -0.75 * a);
    glEnd();
}

void drawTriangle(float a, float b, color color1, color color2)
{
    glBegin(GL_TRIANGLES);
        glColor3fv(color1);
        glVertex2f(0.0 * b, 0.5 * b);
        glVertex2f(-0.5 * a, -0.5 * a);
        glColor3fv(color2);
        glVertex2f(0.5 * a, -0.5 * a);
    glEnd();
}