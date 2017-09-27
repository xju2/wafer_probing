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
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()

        tx_abs_x.text = txt_x_pos.text
        tx_abs_y.text = txt_y_pos.text

    }

    dismiss.onClicked:{
        if(backend.dismiss){
            output.append("connection is dismissed")
        }
    }

    // move x-y stations
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

    // z-axis, move contact and separate.
    property var isContact: false
    btn_mc_toggle.onClicked: {

        if(! isContact && ! backend.zContact) {
            isContact = true
            backend.zContact = true
            txt_zcontact.text = "in contact"
            btn_mc_toggle.text = "mv separate"
        } else if(isContact  && backend.zContact){
            isContact = false
            backend.zContact = false
            txt_zcontact.text = "in separate"
            btn_mc_toggle.text = "mv contact"
        }
        // update location
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }

    btn_set_sep.onClicked: {
        backend.zSep = txt_sep_input.text.toString()
        output.append("Separation is set to"+txt_sep_input.text)
    }

    sb_rough.down.onPressedChanged: {
        backend.rel_z =  -0.600
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }
    sb_rough.up.onPressedChanged: {
        backend.rel_z = 0.600
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }

    sb_precision.down.onPressedChanged: {
        backend.rel_z = -0.060
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }
    sb_precision.up.onPressedChanged: {
        backend.rel_z = 0.060
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }

}
