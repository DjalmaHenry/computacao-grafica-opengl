#include <Windows.h>
#include <GLFW/glfw3.h>
#include <gl/GLU.h>
#include <iostream>
#include "colors.h"
#include "primitives.h"

/* rotate Sun */
float sunAngle = 0.0f;

/* scale Door */
float doorSA = -1.5f;
float doorSB = -1.5f;
float doorSC = -1.5f;
float doorTA = 0.0f;
float doorTB = 0.0f;

/* scale Roof */
float roof = 2.0f;

/* move House */
float houseA = 0.0f;
float houseB = 0.0f;

/* Base */
float baseA = 0.85;
float baseB = 0.12;
float baseC = 0.0;
float baseD = 1.0;
float baseE = 0.6;
float baseF = 0.2;

/* Door */
float doorA = 0.54;
float doorB = 0.17;
float doorC = 0.88;
float doorD = 0.0;
float doorE = 0.15;
float doorF = 0.35;

/* Window */
float windowA = 0.0;
float windowB = 0.45;
float windowC = 0.6;
float windowD = 0.0;
float windowE = 0.15;
float windowF = 0.35;

/* Roof */
float roofA = 0.0;
float roofB = 1.0;
float roofC = 0.0;
float roofD = 0.0;
float roofE = 0.45;
float roofF = 0.6;

boolean colors = true;

void help() {
    std::cout << "                                     " << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "MENU DE INTERACOES" << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "                                     " << std::endl;
    std::cout << "caso  ESC: Finaliza o Programa" << std::endl;
    std::cout << "caso  R: Rotacionar Sol" << std::endl;
    std::cout << "caso  A: Aumentar Porta da Casa" << std::endl;
    std::cout << "caso  MOUSE1: Mudar Cor da Casa" << std::endl;
    std::cout << "caso  MOUSE2: Voltar Cor Original da Casa" << std::endl;
    std::cout << "caso  D: Diminuir Telhado da Casa" << std::endl;
    std::cout << "caso  Seta p/ cima: Transladar Casa para Cima" << std::endl;
    std::cout << "caso  Seta p/ baixo: Transladar Casa para Baixo" << std::endl;
    std::cout << "caso  Seta p/ direita: Transladar Casa para Direita" << std::endl;
    std::cout << "caso  Seta p/ esquerda: Transladar Casa para Esquerda" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

void draw(float dt)
{
    /* Create Sun */
    glPushMatrix();
        glTranslatef(-8.0, 5.0, 0.0);
        glRotatef(sunAngle, 0.0, 0.0, 1.0);
        drawCircle(2.5, yellow, orange);
    glPopMatrix();

    /* Create Terrain */
    glPushMatrix();
        glTranslatef(-20.0, -9.0, 0.0);
        drawSquare(10.0, 200.0, grey, grey_dark);
    glPopMatrix();

    /* Create House Base */
    glPushMatrix();
        glTranslatef(5.0 + houseA, -3.0 + houseB, 0.0);
        color colorBase1 = { baseA, baseB, baseC };
        color colorBase2 = { baseD, baseE, baseF };
        drawSquare(14.0, 20.0, colorBase1, colorBase2);
    glPopMatrix();

    /* Create House Door */
    glPushMatrix();
        glTranslatef(-1.5 + houseA + doorTA, -8.75 + houseB + doorTB, 0.0);
        glScalef(doorSA, doorSB, doorSC);
        color colorDoor1 = { doorA, doorB, doorC };
        color colorDoor2 = { doorD, doorE, doorF };
        drawSquareDoor(6.0, 10.0, colorDoor1, colorDoor2);
    glPopMatrix();

    /* Create House Window */
    glPushMatrix();
        glTranslatef(7.0 + houseA, -3.0 + houseB, 0.0);
        color colorWindow1 = { windowA, windowB, windowC };
        color colorWindow2 = { windowD, windowE, windowF };
        drawSquare(4.0, 8.0, colorWindow1, colorWindow2);
    glPopMatrix();

    /* Create House Roof */
    glPushMatrix();
        glTranslatef(5.8 + houseA, 5.0 + houseB, 0.0);
        color colorRoof1 = { roofA, roofB, roofC };
        color colorRoof2 = { roofD, roofE, roofF };
        drawTriangle(9.0, roof, colorRoof1, colorRoof2);
    glPopMatrix();

    /* Create Star */
    glPushMatrix();
        glTranslatef(10.0, 8.0, 0.0);
        drawTriangle(1.0, 1.0, yellow, yellow);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(10.0, 7.6, 0.0);
        drawTriangle(-1.0, -1.0, yellow, yellow);
    glPopMatrix();
}

/* responsive resize */
void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    /* fix deformation */
    float aspect = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w >= h)
        glOrtho(-10.0 * aspect, 10.0 * aspect, -10.0, 10.0, 1.0, -1.0);
    else
        glOrtho(-10.0, 10.0, -10.0 / aspect, 10.0 / aspect, 1.0, -1.0);
}

int main(void)
{
    /* Initialize the library */
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 600, "Project comp graphic 2D", NULL, NULL);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* MENU in console */
    help();

    glClearColor(0.0, 0.15, 0.25, 1.0); // background color

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
            /* Rotate Sun */
            sunAngle += 5.0f;
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            /* Increase House Door */
            if (doorSA > -2.2f)
            {
                doorSA -= 0.1f;
                doorSB -= 0.1f;
                doorTA -= 0.25f;
                doorTB -= 0.15f;
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            /* Color House */
            /* Base */
            baseA = 0.0;
            baseB = 0.45;
            baseC = 0.6;
            baseD = 0.0;
            baseE = 1.0;
            baseF = 0.0;
            /* Door */
            doorA = 0.85;
            doorB = 0.12;
            doorC = 0.0;
            doorD = 1.0;
            doorE = 0.6;
            doorF = 0.2;
            /* Window */
            windowA = 0.67;
            windowB = 0.67;
            windowC = 0.67;
            windowD = 0.0;
            windowE = 0.0;
            windowF = 0.0;
            /* Roof */
            roofA = 0.54;
            roofB = 0.17;
            roofC = 0.88;
            roofD = 1.0;
            roofE = 1.0;
            roofF = 1.0;
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            /* Recolor House */
            /* Base */
            baseA = 0.85;
            baseB = 0.12;
            baseC = 0.0;
            baseD = 1.0;
            baseE = 0.6;
            baseF = 0.2;
            /* Door */
            doorA = 0.54;
            doorB = 0.17;
            doorC = 0.88;
            doorD = 0.0;
            doorE = 0.15;
            doorF = 0.35;
            /* Window */
            windowA = 0.0;
            windowB = 0.45;
            windowC = 0.6;
            windowD = 0.0;
            windowE = 0.15;
            windowF = 0.35;
            /* Roof */
            roofA = 0.0;
            roofB = 1.0;
            roofC = 0.0;
            roofD = 0.0;
            roofE = 0.45;
            roofF = 0.6;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            /* Decrease House Roof */
            if (roof > -8.0f)
            {
                roof -= 0.1f;
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            /* translate to UP House */
            houseB += 0.1f;
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            /* translate to DOWN House */
            houseB -= 0.1f;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            /* translate to LEFT House */
            houseA -= 0.1f;
        }
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            /* translate to RIGHT House */
            houseA += 0.1f;
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        resize(width, height);

        draw(dt);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}