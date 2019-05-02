import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Interface 1.0
//POLISHING everything is calculated on "id:probability"

ApplicationWindow{
    id: ruleCreationWindow
    title: qsTr("Rule Creation")
    width: screen.width / 3
    height: screen.height / 2
    modality: Qt.ApplicationModal //permet de garder le focus
    Frame{ 
        id: neighborhoodFrame
        anchors.verticalCenterOffset:-(height + newStateFrame.height + 50)
        anchors.centerIn: parent
        Grid{
            rows: 3
            columns: 3
            spacing: 5
            Repeater{
                model: 9
                MouseArea {
                    id: neighborhoodFrameMouseArea
                    width: 25
                    height: 25
                    Rectangle {
                        id: neighborhoodRectangle
                        width: parent.width
                        height: parent.height
                        color: "lightgrey"
                    }
                    Text{
                        text: index //TEST pour tests
                    }

                    onClicked: {
                        var Component = Qt.createComponent("StateListWindow.qml")
                        var window = Component.createObject(mainwindow)
                        window.show()
                    }
                }

            }
        }
    }

    Frame{
        id: newStateFrame
        implicitHeight: 30
        implicitWidth: 30
        anchors.verticalCenterOffset: -(height + 70)
        anchors.centerIn: parent
        MouseArea{
            id : newStateFrameMouseArea
            width: 25
            height: 25
            anchors.centerIn: parent
            Rectangle{
                id: newStateRectangle
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                color:"lightgreen"
            }
            onClicked: {
                var Component = Qt.createComponent("StateListWindow.qml")
                var window = Component.createObject(mainwindow)
                window.show()
            }
        }
    }
    Text {
        id: newStateFrameTitle
        text: qsTr("State to change to")
        anchors.horizontalCenterOffset: -(width + newStateFrame.width/2)
        anchors.centerIn: newStateFrame
    }

    Text{
        id: neighborhoodFrameTitle
        text: qsTr("Select ")
        anchors.horizontalCenterOffset: -(width + neighborhoodFrame.width/2)
        anchors.centerIn: neighborhoodFrame
    }



    TextField{ //POLISHING change to SpinBox ?
        id: probability
        text: myInterface.probability
        validator: IntValidator{bottom: 0; top: 100}
        anchors.centerIn: parent
        placeholderText: qsTr("100%")
        onTextChanged: myInterface.probability = text

        Text {
            id: probabilityText
            text: qsTr("Probability ")
            anchors.horizontalCenterOffset: -parent.width
            anchors.centerIn: parent
        }
    }


    TextField{ //POLISHING change to SpinBox ?
        id: computeProbability
        text: myInterface.computeProbability
        validator: IntValidator{bottom: 0; top: 100}
        anchors.verticalCenterOffset: probability.height
        anchors.centerIn:parent
        placeholderText:qsTr("0%")
        onTextChanged: myInterface.computeProbability = text

        Text {
            id: computeProbabilityText
            text: qsTr("Compute Probability")
            anchors.horizontalCenterOffset: -parent.width
            anchors.centerIn: parent
        }
    }

    RowLayout {
        id: rowLayout
        anchors.verticalCenterOffset: -height
        anchors.centerIn: parent

        Text {
            id: posAndCountText
            text: qsTr("Rule accounts for :")
        }

        RadioButton {
            id: positionRadioButton
            text: qsTr("Position")
            onClicked: {
                myInterface.posAndCount = qsTr("Position")
                myInterface.printPosAndCount() //Test
            }
        }

        RadioButton {
            id: countRadioButton
            text: qsTr("Count")
            autoRepeat: true
            onClicked: {
                myInterface.posAndCount = qsTr("Count")
                myInterface.printPosAndCount() //Test
            }
        }
    }
}


