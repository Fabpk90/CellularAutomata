import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import Interface 1.0

ApplicationWindow {
    id: matrixCustom
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    modality: Qt.ApplicationModal
    title: "MatrixCustomization"
    property color color_property
    property int state:-1
    Text {
        id: name
        text: qsTr("")
    }
    footer:Rectangle {

        id: footerCustom

        height: 50
        color: "#f3f3f4"
        Button {
        id: button
        text: qsTr("Ok")
        //onClicked:myInterface.call
        onClicked: {
           myInterface.okCreateHistory()

            /* var Component = Qt.createComponent("main.qml")
            var window = Component.createObject()
            window.show()
*/
            matrixCustom.close()
            mainwindow.close()
            myInterface.initMatrix()
             var Component = Qt.createComponent("main.qml")
            var window = Component.createObject()
            window.show()

            //  print("JES PEUX FAIRE DES TRUCS LAAAAAA ICI")
        }
    }
        Button{
           id: info
            text: qsTr("Liste d'états")
            x: button.width + 20
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
                     anchors.right: popup.horizontalCenter //parent.horizontalCenter
                     //anchors.rightMargin: 100

                     ListView{
                            id: stateViewCustom
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
                               MouseArea{
                               id: stateArea
                               anchors.fill:parent
                               onClicked: {
                                    matrixCustom.state=index
                                    matrixCustom.color_property=color
                                  name.text=line.text
                               }


                           }
                            }
                        }




                 }

          }

    }
    GridView{
         id:mat
         anchors.fill : parent
         contentHeight: matrixCustom.height
         contentWidth: matrixCustom.width
         ScrollBar.vertical:ScrollBar{id: hbar; active: vbar.active; policy:ScrollBar.AlwaysOn}
         ScrollBar.horizontal: ScrollBar{id: vbar; active: hbar.active; policy: ScrollBar.AlwaysOn}
         highlightFollowsCurrentItem: false
         cellWidth: matrixCustom.width/mod.listOfState.returnSize() //TODO cas où listOfState >= mainwindow.width
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
                 onClicked: {
                    if(matrixCustom.state >=0){
                     rec.color=matrixCustom.color_property
                    model.name=name.text
                    myInterface.updateStateVector(index,matrixCustom.state)
                    }
                 }


             }
         }
    }














    /* ListView{
        id: stateViewCustom
        anchors.left: matrixCustom.left
       // anchors.right: mat.left
        width: 100;height:matrixCustom.height
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
           MouseArea{
           id: stateArea
           anchors.fill:parent
           onClicked: {
                matrixCustom.state=index
                matrixCustom.color_property=color
              name.text=line.text
           }


       }
        }
    }*/


   // onClosing: myInterface.displayEverything()

}
