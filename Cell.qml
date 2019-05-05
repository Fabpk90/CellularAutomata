import QtQuick 2.0

Rectangle{

    id:rec
    property int position: 0
    border.color: "black"
    Text {
        visible: false
        id: name
        text: qsTr("Cell"+position)
    }

    MouseArea{
        anchors.fill: parent
        onClicked:console.log(name.text+" "+rec.color)


    }



}
