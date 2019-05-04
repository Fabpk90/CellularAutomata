import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3


Flickable{
   id: flick
   property int position: 0
   property int rows: 0
   property int columns: 0

    anchors.fill:parent
  contentHeight: grid.height
  contentWidth: grid.width
  ScrollBar.horizontal: ScrollBar{id: hbar; active: vbar.active; policy:ScrollBar.AlwaysOn  }
  ScrollBar.vertical: ScrollBar{id: vbar; active: hbar.active; policy: ScrollBar.AlwaysOn }
   GridLayout{
      x:position/4
       id:grid
       rows: flick.rows
       columns:flick.columns
       rowSpacing: 0
       columnSpacing: 0

       Repeater{
           model:flick.rows*flick.columns

           Cell{height: 10; width: 10; color:"blue"}
       }


   }
}
