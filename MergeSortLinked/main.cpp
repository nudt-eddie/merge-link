
/*
* Group Names: Lucas Hom, Felix Chan Lee, Alan Chan
* Assignment : Lab 3
* Course : CS110C
* Last Modified: October 28 2013
*/


#include <iostream>
#include <sstream>
using namespace std;

//Node struct
struct Node 
{
	int number;
	Node *next;
};

void printList(Node*);
void split(Node*, Node*&, Node*&);
Node* mergeList(Node*&, Node*&);
void mergeSort(Node *& head);



int main() {
    stringstream ss;
    int item;
    string input;

    cout << "Enter numbers to be sorted: ";

    getline(cin, input);
    ss << input;

    Node *head = NULL;  //points to the first node
    Node *cur = NULL;   //points to our current node

    //create linked list
    while(ss >> item)
    {
        //temp Node pointer to hold new item
        Node *temp = new Node;

        temp->next = NULL;

        //Setting up head for the first time
        if(head == NULL)
        {
            head = temp;
            cur = temp;
            cur->number = item;
        }
        // if head is not empty, set up new pointers
        else
        {
            cur->next = temp;
            cur->next->number = item;

            //move up cur
            cur = temp;
            cur->next = NULL;
        }
    }
//run mergesort
    mergeSort(head);

    cout << "Sorted numbers: ";
//print out mergesorted list
    printList(head);

    return 0;

}

//Prints out the list passed by a head pointer
//@param head pointer to a list
//@pre head pointer is passed to function
//@post none
void printList(Node* head) {
    for (Node* cur = head; cur != NULL; cur = cur -> next)
    {
        cout << cur -> number << " ";
    }
}


// sorts the link list pointed to by head
// @param splits and sorts the lists into two halves
// @pre: head points to a linked list of items
// @post: head points to a sorted linked list, containing the items
// that were in the original linked list, but in sorted order
void mergeSort(Node *& head)
{
	//run mergesort until list is down to 1 node
	if ( head->next != NULL)
{ 
	Node *h1, *h2;
	h1 = head; h2 = head;
split(head, h1,h2);
mergeSort(h1);
mergeSort(h2);
head = mergeList(h1,h2);
}
}

// returns a pointer to a sorted linked list that results from merging the sorted
// linked lists pointed to by head1 and head2
//@param head1 and head2 are pointers to lists
// @pre: head1 and head2 point to sorted linked lists
// @post: returns a pointer to a sorted linked list containing the nodes
// that used to be in the sorted linked lists pointed to by head1 and head2;
// head1 and head2 are NULL
Node *mergeList(Node*& head1, Node*& head2)
{
    Node* head = NULL;
    Node* cur1 = NULL;
    Node* cur2 = NULL;
    Node* prev = NULL;
    Node* temp = NULL;

//check if first list has lowest x value in node
    if(head1->number < head2->number)
    {
        //head always points to the smallest node
        head = head1;

        //Initial conditions our pointers must meet
        cur2 = head1;   //points to the smaller of the two current nodes

        prev = cur2;    //prev points to the last sorted node

        cur1 = head2;   //points to the larger of the two current nodes
        temp = cur1;    //points to nodes that otherwise would be cut off
    }
    //head2->number < head1->number
//otherwise we will insert nodes into list 2
    else
    {
        //Modified initial conditions
        head = head2;

        cur2 = head2;
        prev = cur2;
        cur1 = head1;
        temp = cur1;
    }

    //when cur1 == NULL, one list is empty
    while(cur1 != NULL)
    {
        if(cur1->number < cur2->number)
        {
            //swaps cur1 and cur2 because cur2 must point to the smaller node
            temp = cur1;
            cur1 = cur2;
            cur2 = temp;
        }
        //in the right order... proceed sorting
        else if(cur2->number <= cur1->number)
        {
            temp = cur2->next;  //holds first node to be broken

            cur2->next = cur1;  //point to the larger node

            // given a condition that it is not the smallest node 
            if(prev != cur2)
            {
                prev->next = cur2;
                prev = cur2;
            }

            cur2 = cur2->next;
            cur1 = temp;
        }
    }

    //cleanup
    head1 = NULL;
    head2 = NULL;
    cur2 = NULL;
    prev = NULL;
    temp = NULL;

    return head;
}

/**
*Splits the list pointed to by head by traversing the list, cur1 at single node increments, and cur2 *at two nodes per iteration
*@param head	Pointer to the head of the list to be split
*	     head1	reference to a pointer
*	     head2	reference to a pointer
*@pre head points to a linked list of items, and head1 and head2 are NULL
*@post head1 points to the head of the first sublist, and head2 points to the head of the second *	* 	 sublist
*/
void split(Node* head, Node*& head1, Node*& head2)
{
    Node* cur1, *cur2, *prev;

    if (head -> next != NULL)
    {
        Node* p = head;

        int count = 0;

        //Gets the length of the list
        while (p != NULL)
        {
            count++;
            p = p->next;
        }

        //For even lengthed lists...
        if(count%2 == 1)
        {
	//Move cur1 at single increments and cur2 at double increments
	//end condition: cur2->next != NULL
            for (cur1 = head, cur2 = head; cur2->next->next != NULL, cur2->next != NULL;
                    cur1 = cur1->next, cur2 = cur2->next->next)
            {}
        }
        //For odd lengthed lists...
        else
        {
	//end condition: cur2->next->next != NULL
            for (cur1 = head, cur2 = head; cur2->next->next != NULL, cur2->next->next != NULL;
                    cur1 = cur1->next, cur2 = cur2->next->next)
            {}
        }

        prev = cur1->next;

        //split the lists
        cur1 -> next = NULL;
        head1 = head;
        head2 = prev;
    }
    //For single node lists
    else
    {
        head1 = head;
        head2 = NULL;
    }
}


