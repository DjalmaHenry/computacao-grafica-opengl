#include <Windows.h>
#include <GLFW/glfw3.h>
#include <gl/GLU.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "colors.h"
#include "primitives.h"

/* rotate Sun */
float sunAngle = 0.0f;

/* scale Sun */
float sunSA = 1.5f;
float sunSB = 1.5f;
float sunSC = 1.5f;

/* translate Sun */
float sunTA = -30.0f;
float sunTB = 30.0f;
float sunTC = -100.0f;

/* rotate Roof */
float roofAngle = 0.0f;

/* rotate Stars */
static float angle = 0.0;

/* display list */
struct Object {
    GLuint id;
    vec3 pos;
    Object() :id(0), pos(vec3(0.0, 0.0, 0.0)) {}
};

const GLuint totalObjects = 15;
std::vector<Object> objects;


/* responsive resize */
void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    /* fix deformation */
    float aspect = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, aspect, 0.1, 500.0);

    glMatrixMode(GL_MODELVIEW);
}

void help() {
    std::cout << "                                     " << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "MENU DE INTERACOES" << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "                                     " << std::endl;
    std::cout << "caso  ESC: Finaliza o Programa" << std::endl;
    std::cout << "caso  R: Rotacionar Telhado" << std::endl;
    std::cout << "caso  S: Rotacionar Sol" << std::endl;
    std::cout << "caso  MOUSE1: Diminuir Sol" << std::endl;
    std::cout << "caso  MOUSE2: Aumentar Sol" << std::endl;
    std::cout << "caso  Seta p/ cima: Transladar Sol para frente" << std::endl;
    std::cout << "caso  Seta p/ baixo: Transladar Sol para tras" << std::endl;
    std::cout << "caso  Seta p/ direita: Transladar Sol para direita" << std::endl;
    std::cout << "caso  Seta p/ esquerda: Transladar Sol para esquerda" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

/* draw in screen */
void draw(float dt)
{
    float veloc_ang = 60.0 * dt; // 60 degrees per second
    glLoadIdentity();

    /* Create Terrain */
    glCallList(objects[0].id);

    /* interactions with the sun */
    glPushMatrix();
        glTranslatef(sunTA, sunTB, sunTC);
        glRotatef(sunAngle, 1.0, 1.0, 1.0);
        glScalef(sunSA, sunSB, sunSC);
        glCallList(objects[1].id);
    glPopMatrix();

    /* position house base */
    glPushMatrix();
        glTranslatef(5.0, 2.0, -22.0);
        glCallList(objects[2].id);
    glPopMatrix();

    /* position house door */
    glPushMatrix();
        glTranslatef(3.0, 0.8, -18.0);
        glCallList(objects[3].id);
    glPopMatrix();

    /* position house window */
    glPushMatrix();
        glTranslatef(5.8, 2.2, -18.0);
        glCallList(objects[4].id);
    glPopMatrix();

    /* position house roof */
    glPushMatrix();
        glTranslatef(5.0, 4.5, -22.0);
        glRotatef(roofAngle, 0.0, 1.0, 0.0);
        glCallList(objects[5].id);
    glPopMatrix();

    /* generating stars */
    for (int i = 6; i < totalObjects; i++)
    {
        float x = objects[i].pos.x;
        float y = objects[i].pos.y;
        float z = objects[i].pos.z;

        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(angle, 1.0, 1.0, 0.0);
        glCallList(objects[i].id);
        glPopMatrix();
    }

    angle += veloc_ang;
    if (angle >= 360.0)
        angle = 0.0;
}

float random(float a, float b)
{
    float n = (float)rand() / RAND_MAX;
    float t = b - a;
    float r = a + n * t;
    return r;
}

void init()
{
    glClearColor(0.0, 0.15, 0.25, 1.0); // background color
    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < totalObjects; i++)
    {
        Object p;
        objects.push_back(p);
    }

    /* Create Terrain */
    objects[0].id = glGenLists(totalObjects);
    drawTerrain(objects[0].id);

    /* Create Sun */
    objects[1].id = objects[0].id + 1;
    drawSphere(objects[1].id, 5.0, 20.0, 20.0);

    /* Create House Base */
    objects[2].id = objects[0].id + 2;
    drawCube(objects[2].id, 6.0, 5.0, 5.0);

    /* Create House Door */
    objects[3].id = objects[0].id + 3;
    drawCube(objects[3].id, 1.5, 2.5, 0.5);

    /* Create House Window */
    objects[4].id = objects[0].id + 4;
    drawCube(objects[4].id, 2.5, 1.5, 0.5);

    /* Create House Roof */
    objects[5].id = objects[0].id + 5;
    drawPyramid(objects[5].id, 0.0, 7.0, 8.0);

    /* generating stars */
    for (int i = 6; i < totalObjects; i++)
    {
        objects[i].id = objects[0].id + i;
        float x = random(-150, 300);
        float y = random(40, 100);
        float z = random(-600, -200);
        objects[i].pos = vec3(x, y, z);

        drawSphere(objects[i].id, 5.0, 20.0, 20.0);
    }
}

int main(void)
{
    /* Initialize the library */
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 600, "Project comp graphic 3D", NULL, NULL);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* init */
    init();

    /* MENU in console */
    help();

    float value = 0.0;
    float lastTime = 0.0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* FPS control */
        float currentTime = (float)glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            /* Close Program */
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            /* Rotate Roof */
            roofAngle += 5.0f;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            /* Rotate Sun */
            sunAngle += 5.0f;
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            /* Decrease Sun */
            if (sunSA > 0.1f)
            {
                sunSA -= 0.1f;
                sunSB -= 0.1f;
                sunSC -= 0.1f;
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            /* Increase Sun */
            if (sunSA < 5.0f)
            {
                sunSA += 0.1f;
                sunSB += 0.1f;
                sunSC += 0.1f;
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            /* translate to UP Sun */
            sunTC += 5.0f;
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            /* translate to DOWN Sun */
            sunTC -= 5.0f;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            /* translate to LEFT Sun */
            sunTA -= 5.0f;
        }
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            /* translate to RIGHT Sun */
            sunTA += 5.0f;
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        resize(width, height);

        draw(dt);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glDeleteLists(objects[0].id, totalObjects);
    glfwTerminate();
    return 0;
}