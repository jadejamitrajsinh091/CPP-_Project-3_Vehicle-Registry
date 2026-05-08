#include <iostream>
#include <vector>
using namespace std;


// ================= BASE CLASS =================

class Vehicle 
{
protected:

    int vehicleID;
    string manufacturer;
    string model;
    int year;

public:

    static int totalVehicles;

    Vehicle() 
    { 
        totalVehicles++; 
    }

    virtual void input()
    {
        cout << "Enter Vehicle ID: ";
        cin >> vehicleID;
        cin.ignore();

        cout << "Enter Manufacturer: ";
        getline(cin, manufacturer);

        cout << "Enter Model: ";
        getline(cin, model);

        cout << "Enter Year: ";
        cin >> year;
    }

    virtual void display()
    {
        cout << "\nVehicle ID: " << vehicleID << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }

    int getID() 
    { 
        return vehicleID;
    }

    virtual ~Vehicle()
    { 
        totalVehicles--; 
    }
};

int Vehicle::totalVehicles = 0;


// ================= CAR =================

class Car : virtual public Vehicle
{
protected:

    string fuelType;

public:

    void input() override
    {
        Vehicle::input();
        cin.ignore();
        
        cout << "Enter Fuel Type: ";
        getline(cin, fuelType);
    }

    void display() override 
    {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << endl;
    }
};


// ================= ELECTRIC CAR =================

class ElectricCar : public Car
{
protected:

    int batteryCapacity;

public:

    void input() override 
    {
        Car::input();
        
        cout << "Enter Battery Capacity: ";
        cin >> batteryCapacity;
    }

    void display() override 
    {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};


// ================= AIRCRAFT =================

class Aircraft : virtual public Vehicle 
{
protected:

    int flightRange;

public:

    void input() override 
    {
        Vehicle::input();
        
        cout << "Enter Flight Range: ";
        cin >> flightRange;
    }

    void display() override 
    {
        Vehicle::display();
        cout << "Flight Range: " << flightRange << " km" << endl;
    }
};


// ================= FLYING CAR =================

class FlyingCar : public Car, public Aircraft 
{
public:

    void input() override 
    {
        cout << "\n--- Flying Car Details ---\n";

        cout << "Enter Vehicle ID: ";
        cin >> Vehicle::vehicleID;
        cin.ignore();

        cout << "Enter Manufacturer: ";
        getline(cin, Vehicle::manufacturer);

        cout << "Enter Model: ";
        getline(cin, Vehicle::model);

        cout << "Enter Year: ";
        cin >> Vehicle::year;
        cin.ignore();
        
        cout << "Enter Fuel Type: ";
        getline(cin, fuelType);

        cout << "Enter Flight Range: ";
        cin >> flightRange;
    }

    void display() override 
    {
        cout << "\n--- Flying Car ---\n";
        cout << "Vehicle ID: " << Vehicle::vehicleID << endl;
        cout << "Manufacturer: " << Vehicle::manufacturer << endl;
        cout << "Model: " << Vehicle::model << endl;
        cout << "Year: " << Vehicle::year << endl;
        cout << "Fuel Type: " << fuelType << endl;
        cout << "Flight Range: " << flightRange << " km" << endl;
    }

    int getID()
    {
        return Vehicle::vehicleID;
    }
};


// ================= SPORTS CAR =================

class SportsCar : public ElectricCar 
{
    int topSpeed;

public:

    void input() override 
    {
        ElectricCar::input();
        cout << "Enter Top Speed: ";
        cin >> topSpeed;
    }

    void display() override 
    {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};


// ================= SUV =================

class SUV : public Car 
{
public:

    void display() override 
    {
        cout << "\n--- SUV ---\n";
        Car::display();
    }
};


// ================= SEDAN =================

class Sedan : public Car 
{
public:

    void display() override 
    {
        cout << "\n--- Sedan ---\n";
        Car::display();
    }
};


// ================= REGISTRY =================

class VehicleRegistry 
{
    vector<Vehicle*> vehicles;

public:

    void addVehicle() 
    {
        int choice;
        cout << "\n1. Car\n2. Electric Car\n3. Aircraft\n4. Sports Car\n5. SUV\n6. Sedan\n7. Flying Car\n";
        cout << "Select Vehicle Type: ";
        cin >> choice;

        Vehicle* v = nullptr;

        switch (choice)
        {
        case 1:
         v = new Car(); 
         break;
         
        case 2:
         v = new ElectricCar(); 
         break;
         
        case 3: 
         v = new Aircraft(); 
         break;
         
        case 4: 
         v = new SportsCar(); 
         break;
         
        case 5: 
         v = new SUV(); 
         break;
         
        case 6: 
         v = new Sedan(); 
         break;
         
        case 7: 
         v = new FlyingCar(); 
         break;
         
        default: 
         cout << "Invalid Choice!\n"; 
         
        return;
        }

        v->input();
        vehicles.push_back(v);
        cout << "Vehicle Added Successfully!\n";
    }

    void displayAll()
    {
        if (vehicles.empty())
        {
            cout << "No Vehicles Found!\n";
            return;
        }

        for (auto v : vehicles) 
        {
            v->display();
        }
    }

    void searchVehicle(int id) 
    {
        for (auto v : vehicles) 
        {
            if (v->getID() == id) 
            {
                cout << "\nVehicle Found:\n";
                v->display();
                return;
            }
        }
        
        cout << "Vehicle Not Found!\n";
    }

    ~VehicleRegistry()
    {
        for (auto v : vehicles)
            delete v;
    }
};


// ================= MAIN =================

int main() 
{
    VehicleRegistry vr;
    int choice, id;

    do {
        cout << "\n===== Vehicle Registry System =====\n";
        cout << "1. Add Vehicle\n";
        cout << "2. Display All\n";
        cout << "3. Search by ID\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1: 
         vr.addVehicle(); 
         break;
        
        case 2: 
         vr.displayAll(); 
         break;
        
        case 3:
            cout << "Enter Vehicle ID: ";
            cin >> id;
            vr.searchVehicle(id);
            break;
            
        case 4: 
         cout << "Thanks For Visiting!\n"; 
         break;
         
        default: 
         cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}