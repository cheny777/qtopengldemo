#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include <math.h>
#include <QDebug>
#include <QVBoxLayout>
#include <QFileDialog>
#include <fstream>
#include <sstream>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    oppp  = new myopengl(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(ui->pushButton);
    layout->addWidget(oppp);
}

Widget::~Widget()
{
    delete ui;
}

//void Widget::wheelEvent(QWheelEvent *e)
//{
//    if(e->delta()>0){//如果滚轮往上滚
//        qDebug()<<"a";
//    }else{//同样的
//        qDebug()<<"a";
//    }
//}

myopengl::myopengl(QWidget *parent)
    :QGLWidget(parent)
{
    translate = -6.0;
    xRot = yRot = zRot = 0.0;
    // setMouseTracking(true);
    x =y=0;
    buttonbl= true;
    glx = 0;
    gly = 0;
}

void myopengl::init()
{
    translate = -6.0;
    xRot = yRot = zRot = 0.0;
    // setMouseTracking(true);
    x =y=0;
    glx = 0;
    gly = 0;
    buttonbl= true;
    updateGL();
}

void myopengl::setPointS(vector<axis> po)
{
    pointlist.clear();
    pointlist = po;
    updateGL();
}

void myopengl::initializeGL()
{
    /*设置清屏颜色*/
    glClearColor(1,1,1,1);
    /*设置着实技术，可以取值GL_FLAT和GL_SMOOTH。默认取值是GL_SMOOTH。*/
    glShadeModel(GL_SMOOTH);

    glClearDepth(1.0);
    /*GL_ALPHA_TEST	4864	跟据函数glAlphaFunc的条件要求来决定图形透明的层度是否显示。*/
    glEnable(GL_DEPTH_TEST);

}

void myopengl::resizeGL(int w, int h)
{
    glViewport(0, 0, GLint(w), GLint(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, w/h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myopengl::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(glx/(100.0), -gly/(100.0), translate);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);
    // 上面
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    // 下面
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    // 前面
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);

    glEnd();

    //点的大小默认为一个像素，通过下面的函数可以设置一点的大小

    glPointSize(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);
    for(unsigned long long i =0 ; i<pointlist.size() ; i++)
    {
        if(i == pointlist.size()-2)
        {
            glColor3f(0.0f, 1.0f, 0.0f);
        }
        glVertex3f(GLfloat(pointlist[i].x), GLfloat(pointlist[i].y),GLfloat(pointlist[i].z));
    }

    glEnd();


    glPointSize(1.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0,0);
    glVertex3f(100, 0,0);
    glEnd();
    glPointSize(1.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0,0);
    glVertex3f(0, 100,0);
    glEnd();
    glPointSize(1.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0,0);
    glVertex3f(0, 0,100);
    glEnd();
}

void myopengl::keyPressEvent(QKeyEvent *)
{

}

void myopengl::wheelEvent(QWheelEvent *e)
{
    if(e->delta()>0)
    {
        translate +=GLfloat(0.5);
    }
    else
    {
        translate-=GLfloat(0.5);
    }
    qDebug()<<translate;
    updateGL();


}

void myopengl::mousePressEvent(QMouseEvent *event)
{
    x = event->globalPos().x()- this->pos().x()-temxy[0];
    y = event->globalPos().y()- this->pos().y()-temxy[1];
    xx1 = event->globalPos().x()- this->pos().x()-glx;
    yy1 = event->globalPos().y()- this->pos().y()-gly;
}

void myopengl::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton)
    {
        int x1,y1;
        x1 = event->globalPos().x()- this->pos().x();
        y1 = event->globalPos().y()- this->pos().y();

       // qDebug()<<x1-x<<" "<<y1-y;
        yRot = x1-x;
        xRot = y1-y;
        updateGL();
    }
    if(event->buttons() == Qt::RightButton)
    {
        int x1,y1;
        x1 = event->globalPos().x()- this->pos().x();
        y1 =event->globalPos().y() -this->pos().y();

        glx = x1-xx1;
        gly = y1-yy1;
        updateGL();

    }
}

void myopengl::mouseReleaseEvent(QMouseEvent *event)
{
    temxy[0] =  int(yRot);
    temxy[1] =  int(xRot);
}



void Widget::on_pushButton_clicked()
{
    oppp->init();;
}

void Widget::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(NULL,"open","./","tr(*.*)");

    ifstream infile;

    infile.open(path.toStdString().c_str(), ios::in);

    vector<axis> axisvec;

    char buffer[256];
    double doux = 0, douy = 0,douz = 0;
    char o;
    if (infile.is_open())
    {
        qDebug() << "打开成功";
        while (!infile.eof())
        {
            infile.getline(buffer, 256);
            if (buffer[0] == 'G' && buffer[1] == '0' && buffer[2] == '1' && buffer[3] == 'X')
            {
                stringstream sstr(buffer);
                sstr >> o >> o >> o >> o >> doux >> o >> douy>>o>>douz;
                axis as;
                as.x = doux;
                as.y = douy;
                as.z = douz;
                axisvec.push_back(as);
            }
            if (buffer[0] == 'X')
            {
                stringstream sstr(buffer);
                sstr >> o >> doux >> o >> douy>>o>>douz;
                if (o == 'Z')
                {
                    axis as;
                    as.x = doux;
                    as.y = douy;
                    as.z = douz;
                    axisvec.push_back(as);
                }
            }
        }
        oppp->setPointS(axisvec);
    }
}
