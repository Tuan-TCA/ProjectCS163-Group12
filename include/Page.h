#include<raylib.h>
#include "Button.h"
#include "Variables.h"
#include<bits/stdc++.h>
#include "InputField.h"
#include "LinkedList.h"
using namespace std;

enum class Operation {
    Insert,
    Create,
    Delete,
    Search,
    Update
};
enum class InputType {
    Random,
    Keyboard,
    File
};
// LL, HashTable, Tree: Insert, Create, Delete, Search
//INSERT, Create, delete, search input operations: keyboard, random, file

class Page {
    private:
    LinkedListNode* headNode;
public:
    Operation currentOperation;
    vector <Button> functions;
    vector<Button> inputOptions;
    //GUI
    MyRec head;
    Rectangle bottom;
    Rectangle side;
    Button Ok;
    TextBox textbox;
   
    ButtonFromImage home, home2;
    Texture2D background1, background2;

    void init();
    void draw();
    void event();

    // virtual void insertOperation() = 0;
    // virtual void createOperation() = 0;
    // virtual void deleteOperation() = 0;
    // virtual void searchOperation() = 0;
};