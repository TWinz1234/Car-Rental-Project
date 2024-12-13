#include "Customer.h"
#include <iostream>
#include <fstream>
using namespace std;

Customer::Customer() : id(0), payment(0), rentedCarID(0), rentalDays(0), totalCost(0.0), rentalID(0) {}

Customer::Customer(int id, string name, string address, string contactNum, double payment)
    : id(id), name(name), address(address), contactNum(contactNum), payment(payment), rentedCarID(0), rentalDays(0), totalCost(0.0), rentalID(0) {}

// setter & getter functions
int Customer::getId() const
{
    return id;
}
void Customer::setId(int id)
{
    this->id = id;
}

string Customer::getName() const
{
    return name;
}
void Customer::setName(string name)
{
    this->name = name;
}

string Customer::getAddress() const
{
    return address;
}
void Customer::setAddress(string address)
{
    this->address = address;
}

string Customer::getContactNum() const
{
    return contactNum;
}
void Customer::setContactNum(string contactNum)
{
    this->contactNum = contactNum;
}

double Customer::getPayment() const
{
    return payment;
}
void Customer::setPayment(double payment)
{
    this->payment = payment;
}

// I don't think we'll end up using these but I'll put them in for now
string Customer::getLicenseNumber() const
{
    return licenseNumber;
}
void Customer::setLicenseNumber(const string& license)
{
    this->licenseNumber = license;
}

string Customer::getDateOfBirth() const
{
    return dateOfBirth;
}
void Customer::setDateOfBirth(const string& dob)
{
    this->dateOfBirth = dob;
}

// Payment setters & getters  
void Customer::setPaymentDetails(const Payment& payment) {
    this->paymentDetails = payment;
}

Payment Customer::getPaymentDetails() const {
    return paymentDetails;
}
int Customer::getRentalID() const {
    return rentalID;
}

int Customer::getRentedCarID() const {
    return rentedCarID;
}

int Customer::getRentalDays() const {
    return rentalDays;
}

double Customer::getTotalCost() const {
    return totalCost;
}

void Customer::setRentalDetails(int carID, int days, double cost, int rentalID) {
    this->rentedCarID = carID;
    this->rentalDays = days;
    this->totalCost = cost;
    this->rentalID = rentalID;
}


// display
void Customer::displayRentalDetails() const {
    cout << "Rental ID: " << rentalID << "\n";
    cout << "Car ID: " << rentedCarID << "\n";
    cout << "Rental Days: " << rentalDays << "\n";
    cout << "Total Cost: $" << totalCost << "\n";
}

void Customer::serialize(ostream& out) const {
    out << id << " " << name << " " << address << " " << contactNum << " " << payment
        << " " << licenseNumber << " " << dateOfBirth << " " << rentedCarID << " "
        << rentalDays << " " << totalCost << " " << rentalID << "\n";
}

void Customer::deserialize(istream& in) {
    if (!(in >> id >> name >> address >> contactNum >> payment >> licenseNumber >> dateOfBirth >> rentedCarID >> rentalDays >> totalCost >> rentalID)) {
        cerr << "Error deserializing Customer data. Input might be malformed.\n";
    }
}


// I had to look this bit up -> serialize for storing
void Customer::saveToFile(const string& fileName, const vector<Customer>& customers) {
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error: Unable to open file for writing: " << fileName << endl;
        return;
    }
    for (const auto& customer : customers) {
        customer.serialize(outFile);
    }
    outFile.close();
    cout << "Customer data saved to file: " << fileName << endl;
}

vector<Customer> Customer::readFromFile(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: File not found. Creating a new file: " << fileName << "\n";
        ofstream outFile(fileName);
        outFile.close();
        return {};
    }

    vector<Customer> customers;
    while (true) {
        Customer customer;
        customer.deserialize(inFile);
        if (!inFile) break;
        customers.push_back(customer);
    }
    inFile.close();

    return customers;
}

void Customer::display() const {
    cout << "Customer ID: " << id << ", Name: " << name
         << ", Address: " << address << ", Contact: " << contactNum
         << ", Payment: $" << payment << ", License: " << licenseNumber
         << ", DOB: " << dateOfBirth << endl;
}

void Customer::displayPaymentDetails() const {
    if (paymentDetails.getCardNum() == 0) {
        cout << "No linked payment details currently.\n";
        return;
    }

    cout << "Payment Details:\n";
    cout << "  Card Number: " << paymentDetails.getCardNum() << "\n";
    cout << "  Name on Card: " << paymentDetails.getNameCard() << "\n";
    cout << "  Billing Address: " << paymentDetails.getBillAddress() << "\n";
    cout << "  Expiration Date: " << paymentDetails.getExpDate() << "\n";
    cout << "  Security Code: " << paymentDetails.getSecCode() << "\n";
}

