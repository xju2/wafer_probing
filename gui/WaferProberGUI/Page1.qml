import QtQuick 2.7

import io.qt.examples.backend 1.0

Page1Form {

    connect.onClicked: {
        if(backend.to_connect == 0){
            output.append("connection is established.")
        } else{
            output.append("connection failed.")
        }
    }
    connect.onPressAndHold: {
        console.log("You are press and hoding connect-button!")
    }
    connect.onPressed: {
        console.log("connect-button is pressed")
    }
    connect.onReleased: {
        console.log("thanks for releasing connect-button")
    }
    connect.onDoubleClicked: {
        console.log("connect-button is double-clicked")
    }

    // attached signal handler

    BackEnd.onPosXChanged: {
        console.log("x position changed")
        txt_x_pos.text = backend.getPosX
    }
    BackEnd.onPosYChanged: {
        txt_y_pos.text = backend.getPosY
    }


    btn_mv_abs.onClicked: {

        backend.abs_x = tx_abs_x.text.toString()
        backend.abs_y = tx_abs_y.text.toString()

    }

    btn_mv_rel.onClicked: {
        backend.rel_x = tx_rel_x.text.toString()
        backend.rel_y = tx_rel_y.text.toString()
    }

    btn_sh.onClicked: {
        backend.runSH
    }

    btn_sm.onClicked: {
        backend.runSM
    }

    // setup speed..
    btn_speed_x.onClicked: {
        backend.speedX = txt_speed_x.text.toString()
    }

    btn_speed_y.onClicked: {
        backend.speedY = txt_speed_y.text.toString()
    }

    btn_speed_z.onClicked: {
        backend.speedZ = txt_speed_z.text.toString()
    }

}
