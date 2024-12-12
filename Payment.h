#ifndef PAYMENT_H
#define PAYMENT_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Payment{
    protected:
    static const string admin_ledger;
    int id;
    int cardNum;
    int amount;
    int secCode;
    int expDate;
    string billAddress;
    string nameCard;
    

    //constructors
    public:
    Payment();
    Payment(int,int,int,int,int,string,string);

    //setter and getter functions

    int getId() const;
    void setId(int id);
    int getCardNum() const;
    void setCardNum(int cardNum);
    int getAmount() const;
    void setAmount(int amount);
    int getSecCode() const;
    void setSecCode(int secCode);
    int getExpDate() const;
    void setExpDate(int expDate);
    string getBillAddress() const;
    void setBillAddress(string billAddress);
    string getNameCard() const;
    void setNameCard(string nameCard);

    // Serialize and Deserialize
    void serialize(ostream& out) const;
    void deserialize(istream& in);

    // Overridden Methods
    string getType() const override;
    void serialize(ostream& out) const override;
    void deserialize(istream& in) override;
    void display() const override;

    //Ledger
    void saveToLedger() cosnt;
    void displayPayentDetails() const;
    static Payment add();
    static bool update(int);

}

#endif
