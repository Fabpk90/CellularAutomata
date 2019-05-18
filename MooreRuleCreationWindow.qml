import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Interface 1.0

ApplicationWindow{
    id: mooreRuleCreationWindow
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
                    countRow.visible = false
                    selectionRow.visible=true
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
                    selectionRow.visible = false
                    countRow.visible = true
                    myInterface.posAndCount = qsTr("Count")
                    myInterface.printPosAndCount() //Test
                }
            }
        }
        Row{
            id:selectionRow
            visible: false
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
                                color: "lightgrey" //TODO change color to actual color
                            }
                            Text{
                                text: index //TEST affiche
                            }

                            onClicked: {
                                myInterface.setRememberIndex(index)
                                console.log("cpp index = " + myInterface.getRememberIndex() + " index =" + index)
                                var Component = Qt.createComponent("StateListWindow.qml")
                                var window = Component.createObject(mainwindow)
                                window.show()
                            }
                        }
                    }
                }
            }
        }
        Row {
            id:countRow
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text{
                anchors.verticalCenter: parent.verticalCenter
                id: countFrameTitle
                text: qsTr("Select ")
            }
            Frame{
                id: countFrame
                anchors.verticalCenter: parent.verticalCenter
                Grid{
                    rows: 3
                    columns: 3
                    spacing: 5
                    Repeater{
                        model: 9
                        MouseArea {
                            id: countFrameMouseArea
                            width: 25
                            height: 25
                            Rectangle {
                                id: countRectangle
                                width: parent.width
                                height: parent.height
                                color: "lightgrey" //TODO change color to actual color
                            }
                            Text{
                                text: index //TEST affiche
                            }

                            onClicked: {
                                myInterface.setRememberIndex(index)
                                console.log("cpp index = " + myInterface.getRememberIndex() + " index =" + index)
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
                        color:"lightgreen" //TODO change color to actual color
                    }
                    onClicked: {
                        myInterface.setRememberIndex(9)
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
            SpinBox{ //TODO change to float (for all)
                id: probability
                editable: true
                value:parseFloat(myInterface.probability)//valueFromText(locale, myInterface.probability)
                from:  0
                to: 100 * 100
                stepSize: 1
                property int decimals: 2
                property real realValue: value / 100
                validator: DoubleValidator {
                    bottom: Math.min(probability.from, probability.to)
                    top:  Math.max(probability.from, probability.to)
                }
                textFromValue: function(value, locale) {
                    return Number(value / 100).toLocaleString(locale, 'f', probability.decimals)
                }

                valueFromText: function(text, locale) {//ERROR
                    return Number.fromLocaleString(locale, text) * 100
                }

                anchors.verticalCenter: parent.verticalCenter
              //  onValueChanged: myInterface.probability = textFromValue(value, locale)
            }
            Text {
                id: computeProbabilityText
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Compute Probability")
            }
            SpinBox{
                id:computeProbability
                editable: true
                value: myInterface.computeProbability
                from: 0
                to: 100
                anchors.verticalCenter: parent.verticalCenter
                onValueChanged: myInterface.computeProbability = value
            }

        }

    }
    Button{
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        text: qsTr("OK")
        onClicked: {
            myInterface.probability = probability.textFromValue(probability.value,locale)
            ruleListView.appendItem()
            myInterface.printProbability()
            myInterface.printComputeProbability()
            myInterface.okCreateRule()
            mooreRuleCreationWindow.close()
        }
    }
    Button{
        anchors.bottom: parent.bottom
        text: qsTr("Cancel")
        onClicked: mooreRuleCreationWindow.close()
    }
}
