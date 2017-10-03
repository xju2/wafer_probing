#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QQmlEngine>

#include "MotionController.h"
#include <string>
#include <vector>

#define X_MAX 305  // unit of mm. range is: [0, 305] mm
#define Y_MAX 305  // unit of mm. range is: [0, 305] mm
#define Z_MAX 9    // unit of mm. range is: [0, 9] mm

#include "backendattachedtype.h"

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int to_connect READ connectDevice NOTIFY deviceConnected)
    Q_PROPERTY(bool dismiss READ dismiss)
    Q_PROPERTY(float rel_x READ rel_x WRITE setRel_x NOTIFY posXChanged)
    Q_PROPERTY(float rel_y READ rel_y WRITE setRel_y NOTIFY posYChanged)
    Q_PROPERTY(float rel_z READ rel_z WRITE setRel_z)
    Q_PROPERTY(float abs_x READ abs_x WRITE setAbs_x NOTIFY posXChanged)
    Q_PROPERTY(float abs_y READ abs_y WRITE setAbs_y NOTIFY posYChanged)

    // commands for movements.
    Q_PROPERTY(bool runSH READ runSH NOTIFY shPerformed)
    Q_PROPERTY(bool runSM READ runSM NOTIFY smPerformed)

    // retrieve positions
    Q_PROPERTY(float getPosX READ getPosX NOTIFY posXGot)
    Q_PROPERTY(float getPosY READ getPosY NOTIFY posYGot)
    Q_PROPERTY(float getPosZ READ getPosZ NOTIFY posZGot)
    Q_PROPERTY(bool getPosXY READ getPosXY)

    // set speed
    Q_PROPERTY(float speedX READ getSpeedX WRITE setSpeedX NOTIFY speedXSet)
    Q_PROPERTY(float speedY READ getSpeedY WRITE setSpeedY NOTIFY speedYSet)
    Q_PROPERTY(float speedZ READ getSpeedZ WRITE setSpeedZ NOTIFY speedZSet)

    // z-axis.
    Q_PROPERTY(bool zContact READ zContact WRITE setZContact)
    Q_PROPERTY(float zSep READ zSep WRITE setZSep)
    Q_PROPERTY(bool zTop READ zTop)
    Q_PROPERTY(bool zBottom READ zBottom)
    Q_PROPERTY(bool zMid READ zMid)

    // scan X and Y
    Q_PROPERTY(int scanX READ readScanX WRITE scanX)
    Q_PROPERTY(int scanY READ readScanX WRITE scanY)

    // STOP
    Q_PROPERTY(bool stop READ stop)

    // Test X or Y
    Q_PROPERTY(int testXY WRITE setTestXY)

    // calibrate Z-axis
    Q_PROPERTY(bool calibrateZ READ calibrateZ)

public:
    static BackendAttachedType *qmlAttachedProperties(QObject *object)
    {
        return new BackendAttachedType(object);
    }

public:
    explicit BackEnd(QObject *parent = nullptr);

    int connectDevice();
    bool dismiss();

    // getter
    float rel_x(){ return m_rel_x; }
    float rel_y(){ return m_rel_y; }
    float rel_z(){ return m_rel_z; }

    float abs_x(){ return m_abs_x; }
    float abs_y(){ return m_abs_y; }

    // setter
    void setRel_x(float x);
    void setRel_y(float y);
    void setRel_z(float z);
    void setAbs_x(float x);
    void setAbs_y(float y);

    bool runSH();
    bool runSM();
    bool getPosXY(){ get_pos_xy(); return true;}
    float getPosX(){ return m_current_x; emit posXGot(); }
    float getPosY(){ return m_current_y; emit posYGot(); }
    float getPosZ(){
        m_ctrl->get_pos_z();
        m_current_z = m_ctrl->m_position[2];
        return m_current_z;
        emit posZGot();
    }

    void setSpeedX(float speed_x);
    void setSpeedY(float speed_y);
    void setSpeedZ(float speed_z);

    float getSpeedX() { return m_speed_x; }
    float getSpeedY() { return m_speed_y; }
    float getSpeedZ() { return m_speed_z; }

    // read
    bool zContact(){ return m_z_isContact; }
    void setZContact(bool is_contact) {
        if(is_contact && ! m_z_isContact){
            // move to contact
            m_ctrl->mv_rel(2, m_z_sep);
            m_z_isContact = true;
        } else if (!is_contact && m_z_isContact){
            // move to separate
            m_ctrl->mv_rel(2, -1*m_z_sep);
            m_z_isContact = false;
        } else {
            // don't move
        }
    }

    float zSep(){return m_z_sep;}
    void setZSep(float sep){
        m_z_sep = sep;
    }

    // move to top or bottom in z-axis
    bool zTop();
    bool zBottom();
    bool zMid();

    // scan X and Y direction
    void scanX(int times);
    void scanY(int times);
    int readScanX(){ return m_scan_x; }
    int readScanY(){ return m_scan_y; }

    // stop motions
    bool stop(){
        m_ctrl->stop();
        return true;
    }

    void setTestXY(float axis);

    bool calibrateZ(){
        m_ctrl->calibrate_Z();
        return true;
    }

signals:
    void deviceConnected();

    void posXChanged();
    void posYChanged();

    void shPerformed(); // "set home" performed
    void smPerformed(); // "set middle"

    void posXGot(); // X postion returned
    void posYGot(); // Y postion returned
    void posZGot(); // Z postion returned

    void speedXSet();
    void speedYSet();
    void speedZSet();

public slots:

private:
    MotionController* m_ctrl;

    float m_current_x;
    float m_current_y;
    float m_current_z;

    float m_rel_x;
    float m_rel_y;
    float m_rel_z;

    float m_abs_x;
    float m_abs_y;

    float m_z_sep; // distance between needle and chip when in status of separation
    bool m_z_isContact; // tell the program if needle and chip are in contact.

    // variables used for actions. their values are meaningless.
    bool m_runSH;
    bool m_runSM;

    bool m_getPosX; // get position in X-axis
    bool m_getPosY; // Y
    bool m_getPosZ; // Z

    float m_speed_x;
    float m_speed_y;
    float m_speed_z;

    int unit;

    int m_scan_x;
    int m_scan_y;

private: // private functions
    bool is_valid_x(float x){
        return x >= 0 && x <= X_MAX;
    }
    bool is_valid_y(float y){
        return y >= 0 && y <= Y_MAX;
    }
    bool is_valid_z(float z){
        return z >=0 && z <= Z_MAX;
    }
    void get_pos_xy();
};

QML_DECLARE_TYPEINFO(BackEnd, QML_HAS_ATTACHED_PROPERTIES)
#endif // BACKEND_H
