cmake_minimum_required(VERSION 3.30)
project(CarRental3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
        main.cpp
        BaseCar.cpp
        ElectricCar.cpp
        FuelCar.cpp
        Customer.cpp
        admin.cpp
)

# Add header files
set(HEADERS
        BaseCar.h
        ElectricCar.h
        FuelCar.h
        Customer.h
        admin.h
)

# Create the executable
add_executable(CarRental3 ${SOURCES} ${HEADERS})
