#ifndef PAYMENT_H
#define PAYMENT_H
#include <string>
#include <iostream>
#include <fstream>

class Payment {
protected:
    static const std::string admin_ledger;
    int id;
    long cardNum;
    double amount;
    int secCode;
    int expDate;
    std::string billAddress;
    std::string nameCard;

public:
    // Constructors
    Payment();
    Payment(int id, long cardNum, double amount, int secCode, int expDate, std::string billAddress, std::string nameCard);

    // Setter and Getter Functions
    int getId() const;
    void setId(int id);
    long getCardNum() const;
    void setCardNum(long cardNum);
    double getAmount() const;
    void setAmount(double amount);
    int getSecCode() const;
    void setSecCode(int secCode);
    int getExpDate() const;
    void setExpDate(int expDate);
    std::string getBillAddress() const;
    void setBillAddress(const std::string& billAddress);
    std::string getNameCard() const;
    void setNameCard(const std::string& nameCard);

    // Serialize and Deserialize
    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

    // Displaying Information
    void display() const;

    // Ledger
    void saveToLedger() const;
    void displayPaymentDetails() const;

    // Static Methods
    static Payment add();
    static bool update(int id);
};

#endif
