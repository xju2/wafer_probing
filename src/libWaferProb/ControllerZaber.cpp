#include <stdio.h>

#include <string.h>
#include <vector>
#include <stdlib.h>

#include "ControllerZaber.h"
#include "Helper.h"


using namespace std;

ControllerZaber::ControllerZaber(const char* device_name):
    ControllerBase(),
    dn(device_name)
{
    port = -1;
    m_position[0] = m_position[1] = DEFAULT_ZABER_POS;
}

int ControllerZaber::connect(){
    if(m_is_connected) return 0;

    printf("%s:connecting to device %s\n", __FUNCTION__, dn.c_str());

    if( check(za_connect(&port, dn.c_str())) ) {
        printf("%s connected\n", dn.c_str());
        status = 0;
        m_is_connected = true;
    } else {
        printf("%s not connected\n", dn.c_str());
        status = 1;
    }
    return status;
}

ControllerZaber::~ControllerZaber(){
    disconnect();
}

int ControllerZaber::disconnect(){
    if (port > 0){
        za_disconnect(port);
        port = -1;
    }
    return 0;
}

int ControllerZaber::write(const string& cmd)
{
    if (port < 0){
        printf("%s is not open!\n", dn.c_str());
        return -1;
    }
    za_send(port, cmd.c_str());
    char reply[256] = {0};
    za_receive(port, reply, sizeof(reply));
    printf("%s -> %s\n", cmd.c_str(), reply);

    poll_until_idle();
    return 0;
}

string* ControllerZaber::write_with_reply(const string& cmd)
{
    if (port < 0){
        printf("%s is not open!", dn.c_str());
        return NULL;
    }
    char reply[256] = {0};
    za_send(port, cmd.c_str());
    za_receive(port, reply, sizeof(reply));
    printf("%s -> %s\n", cmd.c_str(), reply);
    string* result = new string(reply);

    poll_until_idle();
    return result;
}

int ControllerZaber::set_speed(int axis, float value)
{
    int steps = convert_mm_to_turns(value);
    char cmd[256];
    int n = sprintf(cmd, "/1 %d set maxspeed %d\n", axis, steps);
    return write(cmd);
}

int ControllerZaber::mv_abs(int axis, float value){
    int steps = convert_mm_to_turns(value);
    char cmd[256];
    int n = sprintf(cmd, "/1 %d move abs %d\n", axis, steps);
    return write(cmd);
}

int ControllerZaber::mv_rel(int axis, float value){
    int steps = convert_mm_to_turns(value);
    char cmd[256];
    int n = sprintf(cmd, "/1 %d move rel %d\n", axis, steps);
    return write(cmd);
}

int ControllerZaber::get_position()
{
    if(port < 0){
        return 1;
    }
    char cmd[256];
    int n = sprintf(cmd, "/1 get pos\n");

    string* rpy = write_with_reply(cmd) ;
    if(rpy == NULL) return 2;

    // analyze the reply.
	struct za_reply decoded_reply;
    za_decode(&decoded_reply, const_cast<char*>(rpy->c_str()));
    //  analyze response data.
    string data(decoded_reply.response_data);
    if(strncmp(decoded_reply.response_data, "BADDATA", 7) == 0){
        m_position[0] = m_position[1] = DEFAULT_ZABER_POS;
    } else {
        vector<string> raw_items;
        WaferProb::tokenizeString(data, ' ', raw_items);
        for(int i = 0; i < (int) raw_items.size(); i++){
            m_position[i] = (int)(convert_turns_to_mm(atof(raw_items.at(i).c_str()))*100) / 100.;
        }
    }
    return 0;
}

int ControllerZaber::set_home(){
    return write("/home\n");
}

int ControllerZaber::set_center(){
    // 1952000/2. = 976000
    return write("/move abs 976000\n");
}

int ControllerZaber::park(){
    int status = write("/tools parking park\n");
    if(status == 0){
        printf("%s is parked\n", dn.c_str());
    }
    return status; 
}

int ControllerZaber::unpark()
{
    int status = write("/tools parking unpark\n");
    if(status == 0){
        printf("%s is unparked\n", dn.c_str());
    }
    return status;
}

int ControllerZaber::stop(){
    int status = write("/stop\n");
    get_position();
    return status;
}


int ControllerZaber::convert_mm_to_turns(float value){
    // turns: 1952000 turns
    // length: 305000 micro-meter 
    return value / 0.15625; 
}

float ControllerZaber::convert_turns_to_mm(float turns){
    return turns * 305. / 1952000.; 
}

void ControllerZaber::poll_until_idle(){
    char reply[256] = { 0 };
	struct za_reply decoded_reply;
    const struct timespec ts = { 0, 100000000 }; /* 100mil nanosec = 100ms */

	/* We use za_decode() to decode this string into more manageable parts,
	 * sorting them into the fields of a za_reply struct, then we test
	 * the device_status field. Possible values for device_status are "IDLE"
	 * and "BUSY". */
     int count = 0;
    for(;;)
    {
        za_send(port, "/\n");
        za_receive(port, reply, sizeof(reply));
		za_decode(&decoded_reply, reply);

        if(strncmp(decoded_reply.device_status, "BUSY", 4) == 0)
		{
            nanosleep(&ts, NULL); /* If we're busy, wait then try again */
		}
        else
		{
			break;
		}
        if (count > 1000){break;} else{count ++;}
    }
}

const char* ControllerZaber::device_name(){
    return dn.c_str();
}
