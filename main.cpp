#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glut.h>
//#include <stb_image.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
//#include <GL/glew.h>
#include <GL/freeglut.h>

#define ROWS 10  // Number of rows of asteroids.
// Globals.
static intptr_t font = (intptr_t)GLUT_BITMAP_8_BY_13; // Font selection.
static int width, height; // Size of the OpenGL window.
static float angle = 0.0; // Angle of the spacecraft.
static float xVal = 0, zVal = 0; // Co-ordinates of the spacecraft.
static int isCollision = 0; // Is there collision between the spacecraft and an asteroid?
static unsigned int spacecraft; // Display lists base index.
static int frameCount = 0; // Number of frames
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.
//spinning angle of each asteroid
static float sunSpin=0;
static float mercurySpin=0;
static float venusSpin=0;
static float earthSpin=0;
static float marsSpin=0;
static float jupiterSpin=0;
static float saturnSpin=0;
static float uranusSpin=0;
static float neptuneSpin=0;
static float moonSpin=0;
// rotaion angle of each asteroid aound the sun
static float mercuryRot=0;
static float venusRot=0;
static float earthRot=0;
static float marsRot=0;
static float jupiterRot=0;
static float saturnRot=0;
static float uranusRot=0;
static float neptuneRot=0;
static float moonRot=0;

GLfloat centerX = 0.0f;  // X-coordinate of the center point
GLfloat centerY = 0.0f;  // Y-coordinate of the center point
GLfloat centerZ = -40.0f; //z-coordinate of the center point
// Routine to draw a bitmap character string.

void writeBitmapString(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}
// Asteroid class.
class Asteroid
{
public:
    Asteroid();
    Asteroid(float x, float y, float z, float r, unsigned char colorR,
             unsigned char colorG, unsigned char colorB, float spinAngle);
    float getCenterX() { return centerX; }
    float getCenterY() { return centerY; }
    float getCenterZ() { return centerZ; }
    float getRadius() { return radius; }
    void setspinAngle(float ang){spinAngle=ang;}
    void draw();

public:
    float centerX, centerY, centerZ, radius, spinAngle;
    unsigned char color[3];
};

// Asteroid default constructor.
Asteroid::Asteroid()
{
    centerX = 0.0;
    centerY = 0.0;
    centerZ = 0.0;
    radius = 0.0; // Indicates no asteroid exists in the position.
    spinAngle = 0.0;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
}

// Asteroid constructor.
Asteroid::Asteroid(float x, float y, float z, float r, unsigned char colorR,
                   unsigned char colorG, unsigned char colorB, float sAngle)
{
    centerX = x;
    centerY = y;
    centerZ = z;
    radius = r;
    spinAngle= sAngle;
    color[0] = colorR;
    color[1] = colorG;
    color[2] = colorB;
}

// Function to draw asteroid.
void Asteroid::draw()
{
    if (radius > 0.0) // If asteroid exists.
    {
        glPushMatrix();
        glTranslatef(centerX, centerY, centerZ);
        glRotatef(spinAngle, 0.0, 1.0, 0.0);
        glColor3ubv(color);
        glutSolidSphere(radius, (int)radius * 20, (int)radius * 20);
        glPopMatrix();
    }
}

Asteroid arrayAsteroids[ROWS]; // Global array of asteroids.

// Routine to count the number of frames drawn every second.
void frameCounter(int value)
{
    if (value != 0) // No output the first time frameCounter() is called (from main()).
        std::cout << "FPS = " << frameCount << std::endl;
    frameCount = 0;
    glutTimerFunc(1000, frameCounter, 1);
}
void drawCircle(float X, float Y, float Z, float radius, int numSegments) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);  // Set color to white
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);  // Angle for each segment
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex3f(x + X, y + Y, Z);
    }
    glEnd();

    glFlush();
}

