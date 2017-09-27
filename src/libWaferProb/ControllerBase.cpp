#include "ControllerBase.h"
#include <stdio.h>

#include <sstream>

ControllerBase::ControllerBase()
{
    status = -1;
    m_is_connected = false;
}

ControllerBase::~ControllerBase(){
}
