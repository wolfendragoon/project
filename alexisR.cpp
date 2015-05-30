/* 
 * Alexis Ragus
 * cs335 project: Uberdude
 * textures & sound
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/gl.h>
#include "ppm.h"
extern "C" {
#include "fonts.h"
}
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define numbox 3

#define USE_SOUND

#ifdef USE_SOUND
#include <FMOD/fmod.h>
#include <FMOD/wincompat.h>
#include "fmod.h"
#endif

Ppmimage *maverickImage=NULL;
Ppmimage *overImage=NULL;
Ppmimage *levelImage=NULL;
GLuint maverickTexture;
GLuint levelTexture;
GLuint overTexture;
int maverick = 1;
int gameOver = 1;
int level = 1;


void platforms(void)
{
    //Clear the screen
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //load the images file into a ppm structure.
    levelImage = ppm6GetImage("./images/level.ppm");
    //create opengl texture elements
    glGenTextures(1, &levelTexture);

    //level
    glBindTexture(GL_TEXTURE_2D, levelTexture);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
            levelImage->width, levelImage->height,
            0, GL_RGB, GL_UNSIGNED_BYTE, levelImage->data);

}

void drawPlatforms(float w, float h)
{

    glColor3f(1.0, 1.0, 1.0);
    if (level) {
        glBindTexture(GL_TEXTURE_2D, levelTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, -h);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, h);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(w, h);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(w, -h);
        glEnd();
    }


}


void texture(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    maverickImage = ppm6GetImage("./images/maverick.ppm");
    //create opengl texture elements
    glGenTextures(1, &maverickTexture);

    //maverick
    glBindTexture(GL_TEXTURE_2D, maverickTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
            maverickImage->width, maverickImage->height,
            0, GL_RGB, GL_UNSIGNED_BYTE, maverickImage->data);


    //initialize fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
}

void r_texture()
{

    //texture background
    glColor3f(1.0, 1.0, 1.0);
    if (maverick) {
        glBindTexture(GL_TEXTURE_2D, maverickTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(0, WINDOW_HEIGHT);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(WINDOW_WIDTH, 0);
        glEnd();
    }

}


void createsounds(void)
{
    #ifdef USE_SOUND
    //FMOD_RESULT result;
    if (fmod_init()) {
        printf("ERROR - createsounds\n\n");
        return;
    }
    if (fmod_createsound((const char *)"./title.mp3", 0)) {
        printf("ERROR - createsounds\n\n");
        return;
    }
    //if (fmod_createsound("./sounds/game_over.mp3", 1)) {
    //    printf("ERROR - fmod_createsound()\n\n");
    //    return;
    //}
    fmod_setmode(0,FMOD_LOOP_OFF);
    //fmod_playsound(0);
    //fmod_systemupdate();
    #endif //USE_SOUND
}

void playsound(void)
{
    #ifdef USE_SOUND
    fmod_playsound(0);
    #endif
}

/*
   void game_over()
   {
//Clear the screen
glClearColor(1.0, 1.0, 1.0, 1.0);
//glClear(GL_COLOR_BUFFER_BIT);
//load the images file into a ppm structure.
overImage = ppm6GetImage("./images/game_over.ppm");
//create opengl texture elements
glGenTextures(1, &overTexture);

//---------------------------------------------------------------------
//game over
glBindTexture(GL_TEXTURE_2D, overTexture);

glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexImage2D(GL_TEXTURE_2D, 0, 3,
overImage->width, overImage->height,
0, GL_RGB, GL_UNSIGNED_BYTE, maverickImage->data);


}

void r_gameOver()
{
//texture background
glColor3f(1.0, 1.0, 1.0);
if (gameOver) {
glBindTexture(GL_TEXTURE_2D, overTexture);
glBegin(GL_QUADS);
glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
glTexCoord2f(0.0f, 0.0f); glVertex2i(0, WINDOW_HEIGHT);
glTexCoord2f(1.0f, 0.0f); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
glTexCoord2f(1.0f, 1.0f); glVertex2i(WINDOW_WIDTH, 0);
glEnd();
}


} 

 */
