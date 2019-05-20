import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Interface 1.0

ApplicationWindow{
    id: stateListWindow
    title: qsTr("State Selection")
    width: screen.width/3
    height: screen.height/3
    modality: Qt.ApplicationModal

    Column{
        id: stateList
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 100
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
                Rectangle{
                    width: 20
                    height: 20
                    color: model.stateColor
                }
                Button{
                    text: model.stateName
                    onClicked: {
                        myInterface.associateStateAndIndex(index);
                        stateListWindow.close()
                        myInterface.stateColor=model.stateColor
                    }
                }
            }
        }
    }

    Button{
        anchors.bottom: parent.bottom
        text: "Cancel"
        onClicked: stateListWindow.close()
    }
}
