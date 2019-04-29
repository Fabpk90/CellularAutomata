import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import Interface 1.0

ApplicationWindow{
    id: automataCreationWindow
    title: qsTr("Creation de l'Automate")
    width: screen.width / 3
    height: screen.height / 2
    modality: "ApplicationModal" //permet de garder le focus

    RowLayout {
        id: ty
        Text {
            id: type
            text: qsTr("Type:")
        }
        CheckBox {
            text: qsTr("Dynamic")
        }
        CheckBox {
            text: qsTr("Stochastic")
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
            text: qsTr("1D")
        }
        CheckBox {
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
            text: qsTr("Moore")
        }
        CheckBox {
            text: qsTr("Von Neumann")
        }
    }

    TableView { //Test de mise en forme
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
    }

}
