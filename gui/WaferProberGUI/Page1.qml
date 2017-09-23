import QtQuick 2.7

Page1Form {

    connect.onClicked: {
        if(backend.to_connect == 0){
            output.append("connection is established.")
        } else{
            output.append("connection failed.")
        }
        txt_x_pos.text = backend.getPosX
        txt_y_pos.text = backend.getPosY

        tx_abs_x.text = txt_x_pos.text
        tx_abs_y.text = txt_y_pos.text
    }

    // attached signal handler

    btn_mv_abs.onClicked: {

        backend.abs_x = tx_abs_x.text.toString()
        backend.abs_y = tx_abs_y.text.toString()

        txt_x_pos.text = backend.getPosX
        txt_y_pos.text = backend.getPosY

    }

    btn_mv_rel.onClicked: {
        backend.rel_x = tx_rel_x.text.toString()
        backend.rel_y = tx_rel_y.text.toString()

        txt_x_pos.text = backend.getPosX
        txt_y_pos.text = backend.getPosY
    }

    btn_sh.onClicked: {
        backend.runSH
        txt_x_pos.text = backend.getPosX
        txt_y_pos.text = backend.getPosY
    }

    btn_sm.onClicked: {
        backend.runSM
        txt_x_pos.text = backend.getPosX
        txt_y_pos.text = backend.getPosY
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
