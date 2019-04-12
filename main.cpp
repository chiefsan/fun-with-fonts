#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

void display() {
    glClearColor(1,1,0.1,0);

    glFlush();
}

static void click (int button, int state, int x, int y) {
    return;
}

static void load () {
    ifstream inputFile;
    inputFile.open("font.txt");
    int n;
    inputFile >> n;
    cout << n;
    // for (int i=0; i<512; i+=32) {
    //   for (int j=0; j<512; j+=32) {
    //     for (int x=i+1; x<=i+30; ++x) {
    //       for (int y=j+1; y<=j+30; ++y) {
    //         cout <<
    //       }
    //     }
    //   }
    // }
    return;
}

int main (int argc, char** argv) {
    load();
    glutInit(&argc, argv);
    glutInitWindowPosition(200,50);
    glutInitWindowSize(700,700);
    glutCreateWindow("CG Package");
    glClearColor(1,1,0.1,0);
    gluOrtho2D(0,700,0,700);
    glutDisplayFunc(display);
    glutMouseFunc(click);
    glutMainLoop();
    return 0;
}
