#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include "MotionController.h"
#include <string>
#include <vector>

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool to_connect READ is_connected NOTIFY deviceConnected)
    Q_PROPERTY(float rel_x READ rel_x WRITE setRel_x NOTIFY rel_xChanged)
    Q_PROPERTY(float rel_y READ rel_y WRITE setRel_y NOTIFY rel_yChanged)
    Q_PROPERTY(float abs_x READ abs_x WRITE setAbs_x NOTIFY abs_xChanged)
    Q_PROPERTY(float abs_y READ abs_y WRITE setAbs_y NOTIFY abs_yChanged)

    Q_PROPERTY(bool runMA READ runMA NOTIFY maPerformed)
    Q_PROPERTY(bool runMR READ runMR NOTIFY mrPerformed)

public:
    explicit BackEnd(QObject *parent = nullptr);

    void connectDevice();

    bool is_connected() {
        connectDevice();
        return true;
    }
    void to_connect(bool){
        // input is dummy.
        m_to_connect = true;
        connectDevice();
    }

    // getter
    float rel_x(){ return m_rel_x; }
    float rel_y(){ return m_rel_y; }

    float abs_x(){ return m_abs_x; }
    float abs_y(){ return m_abs_y; }

    // setter
    void setRel_x(float x) {
        m_rel_x = x;
        qInfo("X changed to %.2f", m_rel_x);
        emit rel_xChanged();
    }
    void setRel_y(float y) {
        m_rel_y = y;
        qInfo("Y changed to %.2f", m_rel_y);
        emit rel_yChanged();
    }
    void setAbs_x(float x) { m_abs_x = x; emit abs_xChanged(); }
    void setAbs_y(float y) { m_abs_y = y; emit abs_yChanged(); }

    // runner
    bool runMA();
    bool runMR();

signals:
    void deviceConnected();
    void rel_xChanged();
    void rel_yChanged();
    void abs_xChanged();
    void abs_yChanged();

    void maPerformed();
    void mrPerformed();

public slots:

private:
    MotionController* m_ctrl;

    float m_rel_x;
    float m_rel_y;

    float m_abs_x;
    float m_abs_y;

    float m_z_sep; // distance between needle and chip when in status of separation
    float m_z_isContact; // tell the program if needle and chip are in contact.

    // variables for take actions. Themselves are meaningless.
    bool m_to_connect; // connect device
    bool m_runMR; // make relative movement with rel_x and rel_y
    bool m_runMA; // make absolute movement with abs_x and abs_y

};

#endif // BACKEND_H
