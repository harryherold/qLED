import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import com.myself 1.0

Window {
    id: mainWindow

    visible: true
    title: qsTr("qLedTest")

    ColumnLayout {
        anchors.fill: mainWindow
        width: 150

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: "Control Center"
        }
        Bcm2835Control {
            id: bcm2835Control
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 50

            Label {
                Layout.fillHeight: true
                Layout.preferredWidth: 100

                verticalAlignment: Qt.AlignVCenter
                text: "LED"
                background: Rectangle {
                    color: "#63DE59"
                }
            }
            ToolButton {
                Layout.fillHeight: true
                Layout.preferredWidth: 70

                text: bcm2835Control.isLedOn ? "off" : "on"
                checkable: true
                onToggled: bcm2835Control.toggleLed()
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 50

            Label {
                Layout.fillHeight: true
                Layout.preferredWidth: 100

                verticalAlignment: Qt.AlignVCenter
                text: "LED"
                background: Rectangle {
                    color: "#63DE59"
                }
            }
            ToolButton {
                Layout.fillHeight: true
                Layout.preferredWidth: 70

                text: "blink"
                enabled: bcm2835Control.isBlinking === false
                onClicked: bcm2835Control.blinkLed()
            }
        }
        Button {
            text: "Close"
            onClicked: mainWindow.close()
        }
    }
}
