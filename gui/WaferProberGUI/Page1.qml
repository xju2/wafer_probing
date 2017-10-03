import QtQuick 2.7

Page1Form {

    property var connectRes: -999
    // z-axis, move contact and separate.
    property var isContact: false

    function go_contact(){
        isContact = true
        backend.zContact = true
        txt_zcontact.text = "in contact"
        txt_zcontact.color = "red"
        btn_mc_toggle.text = "mv separate"
    }

    function go_separate(){
        isContact = false
        backend.zContact = false
        txt_zcontact.text = "in separate"
        txt_zcontact.color = "green"
        btn_mc_toggle.text = "mv contact"
    }

    function grey_xy_pos(){
        txt_x_pos.color = "grey"
        txt_y_pos.color = "grey"
    }

    function fill_xy_pos(){
        txt_x_pos.text = Number(backend.getPosX).toLocaleString()
        txt_y_pos.text = Number(backend.getPosY).toLocaleString()
        txt_x_pos.color = "black"
        txt_y_pos.color = "black"
    }

    function fill_z_pos(){
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()
        txt_z_pos.color = "black"
    }

    connect.onClicked: {
        connectRes = backend.to_connect
        if(connectRes == 0){
            output.append("connection is established.")
        } else if(connectRes == -1){
            output.append("XY station failed connection.")
        } else{
            output.append("Z station failed connection. check Ethernet.")
        }
        // get current position
        fill_xy_pos()
        txt_z_pos.text = Number(backend.getPosZ).toLocaleString()

        tx_abs_x.text = txt_x_pos.text
        tx_abs_y.text = txt_y_pos.text
        // set speed in xyz to default value
        backend.speedX = txt_speed_x.text.toString()
        backend.speedY = txt_speed_y.text.toString()
        backend.speedZ = txt_speed_z.text.toString()
    }

    dismiss.onClicked:{
        if(isContact){
            go_separate()
        }

        if(backend.dismiss){
            output.append("connection is dismissed")
        }
    }

    // move x-y stations
    btn_mv_abs.onClicked: {
        if(isContact){
            go_separate()
        }
        grey_xy_pos()
        backend.abs_x = tx_abs_x.text.toString()
        backend.abs_y = tx_abs_y.text.toString()
        fill_xy_pos()
    }

    btn_mv_rel.onClicked: {
        if(isContact){
            go_separate()
        }

        grey_xy_pos()
        backend.rel_x = tx_rel_x.text.toString()
        backend.rel_y = tx_rel_y.text.toString()
        fill_xy_pos()
    }

    btn_sh.onClicked: {
        if(isContact){
            go_separate()
        }

        grey_xy_pos()
        backend.runSH
        fill_xy_pos()
    }

    btn_sm.onClicked: {
        if(isContact){
            go_separate()
        }

        grey_xy_pos()
        backend.runSM
        fill_xy_pos()
    }

    // setup speed..
    btn_speed_x.onClicked: {
        backend.speedX = txt_speed_x.text.toString()
        output.append("speed in X is set to:" + txt_speed_x.text.toString())
    }

    btn_speed_y.onClicked: {
        backend.speedY = txt_speed_y.text.toString()
        output.append("speed in Y is set to:" + txt_speed_y.text.toString())
    }

    btn_speed_z.onClicked: {
        backend.speedZ = txt_speed_z.text.toString()
        output.append("speed in Z is set to:" + txt_speed_z.text.toString())
    }


    // move contact or separate
    btn_mc_toggle.onClicked: {
        if(! isContact && ! backend.zContact) {
            go_contact()
        } else if(isContact  && backend.zContact){
            go_separate()
        }
        // update location
        fill_z_pos()
    }

    btn_set_sep.onClicked: {
        backend.zSep = txt_sep_input.text.toString()
        output.append("Separation is set to"+txt_sep_input.text)
    }
    property var valRough: 0
    sb_rough.onValueChanged: {
        if(sb_rough.value > valRough){
            backend.rel_z =  0.500
        } else {
            backend.rel_z = -0.500
        }
        valRough = sb_rough.value
        fill_z_pos()
    }

    property var  valPrecision: 0
    sb_precision.onValueChanged: {
        if(sb_precision.value > valPrecision){
            backend.rel_z = 0.010
        } else{
            backend.rel_z = -0.010
        }
        valPrecision = sb_precision.value
        fill_z_pos()
    }

    // move Z-axis to the top.
    btn_go_top.onClicked: {
        if(!isContact){
            txt_z_pos.color = "grey"
            backend.zTop
            fill_z_pos()
            output.append("at the Top of Z-axis.")
        }
    }
    btn_go_bottom.onClicked: {
        txt_z_pos.color = "grey"
        backend.zBottom
        fill_z_pos()
        output.append("at the Bottom of Z-axis.")
    }
    btn_go_mid.onClicked: {
        txt_z_pos.color = "grey"
        backend.zMid
        fill_z_pos()
        output.append("at the Middle of Z-axis.")
    }

    btn_scan_x.onClicked: {
        output.append("scanning X")
        if(isContact)
            go_separate()

        txt_x_pos.color = "grey"
        backend.scanX = 1
        fill_xy_pos()
    }

    btn_scan_y.onClicked: {
        output.append("scanning Y")
        if(isContact)
            go_separate()

        txt_y_pos.color = "grey"
        backend.scanY = 1
        fill_xy_pos()
    }
    btn_stop.onClicked: {
        // output.append("stoping all motions")
        backend.stop
        backend.stop
        backend.getPosXY
        fill_xy_pos()
        fill_z_pos()
    }

    btn_test_x.onClicked: {
        backend.testXY = 0
        fill_xy_pos()
    }
    btn_test_y.onClicked: {
        backend.testXY = 1
        fill_xy_pos()
    }

    btn_calibrate.onClicked: {
        backend.calibrateZ
    }
}
