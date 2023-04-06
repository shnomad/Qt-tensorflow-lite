#ifndef SYS_CMD_RESP_H
#define SYS_CMD_RESP_H

#include <QObject>

class sys_cmd_resp : public QObject
{
    Q_OBJECT
public:
    explicit sys_cmd_resp(QObject *parent = nullptr);

    enum comm_cmd {CMD_CAMERA_PREVIEW_START=0x10, CMD_CAMERA_PREVIEW_STOP, CMD_CAMERA_IMAGE_CAPTRUE_ON, CMD_CAMERA_IMAGE_CAPTRUE_OFF, CMD_CAMERA_UNKNOWN=0x1f};Q_ENUM(comm_cmd)

    comm_cmd m_camera_cmd = CMD_CAMERA_UNKNOWN;

    signals:

public slots:
};

#endif // SYS_CMD_RESP_H
