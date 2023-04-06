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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_preview_clicked()
{
    comm_cmd->m_camera_cmd = sys_cmd_resp::CMD_CAMERA_PREVIEW_START;
    emit sig_camera_cmd(comm_cmd);
}

void MainWindow::on_stop_preview_clicked()
{
    comm_cmd->m_camera_cmd = sys_cmd_resp::CMD_CAMERA_PREVIEW_STOP;
    emit sig_camera_cmd(comm_cmd);
}
