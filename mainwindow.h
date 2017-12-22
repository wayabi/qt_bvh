#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPoint>

#include "bvh.h"
#include "rot2.h"

#include "my_graphic_view.h"

namespace Ui {
class MainWindow;
}

class my_graphic_view;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void h_bar(int v);
    void h_button_play();
private:
    void timerEvent(QTimerEvent * e);

public:
    void load_bvh();
    void update_image(int index);

private:
    Ui::MainWindow *ui;
    my_graphic_view* graphic_view_;
    QGraphicsScene scene_;
    QPixmap pixmap_;
    QImage* image_;
    unsigned char* buf_image_;
    int w_image_ = 800;
    int h_image_ = 800;

    int timer_id_ = -1;

    BVH bvh_;
    ROT2* rot_ = NULL;
public:
    int index_motion_ = -1;

};

#endif // MAINWINDOW_H
