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
    rotation: 0

    Button {
        id: connect
        x: 124
        y: 93
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
        x: 32
        y: 181
        width: 114
        height: 18
        text: qsTr("move absolute:")
    }

    Button {
        id: btn_mv_rel
        x: 32
        y: 211
        width: 114
        height: 18
        text: qsTr("move relative:")
    }

    Label {
        id: label
        x: 33
        y: 241
        width: 113
        height: 16
        text: qsTr("current location:")
    }

    Text {
        id: txt_x_pos
        x: 157
        y: 241
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
        x: 234
        y: 241
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
        x: 200
        y: 164
        width: 20
        height: 16
        text: qsTr("X [mm]")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label2
        x: 250
        y: 164
        width: 18
        height: 16
        text: qsTr("Y [mm]")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_abs_x
        x: 157
        y: 181
        width: 51
        height: 20
        text: "0."
        selectionColor: "#008033"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_abs_y
        x: 234
        y: 181
        width: 51
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_rel_x
        x: 157
        y: 211
        width: 51
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_rel_y
        x: 234
        y: 211
        width: 51
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label6
        x: 353
        y: 164
        width: 18
        height: 16
        text: qsTr("Z [mm]")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Button {
        id: btn_mc_toggle
        x: 316
        y: 267
        width: 114
        height: 18
        text: qsTr("move contact")
    }

    Text {
        id: txt_zcontact
        x: 436
        y: 267
        width: 114
        height: 18
        text: qsTr("in separate")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Button {
        id: btn_set_sep
        x: 316
        y: 291
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
        x: 173
        y: 267
        width: 112
        height: 18
        text: qsTr("Go Home [x-y]")
    }

    Button {
        id: btn_sm
        x: 173
        y: 291
        width: 112
        height: 18
        text: qsTr("Set Middle")
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
        x: 285
        y: 93
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
        x: 337
        y: 241
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
        x: 436
        y: 291
        width: 71
        height: 18
        text: qsTr("700")
        wrapMode: Text.NoWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        id: txt_sep_label
        x: 507
        y: 291
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
        x: 308
        y: 185
        width: 140
        height: 21
        from: -10
        spacing: 0
        to: 10
        value: 1
    }

    Label {
        id: label9
        x: 448
        y: 184
        text: qsTr("600 micrometer/step")
    }

    Label {
        id: label10
        x: 454
        y: 214
        text: qsTr("60 micrometer/step")
    }

    SpinBox {
        id: sb_precision
        x: 308
        y: 214
        width: 140
        height: 21
        from: -100
        to: 100
    }
}
