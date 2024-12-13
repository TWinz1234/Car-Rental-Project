#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>

using namespace std;

class Payment {
private:
    int id;
    int cardNum;
    int amount;
    int secCode;
    string expDate;
    string billAddress;
    string nameCard;

public:
    static const string admin_ledger;

    Payment() noexcept;
    Payment(int id, int cardNum, int amount, int secCode, string expDate, const string& billAddress, const string& nameCard);

    // Getters
    int getId() const;
    int getCardNum() const;
    int getAmount() const;
    int getSecCode() const;
    string getExpDate() const;
    string getBillAddress() const;
    string getNameCard() const;

    // Setters
    void setId(int id);
    void setCardNum(int cardNum);
    void setAmount(int amount);
    void setSecCode(int secCode);
    void setExpDate(string expDate);
    void setBillAddress(const string& billAddress);
    void setNameCard(const string& nameCard);

    // Serialize and Deserialize
    void serialize(ostream& out) const;
    void deserialize(istream& in);

    // Display
    void display() const;

    // Ledger Operations
    void saveToLedger() const;
    void displayPaymentDetails() const;

    // Static Member Functions
    static Payment add();
    static bool update(int id);
};

#endif // PAYMENT_H