// Initialization routine.
void setup(void)
{
    spacecraft = glGenLists(1);
    glNewList(spacecraft, GL_COMPILE);
    glPushMatrix();
    glRotatef(180.0, 0.0, 1.0, 0.0); // To make the spacecraft point down the $z$-axis initially.
    glColor3f(1.0, 1.0, 1.0);
    glutWireCone(5.0, 10.0, 10, 10);
    glPopMatrix();
    glEndList();


    arrayAsteroids[0] = Asteroid(0, 0.0, -40.0 , 10.0,
                                 235,172,63,sunSpin);
    arrayAsteroids[1] = Asteroid(5, 0.0, -40.0 - 30.0, 1.5,
                                 rand() % 256, rand() % 256, rand() % 256,mercurySpin);
    arrayAsteroids[2] = Asteroid(10, 0.0, -40.0 - 30.0*2, 3.0,
                                 rand() % 256, rand() % 256, rand() % 256,venusSpin);
    arrayAsteroids[3] = Asteroid(15, 0.0, -40.0 - 30.0*3, 4.0,
                                 rand() % 256, rand() % 256, rand() % 256,earthSpin);
    arrayAsteroids[4] = Asteroid(20, 0.0, -40.0 - 30.0*4, 2.0,
                                 rand() % 256, rand() % 256, rand() % 256,marsSpin);
    arrayAsteroids[5] = Asteroid(25, 0.0, -40.0 - 30.0*5, 6.0,
                                 rand() % 256, rand() % 256, rand() % 256,jupiterSpin);
    arrayAsteroids[6] = Asteroid(30, 0.0, -40.0 - 30.0*6, 5.0,
                                 rand() % 256, rand() % 256, rand() % 256,saturnSpin);
    arrayAsteroids[7] = Asteroid(35, 0.0, -40.0 - 30.0*7, 3.0,
                                 rand() % 256, rand() % 256, rand() % 256,uranusSpin);
    arrayAsteroids[8] = Asteroid(40, 0.0, -40.0 - 30.0*8, 3.0,
                                 rand() % 256, rand() % 256, rand() % 256,neptuneSpin);
    //moon
    arrayAsteroids[9] = Asteroid(21, 0.0, -40.0 - 30.0*3, 1,
                                 rand() % 256, rand() % 256, rand() % 256,moonSpin);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.02, 0.0888, 0.133333, 0.0);

    glutTimerFunc(0, frameCounter, 0); // Initial call of frameCounter().
}
void init() {
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // We'll use light source 0

    // Set up material properties of the sun (arrayAsteroids[0])
    GLfloat sunDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, sunDiffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
}
// Timer function.
void animate(int value)
{
    if (isAnimate)
    {//spinning of each asteroid around itself
        sunSpin += 0.5;
        if (sunSpin > 360.0) sunSpin -= 360.0;
        arrayAsteroids[0].setspinAngle(sunSpin);

        mercurySpin += 2.0;
        if (mercurySpin > 360.0) mercurySpin -= 360.0;
        arrayAsteroids[1].setspinAngle(mercurySpin);

        venusSpin += 1.0;
        if (venusSpin > 360.0) venusSpin -= 360.0;
        arrayAsteroids[2].setspinAngle(venusSpin);

        earthSpin += 3.8;
        if (earthSpin > 360.0) earthSpin -= 360.0;
        arrayAsteroids[3].setspinAngle(earthSpin);

        marsSpin += 4.0;
        if (marsSpin > 360.0) marsSpin -= 360.0;
        arrayAsteroids[4].setspinAngle(marsSpin);

        jupiterSpin += 7.0;
        if (jupiterSpin > 360.0) jupiterSpin -= 360.0;
        arrayAsteroids[5].setspinAngle(jupiterSpin);

        saturnSpin += 6.0;
        if (saturnSpin > 360.0) saturnSpin -= 360.0;
        arrayAsteroids[6].setspinAngle(saturnSpin);

        uranusSpin += 5.0;
        if (uranusSpin > 360.0) uranusSpin -= 360.0;
        arrayAsteroids[7].setspinAngle(uranusSpin);

        neptuneSpin += 5.0;
        if (neptuneSpin > 360.0) neptuneSpin -= 360.0;
        arrayAsteroids[8].setspinAngle(neptuneSpin);

        moonSpin += 10.0;
        if (moonSpin > 360.0) moonSpin -= 360.0;
        arrayAsteroids[9].setspinAngle(moonSpin);

        //rotation around the sun
        mercuryRot += 4.0;
        if (mercuryRot > 360.0) mercuryRot -= 360.0;

        venusRot += 2.5;
        if (venusRot > 360.0) venusRot -= 360.0;

        earthRot += 2.0;
        if (earthRot > 360.0) earthRot -= 360.0;

        marsRot += 1.0;
        if (marsRot > 360.0) marsRot -= 360.0;

        jupiterRot += 0.6;
        if (jupiterRot > 360.0) jupiterRot -= 360.0;

        saturnRot += 0.3;
        if (saturnRot > 360.0) saturnRot -= 360.0;

        uranusRot += 0.1;
        if (uranusRot > 360.0) uranusRot -= 360.0;

        neptuneRot += 0.08;
        if (neptuneRot > 360.0) neptuneRot -= 360.0;

        moonRot += 6.0;
        if (moonRot > 360.0) moonRot -= 360.0;

        glutPostRedisplay();
        glutTimerFunc(animationPeriod, animate, 1);
    }
}

// Function to check if two spheres centered at (x1,y1,z1) and (x2,y2,z2) with
// radius r1 and r2 intersect.
int checkSpheresIntersection(float x1, float y1, float z1, float r1,
                             float x2, float y2, float z2, float r2)
{
    return ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2) <= (r1 + r2)*(r1 + r2));
}

