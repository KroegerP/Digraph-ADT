// Homework 4
// EECE 4040
// Group 3 - Peter Kroeger, Reagan Maddox, Michael Limberg

#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

struct Task {
    Task(int taskNumber, string taskName) : taskNumber(taskNumber), taskName(taskName), next(NULL) {}
    int taskNumber;
    string taskName;
    Task* next;
};

struct OrderPair {
    OrderPair(int firstNum, int secondNum): firstNum(firstNum), secondNum(secondNum) {}
    int firstNum;
    int secondNum;
};

struct Node {
    Node(Task myTask): task(myTask) {}
    Task task;
    Node* next;
};

class Digraph {
    public:
        Digraph(){}
        Digraph(vector<Task*> adjList, vector<OrderPair> myPairs): adjList(adjList), myPairs(myPairs) { CreateDAG(); }
        ~Digraph(){}
        void AddEdge(int src, int dest); //Add edge to the end of the head LL of the source in the adjacency list
        void DelEdge(int src, int dest); //Search for the edge given, remove the edge from the adjacency list
        void CreateDAG();
        void TopologicalSort(); //Implement using DFT, store each task in the sort in a LL
        bool AcyclicCheck();
    private:
        vector<Task*> adjList;
        vector<OrderPair> myPairs;
};

void Digraph::AddEdge(int src, int dest) {
    Task* curNode = adjList[src - 1];
    Task* destNode = adjList[dest - 1];
    while(curNode -> next != NULL) {   //Iterate to the end of the linked list for the src node in the adjacency list
        curNode = curNode -> next;
    }
    curNode -> next = destNode;       //Add the destination node to the linked list chain
    cout << curNode -> taskName << " has a new next from task: " << curNode -> next->taskName << endl;
}

void Digraph::DelEdge(int src, int dest) {
    Task* curNode = adjList[src - 1];
    Task* destNode = adjList[dest - 1];
    while(curNode -> next != destNode) {  //Iterate until the node to be deleted is the next node of the linked list
        curNode = curNode -> next;
    }
    curNode -> next = NULL;                //Set the next node to NULL to remove it from the list
}

void Digraph::CreateDAG() {
    for(int i = 0; i < myPairs.size(); i++) {
        AddEdge(myPairs[i].firstNum, myPairs[i].secondNum);
        if(AcyclicCheck()) {
            DelEdge(myPairs[i].firstNum, myPairs[i].secondNum);
        }
    }
    cout << adjList.size() << endl;
    for(int i = 0; i < adjList.size(); i++) {
        cout << "Task " << i+1 << ": " << adjList[i] -> taskName << " Adj list precedences: " << endl;
        Task* curNode = adjList[i];
        while(curNode -> next != NULL) {
            cout << curNode -> next -> taskNumber << ": " << curNode -> next->taskName << endl;
            curNode = curNode -> next;
        }
    }
}

void Digraph::TopologicalSort() {
    
}

bool Digraph::AcyclicCheck() {
    bool result = false;

    return result;
}


int main() // Test case: run the program involving 8 tasks and associated order relation and submit output of this run
{
    int ans, firstNum, secondNum;
    string curTaskName, taskOrder;

    cout << "How many tasks do you want to input?" << endl;
    cin >> ans;

    // Creates vector adjList of Task type with size that the user inputs
    vector<Task*> adjList;
    string* taskArr = new string[ans];

    // The user sees and interacts with the tasks with numbering 1 through n
    // The back-end sees and interacts with the tasks with numbering 0 throu(n-1)
    for(int i=0; i < ans; i++){
        cout << "Task " << i+1 << ": "; 
        cin >> curTaskName;
        taskArr[i] = curTaskName;
        Task* newTask = new Task(i+1, curTaskName);
        adjList.push_back(newTask);
    }

    vector<OrderPair> myPairs;
    int orderPairAns = 1;

    // Enter the pair relationships for tasks
    while(orderPairAns != 0) {
        cout << "Please input your task order pair as two numbers with a space in between. The order indicates of inputs represents the order the tasks will be done in: ";
        cin >> firstNum >> secondNum;

        // Check validity of pairs
        if(firstNum > 0 && firstNum < (ans + 1) && secondNum > 0 && secondNum < (ans + 1)){
            OrderPair* curPair = new OrderPair(firstNum, secondNum);
            myPairs.push_back(*curPair);
        }
        // else if(cin.fail()) {
        //     cout << "Inputted pair is not valid. Your input has been disregarded." << endl;
        //     cin.clear();
        // }
        else
            cout << "Inputted pair is not valid. Your input has been disregarded." << endl;

        cout << "Do you want to order another task? 1 for Yes 0 for No: ";
        cin >> orderPairAns;
    }

    Digraph* myDigraph = new Digraph(adjList, myPairs);

    myDigraph->TopologicalSort();
    
    return 0;
}