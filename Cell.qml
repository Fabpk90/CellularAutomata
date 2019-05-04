import QtQuick 2.0

Rectangle{

    id:rec
    border.color: "black"
    Text {
        visible: false
        id: name
        text: qsTr("text")
    }

    MouseArea{
        anchors.fill: parent
        onClicked:console.log(name.text+" "+rec.color)


    }



}
