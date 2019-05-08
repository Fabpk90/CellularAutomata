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


    Row{
        id:sizeX
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: neigh.bottom
        Text {
            anchors.topMargin: 15
            anchors.top: parent.top
            text: qsTr("Matrix Size X:")
        }
        SpinBox{
            from: 1
            value: 1
            to: 1000
            stepSize: 1
            editable: true
            onValueChanged: myInterface.sizeX = value
        }
    }

    Row{
        id:sizeY
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: sizeX.bottom
        Text {
            anchors.topMargin: 15
            anchors.top: parent.top
            text: qsTr("Matrix Size Y:")
        }
        SpinBox{
            from: 1
            value: 1
            to: 1000
            stepSize: 1
            editable: true
            onValueChanged: myInterface.sizeY = value
        }
    }

    Row{
        id: maxGenerationsToSimulate
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: sizeY.bottom
        Text {
            anchors.topMargin: 15
            anchors.top: parent.top
            text: qsTr("Max Generations To Simulate: ")
        }
        SpinBox{
            from: 1
            value: 1
            to: 1000
            stepSize: 1
            editable: true
            onValueChanged: {myInterface.maxGenerationsToSimulate = value
                myInterface.printMaxGenerationsToSimulate()
            }
        }
    }

    Column{
        id: stateList
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 100
        anchors.top: maxGenerationsToSimulate.bottom
        Text {
            id: stateText
            text: qsTr("StateColumn")
            horizontalAlignment: Text.AlignHCenter
        }
        ListView{ //Use model to fill list and delegate
            width: 100; height: 100
            spacing: 2

            model: ListModel {
                list_var: stateListView
            }

            delegate: RowLayout{
                Button{
                    TextField{
                        text: model.description
                        onEditingFinished: model.description = text
                        Layout.fillWidth: true
                    }
                }
                Button{
                    text: "X"
                    onClicked: stateListView.removeItem()
                }
            }
        }
    }

    Column{
        id: ruleList
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 100
        anchors.top: maxGenerationsToSimulate.bottom
        Text {
            id: ruleText
            text: qsTr("Rule Column")
            horizontalAlignment: Text.AlignHCenter
        }
        ListView{
            width: 100; height: 100
            spacing: 2
            model: ListModel {
                list_var: ruleListView
            }

            delegate: RowLayout{
                Button{
                    TextField{
                        text: model.description
                        onEditingFinished: model.description = text
                        Layout.fillWidth: true
                    }
                }
                Button{
                    text: "X"
                    onClicked: ruleListView.removeItem()
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
            //TODO test all required checks
            if(twoDim.checked){
                if(vonNeumann.checked){
                    var vonNeumannCreationWindow = Qt.createComponent("VonNeumannRuleCreationWindow.qml")
                    var vonNeumannWindow = vonNeumannCreationWindow.createObject(mainwindow)
                    vonNeumannWindow.show()
                }
                if(moore.checked){
                    var mooreCreationWindow = Qt.createComponent("MooreRuleCreationWindow.qml")
                    var mooreWindow = mooreCreationWindow.createObject(mainwindow)
                    mooreWindow.show()
                }
            }
            if(oneDim.checked){
                var oneDimensionCreationWindow = Qt.createComponent("OneDimensionRuleCreationWindow.qml")
                var oneDimensionWindow = oneDimensionCreationWindow.createObject(mainwindow)
                oneDimensionWindow.show()
            }
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
