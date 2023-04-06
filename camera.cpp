#include "camera.h"
#include <QDateTime>

camera::camera(QObject *parent) : QObject(parent)
{
    camera_timer = new QTimer(this);
    m_console_command = new CLI_monitor;
}

void camera::preview_start()
{
    cap.open(0);

       if(!cap.isOpened())
       {

       }
       else
       {                      
           m_console_command->sendCommand("v4l2-ctl -d /dev/video0 --set-ctrl=auto_exposure=3");
           m_console_command->sendCommand("v4l2-ctl -d /dev/video0 --set-ctrl=focus_automatic_continuous=1");

           connect(camera_timer, SIGNAL(timeout()), this, SLOT(update_image()));
           camera_timer->start(50);
       }
}

void camera::preview_stop()
{
      disconnect(camera_timer, SIGNAL(timeout()), this, SLOT(update_image()));

      cap.release();
      Mat image = Mat::zeros(frame.size(), CV_8UC3);
      qt_image = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);

 //   ui->preview->setPixmap(QPixmap::fromImage(qt_image));
}

void camera::update_image()
{
        cap >> frame;
        cvtColor(frame, frame, COLOR_BGR2RGB);

        if(preview_image_capture)
        {
             QDateTime Current_Time = QDateTime::currentDateTime();
             QString filename = "/home/pi/capture_file/" + Current_Time.toString("yyyyMMddhhmmsszzz") + ".jpg";
             imwrite(filename.toStdString(),frame);
        }

        qt_image = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);

        emit sig_preview_image_update(qt_image);
}

void camera::operation(sys_cmd_resp *cmd_from_host)
{
    switch (cmd_from_host->m_camera_cmd)
    {
        case sys_cmd_resp::CMD_CAMERA_PREVIEW_START:
                preview_start();
            break;

        case sys_cmd_resp::CMD_CAMERA_PREVIEW_STOP:
                preview_stop();
                preview_image_capture = false;
            break;

        case sys_cmd_resp::CMD_CAMERA_IMAGE_CAPTRUE_ON:
                preview_image_capture = true;
            break;

        case sys_cmd_resp::CMD_CAMERA_IMAGE_CAPTRUE_OFF:
                preview_image_capture = false;
            break;
    }
}
