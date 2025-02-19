#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

float mosquitoX = -0.9f;
float mosquitoY = 0.5f;
float mosquitoSpeedX = 0.02f;
float mosquitoSpeedY = 0.01f;
bool showCover = false;
bool showRepellent = false;
bool lightsOn = true;
bool mosquitoVisible = true;
bool layingEggs = false;

float repellentX = 0.7f;
float repellentY = -0.5f;
float repellentRadius = 0.3f;

void displayText(float x, float y, const char* text) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void drawMosquito() {
    if (mosquitoVisible) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        for (float angle = 0; angle < 360; angle += 10) {
            float rad = angle * 3.14159f / 180.0f;
            float bodyX = 0.03f * cos(rad) + mosquitoX;
            float bodyY = 0.06f * sin(rad) + mosquitoY;
            glVertex2f(bodyX, bodyY);
        }
        glEnd();

        glBegin(GL_POLYGON);
        for (float angle = 0; angle < 360; angle += 10) {
            float rad = angle * 3.14159f / 180.0f;
            float headX = 0.02f * cos(rad) + mosquitoX;
            float headY = 0.02f * sin(rad) + mosquitoY + 0.07f;
            glVertex2f(headX, headY);
        }
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(mosquitoX, mosquitoY + 0.09f);
        glVertex2f(mosquitoX, mosquitoY + 0.12f);
        glEnd();

        glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
        glBegin(GL_TRIANGLES);
        glVertex2f(mosquitoX - 0.05f, mosquitoY + 0.02f);
        glVertex2f(mosquitoX - 0.12f, mosquitoY + 0.1f);
        glVertex2f(mosquitoX - 0.05f, mosquitoY + 0.1f);
        glVertex2f(mosquitoX + 0.05f, mosquitoY + 0.02f);
        glVertex2f(mosquitoX + 0.12f, mosquitoY + 0.1f);
        glVertex2f(mosquitoX + 0.05f, mosquitoY + 0.1f);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        for (float offset = -0.03f; offset <= 0.03f; offset += 0.03f) {
            glVertex2f(mosquitoX + offset, mosquitoY - 0.02f);
            glVertex2f(mosquitoX + offset * 1.5f, mosquitoY - 0.1f);
        }
        glEnd();
    }
}

void drawWaterContainer() {
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.8f);
    glVertex2f(0.3f, -0.8f);
    glVertex2f(0.3f, -0.4f);
    glVertex2f(-0.3f, -0.4f);
    glEnd();

    if (showCover) {
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(-0.35f, -0.4f);
        glVertex2f(0.35f, -0.4f);
        glVertex2f(0.3f, -0.35f);
        glVertex2f(-0.3f, -0.35f);
        glEnd();
    }
}

void drawRepellent() {
    if (showRepellent) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(repellentX - 0.1f, repellentY - 0.1f);
        glVertex2f(repellentX + 0.1f, repellentY - 0.1f);
        glVertex2f(repellentX + 0.1f, repellentY + 0.1f);
        glVertex2f(repellentX - 0.1f, repellentY + 0.1f);
        glEnd();
    }
}

void drawEggs() {
    if (layingEggs) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glVertex2f(-0.2f, -0.6f);
        glVertex2f(-0.1f, -0.6f);
        glVertex2f(0.0f, -0.6f);
        glVertex2f(0.1f, -0.6f);
        glVertex2f(0.2f, -0.6f);
        glEnd();
    }
}

void drawSpray() {
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
    for (float angle = 0; angle < 360; angle += 15) {
        float rad = angle * 3.14159f / 180.0f;
        float sprayX = 0.6f * cos(rad);
        float sprayY = 0.6f * sin(rad);
        glVertex2f(0.0f, -0.4f);
        glVertex2f(sprayX, sprayY);
    }
    glEnd();
}

void triggerSprayEffect() {
    mosquitoVisible = false;
    layingEggs = false;

    glutTimerFunc(2000, [](int) { mosquitoVisible = true; }, 0);
}

