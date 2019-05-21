import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import Interface 1.0

ApplicationWindow {
    id: stateCreation
    width: 600
    height: 213
    maximumHeight: 1000
    modality: Qt.ApplicationModal
    title: "StateCreation"


    Button {
        id: button
        x: 459
        y: 167
        width: 83
        height: 29
        text: qsTr("Ok")
        //onClicked:myInterface.call
        onClicked: {
            stateListView.appendState()
            myInterface.okCreateState(";")
            stateCreation.close()
        }
    }

    Button {
        id: button1
        x: 289
        y: 167
        width: 87
        height: 29
        text: qsTr("CANCEL")
        onClicked: stateCreation.close()
    }

    Text {
        id: element
        x: 41
        y: 24
        width: 46
        height: 20
        text: qsTr("Name:")
        font.pixelSize: 12
    }


    ColorDialog{
        id: colorDialog

        onAccepted:{
            rectangle.color=this.color
            myInterface.stateColor=this.color
            stateListView.setStateColor(myInterface.getStateColor())
            //myInterface.printStateColor()
           }
    }

    Button {
        id: button2
        x: 56
        y: 81
        text: qsTr("Choose Color")
        onClicked: colorDialog.open()
    }

    Rectangle {
        id: rectangle
        x: 196
        y: 90
        width: 20
        height: 20
        color: "#ffffff"
        border.color: "#090404"
    }

    Text {
        id: element1
        x: 168
        y: 92
        width: 29
        height: 30
        text: qsTr(":")
        font.pixelSize: 12
    }

    Rectangle {
        id: rectangle1
        x: 120
        y: 18
        width: 155
        height: 26
        color: "#ffffff"
        border.color: "#130303"

        TextInput {
            id: textInput1
            x: 8
            y: 8
            width: 140
            height: 18
            text: qsTr("State"+myInterface.numbState)
            activeFocusOnPress: true
            cursorVisible: true
            font.pixelSize: 12
            onTextChanged:
            {
                myInterface.stateName = textInput1.text
                stateListView.setStateName(myInterface.getStateName())
            }
        }
    }
}
