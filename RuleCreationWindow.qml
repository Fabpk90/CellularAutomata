import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import Interface 1.0
import QtQuick.Layouts 1.3

ApplicationWindow{
    id: ruleCreationWindow
    title: qsTr("Creation de Règle")
    width: screen.width / 3
    height: screen.height / 2
    modality: Qt.ApplicationModal //permet de garder le focus

    //TODO RuleZone (i'm lost)



    TextField{ //TODO change to SpinBox
        id: probability
        text: myInterface.probability
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

    TextField{ //TODO change to SpinBox
        id: computeProbability
        text: myInterface.computeProbability
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
