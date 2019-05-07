import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5
import Interface 1.0

ApplicationWindow{
    id: automataCreationWindow
    title: qsTr("Automata Creation")
    width: screen.width / 3
    height: screen.height / 2
    modality: Qt.ApplicationModal //permet de garder le focus

    RowLayout {
        id: ty
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: type
            text: qsTr("Type:")
        }
        RadioButton {
            id:dynamic
            text: qsTr("Dynamic")
            checked: true
            onClicked: myInterface.type = qsTr("Dynamic")
        }
        RadioButton {
            id:stochastic
            text: qsTr("Stochastic")
            onClicked: myInterface.type = qsTr("Stochastic")
        }
    }
    RowLayout {
        id: dimension
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: ty.bottom
        Text {
            id: dim
            text: qsTr("Dimension:")
        }
        RadioButton {
            id:oneDim
            text: qsTr("1D")
            onClicked: {myInterface.dimension = qsTr("OneDimension")
                myInterface.printDimension()
            }
        }
        RadioButton {
            id:twoDim
            text: qsTr("2D")
            checked: true
            onClicked: {myInterface.dimension = qsTr("TwoDimensions")
                myInterface.printDimension()
            }
        }
    }
    RowLayout {
        id: neigh
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: dimension.bottom
        Text {
            id: neighborhood
            text: qsTr("Neighborhood:")
        }
        RadioButton {
            id:moore
            text: qsTr("Moore")
            checked: true
            onClicked: myInterface.neighborhood = qsTr("Moore")
        }
        RadioButton {
            id:vonNeumann
            text: qsTr("Von Neumann")
            onClicked: myInterface.neighborhood = qsTr("Von Neumann")
        }
    }

    SpinBox{
        id: maxGenerationsToSimulate
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: neigh.bottom
        from: 1
        value: 1
        to: 1000
        stepSize: 1
        onValueChanged: {myInterface.maxGenerationsToSimulate = value
            myInterface.printMaxGenerationsToSimulate()
        }
    }

    Text {
        id: maxGenerationsToSimulateText
        text: qsTr("Max Generations To Simulate: ")
        anchors.verticalCenter: maxGenerationsToSimulate.verticalCenter
        anchors.right: maxGenerationsToSimulate.left
    }


    Column {
        id: stateColumn
        anchors.rightMargin: 95
        anchors.top: maxGenerationsToSimulate.bottom
        anchors.right: parent.horizontalCenter
        Text {
            id: stateText
            text: qsTr("State")
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Column {
        id: ruleColumn
        anchors.top: maxGenerationsToSimulate.bottom
        anchors.leftMargin: 150
        anchors.left: stateColumn.right
        Text {
            id: ruleText
            text: qsTr("Rule")
            anchors.left: parent.left
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignHCenter
        }
    }


    Button{
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        text: qsTr("OK")
        onClicked: automataCreationWindow.close()
    }
    Button{
        anchors.bottom: parent.bottom
        text: qsTr("Cancel")
        onClicked: automataCreationWindow.close()
    }

    Button {
        anchors.top: stateColumn.bottom
        anchors.left: stateColumn.left
        id: addState
        text: qsTr("Add State")
        onClicked: {
            var Component = Qt.createComponent("StateCreationWindow.qml")
            var window = Component.createObject(mainwindow)
            window.show()
        }
    }

    Button {
        anchors.top: ruleColumn.bottom
        anchors.left: ruleColumn.left
        id: addRule
        text: qsTr("Add Rule")
        onClicked: {
            var Component = Qt.createComponent("RuleCreationWindow.qml")
            var window = Component.createObject(mainwindow)
            window.show()
        }
    }

}
