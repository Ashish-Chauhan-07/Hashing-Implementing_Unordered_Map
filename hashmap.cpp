#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

template <class K, class V>
class node
{
public:
    K key;
    V value;
    node *next;
    node *prev;

    node()
        : next(NULL) {}

    node(K key_val, V value_val)
        : key(key_val), value(value_val), next(NULL) {}
};

template <class K, class V>
class HashMap
{
public:
    node<K, V> *table[1000];

    HashMap();
    int hash_function(K key);
    void insert(K key, V value);
    void erase(K key);
    bool find(K key);
    V operator[](K key);
};

template <class K, class V>
HashMap<K, V>::HashMap()
{
    for (int i = 0; i < 1000; i++)
        table[i] = NULL;
    //cout << "HashMap initialised" << endl;
}

template <class K, class V>
int HashMap<K, V>::hash_function(K key)
{
    ostringstream input;
    input << key;
    string key_val = input.str();

    unsigned long long hash_val = 5381L;

    for (int i = 0; i < key_val.size(); i++)
    {
        hash_val = ((hash_val * 33) + (int)key_val[i]);
    }

    // int KEY_HASH_MASK = unsigned(-1) >> 1;
    // hash_val = hash_val & KEY_HASH_MASK;

    //cout << "Hash_val : " << hash_val%1000 << "  ";
    return hash_val % 1000;
}

template <class K, class V>
void HashMap<K, V>::insert(K key, V value)
{
    int index = hash_function(key);
    node<K, V> *temp = table[index];

    if (temp == NULL)
    {
        temp = new node<K, V>(key, value);
        temp->prev = table[index];
        table[index] = temp;
        //cout << "Inserted (first node) : " << value << endl;
    }
    else
    {
        if (temp->key == key && temp->value == value)
            return;
        if (temp->key == key && temp->value != value)
        {
            temp->value = value;
            //cout << "Inserted (repeated key) : " << value << endl;
            return;
        }
        while (temp->next)
        {
            if (temp->key == key && temp->value == value)
                return;
            if (temp->key == key && temp->value != value)
            {
                temp->value = value;
                //cout << "Inserted (repeated key) : " << value << endl;
                return;
            }
            temp = temp->next;
        }

        node<K, V> *new_node = new node<K, V>(key, value);
        temp->next = new_node;
        new_node->prev = temp;
        //cout << "Inserted (new key) : " << value << endl;
    }
}

template <class K, class V>
void HashMap<K, V>::erase(K key)
{
    int index = hash_function(key);

    if (table[index] == NULL)
    {
        cout << key << " Not Found" << endl;
        return;
    }

    node<K, V> *temp = table[index];

    if (temp->next == NULL && temp->key == key)
    {
        table[index] = NULL;
        //free(temp);
        cout << "Deleted (First_node) : " << key << endl;
        return;
    }
    else
    {
        while (temp)
        {
            if (temp->key == key)
            {
                node<K, V> *t = temp;
                temp->prev->next = temp->next;
                if (temp->next != NULL)
                    temp->next->prev = temp->prev;
                //free(t);
                cout << "Deleted (From_Chain) : " << key << endl;
                return;
            }
            temp = temp->next;
        }
    }
    return;
}

template <class K, class V>
bool HashMap<K, V>::find(K key)
{
    int index = hash_function(key);

    if (table[index] == NULL)
    {
        //cout << key << " Not Found" << endl;
        return false;
    }

    node<K, V> *temp = table[index];
    while (temp)
    {
        if (temp->key == key)
        {
            //cout << key << " Found" << endl;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template <class K, class V>
V HashMap<K, V>::operator[](K key)
{
    int index = hash_function(key);

    if (table[index] == NULL)
    {
        //cout << "Wrong Key" << endl;
        static V var;
        return var;
    }
    else
    {
        node<K, V> *temp = table[index];
        while (temp)
        {
            if (temp->key == key)
                return temp->value;
            temp = temp->next;
        }
    }
    //cout << "Wrong Key" << endl;
    static V var;
    return var;
}

int main()
{
    HashMap<string, int> M1;

    while (true)
    {
        cout << "\nEnter the integer to perform respective function : \n"
             << "1. INSERT(key, value)\n"
             << "2. ERASE(key)\n"
             << "3. FIND(key)\n"
             << "4. MAP[key]\n";

        cout << "Option : ";
        int option;
        cin >> option;

        string key;
        int value;
        bool find;

        switch (option)
        {
        case 1:
            cout << "Enter (key, value) to be inserted : ";
            cin >> key;
            cin >> value;
            M1.insert(key, value);
            break;

        case 2:
            cout << "Enter what key to delete : ";
            cin >> key;
            M1.erase(key);
            break;

        case 3:
            cout << "Enter what key to search : ";
            cin >> key;
            find = M1.find(key);
            cout << ((find == false) ? "Not Found" : "Found") << endl;
            break;

        case 4:
            cout << "Enter key to find Map[key] : ";
            cin >> key;
            value = M1[key];
            cout << "Value at Key-" << key << " is : " << value << endl;
            break;
        }
    }

    HashMap<int, int> M1;

    while (true)
    {
        cout << "\nEnter the integer to perform respective function : \n"
             << "1. INSERT(key, value)\n"
             << "2. ERASE(key)\n"
             << "3. FIND(key)\n"
             << "4. MAP[key]\n";

        cout << "Option : ";
        int option;
        cin >> option;

        int key;
        int value;
        bool find;

        switch (option)
        {
        case 1:
            cout << "Enter (key, value) to be inserted : ";
            cin >> key;
            cin >> value;
            M1.insert(key, value);
            break;

        case 2:
            cout << "Enter what key to delete : ";
            cin >> key;
            M1.erase(key);
            break;

        case 3:
            cout << "Enter what key to search : ";
            cin >> key;
            find = M1.find(key);
            cout << ((find == false) ? "Not Found" : "Found") << endl;
            break;

        case 4:
            cout << "Enter key to find Map[key] : ";
            cin >> key;
            value = M1[key];
            cout << "Value at Key-" << key << " is : " << value << endl;
            break;
        }
    }

    // cout << "\n---Implementation of Hash map----\n"
    //      << endl;

    //Count of distinct element in every sub-array of size k
    int arr[] = {2, 1, 2, 3, 2, 1, 4, 5};
    int size = 8;
    int k = 3;

    // HashMap<int, int> Map;
    // int dist_elem_count{0};

    // //first window
    // for (int i = 0; i < k; i++)
    // {
    //     int element = arr[i];
    //     int element_count = Map[element];

    //     if (element_count == 0)
    //         dist_elem_count++;

    //     Map.insert(element, element_count + 1);
    // }

    // cout << dist_elem_count << endl;

    // //iterating for further windows
    // for (int i = k; i < size; i++)
    // {
    //     int prev_win_elem = arr[i - k];
    //     int prev_win_elem_count = Map[prev_win_elem];

    //     if (prev_win_elem_count == 1)
    //         dist_elem_count--;

    //     Map.insert(prev_win_elem, prev_win_elem_count - 1);

    //     int element = arr[i];
    //     int element_count = Map[element];

    //     if (element_count == 0)
    //         dist_elem_count++;

    //     Map.insert(element, element_count + 1);

    //     cout << dist_elem_count << endl;
    // }

    return 0;
}