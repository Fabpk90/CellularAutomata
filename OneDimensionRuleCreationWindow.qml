import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Interface 1.0

ApplicationWindow{
    id: vonNeumannRuleCreationWindow
    title: qsTr("Rule Creation")
    minimumHeight: 384 //(768/2)
    minimumWidth: 456//(1366/3)
    width: screen.width / 3
    height: screen.height / 2
    modality: Qt.ApplicationModal //permet de garder le focus
    Column{
        y: 100
        width: parent.width
        height: parent.height - 200
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 25
        Row{
            id:selectionRow
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text{
                anchors.verticalCenter: parent.verticalCenter
                id: neighborhoodFrameTitle
                text: qsTr("Select ")
            }
            Frame{
                id: neighborhoodFrame
                anchors.verticalCenter: parent.verticalCenter
                Grid{
                    rows: 1
                    columns: 3
                    spacing: 5
                    Repeater{
                        model: 3
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
                                text: index //TEST affiche
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
        }
        Row{
            id: toChangeToRow
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                anchors.verticalCenter: parent.verticalCenter
                id: newStateFrameTitle
                text: qsTr("State to change to")
            }
            Frame{
                anchors.verticalCenter: parent.verticalCenter
                id: newStateFrame
                implicitHeight: 30
                implicitWidth: 30
                spacing: 10
                MouseArea{
                    id : newStateFrameMouseArea
                    anchors.centerIn: parent
                    width: 25
                    height: 25
                    Rectangle{
                        id: newStateRectangle
                        width: parent.width
                        height: parent.height
                        anchors.centerIn: parent.Center
                        color:"lightgreen"
                    }
                    onClicked: {
                        var Component = Qt.createComponent("StateListWindow.qml")
                        var window = Component.createObject(mainwindow)
                        window.show()
                    }
                }
            }
        }
        Row{
            id: probabilitiesRow
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                id: probabilityText
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Probability ")
            }
            TextField{ //POLISHING change to SpinBox ?
                id: probability
                anchors.verticalCenter: parent.verticalCenter
                text: myInterface.probability
                validator: IntValidator{bottom: 0; top: 100}
                placeholderText: qsTr("100%")
                onTextChanged: myInterface.probability = text
            }
            Text {
                id: computeProbabilityText
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Compute Probability")
            }
            TextField{ //POLISHING change to SpinBox ?
                id: computeProbability
                anchors.verticalCenter: parent.verticalCenter
                text: myInterface.computeProbability
                validator: IntValidator{bottom: 0; top: 100}
                placeholderText:qsTr("0%")
                onTextChanged: myInterface.computeProbability = text
            }

        }
        Row{
            id:positionsRow
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                anchors.verticalCenter: parent.verticalCenter
                id: posAndCountText
                text: qsTr("Rule accounts for :")
            }

            RadioButton {
                id: positionRadioButton
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Position")
                onClicked: {
                    myInterface.posAndCount = qsTr("Position")
                    myInterface.printPosAndCount() //Test
                }
            }

            RadioButton {
                id: countRadioButton
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Count")
                autoRepeat: true
                onClicked: {
                    myInterface.posAndCount = qsTr("Count")
                    myInterface.printPosAndCount() //Test
                }
            }
        }
    }
    Button{
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        text: qsTr("OK")
        onClicked: {
            myInterface.printProbability()
            myInterface.printComputeProbability()
            myInterface.okCreateRule()
            vonNeumannRuleCreationWindow.close()
        }
    }
    Button{
        anchors.bottom: parent.bottom
        text: qsTr("Cancel")
        onClicked: vonNeumannRuleCreationWindow.close()
    }
}