void handleSpecialKeyboard(int key, int x, int y) {
    const float moveStep = 0.05f;
    switch (key) {
    case GLUT_KEY_UP:
        mosquitoY += moveStep;
        if (mosquitoY > 1.0f) mosquitoY = 1.0f;
        break;
    case GLUT_KEY_DOWN:
        mosquitoY -= moveStep;
        if (mosquitoY < -1.0f) mosquitoY = -1.0f;
        break;
    case GLUT_KEY_LEFT:
        mosquitoX -= moveStep;
        if (mosquitoX < -1.0f) mosquitoX = -1.0f;
        break;
    case GLUT_KEY_RIGHT:
        mosquitoX += moveStep;
        if (mosquitoX > 1.0f) mosquitoX = 1.0f;
        break;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (lightsOn) {
        glColor3f(1.0f, 1.0f, 0.8f);
    } else {
        glColor3f(0.2f, 0.2f, 0.2f);
    }
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    displayText(-0.95f, 0.9f, "Dengue Prevention:");
    displayText(-0.95f, 0.8f, "Press 'C' to Cover water container.");
    displayText(-0.95f, 0.7f, "Press 'R' to Use mosquito repellent.");
    displayText(-0.95f, 0.6f, "Press 'L' to Spray repellent.");
    displayText(-0.95f, 0.5f, "Press 'M' to Spray mosquito control.");

    if (!mosquitoVisible) {
        drawSpray();
    } else {
        drawMosquito();
    }

    drawWaterContainer();
    drawRepellent();
    drawEggs();

    glutSwapBuffers();
}

void update(int value) {
    if (mosquitoVisible) {
        mosquitoX += mosquitoSpeedX;
        mosquitoY += mosquitoSpeedY;

        if (mosquitoX > 1.0f || mosquitoX < -1.0f) {
            mosquitoSpeedX = -mosquitoSpeedX;
        }
        if (mosquitoY > 1.0f || mosquitoY < -1.0f) {
            mosquitoSpeedY = -mosquitoSpeedY;
        }

        if (!showCover && mosquitoX > -0.3f && mosquitoX < 0.3f && mosquitoY > -0.8f && mosquitoY < -0.4f) {
            layingEggs = true;
        } else {
            layingEggs = false;
        }

        if (showRepellent) {
            float distanceToRepellent = sqrt(pow(mosquitoX - repellentX, 2) + pow(mosquitoY - repellentY, 2));
            if (distanceToRepellent < repellentRadius) {
                mosquitoSpeedX = mosquitoX < repellentX ? -fabs(mosquitoSpeedX) : fabs(mosquitoSpeedX);
                mosquitoSpeedY = mosquitoY < repellentY ? -fabs(mosquitoSpeedY) : fabs(mosquitoSpeedY);
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void handleKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    } else if (key == 'c' || key == 'C') {
        showCover = !showCover;
        layingEggs = false;
    } else if (key == 'r' || key == 'R') {
        showRepellent = !showRepellent;
        if (showRepellent) {
            mosquitoX = -0.9f;
            mosquitoY = 0.5f;
            layingEggs = false;
        }
    } else if (key == 'l' || key == 'L') {
        mosquitoX = (rand() % 2 == 0 ? -1.0f : 1.0f) * (0.5f + static_cast<float>(rand()) / RAND_MAX * 0.5f);
        mosquitoY = (rand() % 2 == 0 ? -1.0f : 1.0f) * (0.5f + static_cast<float>(rand()) / RAND_MAX * 0.5f);

        mosquitoSpeedX *= 0.5f;
        mosquitoSpeedY *= 0.5f;

        glutTimerFunc(2000, [](int) {
            mosquitoSpeedX = 0.02f;
            mosquitoSpeedY = 0.01f;
        }, 0);

        layingEggs = false;
    } else if (key == 'm' || key == 'M') {
        triggerSprayEffect();
    }
    glutPostRedisplay();
}


void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Dengue Awareness Interactive Tool");

    initOpenGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(handleSpecialKeyboard);
    glutTimerFunc(30, update, 0);

    glutMainLoop();
    return 0;
}
