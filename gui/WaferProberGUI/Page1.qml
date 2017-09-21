import QtQuick 2.7

Page1Form {
    slider.onPressedChanged: {
        console.log("value in slider: " + slider.value)
    }
    connect.onClicked: {
        backend.to_connect
    }

    btn_mv_abs.onClicked: {
        backend.abs_x = tx_abs_x
        backend.abs_y = tx_abs_y
        backend.runMA
    }

    btn_mv_rel.onClicked: {
        backend.rel_x = tx_rel_x.text.toString()
        backend.rel_y = tx_rel_y.text.toString()
        backend.runMR
    }
}
