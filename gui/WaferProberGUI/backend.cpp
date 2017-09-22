#include "backend.h"
#include <QDebug>
#include "Helper.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
    // device name is hardcoded!
    m_ctrl = new MotionController("/dev/ttyACM0");

    m_current_x = m_current_y = m_current_z = -1.0;
}

int BackEnd::connectDevice()
{
    int status = m_ctrl->connect();
    if(status == 0){
        get_pos_xy();
    }
    emit deviceConnected();
    return status;
}

void BackEnd::runMA(int axis, float value)
{
    if((axis == 0 && is_valid_x(value)) ||
       (axis == 1 && is_valid_y(value)) ){
        m_ctrl->mv_abs(axis, value);
    }

    // update current position
    get_pos_xy();

    if( (axis == 0 && m_current_x != m_abs_x) ||
        (axis == 1 && m_current_y != m_abs_y) ){
        printf("ERROR in moving to absolute location");
    }
}

void BackEnd::setAbs_x(float x){
    if(x != m_current_x){
        m_abs_x = x;
        runMA(0, m_abs_x);
        emit posXChanged();
    }
}

void BackEnd::setAbs_y(float y){
    if(y != m_current_y){
        m_abs_y = y;
        runMA(1, m_abs_y);
        emit posYChanged();
    }

}

void BackEnd::runMR(int axis, float value)
{
    if ( (axis == 0 && is_valid_x(value+m_current_x)) ||
         (axis == 1 && is_valid_y(value+m_current_y)) ){
        m_ctrl->mv_rel(axis, value);
    }
    // update current position
    get_pos_xy();
}

void BackEnd::setRel_x(float x){
    m_rel_x = x;
    runMR(0, m_rel_x);
    emit posXChanged();
}

void BackEnd::setRel_y(float y){
    m_rel_y = y;
    runMR(1, m_rel_y);
    emit posYChanged();
}

bool BackEnd::runSH(){
    m_ctrl->set_home();
    // update current position
    get_pos_xy();
    emit shPerformed();
    return m_runSH;
}

bool BackEnd::runSM(){
    m_ctrl->set_center();
    // update current position
    get_pos_xy();

    emit smPerformed();
    return m_runSM;
}

void BackEnd::get_pos_xy(){
    m_ctrl->get_position();
    m_current_x = m_ctrl->m_position[0];
    m_current_y = m_ctrl->m_position[1];
}

void BackEnd::setSpeedX(float speed_x){
    m_speed_x = speed_x;
    set_speed(0, m_speed_x);
    emit speedXSet();
}

void BackEnd::setSpeedY(float speed_y){
    m_speed_y = speed_y;
    set_speed(1, m_speed_y);
    emit speedYSet();
}

void BackEnd::setSpeedZ(float speed_z){
    m_speed_z = speed_z;
    set_speed(2, m_speed_z);
    emit speedZSet();
}

void BackEnd::set_speed(int axis, float value){
    m_ctrl->set_speed(axis, value);
}
