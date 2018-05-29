import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import "../buttons"
import "../lists"
import "../bars"
import io.qt.examples.createcards 1.0

Grid{
    columns: 3
    spacing: 20
        Item {

            width: 500; height: 500


            CreateCards {
                    id: createcards
            }
            Component {
                   id: fruitDelegate
                   Text {
                          text: modelData
                          font.pointSize: 25

                   }
               }

               ListView {
                   anchors.fill: parent
                   model: createcards.display(1)
                   delegate: fruitDelegate
               }

    }
        Grid{
            columns: 1
            spacing: 5
            ButtonBar{
                     class_name: "stable"
                     checkable: true
                     model: [
                         {
                             text: 'By Bank Name'
                         },
                         {
                             text: 'By Card Type'
                         }
                           ]
                           onClick: {
                              createcards.sortBy(checkedIndex,1);
                           }

             }
            ButtonBar{
                     class_name: "stable"
                     model: [
                               {
                                   text: 'Export to PDF 🖨️'
                               }
                           ]
                           onClick: {
                               createcards.renderPDF();
                           }

             }
        }








}




