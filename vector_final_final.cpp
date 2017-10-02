#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

class vectorSet {

    vector<int> listVector;

public:

    vector<int> get_listVector() { // Function to return the listVector element as it is a private data member
        return listVector;
    }

    void insert(int value) { // Insert new value inside the set while maintaining uniqueness.
        if (!search(value))
            listVector.push_back(value);
        else
            cout << "Element " << value << " already exists!" << endl;
    }

    int search(int value) { // Search the value - acts as a boolean
        for (int i = 0; i < listVector.size(); ++i) {
            if (value == listVector[i]) {
                return 1;
            }
        }
        return 0;
    }

    void delete_element(int value) { // Delete the element from the set
        int flag = 0;
        for (int i = 0; i < listVector.size(); ++i) {
            if (value == listVector[i]) {
                listVector.erase(listVector.begin() + i);
                flag++;
                break;
            }
        }
        if (flag == 0) {
            cout << "Element " << value << " doesnot exisit in the set" << endl;
        }

    }

    void display() { // Display all the elements in the sets
        cout << "{";
        for (int i = 0; i < listVector.size(); ++i) {
            cout << listVector[i] << ", ";
        }
        if (listVector.size() > 0) {
            cout << "\b\b}";
        } else {
            cout << " }";
        }

        cout << endl;

    }

    void union_set(vectorSet set1, vectorSet set2) { // find the union of two specified set (vectorSet classes)
        vector<int> set1v = set1.get_listVector();
        vector<int> set2v = set2.get_listVector();

        listVector = set1v;

        int flag = 0;

        for (int i = 0; i < set2v.size(); ++i) {

            flag = 0;

            for (int j = 0; j < set1v.size(); ++j) {

                if (set2v[i] == set1v[j]) {
                    flag++;
                    break;
                }
            }
            if (flag == 0) {
                listVector.push_back(set2v[i]);
            }

        }
    }

    void
    intersection_set(vectorSet set1, vectorSet set2) { // find the intersection of two specified set (vectorSet classes)
        vector<int> set1v = set1.get_listVector();
        vector<int> set2v = set2.get_listVector();

        int flag = 0;

        for (int i = 0; i < set1v.size(); ++i) {

            flag = 0;

            for (int j = 0; j < set2v.size(); ++j) {

                if (set2v[j] == set1v[i]) {
                    flag++;
                    break;
                }
            }
            if (flag != 0) {
                listVector.push_back(set1v[i]);
            }

        }
    }

    void
    difference_set(vectorSet set1, vectorSet set2) { // find the difference of two specified set (vectorSet classes)
        vector<int> set1v = set1.get_listVector();
        vector<int> set2v = set2.get_listVector();

        int flag = 0;

        for (int i = 0; i < set1v.size(); ++i) {

            flag = 0;

            for (int j = 0; j < set2v.size(); ++j) {

                if (set2v[j] == set1v[i]) {
                    flag++;
                    break;
                }
            }
            if (flag == 0) {

                listVector.push_back(set1v[i]);
            }
        }
    }

    void clear_class() // clear the whole class
    {
        listVector.clear();
    }


};


int main() {

    vectorSet set1, set2, set3, set4;


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

        vectorSet u1, d1, i1;

        cout << "EQ1: [((S1 U S4)-S3)^S2] : ";
        u1.union_set(set1, set4);
        d1.difference_set(u1, set3);
        i1.intersection_set(d1, set2);
        i1.display();

        vectorSet a2, b2, c2, d2, e2;

        cout << "EQ2: [(S1^S2)U((S3-S2)-(S4-S1))] : ";
        a2.intersection_set(set1, set2);
        b2.difference_set(set3, set2);
        c2.difference_set(set4, set1);
        d2.difference_set(b2, c2);
        e2.union_set(a2, d2);
        e2.display();

        vectorSet a3, b3, c3, d3;

        cout << "EQ3: [S4-S3-S2-S1] : ";
        a3.difference_set(set4, set3);
        b3.difference_set(a3, set2);
        c3.difference_set(b3, set1);
        c3.display();

        vectorSet a4, b4, c4, d4;

        cout << "EQ4: [(S3U((S1-S3)^(S2US4)))] : ";
        a4.difference_set(set1, set3);
        b4.union_set(set2, set4);
        c4.union_set(set3, a4);
        d4.intersection_set(c4, b4);
        d4.display();

    }
    return 0;
}