import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import io.qt.examples.backend 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Wafter Probing console table")

    BackEnd {
        id: backend
    }

    Page1 {
    }
}
