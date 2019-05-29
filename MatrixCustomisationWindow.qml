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
        onClicked: {
           myInterface.okCreateHistory()
            matrixCustom.close()
            mainwindow.close()
            myInterface.initMatrix()
             var mainComponent = Qt.createComponent("main.qml")
            var mainWindow = mainComponent.createObject(mainwindow)
            mainWindow.show()
        }
    }
        Button{//bouton pour ouvrir la liste des états
           id: info
            text: qsTr("Liste d'états")
            x: button.width + 20
            Layout.maximumWidth: 50
            onClicked: popup.open()
        }

        Popup { //affichage de la liste des états
                  id: popup
                  x: info.x
                  y: info.y-200
                 width: 110
                  height: 200
                  closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                 contentItem:  Column{
                     id: listOfState
                     anchors.right: popup.horizontalCenter

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
    GridView{ //affichage de la matrice de cutomisation
         id:mat
         anchors.fill : parent
         contentHeight: matrixCustom.height
         contentWidth: matrixCustom.width
         ScrollBar.vertical:ScrollBar{id: hbar; active: vbar.active; policy:ScrollBar.AlwaysOn}
         ScrollBar.horizontal: ScrollBar{id: vbar; active: hbar.active; policy: ScrollBar.AlwaysOn}
         highlightFollowsCurrentItem: false
         cellWidth: matrixCustom.width/mod.listOfState.returnSize()
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

}
