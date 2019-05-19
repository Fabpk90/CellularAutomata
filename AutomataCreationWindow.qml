import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5
import Interface 1.0

ApplicationWindow{
    id: automataCreationWindow
    title: qsTr("Automata Creation")
    width: screen.width / 3
    height: screen.height / 2
    modality: Qt.ApplicationModal //permet de garder le focus

    RowLayout {
        id: ty
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: type
            text: qsTr("Type:")
        }
        RadioButton {
            id:deterministic
            text: qsTr("Deterministic")
            checked: {
                if(myInterface.type==="Deterministic")
                    deterministic.checked=true
                else deterministic.checked=false
            }

            onClicked:{
                myInterface.type = qsTr("Deterministic")
                ruleListView.removeAllItems()
            }
        }
        RadioButton {
            id:stochastic
            text: qsTr("Stochastic")
            checked: {
                if(myInterface.type==="Stochastic")
                    stochastic.checked=true
                else stochastic.checked=false
            }
            onClicked: {
                myInterface.type = qsTr("Stochastic")
                ruleListView.removeAllItems()
             }
        }
    }
    RowLayout {
        id: dimension
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: ty.bottom
        Text {
            id: dim
            text: qsTr("Dimension:")
        }
        RadioButton {
            id:oneDim
            text: qsTr("1D")
            checked: {
                if(myInterface.dimension==="OneDimension")
                    oneDim.checked=true
                else oneDim.checked=false
            }
            onClicked: {myInterface.dimension = qsTr("OneDimension")
                ruleListView.removeAllItems()
            }
        }
        RadioButton {
            id:twoDim
            text: qsTr("2D")
            checked: {
                if(myInterface.dimension==="TwoDimensions")
                    twoDim.checked=true
                else twoDim.checked=false
            }
            onClicked: {myInterface.dimension = qsTr("TwoDimensions")
                ruleListView.removeAllItems()
            }
        }
    }
    RowLayout {
        id: neigh
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: dimension.bottom
        Text {
            id: neighborhood
            text: qsTr("Neighborhood:")
        }
        RadioButton {
            id:moore
            text: qsTr("Moore")
            checked: {
                if(myInterface.neighborhood==="Moore")
                    moore.checked=true
                else moore.checked=false
            }
            onClicked: {
                myInterface.neighborhood = qsTr("Moore")
                ruleListView.removeAllItems()
            }
        }
        RadioButton {
            id:vonNeumann
            text: qsTr("Von Neumann")
            checked: {
                if(myInterface.neighborhood==="Von Neumann")
                    vonNeumann.checked=true
                else vonNeumann.checked=false
            }
            onClicked:{
                myInterface.neighborhood = qsTr("Von Neumann")
                ruleListView.removeAllItems()
            }
        }
    }


    Row{
        id:sizeX
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: neigh.bottom
        Text {
            anchors.topMargin: 15
            anchors.top: parent.top
            text: qsTr("Matrix Size X:")
        }
        SpinBox{
            from: 1
            value: myInterface.sizeX
            to: 1000
            stepSize: 1
            editable: true
            onValueChanged: myInterface.sizeX = value
        }
    }

    Row{
        id:sizeY
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: sizeX.bottom
        Text {
            anchors.topMargin: 15
            anchors.top: parent.top
            text: qsTr("Matrix Size Y:")
        }
        SpinBox{
            from: 1
            value: myInterface.sizeY
            to: 1000
            stepSize: 1
            editable: true
            onValueChanged: myInterface.sizeY = value
        }
    }

    Row{
        id: maxGenerationsToSimulate
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: sizeY.bottom
        Text {
            anchors.topMargin: 15
            anchors.top: parent.top
            text: qsTr("Max Generations To Simulate: ")
        }
        SpinBox{
            from: 1
            value: myInterface.maxGenerationsToSimulate
            to: 1000
            stepSize: 1
            editable: true
            onValueChanged: myInterface.maxGenerationsToSimulate = value
        }
    }

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
                Text{
                    text: model.stateName
                }
                Rectangle{
                    width: 20
                    height: 20
                    color: model.stateColor
                }

                Button{
                    text: "X"
                    onClicked: stateListView.removeItem(model.number)
                }
            }
        }
    }

    Column{
        id: ruleList
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 100
        anchors.top: maxGenerationsToSimulate.bottom
        Text {
            id: ruleText
            text: qsTr("Rule Column")
            horizontalAlignment: Text.AlignHCenter
        }
        ListView{
            id: ruleView
            width: 100; height: 150
            spacing: 2
            model: ListModel {
                list_var: ruleListView
            }

            delegate: RowLayout{
                Text{
                    text: "Rule" + " " + model.number
                }
                Button{
                    text: "X"
                    onClicked: ruleListView.removeItem(model.number)
                }
            }
        }
    }


    Button {
        anchors.top: stateList.bottom
        anchors.left: stateList.left
        id: addState
        text: qsTr("Add State")
        onClicked: {
            var Component = Qt.createComponent("StateCreationWindow.qml")
            var window = Component.createObject(mainwindow)
            window.show()
            if(stateListView.getListCount()<1)
                addRule.visible=false
            if (stateListView.getListCount()>=1)
                addRule.visible=true
        }
    }
    Button {
        anchors.top: ruleList.bottom
        anchors.left: ruleList.left
        id: addRule
        text: qsTr("Add Rule")
        visible: {
            if(stateListView.getListCount()<1)
                addRule.visible=false
            if (stateListView.getListCount()>=1)
                addRule.visible=true
        }

        onClicked: {
            //TODO test all required checks
            myInterface.cleanRuleCreationWindow()
            if(twoDim.checked){
                if(vonNeumann.checked){
                    var vonNeumannCreationWindow = Qt.createComponent("VonNeumannRuleCreationWindow.qml")
                    var vonNeumannWindow = vonNeumannCreationWindow.createObject(mainwindow)
                    vonNeumannWindow.show()
                }
                if(moore.checked){
                    var mooreCreationWindow = Qt.createComponent("MooreRuleCreationWindow.qml")
                    var mooreWindow = mooreCreationWindow.createObject(mainwindow)
                    mooreWindow.show()
                }
            }
            if(oneDim.checked){
                var oneDimensionCreationWindow = Qt.createComponent("OneDimensionRuleCreationWindow.qml")
                var oneDimensionWindow = oneDimensionCreationWindow.createObject(mainwindow)
                oneDimensionWindow.show()
            }
        }
    }

    Row{
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        spacing: 10
        Button{
            text: qsTr("OK")
            onClicked: {
                myInterface.sendMandatoryInfo()
                automataCreationWindow.close()
                /*var Component = Qt.createComponent("MatrixCustomisationWindow.qml")
                var window = Component.createObject(mainwindow)
                window.show()*/
            }
        }
        Button{
            text: qsTr("Save")
            onClicked: {
                myInterface.sendMandatoryInfo()
                myInterface.saveMatrix()
            }
        }
    }

    Button{
        anchors.bottom: parent.bottom
        text: qsTr("Cancel")
        onClicked:
        {
            ruleListView.removeAllItems()
            stateListView.removeAllItems()
            automataCreationWindow.close()
        }
    }

    onClosing: {
        ruleListView.removeAllItems()
        stateListView.removeAllItems()
    }
}