// Function to check if the spacecraft collides with an asteroid when the center of the base
// of the craft is at (x, 0, z) and it is aligned at an angle a to to the -z direction.
// Collision detection is approximate as instead of the spacecraft we use a bounding sphere.
int asteroidCraftCollision(float x, float z, float a)
{
    int i, j;

    // Check for collision with each asteroid.
    for (i = 0; i<ROWS; i++)
        if (arrayAsteroids[i].getRadius() > 0) // If asteroid exists.
            if (checkSpheresIntersection(x - 5 * sin((M_PI / 180.0) * a), 0.0,
                                         z - 5 * cos((M_PI / 180.0) * a), 7.072,
                                         arrayAsteroids[i].getCenterX(), arrayAsteroids[i].getCenterY(),
                                         arrayAsteroids[i].getCenterZ(), arrayAsteroids[i].getRadius()))
                return 1;
    return 0;
}

// Drawing routine.
void drawScene(void)
{
    frameCount++; // Increment number of frames every redraw.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Rotate scene.
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);

    // Beg	in left viewport.
    glViewport(500, 0, width / 3.0, height/4.0);//demo
    glLoadIdentity();

    // Write text in isolated (i.e., before gluLookAt) translate block.
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos3f(-28.0, 25.0, -30.0);
    if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
    glPopMatrix();

    // Fixed camera.
    gluLookAt(0.0, 100.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glRotatef(-10, 1.0, 0.0, 0.0);
    drawCircle(centerX, centerY,centerZ, 30,100);
    glPopMatrix();

    // Draw all the asteroids in arrayAsteroids in viewport
    GLfloat sunPosition[] = { centerX, centerY, centerZ, 1.0f };
    glDisable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
    //the sun
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
    arrayAsteroids[0].draw();
    glPopMatrix();
    glEnable(GL_LIGHTING);


    //mercury
    GLfloat asteroidAmbient[] ={ 0.44f, 0.59607843f, 0.521568627f, 1.0f };
    GLfloat asteroidShininess = 128.0f; // Set the shininess
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmbient);
    glMaterialf(GL_FRONT, GL_SHININESS, asteroidShininess);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(mercuryRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[1].draw();
    glPopMatrix();

    //venus
    GLfloat asteroidAmbient2[] = { 0.4f, 0.2f, 0.2f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmbient2);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(venusRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[2].draw();
    glPopMatrix();

    // earth
    GLfloat asteroidAmbient3[] = { 0.2f, 0.4f, 0.6f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmbient3);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(earthRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(1.0, 0.0, 0.0);
    arrayAsteroids[3].draw();
    glPopMatrix();

    // mars
    GLfloat asteroidAmbient4[] = { 0.56470588f, 0.25098f, 0.25098f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmbient4);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(marsRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(1.0, 0.0, 1.0);
    arrayAsteroids[4].draw();
    glPopMatrix();

    // Jupiter
    GLfloat asteroidAmbient5[] ={ 0.745098f, 0.3843137f, 0.2745098f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmbient5);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(jupiterRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 1.0, 1.0);
    arrayAsteroids[5].draw();
    glPopMatrix();

    // saturn
    GLfloat asteroidAmbient6[] = { 0.6862745f, 0.6745098f, 0.3058823529f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmbient6);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(saturnRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[6].draw();
    glPopMatrix();

    // uranus
    GLfloat asteroidAmbient7[] = { 0.36862745f, 0.776470588f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmbient7);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(uranusRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[7].draw();
    glPopMatrix();

    // neptune
    GLfloat asteroidAmbient8[] = { 0.0862745f, 0.3803921568f, 0.819607843f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmbient8);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(neptuneRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[8].draw();
    glPopMatrix();

    //moon
    GLfloat asteroidAmbient9[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmbient9);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(earthRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glTranslatef(15, 0.0, -40.0 - 30.0*3);
    glRotatef(moonRot, 0.0, 1.0, 0.0);
    glTranslatef(-15, 0.0, -(-40.0 - 30.0*3));
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[9].draw();
    glPopMatrix();

    // Draw spacecraft.
    glPushMatrix();
    glTranslatef(xVal, 0.0, zVal);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glCallList(spacecraft);
    glPopMatrix();
    // End left viewport.

    // Begin spacecraft
    glViewport(0, 0, width , height);
    glLoadIdentity();

    // Write text in isolated (i.e., before gluLookAt) translate block.
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos3f(-28.0, 25.0, -30.0);
    if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
    glPopMatrix();

    // Locate the camera at the tip of the cone and pointing in the direction of the cone.
    gluLookAt(xVal - 10 * sin((M_PI / 180.0) * angle),
              0.0,
              zVal - 10 * cos((M_PI / 180.0) * angle),
              xVal - 11 * sin((M_PI / 180.0) * angle),
              0.0,
              zVal - 11 * cos((M_PI / 180.0) * angle),
              0.0,
              1.0,
              0.0);
    // Set up the sun's light properties

    GLfloat sunDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sunDiffuse);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);
    glDisable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
    // Draw all the asteroids in arrayAsteroids in spacecraft
    //the sun
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
    arrayAsteroids[0].draw();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    float globAmb[] = { 0.5, 0.5, 0.5, 1.0 };
    float lightDifAndSpec0[] = { 0.5, 0.5, 0.5, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

    //mercury
    GLfloat asteroidAmb[] = { 0.44f, 0.59607843f, 0.521568627f, 1.0f };
    GLfloat asteroidShinines = 128.0f; // Set the shininess
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmb);
    glMaterialf(GL_FRONT, GL_SHININESS, asteroidShininess);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(mercuryRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[1].draw();
    glPopMatrix();

    //venus
    GLfloat asteroidAmb2[] = { 0.4f, 0.2f, 0.2f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmb2);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(venusRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[2].draw();
    glPopMatrix();

    // earth
    GLfloat asteroidAmb3[] = { 0.2f, 0.4f, 0.6f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmb3);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(earthRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(1.0, 0.0, 0.0);
    arrayAsteroids[3].draw();
    glPopMatrix();

    // mars
    GLfloat asteroidAmb4[] = { 0.56470588f, 0.25098f, 0.25098f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmb4);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(marsRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(1.0, 0.0, 1.0);
    arrayAsteroids[4].draw();
    glPopMatrix();

    // Jupiter
    GLfloat asteroidAmb5[] = { 0.745098f, 0.3843137f, 0.2745098f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmb5);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(jupiterRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 1.0, 1.0);
    arrayAsteroids[5].draw();
    glPopMatrix();

    // saturn
    GLfloat asteroidAmb6[] = { 0.6862745f, 0.6745098f, 0.3058823529f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmb6);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(saturnRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[6].draw();
    glPopMatrix();

    // uranus
    GLfloat asteroidAmb7[] = { 0.36862745f, 0.776470588f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmb7);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(uranusRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[7].draw();
    glPopMatrix();

    // neptune
    GLfloat asteroidAmb8[] = { 0.0862745f, 0.3803921568f, 0.819607843f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmb8);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(neptuneRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[8].draw();
    glPopMatrix();

    //moon
    GLfloat asteroidAmb9[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, asteroidAmb9);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(earthRot, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    glTranslatef(15, 0.0, -40.0 - 30.0*3);
    glRotatef(moonRot, 0.0, 1.0, 0.0);
    glTranslatef(-15, 0.0, -(-40.0 - 30.0*3));
    glColor3f(0.0, 0.0, 1.0);
    arrayAsteroids[9].draw();
    glPopMatrix();


    glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
    glMatrixMode(GL_MODELVIEW);

    // Pass the size of the OpenGL window.
    width = w;
    height = h;
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case ' ':
            if (isAnimate) isAnimate = 0;
            else
            {
                isAnimate = 1;
                animate(1);
            }
            break;
        default:
            break;
    }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
    float tempxVal = xVal, tempzVal = zVal, tempAngle = angle;

    // Compute next position.
    if (key == GLUT_KEY_LEFT) tempAngle = angle + 5.0;
    if (key == GLUT_KEY_RIGHT) tempAngle = angle - 5.0;
    if (key == GLUT_KEY_UP)
    {
        tempxVal = xVal - sin(angle * M_PI / 180.0);
        tempzVal = zVal - cos(angle * M_PI / 180.0);
    }
    if (key == GLUT_KEY_DOWN)
    {
        tempxVal = xVal + sin(angle * M_PI / 180.0);
        tempzVal = zVal + cos(angle * M_PI / 180.0);
    }

    // Angle correction.
    if (tempAngle > 360.0) tempAngle -= 360.0;
    if (tempAngle < 0.0) tempAngle += 360.0;

    // Move spacecraft to next position only if there will not be collision with an asteroid.
    if (!asteroidCraftCollision(tempxVal, tempzVal, tempAngle))
    {
        isCollision = 0;
        xVal = tempxVal;
        zVal = tempzVal;
        angle = tempAngle;
    }
    else isCollision = 1;

    glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Press the left/right arrow keys to turn the craft." << std::endl
              << "Press the up/down arrow keys to move the craft." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
    printInteraction();
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("spaceTravel.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

//    glewExperimental = GL_TRUE;
//    glewInit();
    init();
    setup();
    glutMainLoop();
}