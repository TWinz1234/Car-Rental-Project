#include "Customer.h"
#include <iostream>
#include "admin.h"
#include <fstream> // Required for file operatins
using namespace std;

// Constructors
Customer::Customer() : id(0), payment(0) {}

Customer::Customer(int id, string name, string address, string contactNum, int payment)
    : id(id), name(name), address(address), contactNum(contactNum), payment(payment) {}

// Getter and Setter methods
int Customer::getId() const { return id; }
void Customer::setId(int id) { this->id = id; }

string Customer::getName() const { return name; }
void Customer::setName(string name) { this->name = name; }

string Customer::getAddress() const { return address; }
void Customer::setAddress(string address) { this->address = address; }

string Customer::getContactNum() const { return contactNum; }
void Customer::setContactNum(string contactNum) { this->contactNum = contactNum; }

int Customer::getPayment() const { return payment; }
void Customer::setPayment(int payment) { this->payment = payment; }

// Serialize and Deserialize
void Customer::serialize(ostream& out) const {
    out << id << " " << name << " " << address << " " << contactNum << " " << payment << "\n";
}

void Customer::deserialize(istream& in) {
    in >> id >> name >> address >> contactNum >> payment;
}

// Static methods for file management
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
        cout << "File not found. Creating a new file: " << fileName << "\n";
        ofstream outFile(fileName); // Create an empty file
        outFile.close();
        return {};
    }

    vector<Customer> customers;
    while (!inFile.eof()) {
        Customer customer;
        customer.deserialize(inFile);
        if (inFile) customers.push_back(customer);
    }
    inFile.close();

    return customers;
}

// display customer information
// *** I don't think this is properly displayed in the main function
void Customer::display() const {
    cout << "Customer ID: " << id << ", Name: " << name 
         << ", Address: " << address << ", Contact: " << contactNum 
         << ", Payment: $" << payment << endl;
}

