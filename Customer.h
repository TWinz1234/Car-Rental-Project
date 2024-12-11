#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Customer {
private:
    int id;
    string name;
    string address;
    string contactNum;
    int payment;

public:
    // Constructors
    Customer();
    Customer(int id, string name, string address, string contactNum, int payment);

    // Getter and Setter methods
    int getId() const;
    void setId(int id);
    string getName() const;
    void setName(string name);
    string getAddress() const;
    void setAddress(string address);
    string getContactNum() const;
    void setContactNum(string contactNum);
    int getPayment() const;
    void setPayment(int payment);

    // Serialize and Deserialize
    // ** same as the other file
    void serialize(ostream& out) const;
    void deserialize(istream& in);

    // Static methods for file management
    static void saveToFile(const string& fileName, const vector<Customer>& customers);
    static vector<Customer> readFromFile(const string& fileName);
    void display() const;
};

#endif // CUSTOMER_H
