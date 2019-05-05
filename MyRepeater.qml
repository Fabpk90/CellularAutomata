import QtQuick 2.0



Repeater{
    id:repeat
    property int mod:0
    function repeatColor(){
        print("jsp"+this.model)

    }
    property color col: "blue"
    model:repeat.mod

    Cell{id:c;height: 10; width: 10; color: repeat.col;position: index}


}



