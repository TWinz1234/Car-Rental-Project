#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include "BaseCar.h"
using namespace std;

// I think this class needs to be modified to make the classes private
// it still works as it is, the logical is just not perfect
class Admin {
private:
    // Private inventory & admin password
    vector<shared_ptr<BaseCar>> inventory;
    const string adminPassword = "admin123";

public:
    Admin();
    bool authenticate(const string& password) const;
    void addCar(const shared_ptr<BaseCar>& car);
    void listInventory() const;
    void processPayment(double amount) const;
    void setInventory(vector<shared_ptr<BaseCar>> inv);
};

#endif
