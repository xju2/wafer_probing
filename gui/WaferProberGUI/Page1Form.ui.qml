import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    property alias slider: slider
    property alias label3: label3
    property alias label4: label4
    property alias label5: label5
    property alias textInput1: textInput1
    property alias textInput2: textInput2
    property alias textInput3: textInput3
    property alias button: button
    property alias button1: button1
    property alias button2: button2
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
    rotation: 0

    Slider {
        id: slider
        x: 455
        y: 327
        font.family: "Tahoma"
        opacity: 0.6
        rotation: 90
        value: 0.5
        from: 0.01
        to: 3
        stepSize: 0.01
    }

    Button {
        id: connect
        x: 265
        y: 103
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
        x: 370
        y: 159
        text: qsTr("mm/s")
    }

    Label {
        id: label4
        x: 370
        y: 179
        text: qsTr("mm/s")
    }

    Label {
        id: label5
        x: 370
        y: 199
        text: qsTr("mm/s")
    }

    TextInput {
        id: textInput1
        x: 313
        y: 159
        width: 51
        height: 20
        color: "#25a341"
        text: qsTr("Text Input")
        horizontalAlignment: Text.AlignHCenter
        transformOrigin: Item.Center
        font.pixelSize: 12
    }

    TextInput {
        id: textInput2
        x: 313
        y: 179
        width: 51
        height: 20
        text: qsTr("Text Input")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    TextInput {
        id: textInput3
        x: 313
        y: 199
        width: 51
        height: 20
        text: qsTr("Text Input")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    Button {
        id: button
        x: 206
        y: 159
        width: 96
        height: 18
        text: qsTr("Set X speed:")
    }

    Button {
        id: button1
        x: 206
        y: 179
        width: 96
        height: 18
        text: qsTr("Set Y speed:")
    }

    Button {
        id: button2
        x: 206
        y: 199
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
        id: text1
        x: 265
        y: 338
        text: qsTr("Text")
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 296
        y: 338
        text: qsTr("Text")
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
        text: qsTr("set separat")
    }

    Label {
        id: label7
        x: 23
        y: 8
        text: qsTr("")
    }
}
