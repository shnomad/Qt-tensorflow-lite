#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    comm_cmd = new sys_cmd_resp;

    /*Camera function */
    m_camera = new camera;

    connect(this, SIGNAL(sig_camera_cmd(sys_cmd_resp *)), m_camera, SLOT(operation(sys_cmd_resp *)));

    /*Camera Preview Image Update*/
    QObject::connect(m_camera, &camera::sig_preview_image_update, [this](QImage image)
    {
          ui->display_preview->setPixmap(QPixmap::fromImage(image));
    });

    /*push button */
    ui->start_preview->setStyleSheet("default");
    ui->stop_preview->setStyleSheet("default");
    ui->start_preview->setEnabled(true);
    ui->stop_preview->setEnabled(false);
}

void MainWindow::on_start_preview_clicked()
{
//    ui->start_preview->setStyleSheet("background-color:rgb(244,0,0);border-style:insert");
    ui->start_preview->setStyleSheet("border:2px solid #ff0000;");
    ui->stop_preview->setStyleSheet("default");
    ui->start_preview->setEnabled(false);
    ui->stop_preview->setEnabled(true);

    comm_cmd->m_camera_cmd = sys_cmd_resp::CMD_CAMERA_PREVIEW_START;
    emit sig_camera_cmd(comm_cmd);
}

void MainWindow::on_stop_preview_clicked()
{
    ui->start_preview->setStyleSheet("default");
    ui->stop_preview->setStyleSheet("default");
    ui->start_preview->setEnabled(true);
    ui->stop_preview->setEnabled(false);

    comm_cmd->m_camera_cmd = sys_cmd_resp::CMD_CAMERA_PREVIEW_STOP;
    emit sig_camera_cmd(comm_cmd);
}

void MainWindow::on_capture_stateChanged(int arg1)
{
    if(arg1)
        comm_cmd->m_camera_cmd = sys_cmd_resp::CMD_CAMERA_IMAGE_CAPTRUE_ON;
    else
        comm_cmd->m_camera_cmd = sys_cmd_resp::CMD_CAMERA_IMAGE_CAPTRUE_OFF;

    emit sig_camera_cmd(comm_cmd);
}

MainWindow::~MainWindow()
{
    delete ui;
}
