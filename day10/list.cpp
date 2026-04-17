#include <iostream>
#include <list>
using namespace std;

class Car; // forward declaration
void insert(Car*, int); // insert into the list
void input(void); // takes user input
void display(list<Car*>); // displays all elements
std::list<Car*> carList;

class Car {
public:
    int car_number;
    string car_name;
    Car(int car_number, string car_name) : car_number(car_number), car_name(car_name) {}
};

int main() {
    Car* c1 = new Car(1, "Tata");
    Car* c2 = new Car(2, "Toyota");
    Car* c3 = new Car(3, "Ford");
    carList.push_front(c3);
    carList.push_front(c2);
    carList.push_front(c1);
    display(carList);
    input();
    cout << "------------------------" << endl;
    cout << "Car details after insertion of new node: " << endl;
    display(carList);
    return 0;
}

void display(list<Car*> carList) {
    for (Car* c : carList) {
        cout << "Car details are: " << endl;
        cout << c->car_number << endl;
        cout << c->car_name << endl;
    }
}

void input() {
    int option;
    string car_name;
    int car_number;
    cout << "Enter the car details: " << endl;
    cout << "car_number: " << endl;
    cin >> car_number;
    cout << "car_name: " << endl;
    cin >> car_name;
    Car* c = new Car(car_number, car_name);
    cout << "Where do you want to insert this car details? \n1. In front\n2. In back\n3. In middle" << endl;
    cin >> option;
    insert(c, option);
}

void insert(Car* c, int option) {
    switch (option) {
        case 1:
            carList.push_front(c);
            break;
        case 2:
            carList.push_back(c);
            break;
        case 3: {
            int pos;
            cout << "Enter the position (1--N) where you want to insert the element: " << endl;
            cin >> pos;
            auto it = carList.begin();
            for(int i=1; i < pos && it!=carList.end(); ++i)
            {
                ++it;
            }
            carList.insert(it, c);
            break;
        }
    }
}

