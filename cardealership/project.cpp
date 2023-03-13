// CAR DEALERSHIP - David-Leonard Vilvoi


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Car{

protected:
    string make;
    string model;
    int year;
    double price;

public:
    Car(string make, string model, int year, double price){
        this->make = make;
        this->model = model;
        this->year = year;
        this->price = price;
    }

    virtual void printDetails(){
        cout<<make<<" "<<model<<", "<<year<<", $"<<price;
    }

    virtual double calculateCost(int days){
        return price * days;
    }
};

class ElectricCar : public Car{

private:
    double batteryCapacity;
    double range;

public:
    ElectricCar(string make, string model, int year, double price, double batteryCapacity, double range) :
    Car(make, model, year, price){
        this->batteryCapacity = batteryCapacity;
        this->range = range;
    }

    void printDetails(){
         cout<<make<<" "<<model<<", "<<year<<", $"<<price<<", "<<batteryCapacity<<"kWh battery, "<<range<<" mile range";
    }

    double calculateCost(int days){
        return (price/1000) * days;
    }
};

class GasolineCar : public Car{

private:
    double mpg;

public:
    GasolineCar(string make, string model, int year, double price, double mpg) :
    Car(make, model, year, price){
        this->mpg = mpg;
    }

    void printDetails(){
        cout<<make<<" "<<model<<", "<<year<<", $"<<price<<", "<<mpg<<" mpg";
    }

    double calculateCost(int days){
        return (price/1000) * days;
    }
};

class CarRental{

private:
    Car* car;
    string renterName;
    int rentalDays;

public:

    CarRental(Car* car, string renterName, int rentalDays){
        this->car = car;
        this->renterName = renterName;
        this->rentalDays = rentalDays;
    }

    void printDetails(){
        cout<<"Renter name: "<<renterName<<", ";
        car->printDetails();
    }

    double calculateCost(){
        return car->calculateCost(rentalDays);
    }
};

class CarPurchase{

private:
    Car* car;
    string buyerName;

public:

    CarPurchase(Car* car, string buyerName){
        this->car = car;
        this->buyerName = buyerName;
    }

    void printDetails(){
        cout<<"Buyer name: "<<buyerName<<", ";
        car->printDetails();
    }

    double calculateCost(){
        return car->calculateCost(1000);
    }
};

void classicMenu(){

    cout<<"\nMenu:\n";
    cout<<"1. Client\n";
    cout<<"2. Employee\n";
    cout<<"3. Exit\n";
    cout<<"Your choice: ";
}

void clientMenu(){

    cout<<"Client menu:\n";
    cout<<"1. Purchase a car\n";
    cout<<"2. Rent a car\n";
    cout<<"3. Back\n";
    cout<<"Your choice: ";
}

void employeeMenu(){

    cout<<"Employee menu:\n";
    cout<<"1. Add a new car\n";
    cout<<"2. Erase a car\n";
    cout<<"3. See all the cars\n";
    cout<<"4. Change the password\n";
    cout<<"5. Go back\n";
    cout<<"Your choice: ";
}

void changeEmployeeCode(string employeeCode, string &code){
    //cout<<"Please introduce the code again to gain acces: \n";
    //cin>>employeeCode;
    if(employeeCode == code){
        string password;
        cout<<"Introduce the new password: ";
        cin>>password;
        code = password;
    }
    cout<<"The new password is: "<<code;
}

void deleteCar(vector<Car*> &carInventory, int position){
    carInventory.erase(carInventory.begin() + position);
}

