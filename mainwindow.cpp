#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "a.h"
#include "campol.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    image_ = new QImage(QSize(w_image_ , h_image_), QImage::Format_RGB888);

    buf_image_ = image_->bits();
    for(int i=0;i<w_image_*h_image_*3;++i){
        *(buf_image_+i) = 100;
    }

    load_bvh();
    index_motion_ = 0;
    update_image(index_motion_);

    ui->horizontalSlider->setStyleSheet("QSlider::groove:horizontal {background: blue;border: 1px solid black;height: 4px;margin: 16px 0px 16px 0px;}QSlider::handle:horizontal {background: black;border: 1px solid black;border-radius: 10px;width: 20px;margin: -16px 0px -16px 0px;}");
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT (h_bar(int)));
    connect(ui->button_play, SIGNAL (released()),this, SLOT (h_button_play()));
}


MainWindow::~MainWindow()
{
    delete ui;

    delete(image_);
    delete[](buf_image_);

    if(rot_) delete(rot_);
}

void MainWindow::load_bvh()
{
    bvh_.load("./data/scene1.bvh");
    //bvh_.load("./data/yzx");


    ui->horizontalSlider->setRange(0, bvh_.motion_.size()-1);
    ui->horizontalSlider->setValue(0);
}

void MainWindow::update_image(int index)
{
    if(index < 0) return;
    if(rot_) delete(rot_);
    rot_ = ROT2::make_bone(&bvh_);
    double resize0 = rot_->normalize_height();
    double resize1 = 1.0;
    rot_->multiply_len(resize1);
    rot_->update_pos();

    vector<THR> data = ROT2::get_frame(bvh_, index);
    rot_->set_serialized_angle(data);
    rot_->p_ = rot_->p_ * resize0*resize1;


    THR rot_root = rot_->q_al_cl_;
    rot_->q_al_cl_ = THR(1, 0, 0, 0);
    ROT2::refer_parent_angle(rot_);
    rot_->q_al_cl_ = rot_root;
    //rot_->p_ = THR(0, 0, 0);
    rot_->update_pos();

    THR dest_camera(0, 0, 0);
    Q q = qua::e2q(ui->graphicsView->h_rot_camera_, ui->graphicsView->v_rot_camera_, 0, qua::RotSeq::yxz);
    THR pos_camera = THR(0, 0, ui->graphicsView->distance_camera_);
    pos_camera = THR(q*pos_camera.q()/q);
    THR dir_camera = (dest_camera-pos_camera).normalize();
    sm img = CamPol::simple_draw(w_image_, h_image_, rot_, pos_camera, dir_camera, NULL);

    int w = img.buf_.size()/h_image_;
    for(int i=0;i<h_image_;++i){
        memcpy(buf_image_+i*w, &(img.buf_)[(h_image_-i-1)*w], w);
    }

    pixmap_ = QPixmap::fromImage(*image_);
    ui->graphicsView->setScene(&scene_);
    scene_.clear();
    scene_.addPixmap(pixmap_);

}

void MainWindow::h_bar(int v)
{
    index_motion_ = v;
    update_image(index_motion_);
}

void MainWindow::h_button_play()
{
    if(timer_id_ == -1){
        ui->button_play->setText("stop");
        timer_id_ = startTimer(20);
    }else{
        killTimer(timer_id_);
        timer_id_ = -1;
        ui->button_play->setText("play");
    }
}

void MainWindow::timerEvent(QTimerEvent * e)
{
    if(timer_id_ == e->timerId()){
        ++index_motion_;
        if(index_motion_ >= bvh_.motion_.size()){
            index_motion_ = 0;
        }
        update_image(index_motion_);
    }
}

