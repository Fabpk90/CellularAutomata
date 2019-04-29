import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

ApplicationWindow{
    id: ruleCreationWindow
    title: qsTr("Creation de Règle")
    width: screen.width / 3
    height: screen.height / 2
    modality: "ApplicationModal" //permet de garder le focus
    Text {
            anchors.centerIn: parent
            text: qsTr("Creation de regle")
        }
}
