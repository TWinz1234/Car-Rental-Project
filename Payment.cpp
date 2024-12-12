#include "Payment.h"
#include <fstream>

using namespace std;

// Static Member
const string Payment::admin_ledger = "admin_ledger.txt";

// Constructors
Payment::Payment() noexcept {}

Payment::Payment(int id, int cardNum, int amount, int secCode, int expDate, const string& billAddress, const string& nameCard)
    : id(id), cardNum(cardNum), amount(amount), secCode(secCode), expDate(expDate), billAddress(billAddress), nameCard(nameCard) {}

// Getters
int Payment::getId() const {
    return id;
}

int Payment::getCardNum() const {
    return cardNum;
}

int Payment::getAmount() const {
    return amount;
}

int Payment::getSecCode() const {
    return secCode;
}

int Payment::getExpDate() const {
    return expDate;
}

string Payment::getBillAddress() const {
    return billAddress;
}

string Payment::getNameCard() const {
    return nameCard;
}

// Setters
void Payment::setId(int id) {
    this->id = id;
}

void Payment::setCardNum(int cardNum) {
    this->cardNum = cardNum;
}

void Payment::setAmount(int amount) {
    this->amount = amount;
}

void Payment::setSecCode(int secCode) {
    this->secCode = secCode;
}

void Payment::setExpDate(int expDate) {
    this->expDate = expDate;
}

void Payment::setBillAddress(const string& billAddress) {
    this->billAddress = billAddress;
}

void Payment::setNameCard(const string& nameCard) {
    this->nameCard = nameCard;
}

// Serialize and Deserialize
void Payment::serialize(ostream& out) const {
    out << id << ' ' << cardNum << ' ' << amount << ' ' << secCode << ' '
        << expDate << ' ' << billAddress << ' ' << nameCard << endl;
}

void Payment::deserialize(istream& in) {
    in >> id >> cardNum >> amount >> secCode >> expDate;
    in.ignore(); // Ignore the trailing whitespace
    getline(in, billAddress, ' ');
    getline(in, nameCard);
}

// Display
void Payment::display() const {
    cout << "ID: " << id << "\n"
         << "Card Number: " << cardNum << "\n"
         << "Amount: " << amount << "\n"
         << "Security Code: " << secCode << "\n"
         << "Expiration Date: " << expDate << "\n"
         << "Billing Address: " << billAddress << "\n"
         << "Name on Card: " << nameCard << endl;
}

// Ledger Operations
void Payment::saveToLedger() const {
    ofstream out(admin_ledger, ios::app);
    if (out.is_open()) {
        serialize(out);
        out.close();
    } else {
        cerr << "Error: Unable to open ledger file for writing." << endl;
    }
}

void Payment::displayPaymentDetails() const {
    cout << "Payment Details:\n";
    display();
}

// Static Member Functions
Payment Payment::add() {
    Payment payment;
    cout << "Enter Payment Details:\n";
    cout << "ID: ";
    cin >> payment.id;
    cout << "Card Number: ";
    cin >> payment.cardNum;
    cout << "Amount: ";
    cin >> payment.amount;
    cout << "Security Code: ";
    cin >> payment.secCode;
    cout << "Expiration Date: ";
    cin >> payment.expDate;
    cin.ignore(); // Ignore the newline character
    cout << "Billing Address: ";
    getline(cin, payment.billAddress);
    cout << "Name on Card: ";
    getline(cin, payment.nameCard);
    payment.saveToLedger();
    return payment;
}

bool Payment::update(int id) {
    // Placeholder for update logic
    cout << "Updating payment with ID: " << id << endl;
    return true;
}
