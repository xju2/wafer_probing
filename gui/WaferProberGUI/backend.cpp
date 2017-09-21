#include "backend.h"
#include <QDebug>
#include "Helper.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
    // device name is hardcoded!
    m_ctrl = new MotionController("/dev/ttyACM0");
}

void BackEnd::connectDevice()
{
    m_ctrl->connect();
    emit deviceConnected();
}

bool BackEnd::runMA(){
    int x_axis = WaferProb::axis_number("X");
    int y_axis = WaferProb::axis_number("Y");

    m_ctrl->mv_abs(x_axis, m_abs_x);
    m_ctrl->mv_abs(y_axis, m_abs_y);
    emit maPerformed();
    return m_runMA;
}

bool BackEnd::runMR(){
    int x_axis = WaferProb::axis_number("X");
    int y_axis = WaferProb::axis_number("Y");

    m_ctrl->mv_rel(x_axis, m_abs_x);
    m_ctrl->mv_rel(y_axis, m_abs_y);
    emit mrPerformed();
    return m_runMR;
}
