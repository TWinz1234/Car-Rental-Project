#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <filesystem>
#include "BaseCar.h"
#include "FuelCar.h"
#include "ElectricCar.h"
#include "Customer.h"
#include "Payment.h"
#include "admin.h"

using namespace std;

// function protoyping
void displayMainMenu();
void adminMenu(Admin& admin, vector<Customer>& customers, vector<shared_ptr<BaseCar>>& cars);
void customerMenu(vector<shared_ptr<BaseCar>>& cars, vector<Customer>& customers);
void addCar(Admin& admin, vector<shared_ptr<BaseCar>>& cars);
void listCars(const vector<shared_ptr<BaseCar>>& cars);
void rentCar(vector<shared_ptr<BaseCar>>& cars, vector<Customer>& customers);
void searchCars(const vector<shared_ptr<BaseCar>>& cars);
void updateCustomerDisplay(const vector<Customer>& customers);


int main() {
    cout << "Starting Car Rental System...\n" << endl;

    // Relative directory for all data files -> create a data file if it doesn't exist
    // we might need to stay with this because I'm having issues with the text files not saving
    string relativePath = "./data"; 

    vector<Customer> customers = Customer::readFromFile(relativePath + "/customers.txt");
    vector<shared_ptr<BaseCar>> cars = BaseCar::readFromFile(relativePath + "/CarInventory.txt");

    Admin admin;
    admin.setInventory(cars);

    cout << "Loaded " << customers.size() << " customers and " << cars.size() << " cars.\n" << flush;

    int roleChoice;

    // load relevant menu based on main menu input
    while (true) {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> roleChoice;

        if (cin.fail()) {
            cin.clear();
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (roleChoice == 1) {
            customerMenu(cars, customers);
        } else if (roleChoice == 2) {
            string password;
            cout << "Enter admin password: ";
            cin >> password;

            if (admin.authenticate(password)) {
                adminMenu(admin, customers, cars);
            } else {
                cout << "Invalid password. Please re-enter password.\n";
                cin >> passowrd;
            }
        } else if (roleChoice == 3) {
            cout << "Exiting the system. Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

void displayMainMenu() {
    cout << "\nCar Rental System Menu:\n"
         << "1. Customer\n"
         << "2. Admin\n"
         << "3. Exit\n";
}


void adminMenu(Admin& admin, vector<Customer>& customers, vector<shared_ptr<BaseCar>>& cars) {
    int choice;
    do {
        cout << "\nAdmin Menu:\n"
             << "1. View Inventory\n"
             << "2. Add Car to Inventory\n"
             << "3. View Customer Data\n"
             << "4. Exit to Main Menu\n"
             << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                admin.listInventory();
                break;
            case 2:
                addCar(admin, cars);
                break;
            case 3:
                if (customers.empty()) {
                    cout << "No customers available.\n";
                } else {
                    updateCustomerDisplay(customers);
                }
                break;
            case 4:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}


void customerMenu(vector<shared_ptr<BaseCar>>& cars, vector<Customer>& customers) {
    int choice;
    do {
        cout << "\nCustomer Menu:\n"
             << "1. View Cars\n"
             << "2. Rent a Car\n"
             << "3. Search Cars\n"
             << "4. Exit to Main Menu\n"
             << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        switch (choice) {
        case 1:
            listCars(cars); // Use the updated function here
            break;
        case 2:
            rentCar(cars, customers);
            break;
        case 3:
            searchCars(cars);
            break;
        case 4:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}


void addCar(Admin& admin, vector<shared_ptr<BaseCar>>& cars) {
    int carType;
    cout << "Enter Car Type (1 = Fuel, 2 = Electric): ";
    cin >> carType;

    if (cin.fail()) {
        cin.clear();
        cout << "Invalid input.\n";
        return;
    }

    int carID = cars.size() + 1;
    int year, capacity;
    double pricePerDay;
    string model, make, color;

    cout << "Enter Model: ";
    getline(cin, model);
    cout << "Enter Make: ";
    getline(cin, make);
    cout << "Enter Year: ";
    cin >> year;
    cout << "Enter Price Per Day: ";
    cin >> pricePerDay;
    cout << "Enter Capacity: ";
    cin >> capacity;
    cout << "Enter Color: ";
    getline(cin, color);

    if (carType == 1) {
        double tankCapacity;
        string fuelType;
        cout << "Enter Fuel Type: ";
        getline(cin, fuelType);
        cout << "Enter Tank Capacity (gallons): ";
        cin >> tankCapacity;
        auto car = make_shared<FuelCar>(carID, model, make, year, pricePerDay, capacity, color, fuelType, tankCapacity);
        car->setRented(false); // Set default rented status
        cars.push_back(car);
    } else if (carType == 2) {
        double batteryCapacity;
        int rangePerCharge;
        cout << "Enter Battery Capacity (kWh): ";
        cin >> batteryCapacity;
        cout << "Enter Range Per Charge (miles): ";
        cin >> rangePerCharge;
        auto car = make_shared<ElectricCar>(carID, model, make, year, pricePerDay, capacity, color, batteryCapacity, rangePerCharge);
        car->setRented(false); // Set default rented status
        cars.push_back(car);
    } else {
        cout << "Invalid car type.\n";
        return;
    }

    admin.addCar(cars.back());
    cout << "Car added successfully.\n";
}

void listCars(const vector<shared_ptr<BaseCar>>& cars) {
    if (cars.empty()) {
        cout << "No cars available in the inventory.\n";
        return;
    }
    cout << "Cars available for rent:\n";
    for (const auto& car : cars) {
        car->display(); // Display each car's details, including rental status
    }
}


void rentCar(vector<shared_ptr<BaseCar>>& cars, vector<Customer>& customers) {
    if (cars.empty()) {
        cout << "No cars available to rent.\n";
        return;
    }

    string model;
    cout << "Enter the model of the car you want to rent: ";
    getline(cin, model);

    auto it = find_if(cars.begin(), cars.end(), [&model](const shared_ptr<BaseCar>& car) {
        return !car->isRented() && car->getModel() == model;
    });

    if (it == cars.end()) {
        cout << "No available cars with model " << model << ".\n";
        return;
    }

    int rentalDays;
    cout << "Enter the number of days you want to rent the car: ";
    cin >> rentalDays;

    // generate a random number for the rental ID -> between [1000,9999]
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000, 9999);
    int rentalID = dis(gen);

    (*it)->setRented(true);
    double totalCost = (*it)->getPricePerDay() * rentalDays;

    cout << "\nRental Details:\n";
    cout << "Rental ID: " << rentalID << "\n";
    cout << "Car Model: " << (*it)->getModel() << "\n";
    cout << "Rental Days: " << rentalDays << "\n";
    cout << "Total Cost: $" << fixed << setprecision(2) << totalCost << "\n";

    //  Generate Customer ID -> start at 1 if it's blank, otherwise, CustomerID += 1
    int nextCustomerID = 1;
    if (!customers.empty()) {
        nextCustomerID = customers.back().getId() + 1;
    }
    
    string formattedCustomerID = (nextCustomerID < 10 ? "00" : (nextCustomerID < 100 ? "0" : "")) + to_string(nextCustomerID);

    // Initiate and get customer information
    Customer newCustomer;
    string name, address, contactNum;

    cout << "\nEnter your details:\n";
    cout << "Name: ";
    getline(cin, name);
    cout << "Address: ";
    getline(cin, address);
    cout << "Contact Number: ";
    getline(cin, contactNum);

    // use setter functions 
    newCustomer.setId(nextCustomerID);
    newCustomer.setName(name);
    newCustomer.setAddress(address);
    newCustomer.setContactNum(contactNum);
    newCustomer.setRentalDetails((*it)->getCarID(), rentalDays, totalCost, rentalID);

    // Display the genreated Customer ID
    cout << "Assigned Customer ID: " << formattedCustomerID << "\n";

    // Payment Processing
    // / Create and save payment, then link payment to specific customer
    Payment payment = Payment::add(); 
    newCustomer.setPaymentDetails(payment);
    // Push to admin ledger file
    payment.saveToLedger();
    cout << "Payment recorded successfully.\n";

    // Push customer to back of list
    customers.push_back(newCustomer); 
}

void searchCars(const vector<shared_ptr<BaseCar>>& cars) {
    cout << "Enter search criteria (1 = Model, 2 = Capacity): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string model;
        cout << "Enter model to search: ";
        getline(cin, model);
        for (const auto& car : cars) {
            if (car->getModel() == model) {
                car->display();
            }
        }
    } else if (choice == 2) {
        int capacity;
        cout << "Enter capacity to search: ";
        cin >> capacity;
        for (const auto& car : cars) {
            if (car->getCapacity() == capacity) {
                car->display();
            }
        }
    } else {
        cout << "Invalid choice.\n";
    }
}

void updateCustomerDisplay(const vector<Customer>& customers) {
    if (customers.empty()) {
        cout << "No customers found.\n";
        return;
    }

    cout << "Customer List:\n";
    cout << "------------------------------------------------------\n";

    for (const auto& customer : customers) {
        cout << "Customer ID: " << customer.getId() << "\n";
        cout << "Name: " << customer.getName() << "\n";
        cout << "Contact: " << customer.getContactNum() << "\n";

        cout << "Rental Details:\n";
        cout << "  Rental ID: " << customer.getRentalID() << "\n";
        cout << "  Car ID: " << customer.getRentedCarID() << "\n";
        cout << "  Rental Days: " << customer.getRentalDays() << "\n";
        cout << "  Total Cost: $" << fixed << setprecision(2) << customer.getTotalCost() << "\n";

        customer.displayPaymentDetails(); // Call the updated payment details method
        cout << "------------------------------------------------------\n";
    }
}


