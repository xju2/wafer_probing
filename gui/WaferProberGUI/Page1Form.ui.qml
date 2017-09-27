import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    property alias label3: label3
    property alias label4: label4
    property alias label5: label5
    property alias connect: connect
    property alias btn_mv_abs: btn_mv_abs
    property alias btn_mv_rel: btn_mv_rel
    property alias tx_abs_x: tx_abs_x
    property alias tx_abs_y: tx_abs_y
    property alias tx_rel_x: tx_rel_x
    property alias tx_rel_y: tx_rel_y
    property alias btn_sm: btn_sm
    property alias btn_sh: btn_sh
    property alias txt_x_pos: txt_x_pos
    property alias txt_y_pos: txt_y_pos
    property alias output: output
    property alias btn_speed_x: btn_speed_x
    property alias btn_speed_y: btn_speed_y
    property alias btn_speed_z: btn_speed_z
    property alias txt_speed_x: txt_speed_x
    property alias txt_speed_y: txt_speed_y
    property alias txt_speed_z: txt_speed_z
    property alias btn_mc_toggle: btn_mc_toggle
    property alias dismiss: dismiss
    property alias txt_zcontact: txt_zcontact
    property alias txt_z_pos: txt_z_pos
    property alias btn_set_sep: btn_set_sep
    property alias txt_sep_input: txt_sep_input
    property alias sb_precision: sb_precision
    property alias sb_rough: sb_rough
    property alias btn_go_top: btn_go_top
    property alias btn_go_bottom: btn_go_bottom
    property alias btn_go_mid: btn_go_mid
    rotation: 0

    Button {
        id: connect
        x: 147
        y: 42
        text: qsTr("Connect")
        visible: true
        autoRepeat: false
        autoExclusive: false
        checked: false
        enabled: true
        spacing: 0
        highlighted: false
        font.family: "Tahoma"
        checkable: false
    }

    Label {
        id: label3
        x: 563
        y: 398
        text: qsTr("mm/s")
    }

    Label {
        id: label4
        x: 563
        y: 418
        text: qsTr("mm/s")
    }

    Label {
        id: label5
        x: 563
        y: 438
        text: qsTr("mm/s")
    }

    TextInput {
        id: txt_speed_x
        x: 506
        y: 398
        width: 51
        height: 20
        color: "#25a341"
        text: qsTr("5")
        horizontalAlignment: Text.AlignHCenter
        transformOrigin: Item.Center
        font.pixelSize: 12
    }

    TextInput {
        id: txt_speed_y
        x: 506
        y: 418
        width: 51
        height: 20
        text: qsTr("5")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    TextInput {
        id: txt_speed_z
        x: 506
        y: 438
        width: 51
        height: 20
        text: qsTr("5")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    Button {
        id: btn_speed_x
        x: 430
        y: 397
        width: 59
        height: 18
        text: qsTr("X:")
        font.pointSize: 9
    }

    Button {
        id: btn_speed_y
        x: 430
        y: 417
        width: 59
        height: 18
        text: qsTr("Y:")
    }

    Button {
        id: btn_speed_z
        x: 430
        y: 437
        width: 59
        height: 18
        text: qsTr("Z:")
    }

    Button {
        id: btn_mv_abs
        x: 55
        y: 130
        width: 114
        height: 18
        text: qsTr("mv absolute:")
    }

    Button {
        id: btn_mv_rel
        x: 55
        y: 160
        width: 114
        height: 18
        text: qsTr("mv relative:")
    }

    Label {
        id: label
        x: 56
        y: 190
        width: 113
        height: 18
        text: qsTr("current location:")
    }

    Text {
        id: txt_x_pos
        x: 180
        y: 190
        width: 51
        height: 20
        text: qsTr("0")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        textFormat: Text.PlainText
        font.pixelSize: 12
    }

    Text {
        id: txt_y_pos
        x: 257
        y: 190
        width: 51
        height: 20
        text: qsTr("0")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        textFormat: Text.PlainText
        font.pixelSize: 12
    }

    Label {
        id: label1
        x: 180
        y: 113
        width: 51
        height: 18
        text: qsTr("X [mm]")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label2
        x: 257
        y: 113
        width: 51
        height: 18
        text: qsTr("Y [mm]")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_abs_x
        x: 180
        y: 130
        width: 51
        height: 20
        text: "0."
        selectionColor: "#008033"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_abs_y
        x: 257
        y: 130
        width: 51
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_rel_x
        x: 180
        y: 160
        width: 51
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_rel_y
        x: 257
        y: 160
        width: 51
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label6
        x: 376
        y: 113
        width: 18
        height: 16
        text: qsTr("Z [mm]")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Button {
        id: btn_mc_toggle
        x: 339
        y: 216
        width: 114
        height: 18
        text: qsTr("mv contact")
    }

    Text {
        id: txt_zcontact
        x: 459
        y: 216
        width: 114
        height: 29
        text: qsTr("in separate")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Button {
        id: btn_set_sep
        x: 339
        y: 240
        width: 114
        height: 18
        text: qsTr("set separate")
    }

    Label {
        id: label7
        x: 23
        y: 8
        text: qsTr("")
    }

    Button {
        id: btn_sh
        x: 196
        y: 216
        width: 112
        height: 18
        text: qsTr("go home [x-y]")
    }

    Button {
        id: btn_sm
        x: 196
        y: 240
        width: 112
        height: 18
        text: qsTr("set middle")
    }

    Flickable {
        id: flickable
        x: 23
        y: 388
        width: 395
        height: 75
        flickableDirection: Flickable.VerticalFlick

        TextArea.flickable: TextArea {
            id: output
            x: 0
            y: 0
            width: 393
            height: 72
            wrapMode: TextArea.Wrap
            text: "Program started..."
            opacity: 0.8
            color: "steelblue"
        }

        ScrollBar.vertical: ScrollBar {
            id: sbText
            policy: ScrollBar.AlwaysOn
        }
    }

    Button {
        id: dismiss
        x: 308
        y: 42
        text: qsTr("Disconnect")
        spacing: 0
        autoExclusive: false
        visible: true
        autoRepeat: false
        enabled: true
        font.family: "Tahoma"
        checkable: false
        highlighted: false
        checked: false
    }

    Text {
        id: txt_z_pos
        x: 360
        y: 190
        width: 51
        height: 20
        text: qsTr("0")
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        textFormat: Text.PlainText
    }

    TextInput {
        id: txt_sep_input
        x: 459
        y: 240
        width: 71
        height: 18
        text: qsTr("700")
        wrapMode: Text.NoWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        id: txt_sep_label
        x: 530
        y: 240
        width: 51
        height: 20
        text: qsTr("micrometer")
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        textFormat: Text.PlainText
    }

    Label {
        id: label8
        x: 488
        y: 374
        width: 113
        height: 17
        text: qsTr("Set Speed")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    SpinBox {
        id: sb_rough
        x: 331
        y: 134
        width: 140
        height: 21
        from: -10
        spacing: 0
        to: 10
        value: 1
    }

    Label {
        id: label9
        x: 471
        y: 133
        height: 18
        text: qsTr("600 micrometer/step")
    }

    Label {
        id: label10
        x: 477
        y: 163
        height: 18
        text: qsTr("60 micrometer/step")
    }

    SpinBox {
        id: sb_precision
        x: 331
        y: 163
        width: 140
        height: 21
        from: -100
        to: 100
    }

    Button {
        id: btn_go_top
        x: 339
        y: 264
        width: 114
        height: 18
        text: qsTr("go top")
    }

    Button {
        id: btn_go_bottom
        x: 339
        y: 288
        width: 114
        height: 18
        text: qsTr("go bottom")
    }

    Button {
        id: btn_go_mid
        x: 339
        y: 312
        width: 114
        height: 18
        text: qsTr("go middle")
    }
}
