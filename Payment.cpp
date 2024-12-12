#include "Payment.h"
#include <iostream>
#include <string>
using namespace std;

const string Payment::admin_ledger = "admin_ledger.txt";
Payment::Payment(){}
Payment::Payment(int id, int cardNum, int amount, int secCode, int expDate, string billAdress, string nameCard){
    this->id = id;
    this->cardNum = cardNum;
    this->amount = amount;
    this->secCode = secCode;
    this->expDate = expDate;
    this->billAdress = billAdress;
    this->nameCard = nameCard;
}
//get
int Payment::getId() const {
    return id;
}
int Payment::getCardNum() const {
    return cardNum;
}
int Payment::getAmount() cosnt{
    return amount;
}
int Payment::getSecCode() const{
    return secCode;
}
 int Payment::getExpDate() const{
    return expDate;
 }
string Payment::getBillAddress() const{
    return billAdress;
}
string Payment::getNameCard() const{
    return nameCard;
}
//set
void Payment::setId(int id){
    this->id = id;
}
void Payment::setCardNum(int cardNum){
    this->cardNum = cardNum;
}
void Payment::setAmount(int amount){
    this->amount = amount;
}
void Payment::setSecCode(int secCode){
    this->secCode = secCode;
}
void Payment::setExpDate(int expDate){
    this->expDate = expDate;
}
 void Payment::setBillAddress(string billAddress){
    this->billAddress = billAddress;
}
void setNameCard(string nameCard){
    this->nameCard = nameCard;
}
