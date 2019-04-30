import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import Interface 1.0

ApplicationWindow{
    id: ruleCreationWindow
    title: qsTr("Creation de Règle")
    width: screen.width / 3
    height: screen.height / 2
    modality: Qt.ApplicationModal
    TextField{
        id: probability
        text: myInterface.probability
        anchors.centerIn: parent
        placeholderText: qsTr("100%")
        onTextChanged: myInterface.probability = text
    }
}
