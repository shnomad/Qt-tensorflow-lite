QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    sys_cmd_resp.cpp

HEADERS += \
    camera.h \
    mainwindow.h \
    sys_cmd_resp.h

FORMS += \
    mainwindow.ui

INCLUDEPATH +=/opt/ML/RPI4/sysroot/usr/include \
              /opt/ML/RPI4/sysroot/usr/local/include/opencv4
LIBS += -L/opt/ML/RPI4/sysroot/usr/lib/arm-linux-gnueabihf -ledgetpu \
         -lopencv_core \
         -lopencv_features2d \
         -lopencv_flann \
         -lopencv_highgui \
         -lopencv_imgcodecs \
         -lopencv_imgproc \
         -lopencv_ml \
         -lopencv_objdetect \
         -lopencv_photo \
         -lopencv_shape \
         -lopencv_stitching \
         -lopencv_superres \
         -lopencv_video \
         -lopencv_videoio \
         -lopencv_videostab \
         -lopencv_optflow \
         -lopencv_ximgproc \
         -lopencv_xfeatures2d

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
