#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

class linkedListSet {

    struct node {
        int data;
        node *next;
    };

    node *head, *tail; // Objects used to store the current begining and ending of the linked list

public:

    linkedListSet() {
        head = NULL;
        tail = NULL;
    }

    node *get_linkedListSet() {
        return head;
    }

    node *get_linkedListSet_tail() {
        return tail;
    }

    void insert(int value) // Function for inserting new value into the linked list
    {
        node *temp = new node; // Dynamically generated node to store the new data

        temp->data = value;  // We set the value of data variable to the value supplied by user
        temp->next = NULL;

        if (!search(temp->data)) {
            if (head == NULL)  // Check if the linked list is empty
            {
                head = temp;    // temp will be the first node incase the list is empty
                tail = temp;
                tail->next = NULL;
                temp = NULL;
            } else {
                tail->next = temp; // Store the new node at the end of the previous node
                tail = temp;
            }

        } else {
            cout << "Element " << value << " already exists in the set" << endl;
        }
    }

    int search(int value) // function to return the boolean if the value is found or not
    {
        node *temp = new node; // a new node for traversing the list
        temp = head;

        while (temp != NULL) {

            if (temp->data == value) {
                return 1;
            }

            temp = temp->next;

        }

        return 0;

    }

    void delete_element(int search) { // function to delete the supplied value from the list

        node *prev = NULL, *t = NULL; // for traversing the linked list


        for (prev = t = head; t != NULL; prev = t, t = t->next) {
            if (t->data == search) {
                break;
            }
        }

        if (t == NULL) {
            cout << "Element " << search << " doesnot exist in the set" << endl;
        } else {

            if (t == head) {
                head = t->next;
            } else if (t->next == NULL) {
                prev->next = NULL;
            } else {
                prev->next = t->next;
            }

            free(t); // Free up the memory
        }

    }

    void display() // Function for displaying data from the linked list
    {
        node *temp = new node; // a new node for traversing the list
        temp = head;

        cout << "{";

        while (temp != NULL) {
            cout << temp->data << ", ";

            temp = temp->next;
        }

        if (head != NULL) {
            cout << "\b\b}";
        } else {
            cout << " }";
        }
        cout << endl;
    }

    void union_set(linkedListSet set1, linkedListSet set2) {
        node *set1n = set1.get_linkedListSet();
        node *tail1 = set1.get_linkedListSet_tail();
        node *set2n = set2.get_linkedListSet();

        node *tmp = set1n;

        while (tmp != NULL) {
            insert(tmp->data);
            tmp = tmp->next;
        }

        int flag = 0;

        tmp = set1n;

        while (set2n != NULL) {
            flag = 0;
            tmp = set1n;

            while (tmp != NULL) {
                if (tmp->data == set2n->data) {
                    flag++;
                    break;
                }
                tmp = tmp->next;
            }

            if (flag == 0) {
                insert(set2n->data);
            }

            set2n = set2n->next;
        }


    }


    void intersection_set(linkedListSet set1, linkedListSet set2) {
        node *set1n = set1.get_linkedListSet();
        node *set2n = set2.get_linkedListSet();

        node *tmp = set2n;

        int flag = 0;

        while (set1n != NULL) {
            flag = 0;

            set2n = tmp;

            while (set2n != NULL) {
                if (set1n->data == set2n->data) {
                    insert(set1n->data);
                    break;
                }

                set2n = set2n->next;


            }

            set1n = set1n->next;
        }
    }

    void difference_set(linkedListSet set1, linkedListSet set2) {
        node *set1n = set1.get_linkedListSet();
        node *tail1 = set1.get_linkedListSet_tail();
        node *set2n = set2.get_linkedListSet();

        node *tmp = set2n;

        int flag = 0;

        tmp = set1n;

        while (set1n != NULL) {
            flag = 0;
            tmp = set2n;

            while (tmp != NULL) {
                if (tmp->data == set1n->data) {
                    flag++;
                    break;
                }
                tmp = tmp->next;
            }

            if (flag == 0) {
                insert(set1n->data);
            }

            set1n = set1n->next;
        }


    }


};


int main() {

    linkedListSet set1, set2, set3, set4;


    char f1name[100], f2name[100], f3name[100], f4name[100];

    cout << "Enter name of File 1: ";
    cin >> f1name;
    cout << "Enter name of File 2: ";
    cin >> f2name;
    cout << "Enter name of File 3: ";
    cin >> f3name;
    cout << "Enter name of File 4: ";
    cin >> f4name;

    ifstream file1(f1name);
    ifstream file2(f2name);
    ifstream file3(f3name);
    ifstream file4(f4name);

    if (!file1 || !file2 || !file3 || !file4) {
        if (!file1) {
            cout << "File 1 doesnot exisit!" << endl;
        }
        if (!file2) {
            cout << "File 2 doesnot exisit!" << endl;
        }
        if (!file3) {
            cout << "File 3 doesnot exisit!" << endl;
        }
        if (!file4) {
            cout << "File 4 doesnot exisit!" << endl;
        }
    } else {

        int number;

        while (file1 >> number) {
            set1.insert(number);
        }
        file1.close();

        while (file2 >> number) {
            set2.insert(number);
        }
        file2.close();

        while (file3 >> number) {
            set3.insert(number);
        }
        file3.close();

        while (file4 >> number) {
            set4.insert(number);
        }

        file4.close();


        cout << "Set1: ";
        set1.display();
        cout << "Set2: ";
        set2.display();
        cout << "Set3: ";
        set3.display();
        cout << "Set4: ";
        set4.display();

        cout << endl << "----------------------------" << endl << endl;

        linkedListSet u1, d1, i1;

        cout << "EQ1: [((S1 U S4)-S3)^S2] : ";
        u1.union_set(set1, set4);
        d1.difference_set(u1, set3);
        i1.intersection_set(d1, set2);
        i1.display();

        linkedListSet a2, b2, c2, d2, e2;

        cout << "EQ2: [(S1^S2)U((S3-S2)-(S4-S1))] : ";
        a2.intersection_set(set1, set2);
        b2.difference_set(set3, set2);
        c2.difference_set(set4, set1);
        d2.difference_set(b2, c2);
        e2.union_set(a2, d2);
        e2.display();

        linkedListSet a3, b3, c3, d3;

        cout << "EQ3: [S4-S3-S2-S1] : ";
        a3.difference_set(set4, set3);
        b3.difference_set(a3, set2);
        c3.difference_set(b3, set1);
        c3.display();

        linkedListSet a4, b4, c4, d4;

        cout << "EQ4: [(S3U((S1-S3)^(S2US4)))] : ";
        a4.difference_set(set1, set3);
        b4.union_set(set2, set4);
        c4.union_set(set3, a4);
        d4.intersection_set(c4, b4);
        d4.display();

    }

    return 0;
}