#ifndef MY_GRAPHIC_VIEW_H
#define MY_GRAPHIC_VIEW_H

#include <QGraphicsView>
#include "mainwindow.h"

class MainWindow;
class my_graphic_view : public QGraphicsView
{
public:
    explicit my_graphic_view(QWidget* parent);

private slots:
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void wheelEvent(QWheelEvent * event);

public:
    MainWindow* main_;
    QPoint pos_mouse_;
    bool flag_drag_ = false;
    int* index_motion_;

    double v_rot_camera_;
    double h_rot_camera_;
    double distance_camera_ = 1.0;
};

#endif // MY_GRAPHIC_VIEW_H
