#include"animationmanager.h"
AnimationManager::AnimationManager(QObject* parent):QObject(parent)
,m_frame(0),
m_mode(relaxMode){

}


AnimationManager::AnimationManager(QVector<QString> filepath,QVector<int> framesnum,QObject* parent):QObject(parent),
    m_frame(0),
    m_mode(relaxMode),
    m_framevector(framesnum),
    m_filepath(filepath){
    m_currentframe=QImage(m_filepath[m_mode].arg(m_frame));
}
AnimationManager::~AnimationManager(){

}
void AnimationManager::set_frame_vector(QVector<int> framecevtor){
    m_framevector=framecevtor;
}

void AnimationManager::set_filepath(QVector<QString> filepath){
    m_filepath=filepath;
}

void AnimationManager::advance(){
    m_frame=(m_frame+1)%m_framevector[m_mode];
    m_currentframe=QImage(m_filepath[m_mode].arg(m_frame));
    if(m_mode==attackMode && m_frame==m_framevector[attackMode]-1){
        emit attackFinish();
        m_mode=relaxMode;
    }
}

void AnimationManager::changeMode(animeMode mode){
    if(m_mode==mode||m_mode==attackMode)
        return;

    m_frame=0;
    m_mode=mode;
}

QImage& AnimationManager::get_currentframe(){
    return m_currentframe;
}

animeMode AnimationManager::get_mode(){
    return m_mode;
}
