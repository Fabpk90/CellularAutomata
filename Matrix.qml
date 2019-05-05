import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3


Item{
    id: item
    anchors.fill:parent
    property int h: 0
    property int rows: 0
    property int columns: 0
    Flickable{
        id: flick

        anchors.fill:item
        contentHeight: grid.height
        contentWidth: grid.width
        ScrollBar.horizontal: ScrollBar{id: hbar; active: vbar.active; policy:ScrollBar.AlwaysOn  }
        ScrollBar.vertical: ScrollBar{id: vbar; active: hbar.active; policy: ScrollBar.AlwaysOn }
        GridLayout{
            x:item.h/4
            id:grid
            rows: item.rows
            columns:item.columns
            rowSpacing: 0
            columnSpacing: 0

       MyRepeater{

            mod:grid.rows*grid.columns


       }


        }
    }

}