void menu(){
    vector<Car*> carInventory;
    carInventory.push_back(new ElectricCar("Tesla", "Model S", 2022, 80000, 100, 400));
    carInventory.push_back(new GasolineCar("Toyota", "Camry", 2022, 25000, 30));

    string code = "0000";

    bool running = true;
    while(running){
 
        classicMenu();
        int choice;
        cin>>choice;

        switch(choice){
            case 1:{      // 1. client
                bool runningClient = true;
                while(runningClient){
                    clientMenu();
                    int clientChoice;
                    cin>>clientChoice;

                    switch(clientChoice){
                        case 1:{     // 1. purchase
                            int carIndex;
                            string buyerName;
                            cout<<"\nWhich car would you like to purchase?"<<endl;
                            for(int i = 0; i < carInventory.size(); i++){ 
                                cout << i + 1 << ". ";
                                carInventory[i]->printDetails();
                                cout << endl;
                            }
                            cout<<"Enter the index of the car you want to purchase: ";
                            cin>>carIndex;
                            cout<<"Enter your name: ";
                            cin>>buyerName;
                            CarPurchase* purchase = new CarPurchase(carInventory[carIndex - 1], buyerName);
                            purchase->printDetails();
                            cout<<"Total cost: $"<<purchase->calculateCost()<<endl;
                            carInventory.erase(carInventory.begin() + carIndex);

                            break;
                        }
                        case 2:{     // 2. rent
                            int carIndex, rentalDays;
                            string renterName;
                            cout<<"Which car would you like to rent?"<<endl;
                            for(int i=0; i < carInventory.size(); i++){
                                cout<<i + 1<<". ";
                                carInventory[i]->printDetails();
                                cout<<endl;
                            }
                            cout<<"Enter the index of the car you want to rent: ";
                            cin>>carIndex;
                            cout<<"Enter your name: ";
                            cin>>renterName;
                            cout<<"Enter the number of rental days (max 7): ";
                            cin>>rentalDays;
                            if(rentalDays > 7)
                                rentalDays = 7;
                            CarRental* rental = new CarRental(carInventory[carIndex - 1], renterName, rentalDays);
                            rental->printDetails();
                            cout<<"Total cost: $"<<rental->calculateCost()<<endl;
                            break;
                        }
                        case 3:{     // 3. back
                            runningClient = false;
                            cout<<"Going back...\n";
                            break;
                        }
                        default:{
                            cout<<"Incorrect choice. Please try again.\n";
                            break;
                        }
                    }
                }
                break;
            }
            case 2:{      // 2. employee
                bool runningEmployee = true;
                string employeeCode;


                cout<<"Introduce verification code: ";
                cin>>employeeCode;

                if(employeeCode == code){
                    while(runningEmployee){
                        employeeMenu();
                        int employeeChoice;
                        cin>>employeeChoice;

                        switch(employeeChoice){
                            case 1:{     // 1. add a new car
                                string make;
                                string model;
                                int year;
                                double price;
                                cout<<"Is it an electric car or combustion-based one? (press 1 for electric, press 2 for combustion)\n";
                                int ElectricSauPetrol;
                                cin>>ElectricSauPetrol;
                                
                                if(ElectricSauPetrol == 1){
                                    double batteryCapacity;
                                    double range;

                                    cout<<"Introduce the make: "; cin>>make; cout<<endl;
                                    cout<<"Introduce the model: "; cin>>model; cout<<endl;
                                    cout<<"Introduce the year of production: "; cin>>year; cout<<endl;
                                    cout<<"Introduce the price: "; cin>>price; cout<<endl;
                                    cout<<"Introduce the battery capacity: "; cin>>batteryCapacity; cout<<endl;
                                    cout<<"Introduce the range: "; cin>>range; cout<<endl;

                                    carInventory.push_back(new ElectricCar(make, model, year, price, batteryCapacity, range));    
                                }else if (ElectricSauPetrol == 2){
                                    double mpg;

                                    cout<<"Introduce the make: "; cin>>make; cout<<endl;
                                    cout<<"Introduce the model: "; cin>>model; cout<<endl;
                                    cout<<"Introduce the year of production: "; cin>>year; cout<<endl;
                                    cout<<"Introduce the price: "; cin>>price; cout<<endl;
                                    cout<<"Introduce mpg: "; cin>>mpg; cout<<endl;

                                    carInventory.push_back(new GasolineCar(make, model, year, price, mpg));
                                }
                                break;
                            }
                            case 2:{     // 2. erase a car
                                int carIndex;
                                cout<<"Which car would you like to erase?\n";
                                for(int i=0; i < carInventory.size(); i++){
                                    cout<<i + 1<<". ";
                                    carInventory[i]->printDetails();
                                    cout<<endl;
                                }
                                cout<<"Enter the index of the car you want to erase: ";
                                cin>>carIndex;
                                carInventory.erase(carInventory.begin() + carIndex - 1);
                                break;
                            }
                            case 3:{     // 3. see all the cars
                                for(int i = 0; i < carInventory.size(); i++){ 
                                    cout << i + 1 << ". ";
                                    carInventory[i]->printDetails();
                                    cout << endl;
                                }
                                break;
                            }
                            case 4:{     // 4. change the code
                                cout<<"Please introduce the code again to gain acces: \n";
                                cin>>employeeCode;
                                if(employeeCode == code)
                                    changeEmployeeCode(employeeCode, code);
                                break;
                            }
                            case 5:{     // 5. go back
                            
                                runningEmployee = false;
                                cout<<"Going back...\n";
                                break;
                            }
                            default:{
                                cout<<"Incorrect choice. Please try again.\n";
                                break;
                            }
                        }
                    }
                    
                }
                break;
            }
            case 3:{     // 3. exit
                running = false;
                cout<<"Exiting...\n";
                break;
            }
            default:{
                cout<<"Incorrect choice. Please try again.\n";
                break;
            }
        }
    }
}

int main(){
    
    menu();
    return 0;
}
        
            


        
    

