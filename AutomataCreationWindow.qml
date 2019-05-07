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
        id: sizeX
        anchors.right: parent.horizontalCenter
        anchors.top: sizeXText.bottom
        from: 1
        value: 1
        to: 100
        stepSize: 1
        editable: true
        onValueChanged: myInterface.sizeX = value
    }
    Text {
        anchors.topMargin: 10
        id: sizeXText
        text: qsTr("Matrix Size X:")
        anchors.horizontalCenter: sizeX.horizontalCenter
        anchors.top: neigh.bottom
    }

    SpinBox{
        id: sizeY
        anchors.top: sizeYText.bottom
        anchors.left: sizeX.right
        from: 1
        value: 1
        to: 100
        stepSize: 1
        editable: true
        onValueChanged: myInterface.sizeY = value
    }
    Text {
        anchors.topMargin: 10
        id: sizeYText
        text: qsTr("Matrix Size Y:")
        anchors.horizontalCenter: sizeY.horizontalCenter
        anchors.top: neigh.bottom
    }

    SpinBox{
        id: maxGenerationsToSimulate
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: sizeX.bottom
        from: 1
        value: 1
        to: 1000
        stepSize: 1
        editable: true
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


    ListView{ //TODO: Use model to fill list and delegate
        id: stateList
        width: 100; height: 100
        anchors.rightMargin: 60
        anchors.top: maxGenerationsToSimulate.bottom
        anchors.right: parent.horizontalCenter
        Text {
            id: stateText
            text: qsTr("State Column")
            horizontalAlignment: Text.AlignHCenter
        }

        //model: StateListModel {}

        delegate: RowLayout{
            width: stateList.width
            Button{
                text: "State"
                onClicked: {//TODO: Modifier l'état
                }
            }
            Button{
                text: "X"
                onClicked: {//TODO: Supprimer l'état
                }
            }
        }
    }
    ListView{ //TODO: Use model to fill list and delegate
        id: ruleList
        width: 100; height: 100
        anchors.top: maxGenerationsToSimulate.bottom
        anchors.leftMargin: 150
        anchors.left: stateList.right
        spacing: 5
        Text {
            id: ruleText
            text: qsTr("Rule Column")
            anchors.left: parent.left
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignHCenter
        }

        //model: RuleListModel {}

        delegate: RowLayout{
            width: ruleList.width
            Button{
                text: "Rule"
                onClicked: {//TODO: Modifier la règle
                }
            }
            Button{
                text: "X"
                onClicked: {//TODO: Supprimer la règle
                }
            }
        }

    }

    Button {
        anchors.top: stateList.bottom
        anchors.left: stateList.left
        id: addState
        text: qsTr("Add State")
        onClicked: {
            var Component = Qt.createComponent("StateCreationWindow.qml")
            var window = Component.createObject(mainwindow)
            window.show()
        }
    }
    Button {
        anchors.top: ruleList.bottom
        anchors.left: ruleList.left
        id: addRule
        text: qsTr("Add Rule")
        onClicked: {
            var Component = Qt.createComponent("RuleCreationWindow.qml")
            var window = Component.createObject(mainwindow)
            window.show()
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
}
