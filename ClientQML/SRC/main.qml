import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.5

import tcp 1.0

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Client")
    Item {
        id: mainItem
        anchors.fill: parent
        Item {
            id: lineControl
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 70
            Button {
                id: buttonOpen
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.leftMargin: 10
                width: 80
                height: (parent.anchors.bottom-anchors.topMargin)/2
                text: qsTr("Open")
                onClicked: openDialog.open()
                background: Rectangle {
                    color: "#F0F0FF"
                    border.color: "black"
                    border.width: 1
                }
            }
            Button {
                id: buttonConnect
                anchors.top: parent.top
                anchors.left: buttonOpen.right
                anchors.topMargin: 5
                anchors.bottomMargin: 5
                anchors.leftMargin: 30
                width: buttonOpen.width
                height: buttonOpen.height
                text: qsTr("Connect")
                onClicked: connect()
                background: Rectangle {
                    color: "#F0F0FF"
                    border.color: "black"
                    border.width: 1
                }
            }
            Button {
                id: buttonSend
                anchors.top: parent.top
                anchors.left: buttonConnect.right
                anchors.topMargin: 5
                anchors.leftMargin: 30
                width: buttonOpen.width
                height: buttonOpen.height
                text: qsTr("Send")
                enabled: false
                onClicked: sendToServer()
                background: Rectangle {
                    color: "#F0F0FF"
                    border.color: "black"
                    border.width: 1
                }
            }
            Text {
                id: textConnect
                color: "#000000"
                anchors.top: parent.top
                anchors.left: buttonSend.right
                anchors.topMargin: 5
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                width: parent.width-anchors.left
                height: buttonOpen.height/2
                font.pixelSize: 10
                clip: true
            }
            TextInput {
                id: textIP
                color: "#000000"
                anchors.top: textConnect.bottom
                anchors.left: buttonSend.right
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                width: parent.width-anchors.left
                height: buttonOpen.height/2
                font.pixelSize: 10
                text: "127.0.0.1"
            }
            Label {
                id: labelMethod
                anchors.left: parent.left
                anchors.top: buttonOpen.bottom
                anchors.bottom: parent.bottom
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.bottomMargin: 5
                width: 80

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Label.Wrap
                text: "Processing Method"
            }
            ComboBox {
                id: comboMethod
                anchors.top: buttonOpen.bottom
                anchors.left: labelMethod.right
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.topMargin: 5
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.bottomMargin: 5
                model: ListModel {
                    id: model
                    ListElement { text: "Word" }
                    ListElement { text: "Char" }
                }
                onAccepted: {
                    if (find(editText) === -1)
                        model.append({text: editText})
                }
            }
        }


        Item {
            id: textItem
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: lineControl.bottom
            anchors.bottom: parent.bottom

            Rectangle {
                id: rectSRC
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottomMargin: 5
                anchors.topMargin: 5
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                height: parent.height/2-anchors.topMargin-anchors.bottomMargin
                color: "#F0F0FF"
                border.color: "black"
                ScrollView {
                    anchors.fill: parent
                    anchors.margins: 5
                    clip: true
                    TextEdit {
                        id: textSRC
                        color: "#000000"
                        font.pixelSize: 15
                        wrapMode: TextEdit.Wrap
                        focus: true
                    }
                }
            }
            Rectangle {
                id: rectRes
                anchors.top: rectSRC.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottomMargin: 5
                anchors.topMargin: 5
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                height: rectSRC.height
                color: "#F0F0FF"
                border.color: "black"
                ScrollView {
                    id: scrollRes
                    anchors.fill: parent
                    anchors.margins: 5
                    clip: true
                    Text {
                        id: textRes
                        color: "#000000"
                        font.pixelSize: 15
                        wrapMode: TextEdit.Wrap
                    }
                }
            }
        }
    }
    FileDialog {
        id: openDialog
        title: "Open file"
        selectMultiple: false
        nameFilters: ["Text files (*.txt)"]
        onAccepted: setText(openDialog.fileUrl)
    }
    Connections {
        target: C_TCP
        onReceivedText: {
            textRes.text = C_TCP.getText()
            scrollRes.ScrollBar.vertical.position = 0
        }
        onObjectState: {
            buttonSend.enabled = C_TCP.getState()
            if (buttonSend.enabled == true)
                textConnect.text = "Connection established"
            else
                textConnect.text = "Connection lost"
        }
        onSendError: {
            textConnect.text = C_TCP.getTextError()
        }
    }
    function setText(fileUrl) {
        textSRC.text = openFile(fileUrl)
        textRes.text = ""
    }
    function openFile(fileUrl) {
        return Serv.open(fileUrl)
    }
    function connect() {
        textConnect.text = "Connect"
        C_TCP.connectTCP(textIP.text)
    }
    function sendToServer() {
        C_TCP.sendToServerTCP(comboMethod.textAt(comboMethod.currentIndex),Serv.getFileName(),textSRC.text)
    }
}
