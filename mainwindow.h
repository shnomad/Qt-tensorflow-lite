#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sys_cmd_resp.h"
#include "camera.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_preview_clicked();
    void on_stop_preview_clicked();

signals:
    void sig_camera_cmd(sys_cmd_resp *);

private:
    Ui::MainWindow *ui;
    sys_cmd_resp *comm_cmd;
    camera *m_camera;
};
#endif // MAINWINDOW_H
