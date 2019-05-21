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
                onClicked: {
                    fileDialogLoad.open()
                    myInterface.loadInterface()
                }
            }

            MenuItem {
                text: "Close"
                onClicked: Qt.quit()
            }
        }
        Menu{
            title: "Automaton"
            MenuItem { text: "Create new Automaton"
                onClicked: {
                    myInterface.initialiseParser()
                    var Component = Qt.createComponent("AutomataCreationWindow.qml")
                    var window = Component.createObject(mainwindow)
                    window.show()
                    ruleListView.removeAllItems()
                    stateListView.removeAllItems()
                    mat.visible= true

                }
            }
            MenuItem { text: "Edit Automaton"
                id: editItem
                onClicked: {
                    var Component = Qt.createComponent("AutomataCreationWindow.qml")
                    var window = Component.createObject(mainwindow)
                    window.show()
                    mat.visible = true
                }
            }
        }
    }

    GridView{
         id:mat
         anchors.fill : parent
         //visible: false //TODO uncomment in final version
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
                     text: qsTr(model.name)
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
                text: "0"
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
                   width: 110
                    height: 200
                  /*  modal: true
                    focus: true*/
                    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                   contentItem:  Column{
                       id: listOfState
                       anchors.right: popup.horizontalCenter

                       ListView{
                           id: stateView
                           width: popup.width; height:popup.height
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
                              color: model.stateColor
                           }
                       }




                   }

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
                onClicked: {
                    myInterface.chooseGen(textField.text)
                    currentGeneration.text=myInterface.returnCurrentGen()
                    mat.visible = true
                }
            }

            Item {
                width: 50
            }

            Button{
                text: qsTr("⏮")
                font.pointSize: 14
                Layout.maximumHeight: 40
                onClicked: {
                    matrixview.backward()
                    currentGeneration.text=myInterface.returnCurrentGen()
                    mat.visible = true
                }
            }

            Button{
                text: qsTr("❙❙")
                font.pointSize: 16
                Layout.maximumHeight: 40
                onClicked:{
                    matrixview.pause()
                    currentGeneration.text=myInterface.returnCurrentGen()
                    mat.visible = true
                }
            }

            Button{
                text: qsTr("▶️")
                font.pointSize: 18
                Layout.maximumHeight: 40
                onClicked:{
                    currentGeneration.text=myInterface.returnCurrentGen()
                    matrixview.play()
                    mat.visible = true
                }
            }

            Button{
                text: qsTr("⏭")
                font.pointSize: 14
                Layout.maximumHeight: 40
                onClicked:{
                    matrixview.forward()
                    currentGeneration.text=myInterface.returnCurrentGen()
                    mat.visible = true
                }
            }

            Item {
                width: 50
            }

            Button{
                text: qsTr("Recompute")
                onClicked: {
                    currentGeneration.text=myInterface.returnCurrentGen()
                    myInterface.displayMatrix()
                }
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
            myInterface.callSaveMatrix("test",Qt.resolvedUrl(this.fileUrl))//TODO
        }
        onRejected: {
        }

    }

    FileDialog{
        id:fileDialogLoad
        title: "Please choose a file to load"
        folder: shortcuts.home
        onAccepted: {
           myInterface.initialiseParser()
           myInterface.callLoad("test", Qt.resolvedUrl(this.fileUrl))
           mainwindow.close()
           var Component = Qt.createComponent("main.qml")
           var window = Component.createObject(mainwindow)
           window.show()

        }
        onRejected: {
        }
    }

}
