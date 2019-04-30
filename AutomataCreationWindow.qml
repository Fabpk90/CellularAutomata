import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
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
        CheckBox {
            id:dynamic
            text: qsTr("Dynamic")
        }
        CheckBox {
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
        CheckBox {
            id:oneDim
            text: qsTr("1D")
        }
        CheckBox {
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
        CheckBox {
            id:moore
            text: qsTr("Moore")
        }
        CheckBox {
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
        TableViewColumn {
            role: "state"
            title: "State"
            width: 100
        }
        TableViewColumn {
            role: "rule"
            title: "Rule"
            width: 100
        }
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
            var Component = Qt.createComponent("") //TODO quand on va merge ajouter StateCreationWindow.qml
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
            var Component = Qt.createComponent("RuleCreationWindow.qml")
            var window = Component.createObject(mainwindow)
            window.show()
        }
    }

}
