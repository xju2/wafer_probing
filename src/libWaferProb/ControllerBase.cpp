#include "ControllerBase.h"
#include <stdio.h>

#include <sstream>

ControllerBase::ControllerBase()
{
    status = -1;
}

ControllerBase::~ControllerBase(){
}

int ControllerBase::get_status(){
    return status;
}
