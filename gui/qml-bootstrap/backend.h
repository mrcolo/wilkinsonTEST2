#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QMessageBox>
#include "../../src/parse.h"
#include "../../src/card.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class BackEnd : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString number READ number WRITE verify NOTIFY userNameChanged)


public:
    parse myParser;
    explicit BackEnd(QObject *parent = nullptr)
    {
        myParser.parseAll();
    }

    Q_INVOKABLE QString verify(QString text){
        QMessageBox msgBox;
        string cardToString = text.toUtf8().constData();
        string result;
        if(cardToString.length() == 16){
            if(cardToString[0] == '4'){
                for(int i = 0; i < myParser.myVISA.size();i++)
                    if(stoi(cardToString.substr(0,6)) == myParser.myVISA[i].getBin())
                        result = (string("Type: Visa\n") +string("Company:")+ myParser.myVISA[i].getCompany() +
                                 "\nCard: "+ myParser.myVISA[i].getCardType() +
                                 "\nType: "+ myParser.myVISA[i].getDebitCredit() +
                                 "\nCountry: "+ myParser.myVISA[i].getCountry() +
                                 "\nPhone: "+ myParser.myVISA[i].getPhone());
            }

            if(cardToString[0] == '3'){
                for(int i = 0; i < myParser.myAMEX.size();i++)
                    if(stoi(cardToString.substr(0,6)) == myParser.myAMEX[i].getBin())
                        result = (string("Type: American Express\n")+string("Company: ")+ myParser.myAMEX[i].getCompany() +
                                 "\nCard: "+ myParser.myAMEX[i].getCardType() +
                                 "\nType: "+ myParser.myAMEX[i].getDebitCredit() +
                                 "\nCountry: "+ myParser.myAMEX[i].getCountry() +
                                 "\nPhone: "+ myParser.myAMEX[i].getPhone());
            }
            if(cardToString[0] == '5')
                for(int i = 0; i < myParser.myMS.size();i++)
                    if(stoi(cardToString.substr(0,6)) == myParser.myMS[i].getBin())
                        result = string("Type: American Express\n")+string("Company: ")+ myParser.myMS[i].getCompany() +
                                 "\n"+"Card: " + myParser.myMS[i].getCardType() +
                                 "\n"+"Type: " + myParser.myMS[i].getDebitCredit() +
                                 "\n"+"Country: " + myParser.myMS[i].getCountry() +
                                 "\n"+"Phone: "+ myParser.myMS[i].getPhone();

            QString qstr = QString::fromStdString(result);
            msgBox.setText(qstr);
        }
        else{
              msgBox.setText("Card Not Valid");
        }

        if(!text.isEmpty()){
            msgBox.exec();
        }
    }
};

#endif // BACKEND_H