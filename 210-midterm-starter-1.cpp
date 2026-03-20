//COMSC-210 | Doubly Linked List | Akashdeep Singh
#include <iostream> // This statement allows cout, cin, and other standard I/O operations to be used
#include <cstdlib>  //this allows the use of rand(), srand()
#include <ctime>    //this allows the use of time() for random seed 
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
        if (!head) return;   // if empty list than nothing to delete

        Node* temp = head; // start searching from head aka the beggining 
        
        while (temp && temp->data != value)   //search for node with matching value 
            temp = temp->next; //move forward until match or end of list 

        if (!temp) return; // value not found 

        if (temp->prev) // fix previous node
            temp->prev->next = temp->next; // if not head previous node skips over temp
        else
            head = temp->next; //if deleting head move head forward

        if (temp->next) //fix next node 
            temp->next->prev = temp->prev; // if not tail, than next node wil skip back over temp
        else
            tail = temp->prev; //if deleting tail than move tail backward

        delete temp;    // free memory of removed node 
    }

    //this entire portion below jsut deletes node by posiition (1-based index)
    void delete_pos(int pos) { 
        if (!head) {
            cout << "List is empty." << endl;   //cant delete from empty list 
            return;
        }
    
        //deleting first node
        if (pos == 1) {
            pop_front();    // reuse function to delete first node
            return;
        }
    
        Node* temp = head;  //start at head
    
        //move to desired position
        for (int i = 1; i < pos; i++){
            if (!temp) {    //ran past end of list
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;  // move forward one node each loop
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        //deleting last node 
        if (!temp->next) {
            pop_back(); // reuse fucntion for last node
            return;
        }
    
        //reconnect neighbors around temp
        Node* tempPrev = temp->prev;    //store pointer to node before temp
        tempPrev->next = temp->next;    //skip temp going forward
        temp->next->prev = tempPrev;    // skip temp going backward
        delete temp;                    //free memory
    }

    // add node to the end of the list 
    void push_back(int v) {
        Node* newNode = new Node(v); // allocate new node
        if (!tail)  // if empty list 
            head = tail = newNode;  // both pointers point to new node 
        else {
            tail->next = newNode;   //old tail points forward to new node 
            newNode->prev = tail;   // new node points backward to old tail
            tail = newNode; // update tail pointer 
        }
    }
    
    //adds node to front of list 
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;   //new node points to old head
            head->prev = newNode;   // old head points back to new node 
            head = newNode; // update head pointer 
        }
    }
    
    // remove first node 
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;   // nothing to remove
            return;
        }

        Node * temp = head; //store node to delete (stores current head)

        if (head->next) {
            head = head->next;  //move head forward
            head->prev = nullptr;   // new head has no previous 
        }
        else
            head = tail = nullptr;  //list had only one node
        delete temp;
    }

    // removes last node 
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;   // nothing to remove 
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
        
        Node* current = head;   //start at first node 

        if (!current) {
            cout << "List is empty." << endl;
            return;
        }

        bool printFlag = true;  // controls printing vs skipping 

        while (current) {

            if (printFlag)
                cout << current->data << " ";   // print current nodes data

            printFlag = !printFlag; //flip true/false each loop

            current = current->next;    // move forward
        }
        cout << endl;
    }

    //destructor that deletes entire list 
    ~DoublyLinkedList() {
        while (head) {  //loop until list is empty
            Node* temp = head;  // store current node 
            head = head->next;  // move head forward
            delete temp;    // delete old node
        }
    }
    //print forward
    void print() {
        Node* current = head;   //start at first node 
        if (!current) {
            cout << "List is empty." << endl;   //nothing ot print 
            return;
        }
        while (current) {
            cout << current->data << " ";   // print node value
            current = current->next;    //move forward
        }
        cout << endl;   // end line
    }

    //print backward
    void print_reverse() {
        Node* current = tail;   //start at last node 
        if (!current) { 
            cout << "List is empty." << endl;   //nothing to print
            return;
        }
        while (current) {
            cout << current->data << " ";   //print node value
            current = current->prev;    // move backward
        }
        cout << endl;   // end line
    }
};

int main() {
    
    srand(time(0)); // seed random generator with current time

    DoublyLinkedList list;  //create empty list object

    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS; // random size between 5 and 20

    // populates list with random values
    for (int i = 0; i < size; i++)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);    //inserts random #'s into list

    cout << "Forward:\n";   // label output
    list.print();   //print list from head to tail 

    cout << "Backward:\n";  // label output
    list.print_reverse();   //print list from tail to head

    cout << "\nEvery other element:\n"; //label output
    list.every_other_element(); // print alternating nodes

    return 0;   // end program
}