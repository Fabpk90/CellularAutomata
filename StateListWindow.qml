import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Interface 1.0

ApplicationWindow{
    id: stateCreationWindow
    title: qsTr("State Selection")
    width: screen.width/3
    height: screen.height/3
    modality: Qt.ApplicationModal

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
        ListView{
            id: stateView
            width: 100; height: 150
            spacing: 2

            model: ListModel {
                list_var: stateListView
            }

            delegate: RowLayout{
                Button{
                    text: "State" + " " + model.number
                    onClicked: {
                        //TODO select state /*idee remove Ok onClicked select index and close window*/
                    }
                }
            }
        }
    }
    Button{
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        text: "Ok"
        onClicked: {
            //TODO choose state
            stateCreationWindow.close()
        }
    }

    Button{
        anchors.bottom: parent.bottom
        text: "Cancel"
        onClicked: stateCreationWindow.close()
    }

    //TODO
}
