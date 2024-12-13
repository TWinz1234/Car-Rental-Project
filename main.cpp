// Updated main.cpp
#include <iostream>
#include <vector>
#include <memory>
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

    string relativePath = "./data"; // Relative directory for all data files

    vector<Customer> customers = Customer::readFromFile(relativePath + "/customers.txt");
    vector<shared_ptr<BaseCar>> cars = BaseCar::readFromFile(relativePath + "/CarInventory.txt");

    Admin admin;
    admin.setInventory(cars);

    cout << "Loaded " << customers.size() << " customers and " << cars.size() << " cars.\n" << flush;

    int roleChoice;

    while (true) {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> roleChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fix double enter issue

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cout << "Invalid password. Access denied.\n";
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fix double enter issue

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fix double enter issue

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                listCars(cars);
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fix double enter issue
    cout << "Enter Color: ";
    getline(cin, color);

    if (carType == 1) {
        double tankCapacity;
        string fuelType;
        cout << "Enter Fuel Type: ";
        getline(cin, fuelType);
        cout << "Enter Tank Capacity (gallons): ";
        cin >> tankCapacity;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fix double enter issue
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fix double enter issue
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

    // Display header with consistent column spacing
    cout << left << setw(10) << "Car ID" << setw(15) << "Model" << setw(15) << "Make"
         << setw(8) << "Year" << setw(15) << "Price/Day" << setw(10) << "Capacity"
         << setw(10) << "Color" << setw(10) << "Rented" << endl;

    // Add a line separator for better readability
    cout << string(85, '-') << endl;

    // Display each car's details in well-aligned columns
    for (const auto& car : cars) {
        cout << left << setw(10) << car->getCarID()
             << setw(15) << car->getModel()
             << setw(15) << car->getMake()
             << setw(8) << car->getYear()
             << setw(15) << fixed << setprecision(2) << car->getPricePerDay()
             << setw(10) << car->getCapacity()
             << setw(10) << car->getColor()
             << setw(10) << (car->isRented() ? "Yes" : "No") << endl;
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fix double enter issue

    (*it)->setRented(true);
    double totalCost = (*it)->getPricePerDay() * rentalDays;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000, 9999);
    int rentalID = dis(gen);

    cout << "You have rented the following car:\n";
    (*it)->display();
    cout << "Total cost: $" << totalCost << "\n";
    cout << "Rental ID: " << rentalID << "\n";

    Customer newCustomer;
    newCustomer.setId(customers.size() + 1);
    cout << "Enter your details:\n";
    cout << "Name: ";
    string name;
    getline(cin, name);
    newCustomer.setName(name);
    cout << "Contact Number: ";
    string contactNum;
    getline(cin, contactNum);
    newCustomer.setContactNum(contactNum);

    newCustomer.setRentalDetails((*it)->getCarID(), rentalDays, totalCost, rentalID);
    customers.push_back(newCustomer);

    Payment payment = Payment::add();
    payment.saveToLedger();

    cout << "Payment recorded successfully.\n";

    cars.erase(it);
}

void searchCars(const vector<shared_ptr<BaseCar>>& cars) {
    cout << "Enter search criteria (1 = Model, 2 = Capacity): ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cout << "Customer List:\n";
    for (const auto& customer : customers) {
        customer.display();
        cout << "Rental Details:\n";
        customer.displayRentalDetails();
        cout << "Payment Details:\n";
        customer.displayPaymentDetails();
    }
}
