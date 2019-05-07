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
        Text {
            id: type
            text: qsTr("Type:")
        }
        RadioButton {
            id:dynamic
            text: qsTr("Dynamic")
        }
        RadioButton {
            id:stochastic
            text: qsTr("Stochastic")

            onClicked: {dynamic.checked()}
        }
    }
    RowLayout {
        id: dimension
        anchors.top: ty.bottom
        Text {
            id: dim
            text: qsTr("Dimension:")
        }
        RadioButton {
            id:oneDim
            text: qsTr("1D")
        }
        RadioButton {
            id:twoDim
            text: qsTr("2D")
        }
    }
    RowLayout {
        id: neigh
        anchors.top: dimension.bottom
        Text {
            id: neighborhood
            text: qsTr("Neighborhood:")
        }
        RadioButton {
            id:moore
            text: qsTr("Moore")
        }
        RadioButton {
            id:vonNeumann
            text: qsTr("Von Neumann")
        }
    }

    TableView {
        id: tab
        anchors.centerIn: parent
        anchors.left: parent.horizontalCenter
        //Test de mise en forme
        anchors.top: neigh.bottom
        /*TableViewColumn {
            role: "state"
            title: "State"
            width: 100
        }
        TableViewColumn {
            role: "rule"
            title: "Rule"
            width: 100
        }*/
    }

    Button{
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        text: qsTr("OK")
    }
    Button{
        anchors.bottom: parent.bottom
        text: qsTr("Cancel")
        onClicked: automataCreationWindow.close()
    }

    Button {
        anchors.top: tab.bottom
        anchors.left: tab.left
        id: addState
        text: qsTr("Add State")
        onClicked: {
            var Component = Qt.createComponent("StateCreationWindow.qml")
            var window = Component.createObject(mainwindow)
            window.show()
        }
    }

    Button {
        anchors.top: tab.bottom
        anchors.right: tab.right
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
}
