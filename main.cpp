// Fun with Fonts

// Render fonts in OpenGL

#include "windows.h"

#include <GL/glut.h>

#include <vector>

#include <fstream>

// Bitmap of all characters
bool font[256][32][32];
// Indicates if character should be bold
bool bold = false;
// Indicates if character should be underlined
bool underline = false;
// Indicates if character should be struck through
bool strikethrough = false;
// Indicates if character should be italicized
bool italic = false;
// Raster position in x coordinate
int rasterx = 20;
// Raster position in y coordinate
int rastery = 20;

// Represents rendering from top left
const unsigned short TOP_LEFT = 12;
// Represents rendering from top right
const unsigned short TOP_RIGHT = 23;
// Represents rendering from bottom left
const unsigned short BOTTOM_LEFT = 43;
// Represents rendering from bottom right
const unsigned short BOTTOM_RIGHT = 54;

// Reads the image and loads the font into the font bitmap
void load(std::string path) {

    std::ifstream inputFile;
    inputFile.open(path, std::ios:: in );
    double n;
    std::vector < double > arr;

    for (int i = 0; i < 512; ++i) {
        for (int j = 0; j < 512; ++j) {
            inputFile >> n;
            arr.push_back(n);
        }
    }

    int k = -1;
    for (int i = 0; i < 512; i += 32) {
        for (int j = 0; j < 512; j += 32) {
            k += 1;
            for (int x = i + 1 - 1; x <= i + 30 + 1; ++x) {
                for (int y = j + 1 - 1; y <= j + 30 + 1; ++y) {
                    n = arr[x * 512 + y];
                    n = n != 0 ? 1 : 0;
                    arr[x * 512 + y] = n;
                    font[k][x - (i + 1 - 1)][y - (j + 1 - 1)] = n;
                }
            }
        }
    }

    return;
}

// GLUT display function
static void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, .1, 0);

    glFlush();

    return;
}

// GLUT mouse function
// Sets the raster position
void click(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN) {
        glRasterPos2i(x, 600 - y);
        rasterx = x;
        rastery = y;
    }

    return;
}

// Render the font on the screen in the raster position following the required method and scaling
// xchange -> change in rasterx after rendering the font
// ychange -> change in rastery after rendering the font
void write(bool g[32][32], int xchange = 33, int ychange = -32, unsigned short method = TOP_LEFT, unsigned short scale = 1) {

    int size = 32;
    int newSize = (int)(scale * 32);

    bool ** f;
    f = new bool * [newSize];
    for (int i = 0; i < newSize; ++i) {
        f[i] = new bool[newSize];
    }

    // 1*1 cell becomes factor*factor cells
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            for (int k = 0; k < scale; ++k) {
                for (int l = 0; l < scale; ++l) {
                    f[i * scale + k][j * scale + l] = g[i][j];
                }
            }
        }
    }
    size = newSize;

    glBegin(GL_POINTS);

    if (method == BOTTOM_LEFT) {
        for (int i = size - 1; i >= 0; i--) {
            for (int j = 0; j < size; ++j) {
                if (f[i][j] == 1)
                    glVertex2f(rasterx, 600 - rastery);
                rasterx += 1;
            }
            rasterx -= size;
            rastery -= 1;
        }
    } else if (method == BOTTOM_RIGHT) {
        for (int i = size - 1; i >= 0; i--) {
            for (int j = size - 1; j >= 0; j--) {
                if (f[i][j] == 1)
                    glVertex2f(rasterx, 600 - rastery);
                rasterx -= 1;
            }
            rasterx += size;
            rastery -= 1;
        }
    } else if (method == TOP_RIGHT) {
        for (int i = 0; i < size; ++i) {
            for (int j = size - 1; j >= 0; j--) {
                if (f[i][j] == 1)
                    glVertex2f(rasterx, 600 - rastery);
                rasterx -= 1;
            }
            rasterx += size;
            rastery += 1;
        }

    } else if (method == TOP_LEFT) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (f[i][j] == 1)
                    glVertex2f(rasterx, 600 - rastery);
                rasterx += 1;
            }
            rasterx -= size;
            rastery += 1;
        }
    }

    rastery += ychange;
    rasterx += xchange;

    glEnd();
    glFlush();

    return;
}

// GLUT keyboard function
// type the character based on keyboard input
// toggle transformations
//  / - italic
//  ] - strikethrough
//  [ - underline
//  * - bold
void type(unsigned char c, int x, int y) {

    if (c == '/') {
        italic = !italic;
        return;
    }

    if (c == ']') {
        strikethrough = !strikethrough;
        return;
    }

    if (c == '[') {
        underline = !underline;
        return;
    }

    if (c == '*') {
        bold = !bold;
        return;
    }

    bool f[32][32];
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            if (i == 31 || j == 31 || i == 0 || j == 0)
                f[i][j] = 0;
            else
                f[i][j] = font[c][i][j];
        }
    }

    // if font[i][j] is set then font[i+1][j] and font[i][j+1] are set
    if (bold) {
        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 32; ++j) {
                f[i][j] = font[c][i][j];
                if (i > 1) {
                    if (font[c][i - 1][j] == 1)
                        f[i][j] = 1;
                }
                if (j > 1) {
                    if (font[c][i][j - 1] == 1)
                        f[i][j] = 1;
                }
                if (i == 31 || j == 31 || i == 0 || j == 0)
                    f[i][j] = 0;
            }
        }
    }

    //  shear transformation
    if (italic) {
        for (int i = 0; i < 8; ++i)
            for (int j = 31; j >= 6; --j)
                f[i][j] = f[i][j - 4];
        for (int i = 8; i < 16; ++i)
            for (int j = 31; j >= 3; --j)
                f[i][j] = f[i][j - 2];
        for (int i = 16; i < 24; ++i)
            for (int j = 0; j < 32 - 3; ++j)
                f[i][j] = f[i][j + 2];
        for (int i = 24; i < 32; ++i)
            for (int j = 0; j < 32 - 6; ++j)
                f[i][j] = f[i][j + 2];
    }

    //  strike through
    if (strikethrough) {
        for (int i = 14; i < 16; ++i) {
            for (int j = 0; j < 32; ++j) {
                f[i][j] = 1;
            }
        }
    }

    //  underline
    if (underline) {
        for (int i = 28; i < 30; ++i) {
            for (int j = 2; j < 30; ++j) {
                f[i][j] = 1;
            }
        }
    }

    // write(f);
    write(f, 96 + 1, -96, TOP_LEFT, 3);

    glFlush();

    return;
}

int main(int argc, char ** argv) {

    load("D:\\Programming\\College\\CGV\\package\\font.txt");

    glutInit( & argc, argv);
    glutInitWindowPosition(200, 50);
    glutInitWindowSize(1200, 600);
    glutCreateWindow("Fun with Fonts");
    glClearColor(0, 0, .1, 0);
    gluOrtho2D(0, 1200, 0, 600);
    glRasterPos2i(200, 200);
    glutDisplayFunc(display);
    glutKeyboardFunc(type);
    glutMouseFunc(click);
    glutMainLoop();

    return EXIT_SUCCESS;
}
