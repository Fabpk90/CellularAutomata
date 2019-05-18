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
    height: Screen.desktopAvailableHeight
    width: Screen.desktopAvailableWidth
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
                onClicked:
                    fileDialogSave.open()
            }
            MenuItem{
                text: "Load"
                onClicked: fileDialogLoad.open()
            }

            MenuItem {
                text: "Close"
                onClicked: Qt.quit()
            }
        }
        Menu{
            title: "New"
            MenuItem { text: "Create new Automaton"
                onClicked: {
                    myInterface.initialiseParser()
                    var Component = Qt.createComponent("AutomataCreationWindow.qml") //TODO change this to level 2 window on merge and add level 3 window in level 2
                    var window = Component.createObject(mainwindow)
                    window.show()
                }
            }
        }
    }

   /*GridView{
        id:mat
        x: mainwindow.width/4
        flickableDirection: Flickable.AutoFlickIfNeeded
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

    }*/

    GridView{
         id:mat
         anchors.fill : parent
         contentHeight: mainwindow.height - footer.height
         contentWidth: mainwindow.width
         ScrollBar.vertical:ScrollBar{id: hbar; active: vbar.active; policy:ScrollBar.AlwaysOn}
         ScrollBar.horizontal: ScrollBar{id: vbar; active: hbar.active; policy: ScrollBar.AlwaysOn}
         highlightFollowsCurrentItem: false
         cellWidth: mainwindow.width/mod.listOfState.returnSize() //TODO cas où listOfState >= mainwindow.width
         cellHeight: cellWidth
         cacheBuffer: 2000
         flickableDirection: Flickable.HorizontalAndVerticalFlick
         model:MatrixModel{
             id: mod
             listOfState:matrixview
         }
         delegate: Rectangle{
             id:rec
             width: mat.cellHeight
             height:mat.cellWidth
             color:model.color
             border.color:"black"
                 MouseArea{
                 id: mousearea
                 anchors.fill:parent
                 onClicked: print(tooltip.text+""+index)
                 ToolTip{
                     id:tooltip
                     text: qsTr("text" + index)
                     visible: parent.pressed

                 }

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
               id: info
                text: qsTr("Info")
                Layout.maximumWidth: 50
                onClicked: popup.open()
            }


          Popup {
                    id: popup
                    x: info.x
                    y: info.y-200
                   width: 200
                    height: 200
                  /*  modal: true
                    focus: true*/
                    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                   contentItem:  Column{
                       id: listOfState
                       anchors.right: popup.horizontalCenter //parent.horizontalCenter
                       //anchors.rightMargin: 100

                       ListView{
                           id: stateView
                           width: 100; height: 150
                           spacing: 15

                           model: ListModel {
                               list_var: stateListView
                           }

                           delegate: Rectangle{
                               height:line.height
                               width:line.width
                               Text {
                                   id:line
                                   text: model.stateName
                               }
                              color: "blue"// model.stateColor
                           }
                       }

                       ListView{
                           id: ruleView
                           anchors.rightMargin: 100
                           width: 100; height: 150
                           spacing: 15

                           model: ListModel {
                               list_var: ruleListView
                           }

                           delegate: Rectangle{
                               height:ruleLine.height
                               width:ruleLine.width
                               Text {
                                   id:ruleLine
                                   text: model.stateName
                               }
                              color: "blue"// model.stateColor
                           }
                       }


                   }

            }

  /*          Component {
                id: contactDelegate
                Item {
                    width: 180; height: 40
                    Column {
                        Text { text: '<b>Name:</b> ' + name }
                        Text { text: '<b>Number:</b> ' + number }
                    }
                }
            }
*/
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
                onClicked: myInterface.chooseGen(textField.text)

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
        title: "Please choose a file to save"
        folder: shortcuts.home
        selectExisting: false
        selectMultiple: false
        onAccepted: {
            myInterface.callSaveMatrix("test",this.fileUrl)
        }
        onRejected: {
        }

    }

    FileDialog{
        id:fileDialogLoad
        title: "Please choose a file to load"
        folder: shortcuts.home
        onAccepted: {
            myInterface.callLoad("test", this.fileUrl)
        }
        onRejected: {
        }
    }

}
