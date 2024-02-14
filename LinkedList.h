// ASU CSE310 Spring 2024 Assignment #1
// Name: Nilay Kumar  
// ASU ID: 1225127891
// Description:

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Car represents a Car information
struct Car
{
    string model, make;
    int vin;            //vehicle identification number
    double price;
    struct Car* next;
};

//class LinkedList will contains a linked list of Cars
class LinkedList
{
    private:
        struct Car* head;

    public:
        LinkedList();
        ~LinkedList();
        bool findCar(int aVin);
        bool addCar(string model, string make, int vin, double price);
        bool removeByVin(int aVin);
        bool removeByModelAndMake(string model, string make);
        bool changeCarInfo(int aVin, string newModelAndMake);
        bool updateCarPrice(int aVin, double newPrice);
        void printCarListByMake(string make);
        void printCarList();
        void deleteNodes();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    //add your own code DONE
    //----

    //needs to point to nullptr since the linkedlist is empty
    head = nullptr;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it. 
int carCount = 0; //number of cars to keep track of when printing the output
LinkedList::~LinkedList()
{
	//add your own code DONE
    //----
    
    

    Car* current = head;

//Loop through each item that exists in the Linked List and empty it, by deleting all the nodes.
    while (current != nullptr) {

        Car* nextCar = current->next;
        delete current;

        current = nextCar;
        carCount++;

        current = head;     //reset back to the start incase it doesn't happen

    }

    //shouldn't leave head at current because current doesn't exist
    head = nullptr;


    cout<< "The number of deleted Car is: " << carCount <<"\n";
}

//A function to identify if the parameterized Car is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::findCar(int aVin)
{
	//add your own code DONE
    //----
// maybe check just in case what if the linked list is already empty
    Car* current = head;
    if (head == nullptr) {
        return false;
    }
// loop through the linked list while comparing all the vin to the aVin
    while ( current != nullptr) {
        if (current->vin == aVin) {     //if found, will return true
            return true;
        }

        current = current->next;
        
    }
    return false;       // if not found then just return false;

}



//Creates a new Car and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of Cars by their make and model, i.e.
//first by make, if two cars have same makes, then we will list them by model. Note: each Car
//has a unique vin, the vehicle identification number, but may have the same make and model.
//In case two Cars have same make and model, they should be inserted according to the
//increasing order of their vins.
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addCar(string model, string make, int vin, double price)
{
    //make the car first
    Car* newCar = new Car;
    newCar->model = model;
    newCar->make = make;
    newCar->vin = vin;
    newCar->price = price;
    newCar->next = nullptr; //nullptr because we don't know where we need to put it yet

     //if the Car already exist, return false
     //add your own code DONE
     //----

     Car* current = head;
     //checks for if the car already exists, if it does, returns error message
    if (findCar(vin)) {
        cout << "Duplicated Car. Not added.\n";
        delete newCar;      //free up memory for duplicated cars
        return false;
    }

     //check if list is empty or not
    if (head == nullptr) {
        newCar->next = head;
        head = newCar;
        return true;
    }

    //add your own code DONE
    //----

    //need to make a case where if there's only one item in the linked list
    if (current->next == nullptr) {
        if (make < current->make) {
            newCar->next = head;
            head = newCar;
            return true;
        }
        else if (make == current->make) {
            if (model < current->model) {
                newCar->next = head;
                head = newCar;
                return true;
            }
            else if(model == current->model) {
                if (vin < current->vin) {
                    newCar->next = head;
                    head = newCar;
                    return true;
                }
            }
        }
    }
    current = head;

    //lets add condition for if added node needs to be new head
    if (make < current->make) {
        newCar->next = head;
        head = newCar;
        return true;
    }
    else if (make == current->make) {
        if (model < current->model) {
            newCar->next = head;
            head = newCar;
            return true;
        }
        else if (model == current->model) {
            if (vin < current->vin) {
                newCar->next = head;
                head = newCar;
                return true;
            }
        }
    }

    //loop through and find location to insert 
    //first compare by make, if same, then model, if same, then vin
    current = head;
    while (current->next != nullptr){
        //make is less than the next node, so it should go before the next node
        if (make < current->next->make) {
            newCar->next = current->next;
            current->next = newCar;
            return true;
        }
        //if make is same, check model
        else if(make == current->next->make) {
            if (model < current->next->model) {
                newCar->next = current->next;
                current->next = newCar;
                return true;
            }
            //if model is the same, check vin
            else if (model == current->next->model) {
                if (vin < current->next->vin) {
                    newCar->next = current->next;
                    current->next = newCar;
                    return true;
                }
            }
        }
        current = current->next;
        
    }

    //if new car should be at the end of the list
    current->next = newCar;
    return true;


    
}

//Removes the specified Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeByVin(int aVin)
 {
	//add your own code
    //----

    //lets check for case of an empty list first
    if (head == nullptr) {
        return false;
    }

    //now lets call the findCar function to check if Vin exists
    if (!findCar(aVin)) {
        return false;
    }
    
    // if it does, we can begin our operations, first start with the case if the node to remove is the head
    if (head->vin == aVin) {
        Car* toRemove = head;
        head = head->next;
        delete toRemove;
        return true;
    }

   Car* current = head; 
    //next, the case if the node is not the head
    while (current->next != nullptr) {
        if (current->next->vin == aVin) {
            Car* toRemove = current->next;
            current->next = current->next->next;
            delete toRemove;
            return true;
        }
        else {
            current = current->next;
        }
        
    }
    return false;
 }

//Removes the given Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all Cars with
//the same model and make should be removed from the list.
bool LinkedList::removeByModelAndMake(string model, string make)
{
	//add your own code
    //----

    //once again check if list is empty
    if (head == nullptr) {

        return false;
    }

    //traverse through the array this time instead using factors of make and model
    bool removedSuccessfully = false;       //so I can print out the no such car found

    

    Car* current = head;
    //now check rest of the body
    while (current != nullptr) {
        //check head node
        if (head->model == model && head->make == make) {
            Car* toRemove = head;
            head = head->next;
            delete toRemove;
            removedSuccessfully = true;
        }
        if (current->next != nullptr && current->next->model == model && current->next->make == make) {
            Car* toRemove = current->next;
            current->next = current->next->next;
            delete toRemove;
            removedSuccessfully = true;
        }
        else {
        current = current->next;
        }
    }

    //print out whether it was removed successfully and if not, print the error message
    if (removedSuccessfully == false) {
        cout << "No such Car found.\n";
        return false;
    }
    else {
        return true;
    }
    


}

//Modifies the data of the given Car. Return true if it modifies successfully and
//false otherwise. Note: after changing a Car model and make, the linked list must still
//maintain the alphabetical order.
bool LinkedList::changeCarInfo(int aVin, string newModelAndMake)
{
   //split newModelAndMake string to get model and make accordingly
   //add your own code
   //----


   //check for empty list case
    Car* current = head;
    if (head == nullptr) {
        return false;
    }
   
   //first lets split the model and make
   //find the position of the space
   size_t spacePosition = newModelAndMake.find(' ');

    bool hasFound = false;
    double priceValue;
    string model;
    string make;
    // split up the string
   if (spacePosition != string::npos) {
    model = newModelAndMake.substr(0, spacePosition);
    make = newModelAndMake.substr(spacePosition + 1);
    
    current = head;
    //go through the list and find the VIN
    while (current != nullptr) {
        if (current->vin == aVin) {
            hasFound = true;
            current->model = model;             //update the values if the vin is found
            current->make = make;
            priceValue = current->price;
        }
        
        current = current->next;
    }
    
    
    }

    //We have to ensure alphabetical order still exists
    //Remove the node, and then add it back in using the addCar function
    
    removeByVin(aVin);
    addCar(model, make, aVin, priceValue);

    if (hasFound) {
            return true;
    }
    else {
        return false;
    }
}





bool LinkedList::updateCarPrice(int aVin, double newPrice)
{
	//add your own code
    //----

    //check empty list case
    Car* current = head;
    if (head == nullptr) {
        return false;
    }

    //traverse through the list to find where it is, and then stop on the correct node
    while (current != nullptr && current->vin != aVin) {
        current = current->next;
    }
    //update the value of price
    if (current != nullptr) {
        current->price = newPrice;
        return true;

    }
    //return error message if it's not found
    else {
        cout << "Car is NOT inside the list, cannot change its price.\n";
        return false;
    }



}

//Prints all Cars in the list with the same make.
void LinkedList::printCarListByMake(string make)
{
    //add your own code
    //----
    //check if list is empty
    Car* current = head;
    if (head == nullptr) {
        cout << "The list is empty\n";
        return;
    }

    //loop through the list, and if the make matches, then print all the information about it
    bool found = false;
    while (current != nullptr) {
        if (current->make == make) {
            cout << left    << setw(12) << current->model
                 << left    << setw(12) << current->make
                 << right   << setw(8) << current->vin
                 << setw(10) << fixed << setprecision(2) << current->price << "\n";
            found = true;
        }
        current = current->next;
    }

    //if not found, then return error statement
    if (!found) {
        cout << "No Cars with the specified make found.\n";
    }


 }

//Prints all Cars in the linked list starting from the head node.
void LinkedList::printCarList()
{
    //add your own code
    //----
    //check if list is empty
    Car* current = head;
    if (head == nullptr) {
        cout << "The list is empty\n";
        return;
    }

    //traverse through each item and print it
    while (current != nullptr) {
        cout << left    << setw(12) << current->model
             << left    << setw(12) << current->make
             << right   << setw(8) << current->vin
             << setw(10) << fixed << setprecision(2) << current->price << "\n";
        current = current->next;
    }
}

//need to make one because I'm getting a segmentation fault
void LinkedList::deleteNodes() {
    while (head != nullptr) {
        Car* nextNode = head->next;
        delete head;
        head = nextNode;
        carCount++;
    }
}
