#include "draw.h"

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{ 
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

    aspectRatio = width / (float) height;

    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1) 
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio, 
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }
}


// Chargement de l'image 
SDL_Surface* Image_Load(char* image_path){
    SDL_Surface* image = IMG_Load(image_path);
    if(NULL == image) {
        fprintf(stderr, "Echec du chargement de l'image %s\n", image_path);
        exit(EXIT_FAILURE);
    }
    return image;
}


// Initialisation de la texture (à partir de l'image)
GLuint Texture_Load(char* image_path){
    GLuint texture_id;
    //chargement de l'image
    SDL_Surface* image = Image_Load(image_path);

    glGenTextures(1, &texture_id);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLenum format;
    switch(image->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", image_path);
            return EXIT_FAILURE;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
    
    /* Liberation de la memoire allouee sur le GPU pour la texture */
    glDeleteTextures(1, &texture_id);

    /* Liberation de la mémoire occupee par img */ 
    SDL_FreeSurface(image);

    return texture_id;
}

//////////////////////////////////////
///////////OBJETS CANONIQUES//////////
//////////////////////////////////////
void drawOrigin() 
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 1.0 , 0.0);

    glColor3f(0., 1., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 0.0 , 1.0);

    glEnd();

    glColor3fv(currentColor);
}

void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.5 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( -0.5 , 0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( 0.5 , -0.5);

    glEnd();
}

void drawCircle(int filled) 
{
    int i = 0;

    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    for(i = 0; i < CIRCLE_SUBDIVS; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));
    }
    glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));

    glEnd();
}

void drawRoundedSquare(int filled)
{
    const float r = 0.1;
    const float s = 1. / 2;
    const float t = s - r;

    int i = 0;

    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f(s, t);
    for(i = 1; i < CIRCLE_SUBDIVS / 4; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r + t, 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r + t);
    }
    glVertex2f(t, s);
    glVertex2f(-t, s);
    for(i = CIRCLE_SUBDIVS / 4; i < CIRCLE_SUBDIVS / 4 * 2; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r - t, 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r + t);
    }
    glVertex2f(-s, t);
    glVertex2f(-s, -t);
    for(i = CIRCLE_SUBDIVS / 4 * 2; i < CIRCLE_SUBDIVS / 4 * 3; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r - t, 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r - t);
    }
    glVertex2f(-t, -s);
    glVertex2f(t, -s);
    for(i = CIRCLE_SUBDIVS / 4 * 3; i < CIRCLE_SUBDIVS / 4 * 4; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r + t, 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r - t);
    }
    glVertex2f(s, -t);
    glVertex2f(s, t);

    glEnd();
}