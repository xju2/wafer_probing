#include "backend.h"
#include <QDebug>
#include "Helper.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
    // device name is hardcoded!
    m_ctrl = new MotionController("/dev/ttyACM0");

    m_current_x = m_current_y = m_current_z = -1.0;
    unit = 1000;
    m_z_sep = 700; // micrometer
    m_z_isContact = false;
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

bool BackEnd::dismiss(){
    if(m_z_isContact){
        m_ctrl->mv_rel(2, -1*m_z_sep);
    }
    m_ctrl->disconnect();
    return true;
}

void BackEnd::setAbs_x(float x){
    if(x != m_current_x && is_valid_x(x)){
        m_abs_x = x;
        m_ctrl->mv_abs(0, m_abs_x*unit);
        emit posXChanged();

        get_pos_xy();
    }
}

void BackEnd::setAbs_y(float y){
    if(y != m_current_y && is_valid_y(y)){
        m_abs_y = y;
        m_ctrl->mv_abs(1, m_abs_y*unit);
        emit posYChanged();
        get_pos_xy();
    }
}

void BackEnd::setRel_x(float x){
    if(is_valid_x(x+m_current_x)){
        m_rel_x = x;
        m_ctrl->mv_rel(0, m_rel_x*unit);
        emit posXChanged();
        get_pos_xy();
    }
}

void BackEnd::setRel_y(float y){
    if(is_valid_y(y+m_current_y)){
        m_rel_y = y;
        m_ctrl->mv_rel(1, m_rel_y*unit);
        emit posYChanged();
        get_pos_xy();
    }
}

void BackEnd::setRel_z(float z){
    // z is in unit of mm.
    if(is_valid_z(z + m_current_z)){
        m_rel_z = z;
        m_ctrl->mv_rel(2, m_rel_z);
        m_ctrl->get_pos_z();
        m_current_z = m_ctrl->m_position[2];
    }
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
    m_ctrl->get_pos_xy();
    m_current_x = m_ctrl->m_position[0];
    m_current_y = m_ctrl->m_position[1];
}

void BackEnd::setSpeedX(float speed_x){
    m_speed_x = speed_x;
    m_ctrl->set_speed(0, m_speed_x*unit);
    emit speedXSet();
}

void BackEnd::setSpeedY(float speed_y){
    m_speed_y = speed_y;
    m_ctrl->set_speed(1, m_speed_y*unit);
    emit speedYSet();
}

void BackEnd::setSpeedZ(float speed_z){
    m_speed_z = speed_z;
    m_ctrl->set_speed(2, m_speed_z*unit);
    emit speedZSet();
}

bool BackEnd::zTop(){
    m_ctrl->mv_abs(2, 14.189);
    m_ctrl->get_pos_z();
    m_current_z = m_ctrl->m_position[2];
    return true;
}

bool BackEnd::zBottom(){
    m_ctrl->mv_abs(2, 0.);
    m_ctrl->get_pos_z();
    m_current_z = m_ctrl->m_position[2];
    return true;
}

bool BackEnd::zMid(){
    m_ctrl->mv_abs(2, 7.0945);
    m_ctrl->get_pos_z();
    m_current_z = m_ctrl->m_position[2];
    return true;
}
