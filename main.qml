import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
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
        Menu{
            title: "File"
            MenuItem {
             text: "Save"
             onClicked: fileDialogSave.open()
            }
            MenuItem { text: "Close"}
        }
        Menu{
            title: "New"
            MenuItem { text: "Create new Automaton"
                onClicked: {
                    var Component = Qt.createComponent("AutomataCreationWindow.qml") //TODO change this to level 2 window on merge and add level 3 window in level 2
                    var window = Component.createObject(mainwindow)
                    window.show()
                }
            }
        }
    }


   GridView{
        id:mat
        x: mainwindow.width/4
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        contentHeight:mainwindow.height
        contentWidth: mainwindow.width
        ScrollBar.vertical:ScrollBar{id: hbar; active: vbar.active; policy:ScrollBar.AlwaysOn}
        ScrollBar.horizontal: ScrollBar{id: vbar; active: hbar.active; policy: ScrollBar.AlwaysOn}
        width: mod.listOfState.returnSize()*10
        height: width
        cellHeight:10
        cellWidth: 10
        model:MatrixModel{
            id: mod
            listOfState:matrixview
        }
        delegate: Rectangle{
            id:rec
            width: mat.cellHeight
            height:mat.cellWidth
            color:model.color
            Text {
                visible: false
                id: t
                text: qsTr(model.name)
            }
            border.color:"black"

            ToolTip{
                id:tooltip
                text:t.text
                visible: mousearea.pressed

            }
            MouseArea{
                id: mousearea
                anchors.fill:parent

            }

        }

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
                onClicked: matrixview.backward()
            }

            Button{
                text: qsTr("❙❙")
                font.pointSize: 16
                Layout.maximumHeight: 40
                onClicked: matrixview.pause()
            }

            Button{
                text: qsTr("▶️")
                font.pointSize: 18
                Layout.maximumHeight: 40
                onClicked:matrixview.play()
            }

            Button{
                text: qsTr("⏭")
                font.pointSize: 14
                Layout.maximumHeight: 40
                onClicked: matrixview.forward()
            }

            Item {
                width: 50
            }

            Button{
                text: qsTr("Recompute")
            }

        }

    }

    FileDialog{
        id:fileDialogSave
        onAccepted: myInterface.callSaveMatrix("test",this.fileUrl)


    }

    FileDialog{
        id:fileDialogLoad
        onAccepted: myInterface.callLoad("test", this.fileUrl)


    }

}
