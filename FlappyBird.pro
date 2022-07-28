QT       += core gui multimedia \
    widgets

SOURCES += \
    src/entity/bird.cpp \
    src/entity/pillar.cpp \
    src/game.cpp \
    src/scene/gameoverscene.cpp \
    src/scene/gamescene.cpp \
    src/main.cpp \
    src/scene/titlescene.cpp \
    src/view.cpp

HEADERS += \
    src/entity/bird.h \
    src/entity/pillar.h \
    src/game.h \
    src/scene/gameoverscene.h \
    src/scene/gamescene.h \
    src/scene/titlescene.h \
    src/view.h

RESOURCES += \
    resource.qrc
