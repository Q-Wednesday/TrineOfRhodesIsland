QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11\
            resources_big

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
    adventurescene.cpp \
    airwall.cpp \
    animationmanager.cpp \
    bullet.cpp \
    character.cpp \
    checkpoint.cpp \
    deadzone.cpp \
    editorscene.cpp \
    editortab.cpp \
    enemy.cpp \
    enemygenerator.cpp \
    entity.cpp \
    exusiai.cpp \
    fireball.cpp \
    flower.cpp \
    fragileland.cpp \
    gamecontroller.cpp \
    gamescene.cpp \
    hidentrap.cpp \
    hintland.cpp \
    land.cpp \
    loadingscene.cpp \
    losescene.cpp \
    main.cpp \
    mainwindow.cpp \
    mapreader.cpp \
    missile.cpp \
    movingland.cpp \
    mushroom.cpp \
    normalland.cpp \
    prop.cpp \
    selectmapscene.cpp \
    setvolumedialog.cpp \
    sheep.cpp \
    silver.cpp \
    spikeland.cpp \
    springland.cpp \
    titlescene.cpp \
    trap.cpp \
    winscene.cpp \
    worm1.cpp \
    worm2.cpp \
    worm3.cpp

HEADERS += \
    adventurescene.h \
    airwall.h \
    allentities.h \
    animationmanager.h \
    bullet.h \
    character.h \
    checkpoint.h \
    constant.h \
    deadzone.h \
    editorscene.h \
    editortab.h \
    enemy.h \
    enemygenerator.h \
    entity.h \
    exusiai.h \
    fireball.h \
    flower.h \
    fragileland.h \
    gamecontroller.h \
    gamescene.h \
    hidentrap.h \
    hintland.h \
    land.h \
    loadingscene.h \
    losescene.h \
    mainwindow.h \
    mapreader.h \
    missile.h \
    movingland.h \
    mushroom.h \
    normalland.h \
    prop.h \
    selectmapscene.h \
    setvolumedialog.h \
    sheep.h \
    silver.h \
    spikeland.h \
    springland.h \
    titlescene.h \
    trap.h \
    winscene.h \
    worm1.h \
    worm2.h \
    worm3.h

FORMS += \
    adventurescene.ui \
    editorscene.ui \
    editortab.ui \
    loadingscene.ui \
    losescene.ui \
    mainwindow.ui \
    selectmapscene.ui \
    setvolumedialog.ui \
    titlescene.ui \
    winscene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc
