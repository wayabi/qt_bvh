#include "my_graphic_view.h"

my_graphic_view::my_graphic_view(QWidget* parent) : QGraphicsView(parent)
{
    main_ = (MainWindow*)(parent->parent());
}

void my_graphic_view::mousePressEvent ( QMouseEvent * event )
{
    pos_mouse_ = event->pos();
    flag_drag_ = true;
}

void my_graphic_view::mouseReleaseEvent ( QMouseEvent * event )
{
    flag_drag_ = false;

}

void my_graphic_view::wheelEvent ( QWheelEvent * event )
{
    double a = -0.03;
    double min = 0.1;
    double max = 10;

    int delta = event->angleDelta().y()/8;
    distance_camera_ += a * delta;
    if(distance_camera_ < min) distance_camera_ = min;
    if(distance_camera_ > max) distance_camera_ = max;
    main_->update_image(main_->index_motion_);
}

void my_graphic_view::mouseMoveEvent ( QMouseEvent * event )
{
    QPoint old = pos_mouse_;
    pos_mouse_ = event->pos();
    if(flag_drag_){
        QPoint p = pos_mouse_ - old;
        int x = p.x();
        int y = p.y();
        double a = 0.01;
        v_rot_camera_ -= a*y;
        double max_v_rot = 1.5;
        if(v_rot_camera_ > max_v_rot) v_rot_camera_ = max_v_rot;
        if(v_rot_camera_ < -max_v_rot) v_rot_camera_ = -max_v_rot;
        h_rot_camera_ += a*x;

        main_->update_image(main_->index_motion_);
    }

}
