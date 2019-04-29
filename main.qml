import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import Interface 1.0

ApplicationWindow {
    id: mainwindow
    visible: true
    width: screen.width
    height: screen.height
    minimumWidth: 900
    minimumHeight: 600
    title: qsTr("Cellular Automata Simulator")

    Interface{
        id:myInterface
    }

    menuBar: MenuBar{
        Material.theme : Material.Light
        Menu{
            title: "File"
            MenuItem { text: "Save"}
            MenuItem { text: "Close"}
        }
        Menu{
            title: "New"
            MenuItem { text: "Create new Automaton"
                onClicked: {
                    var Component = Qt.createComponent("RuleCreationWindow.qml") //TODO change this to level 2 window on merge and add level 3 window in level 2
                    var window = Component.createObject(mainwindow)
                    window.show()
                }
            }
        }
    }

    TableView {
        id: matrixView
        anchors.fill: parent

        rowSpacing: 1
        columnSpacing: 1

        ScrollBar.horizontal: ScrollBar{}
        ScrollBar.vertical: ScrollBar{}

        delegate:  Rectangle{
            id: cell
            implicitHeight: 15
            implicitWidth: 15

            color: model.Value ? "#f3f3f4" : "#b5b7bf"
        }
        contentX: (contentWidth - width) / 2;
        contentY: (contentHeight - height) /2;

    }


    footer: Rectangle{
        id: footer
        height: 80
        color: "#f3f3f4"

        RowLayout{
            spacing: 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id: currentGeneration
                text: qsTr("125")
                font.pixelSize: 12
            }

            Item {
                width: 50
            }

            Button{
                text: qsTr("Info")
                Layout.maximumWidth: 50
            }

            Item {
                width: 50
            }

            TextField {
                id: textField
                text: qsTr("")
                horizontalAlignment: Text.AlignRight
                placeholderText: "Jump to Generation"
                Layout.maximumWidth: 132
            }

            Button{
                text: qsTr("Go")
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.maximumHeight: 50
                Layout.maximumWidth: 50
            }

            Item {
                width: 50
            }

            Button{
                text: qsTr("⏮")
                font.pointSize: 14
                Layout.maximumHeight: 40
            }

            Button{
                text: qsTr("❙❙")
                font.pointSize: 16
                Layout.maximumHeight: 40
            }

            Button{
                text: qsTr("▶️")
                font.pointSize: 18
                Layout.maximumHeight: 40
            }

            Button{
                text: qsTr("⏭")
                font.pointSize: 14
                Layout.maximumHeight: 40
            }

            Item {
                width: 50
            }

            Button{
                text: qsTr("Recompute")
            }

        }

    }
}
