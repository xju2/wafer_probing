import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    property alias label3: label3
    property alias label4: label4
    property alias label5: label5
    property alias connect: connect
    property alias button5: button5
    property alias button6: button6
    property alias button7: button7
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
        x: 229
        y: 149
        text: qsTr("mm/s")
    }

    Label {
        id: label4
        x: 229
        y: 169
        text: qsTr("mm/s")
    }

    Label {
        id: label5
        x: 229
        y: 189
        text: qsTr("mm/s")
    }

    TextInput {
        id: txt_speed_x
        x: 172
        y: 149
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
        x: 172
        y: 169
        width: 51
        height: 20
        text: qsTr("5")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    TextInput {
        id: txt_speed_z
        x: 172
        y: 189
        width: 51
        height: 20
        text: qsTr("5")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    Button {
        id: btn_speed_x
        x: 65
        y: 149
        width: 96
        height: 18
        text: qsTr("Set X speed:")
    }

    Button {
        id: btn_speed_y
        x: 65
        y: 169
        width: 96
        height: 18
        text: qsTr("Set Y speed:")
    }

    Button {
        id: btn_speed_z
        x: 65
        y: 189
        width: 96
        height: 18
        text: qsTr("Set Z speed:")
    }

    Button {
        id: btn_mv_abs
        x: 140
        y: 278
        width: 114
        height: 18
        text: qsTr("move absolute:")
    }

    Button {
        id: btn_mv_rel
        x: 140
        y: 308
        width: 114
        height: 18
        text: qsTr("move relative:")
    }

    Label {
        id: label
        x: 141
        y: 338
        width: 113
        height: 16
        text: qsTr("current location:")
    }

    Text {
        id: txt_x_pos
        x: 265
        y: 338
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
        x: 342
        y: 338
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
        x: 280
        y: 261
        width: 20
        height: 16
        text: qsTr("X [mm]")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label2
        x: 358
        y: 261
        width: 18
        height: 16
        text: qsTr("Y [mm]")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_abs_x
        x: 265
        y: 278
        width: 51
        height: 20
        text: "0."
        selectionColor: "#008033"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_abs_y
        x: 342
        y: 278
        width: 51
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_rel_x
        x: 265
        y: 308
        width: 51
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    TextInput {
        id: tx_rel_y
        x: 342
        y: 308
        width: 51
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label6
        x: 442
        y: 261
        width: 18
        height: 16
        text: qsTr("Z")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Button {
        id: button5
        x: 407
        y: 278
        width: 114
        height: 18
        text: qsTr("move contact")
    }

    Button {
        id: button6
        x: 407
        y: 308
        width: 114
        height: 18
        text: qsTr("move separate")
    }

    Button {
        id: button7
        x: 407
        y: 338
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
        x: 364
        y: 149
        width: 96
        height: 18
        text: qsTr("Set Home")
    }

    Button {
        id: btn_sm
        x: 364
        y: 173
        width: 96
        height: 18
        text: qsTr("Set Middle")
    }

    Flickable {
        id: flickable
        x: 129
        y: 379
        width: 400
        height: 75
        flickableDirection: Flickable.VerticalFlick

        TextArea.flickable: TextArea {
            id: output
            x: 0
            y: 0
            width: 395
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
}
