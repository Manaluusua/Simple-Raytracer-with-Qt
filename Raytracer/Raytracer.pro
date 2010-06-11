# -------------------------------------------------
# Project created by QtCreator 2010-01-14T23:17:34
# -------------------------------------------------
QT += opengl
TARGET = Raytracer
TEMPLATE = app
SOURCES += main.cpp \
    plane.cpp \
    ray.cpp \
    material.cpp \
    light.cpp \
    world.cpp \
    object.cpp \
    raytracer.cpp \
    renderwindow.cpp \
    camera.cpp \
    sphere.cpp \
    poissonsdiscgenerator.cpp
HEADERS += plane.h \
    utils.h \
    ray.h \
    geometry.h \
    material.h \
    light.h \
    world.h \
    object.h \
    raytracer.h \
    renderwindow.h \
    camera.h \
    sphere.h \
    poissonsdiscgenerator.h
FORMS += renderwindow.ui
