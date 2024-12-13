#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <vector>
#include <fstream>
#include "Payment.h"
using namespace std;

class Customer {
private:
    int id;
    string name;
    string address;
    string contactNum;
    double payment;
    string licenseNumber;
    string dateOfBirth;
    int rentedCarID;      
    int rentalDays;       
    double totalCost;     
    int rentalID;         
    Payment paymentDetails;


public:
    Customer();
    Customer(int id, string name, string address, string contactNum, double payment);

    // setters and getters
    int getId() const;
    void setId(int id);
    string getName() const;
    void setName(string name);
    string getAddress() const;
    void setAddress(string address);
    string getContactNum() const;
    void setContactNum(string contactNum);
    double getPayment() const;
    void setPayment(double payment);
    string getLicenseNumber() const;
    void setLicenseNumber(const string& license);
    string getDateOfBirth() const;
    void setDateOfBirth(const string& dob);


    // display 
    void setRentalDetails(int carID, int rentalDays, double totalCost, int rentalID);
    void displayRentalDetails() const;

    // use serialize for output to file, input to read from file
    void serialize(ostream& out) const;
    void deserialize(istream& in);

    // I had to look this part up -> save to file from customer vector 
    static void saveToFile(const string& fileName, const vector<Customer>& customers);
    static vector<Customer> readFromFile(const string& fileName);
    void display() const;

    void displayPaymentDetails() const;

    void setPaymentDetails(const Payment& payment);
    Payment getPaymentDetails() const;

    int getRentalID() const;
    int getRentedCarID() const;
    int getRentalDays() const;
    double getTotalCost() const;


};

#endif // CUSTOMER_H
