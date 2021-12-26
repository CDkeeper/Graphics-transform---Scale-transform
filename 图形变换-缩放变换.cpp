#include<GL/glut.h>
#include<math.h>
#include<Windows.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
GLuint regHex;//显示表标识

class wcPt2D {
public:
    GLfloat x, y;
    wcPt2D(GLfloat x = 0, GLfloat y = 0) {
        this->x = x;
        this->y = y;
    }
};
wcPt2D verts[4] = { wcPt2D(10.0, 10.0), wcPt2D(10.0, 100.0), wcPt2D(100.0, 10.0), wcPt2D(100.0, 100.0) };
GLfloat sx;
GLfloat sy;//缩放系数
void scale(wcPt2D* verts, GLfloat sx, GLfloat sy) {
    //缩放函数，作为例子平移四边形
    GLint nverts = 4;
    wcPt2D fixedPt = verts[0];//选择左下的点作为基准点
    GLint k;
    wcPt2D newVerts[4];//使用一个新的顶点对象集，方便观察平移效果
    for (k = 0; k < nverts; ++k) {
        newVerts[k].x = verts[k].x * sx + fixedPt.x * (1 - sx) + 200;//加200是为了水平平移200个像素，方便比较
        newVerts[k].y = verts[k].y * sy + fixedPt.y * (1 - sy);
    }

    glBegin(GL_QUADS);
    for (k = 0; k < nverts; ++k) {
        glVertex2f(verts[k].x, verts[k].y);
    }
    for (k = 0; k < nverts; ++k) {
        glVertex2f(newVerts[k].x, newVerts[k].y);
    }
    glEnd();

    glFlush();
}
void funcPlot() {
    glClear(GL_COLOR_BUFFER_BIT);
    scale(verts, sx, sy);
}

static void init(void) {
    //初始化函数，并加入表

    glClearColor(1.0, 1.0, 1.0, 0.0);//设置为白色背景
    regHex = glGenLists(1);//获得一个标识
    glColor3f(0.8, 0.7, 0.6);
    glPointSize(2);

}

void winReshapeFcn(int newWidth, int newHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newWidth);
    glClear(GL_COLOR_BUFFER_BIT);

}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("基本图形几何变换之缩放");
    sx = 2, sy = 2;
    init();
    glutDisplayFunc(funcPlot);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
    return 0;
}
