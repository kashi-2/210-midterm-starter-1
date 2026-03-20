//COMSC-210 | Doubly Linked List | Akashdeep Singh
#include <iostream> // This statement allows cout, cin, and other standard I/O operations to be used
using namespace std; // this allows the use of cout and string without having to write down std:: 

//Below this comment, is the constants used for random # generation
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList { // this line, begins the class that implements the list
private:    // this just marks internal members that are not accessible outside the class
    //Below, node structure which represents one element in the list 
    struct Node {   // this line just defines the node structure
        int data;   // the actual value that is stored in the node
        Node* prev; // pointer to the previous node
        Node* next; //pointer to the next node 
        
        // constructor intializes node values
        Node(int val, Node* p = nullptr, Node* n = nullptr) { //constructor with default pointer values
            data = val; // stores the value in the node 
            prev = p; //sets up previous pointer 
            next = n; // sets up next pointer 
        }   // this ends the constructor 
    };  //this ends the node struct 

    Node* head; // Pointer to first node in the list 
    Node* tail; // Pointer to last node in the list 

public: // this line marks functions accessible outside the class 
    DoublyLinkedList() { head = nullptr; tail = nullptr; }  // this is where the constructor starts, it intializes the empty list, head = nullptr; (this jsut means no first node yet) while the tail version just means no last node yet

    void insert_after(int value, int position) { //inserts after a given position
        if (position < 0) {     //if the position is less than 0 it will output to the user "Position must be >=0."
            cout << "Position must be >= 0." << endl; // prints the error message
            return; //stops function
        } // ends invalid check

        Node* newNode = new Node(value); // creates a new node with the given value 
        if (!head) {    // chekcs if list is empty
            head = tail = newNode;  // new node becomes both head and tail
            return; // this just means the insertion is complete
        } // ends empty list case 

        Node* temp = head; // temp pointer starts at head 
        for (int i = 0; i < position && temp; ++i) //move temp forward position times
            temp = temp->next;  // advances pointer 

        if (!temp) { //checks if position is out of range
            cout << "Position exceeds list size. Node not inserted.\n"; //prints error message everything thats in the " "
            delete newNode; // this just is there to prevent memory leak
            return; // stops function
        }

        newNode->next = temp->next; // new node points to node after temp
        newNode->prev = temp;   // new node points back to temp
        if (temp->next) //checks if insering in the middle 
            temp->next->prev = newNode; //fix next nodes prev pointer 
        else // otherwise inserting at end 
            tail = newNode;
        temp->next = newNode;     // 57 and 58 is basically just updating tail pointer and than links the temp forward to new node 
    } //ends insert_after()

    void delete_val(int value) {  // delete node by value 
        if (!head) return;   // empty list

        Node* temp = head; // start searching from head
        
        while (temp && temp->data != value)   //search for node with matching value 
            temp = temp->next;

        if (!temp) return; // value not found 

        if (temp->prev) // fix previous node
            temp->prev->next = temp->next;
        else
            head = temp->next; //deleting head

        if (temp->next) //fix next node 
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; //deleting tail

        delete temp;    // free memory
    }

    //this entire portion below jsut deletes node by posiition (1-based index)
    void delete_pos(int pos) { 
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        //deleting first node
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        //move to desired position
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        //deleting last node 
        if (!temp->next) {
            pop_back();
            return;
        }
    
        //reconnect neighbors around temp
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    // add node to the end of the list 
    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)  //empty list 
            head = tail = newNode;
        else {
            tail->next = newNode;   //old tail points forward
            newNode->prev = tail;   // new node points back
            tail = newNode; // update tail pointer 
        }
    }
    
    //adds node to front of list 
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;   //new node points forward
            head->prev = newNode;   // old head points back
            head = newNode; // update head
        }
    }
    
    // remove first node 
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; //store current head

        if (head->next) {
            head = head->next;  //move head forward
            head->prev = nullptr;   // new head has no previous 
        }
        else
            head = tail = nullptr;  //only one node 
        delete temp;
    }

    // removes last node 
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;  // move tail backward
            tail->next = nullptr;   // new tail has no next 
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    // New method: prints every other element 
    void every_other_element() {
        
        Node* current = head;

        if (!current) {
            cout << "List is empty." << endl;
            return;
        }

        bool printFlag = true;

        while (current) {

            if (printFlag)
                cout << current->data << " ";

            printFlag = !printFlag; //flip true/false

            current = current->next;
        }
        cout << endl;
    }

    //destructor that deletes entire list 
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    //print forward
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    //print backward
    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    
    srand(time(0)); 

    DoublyLinkedList list;

    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;

    // populates list with random values
    for (int i = 0; i < size; i++)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);

    cout << "Forward:\n";
    list.print();

    cout << "Backward:\n";
    list.print_reverse();

    cout << "\nEvery other element:\n";
    list.every_other_element();
    
    return 0;
}