#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int TABLE_SIZE = 128;


// HashEntry Class Declaration
class HashEntry { // We will use the value of that place as the key as the elements are unique

public:
    int key;
    int value;

    HashEntry(int key, int value) {
        this->key = key;
        this->value = value;
    }
};


// HashMap Class Declaration
class HashMap {

    vector<int> keymap;
    HashEntry **table;


public:

    HashMap() {
        table = new HashEntry *[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL;
        }
    }

    vector<int> get_vector() {
        return keymap;
    }

    HashEntry **get_table() {
        return table;
    }

    // Hash Function
    int HashFunc(int key) {
        return key % TABLE_SIZE;
    }

    //Insert Element at a key
    void insert(int key) {

        int value = key;

        if (!search(key)) {

            keymap.push_back(key);

            int hash = HashFunc(key);
            while (table[hash] != NULL && table[hash]->key != key) {
                hash = HashFunc(hash + 1);
            }
            if (table[hash] != NULL)
                delete table[hash];
            table[hash] = new HashEntry(key, value);
        } else {
            cout << "Element " << key << " already exists!" << endl;
        }
    }


    // Search Element at a key
    int search(int key) {
        int hash = HashFunc(key);
        while (table[hash] != NULL && table[hash]->key != key) {
            hash = HashFunc(hash + 1);
        }
        if (table[hash] == NULL)
            return 0;
        else
            //  return table[hash]->value;
            return 1;

    }


    void display() {

        cout << "{";

        for (unsigned int i = 0; i < keymap.size(); i++) {
            cout << table[keymap[i]]->value << ", ";
        }

        if (keymap.size() > 0) {
            cout << "\b\b}";
        } else {
            cout << " }";

        }

        cout << endl;

    }

    // Remove Element at a key
    void delete_element(int key) {
        int hash = HashFunc(key);
        while (table[hash] != NULL) {
            if (table[hash]->key == key)
                break;
            hash = HashFunc(hash + 1);
        }
        if (table[hash] == NULL) {
            cout << "Element " << key << " not found" << endl;
            return;
        } else {

            vector<int>::iterator position = find(keymap.begin(), keymap.end(), key);
            if (position != keymap.end()) // == keymap.end() means the element was not found
                keymap.erase(position);


            delete table[hash];
        }
        cout << "Element " << key << " Deleted" << endl;
    }

    void union_set(HashMap &set1, HashMap &set2) {

        vector<int> set1v = set1.get_vector();
        vector<int> set2v = set2.get_vector();

        HashEntry **map1 = set1.get_table();
        HashEntry **map2 = set2.get_table();

        for (int i = 0; i < set1v.size(); ++i) {
            insert(map1[set1v[i]]->value);
        }
        int flag = 0;
        for (int i = 0; i < set2v.size(); ++i) {
            flag = 0;
            for (int j = 0; j < set1v.size(); ++j) {
                if (map1[set1v[j]]->value == map2[set2v[i]]->value) {
                    flag++;
                    break;
                }
            }
            if (flag == 0) {
                insert(map2[set2v[i]]->value);
            }
        }


    }

    void intersection_set(HashMap &set1, HashMap &set2) {

        vector<int> set1v = set1.get_vector();
        vector<int> set2v = set2.get_vector();

        HashEntry **map1 = set1.get_table();
        HashEntry **map2 = set2.get_table();


        int flag = 0;

        for (int i = 0; i < set1v.size(); ++i) {
            flag = 0;
            for (int j = 0; j < set2v.size(); ++j) {
                if (map1[set1v[i]]->value == map2[set2v[j]]->value) {
                    flag++;
                    break;
                }
            }
            if (flag != 0) {
                insert(map1[set1v[i]]->value);
            }
        }


    }

    void difference_set(HashMap &set1, HashMap &set2) {

        vector<int> set1v = set1.get_vector();
        vector<int> set2v = set2.get_vector();

        HashEntry **map1 = set1.get_table();
        HashEntry **map2 = set2.get_table();


        int flag = 0;

        for (int i = 0; i < set1v.size(); ++i) {
            flag = 0;
            for (int j = 0; j < set2v.size(); ++j) {
                if (map1[set1v[i]]->value == map2[set2v[j]]->value) {
                    flag++;
                    break;
                }
            }
            if (flag == 0) {
                insert(map1[set1v[i]]->value);
            }
        }


    }


    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != NULL)
                delete table[i];
            delete[] table;
        }
    }


};


int main() {

    HashMap set1, set2, set3, set4;


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

        HashMap u1, d1, i1;

        cout << "EQ1: [((S1 U S4)-S3)^S2] : ";
        u1.union_set(set1, set4);
        d1.difference_set(u1, set3);
        i1.intersection_set(d1, set2);
        i1.display();

        HashMap a2, b2, c2, d2, e2;

        cout << "EQ2: [(S1^S2)U((S3-S2)-(S4-S1))] : ";
        a2.intersection_set(set1, set2);
        b2.difference_set(set3, set2);
        c2.difference_set(set4, set1);
        d2.difference_set(b2, c2);
        e2.union_set(a2, d2);
        e2.display();

        HashMap a3, b3, c3, d3;

        cout << "EQ3: [S4-S3-S2-S1] : ";
        a3.difference_set(set4, set3);
        b3.difference_set(a3, set2);
        c3.difference_set(b3, set1);
        c3.display();

        HashMap a4, b4, c4, d4;

        cout << "EQ4: [(S3U((S1-S3)^(S2US4)))] : ";
        a4.difference_set(set1, set3);
        b4.union_set(set2, set4);
        c4.union_set(set3, a4);
        d4.intersection_set(c4, b4);
        d4.display();

    }
    return 0;
}