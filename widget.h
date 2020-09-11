#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <GL/glu.h>
#include <QGLWidget>
#include <GL/gl.h>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <vector>

using namespace std;

typedef struct axis
{
    double x;
    double y;
    double z;
}axis;



namespace Ui {
class Widget;
}

class myopengl;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = NULL);
    ~Widget();

protected:
    //void wheelEvent(QWheelEvent *e);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    myopengl *oppp;
};

class myopengl: public QGLWidget
{
     Q_OBJECT
public:
    myopengl(QWidget *parent = NULL);
    void init();
    void setPointS( vector<axis> po);
protected:
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    GLfloat translate, xRot, yRot, zRot;

    int x;
    int y;
    int xx1;
    int yy1;
    bool buttonbl;

    int temxy[2];
    vector<axis> pointlist;

    double glx,gly;


};


#endif // WIDGET_H
