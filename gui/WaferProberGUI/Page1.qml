import QtQuick 2.7

Page1Form {

    property var connectRes: -999
    connect.onClicked: {
        connectRes = backend.to_connect
        if(connectRes == 0){
            output.append("connection is established.")
        } else if(connectRes == -1){
            output.append("XY station failed connection.")
        } else{
            output.append("Z station failed connection. check Ethernet.")
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
            txt_zcontact.color = "red"
            btn_mc_toggle.text = "mv separate"
        } else if(isContact  && backend.zContact){
            isContact = false
            backend.zContact = false
            txt_zcontact.text = "in separate"
            txt_zcontact.color = "green"
            btn_mc_toggle.text = "mv contact"
        }
        // update location
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }

    btn_set_sep.onClicked: {
        backend.zSep = txt_sep_input.text.toString()
        output.append("Separation is set to"+txt_sep_input.text)
    }
    property var valRough: 0
    sb_rough.onValueChanged: {
        if(sb_rough.value > valRough){
            backend.rel_z =  0.600
        } else {
            backend.rel_z = -0.600
        }
        valRough = sb_rough.value
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }

    property var  valPrecision: 0
    sb_precision.onValueChanged: {
        if(sb_precision.value > valPrecision){
            backend.rel_z = 0.060
        } else{
            backend.rel_z = -0.060
        }
        valPrecision = sb_precision.value
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }

    btn_go_top.onClicked: {
        backend.zTop
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }
    btn_go_bottom.onClicked: {
        backend.zBottom
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }
    btn_go_mid.onClicked: {
        backend.zMid
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
    }

}
