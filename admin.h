#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include <memory>
#include "BaseCar.h"

// I think this class needs to be modified to make the classes private
// it still works as it is, the logical is just not perfect
class Admin {
private:
    std::vector<std::shared_ptr<BaseCar>> inventory; // Private inventory
    const std::string adminPassword = "admin123";    // Admin password

public:
    Admin();
    bool authenticate(const std::string& password) const;
    void addCar(const std::shared_ptr<BaseCar>& car);
    void listInventory() const;
    void processPayment(double amount) const;
};

#endif
