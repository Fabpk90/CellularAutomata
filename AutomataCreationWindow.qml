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
    minimumHeight: 540
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
                myInterface.removeAllRulesAutomata()
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
                myInterface.removeAllRulesAutomata()
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
                myInterface.removeAllRulesAutomata()
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
                myInterface.removeAllRulesAutomata()
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
                myInterface.removeAllRulesAutomata()
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
                myInterface.removeAllRulesAutomata()
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
            text: qsTr("Matrix Size:")
        }
        SpinBox{
            id: sizeXSpin
            from: 2
            value: 2
            to: 100
            stepSize: 1
            editable: true
            onValueChanged: myInterface.sizeX = value
        }
    }

    /*Row{
        id:sizeY
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: sizeX.bottom
        visible: {
            if(myInterface.dimension==="OneDimension") true
            else false
        }

        Text {
            anchors.topMargin: 15
            anchors.top: parent.top
            text: qsTr("Matrix Size Y:")
        }
        SpinBox{
            from: {
                if(myInterface.dimension==="TwoDimensions") 2
                else 1
            }
            value: myInterface.sizeY
            to: {
                if(myInterface.dimension==="TwoDimensions") 100
                else 1
            }
            stepSize: 1
            editable: true
            onValueChanged: myInterface.sizeY = value
        }
    }*/

    Row{
        id: maxGenerationsToSimulate
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: sizeX.bottom
        Text {
            anchors.topMargin: 15
            anchors.top: parent.top
            text: qsTr("Max Generations To Simulate: ")
        }
        SpinBox{
            from: 1
            value: myInterface.maxGenerationsToSimulate
            to: 100
            stepSize: 1
            editable: true
            onValueChanged: myInterface.maxGenerationsToSimulate = value
        }
    }

    Column{
        id: stateList
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 0
        anchors.top: maxGenerationsToSimulate.bottom
        Text {
            id: stateText
            text: qsTr("StateColumn")
            horizontalAlignment: Text.AlignHCenter
        }
        ListView{
            id: stateView
            width: 200; height: 200
            spacing: 2
            clip: true
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
                    Layout.preferredWidth: 40
                    onClicked:{
                        myInterface.removeStateAutomata(model.number)
                        stateListView.removeItem(model.number)
                        myInterface.removeAllRulesAutomata()
                        ruleListView.removeAllItems()
                    }
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
            width: 200; height: 200
            spacing: 2
            clip: true
            model: ListModel {
                list_var: ruleListView
            }
            delegate: RowLayout{
                Text{
                    text: "Rule" + " " + model.number
                }
                Button{
                    text: "X"
                    Layout.preferredWidth: 40
                    onClicked:{
                        myInterface.removeRuleAutomata(model.number)
                        ruleListView.removeItem(model.number)
                    }
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
            var stateCreationWindow = Qt.createComponent("StateCreationWindow.qml")
            var stateWindow = stateCreationWindow.createObject(automataCreationWindow)
            stateWindow.show()
            if(stateListView.getListCount()<1)
            {
                okButton.enabled=false
                addRule.enabled=false
            }
            if (stateListView.getListCount()>=1)
            {
                okButton.enabled=true
                addRule.enabled=true
            }
        }
    }
    Button {
        anchors.top: ruleList.bottom
        anchors.left: ruleList.left
        id: addRule
        text: qsTr("Add Rule")
        enabled: {
            if(stateListView.getListCount()<1)
                addRule.enabled=false
            if (stateListView.getListCount()>=1)
                addRule.enabled=true
        }

        onClicked: {
            myInterface.cleanRuleCreationWindow()
            if(twoDim.checked){
                if(vonNeumann.checked){
                    var vonNeumannCreationWindow = Qt.createComponent("VonNeumannRuleCreationWindow.qml")
                    var vonNeumannWindow = vonNeumannCreationWindow.createObject(automataCreationWindow)
                    vonNeumannWindow.show()
                }
                if(moore.checked){
                    var mooreCreationWindow = Qt.createComponent("MooreRuleCreationWindow.qml")
                    var mooreWindow = mooreCreationWindow.createObject(automataCreationWindow)
                    mooreWindow.show()
                }
            }
            if(oneDim.checked){
                var oneDimensionCreationWindow = Qt.createComponent("OneDimensionRuleCreationWindow.qml")
                var oneDimensionWindow = oneDimensionCreationWindow.createObject(automataCreationWindow)
                oneDimensionWindow.show()
            }
        }
    }

    Button{
        id: okButton
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        text: qsTr("OK")
        enabled:
        {
            if(stateListView.getListCount()<1)
            {
                okButton.enabled=false
            }
            if (stateListView.getListCount()>=1)
            {
                okButton.enabled=true
            }
        }

        onClicked: {
            myInterface.sendMandatoryInfo()
            myInterface.sizeTheVector()
            matrixview.sizeMatrix(myInterface.sizeX,myInterface.sizeY)
            var matrixCustWindow = Qt.createComponent("MatrixCustomisationWindow.qml")
            var matrixCustomisationWindow = matrixCustWindow.createObject(automataCreationWindow)
            automataCreationWindow.close()
            matrixCustomisationWindow.show()
        }
    }


    Button{
        anchors.bottom: parent.bottom
        text: qsTr("Cancel")
        onClicked:
        {
            ruleListView.removeAllItems()
            stateListView.removeAllItems()
            myInterface.removeAllRulesAutomata()
            myInterface.removeAllStatesAutomata()
            automataCreationWindow.close()
        }
    }
}
