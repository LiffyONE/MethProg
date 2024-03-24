#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <map>
#include <unordered_map>
#include <set>
#include <list>

using namespace std;

struct Camp
{
    string squad;
    string year;
    string name;
    string date;
    string shift_number;

    bool operator==(const Camp& camp) const {
        return this->year == camp.year && this->squad == camp.squad && this->shift_number == camp.shift_number && this->name == camp.name;
    }

    bool operator<(const Camp& camp) const {
        if (this->year == camp.year)
            if (this->squad == camp.squad)
                if (this->shift_number == camp.shift_number)
                    return this->name < camp.name;
                else return this->shift_number < camp.shift_number;
            else return this->squad < camp.squad;
        else return this->year < camp.year;
    }

    bool operator<=(const Camp& camp) const {
        return *this < camp || *this == camp;
    }

    bool operator>(const Camp& camp) const {
        return !(*this <= camp);
    }

    bool operator>=(const Camp& camp) const {
        return !(*this < camp);
    }

    friend ostream& operator<<(ostream& os, const Camp& camp);
};

ostream& operator<<(ostream& os, const Camp& camp)
{
    os << camp.year << ' ' << camp.squad << ' ' << camp.shift_number << ' ' << camp.name;
    return os;
}

vector<Camp> readData(const string& file, int size)
{
    ifstream inputFile(file);
    vector<Camp> result(size);
    if (!inputFile.is_open()) {
        cerr << "Error: Couldn't open file " << file << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++)
    {
        inputFile >> result[i].year;
        inputFile >> result[i].squad;
        inputFile >> result[i].name;
        inputFile >> result[i].date;
        inputFile >> result[i].shift_number;
    }
    inputFile.close();
    return result;
}

struct CampHash {
    size_t operator()(const Camp& record) const {
        return hash<string>()(record.year) ^ hash<string>()(record.squad) ^ hash<string>()(record.name) ^
            hash<string>()(record.date) ^ hash<string>()(record.shift_number);
    }
};

class BinarySearchTree {
private:
    struct Node {
        Camp data;
        Node* left;
        Node* right;
        Node(const Camp& item) : data(item), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const Camp& item) {
        if (!node) {
            node = new Node(item);
            return;
        }

        if (item < node->data)
            insert(node->left, item);
        else
            insert(node->right, item);
    }

    bool search(Node* node, const string& key, Camp& result) const {
        if (!node)
            return false;

        if (node->data.year == key) {
            result = node->data;
            return true;
        }

        if (key < node->data.year)
            return search(node->left, key, result);
        else
            return search(node->right, key, result);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(const Camp& item) {
        insert(root, item);
    }

    bool search(const string& key, Camp& result) const {
        return search(root, key, result);
    }
};

// Хэш-таблица
class HashMap {
private:
    vector<list<Camp>> table;
    int size;

    int hashFunction(const string& key) const {
        int hash = 0;
        for (char c : key)
            hash = (hash * 31 + c) % table.size();
        return hash;
    }

public:
    HashMap(int initialSize) : size(initialSize) {
        table.resize(size);
    }

    void insert(const Camp& record) {
        int index = hashFunction(record.year);
        table[index].push_back(record);
    }

    bool search(const string& key, Camp& result) const {
        int index = hashFunction(key);
        for (const auto& record : table[index]) {
            if (record.year == key) {
                result = record;
                return true;
            }
        }
        return false;
    }
};

void performSearch(const vector<Camp>& records, const set<string>& keys) {
    BinarySearchTree bst;
    HashMap hashmap(100); 

    for (const auto& record : records) {
        bst.insert(record);
        hashmap.insert(record);
    }

    clock_t bst_start = clock();
    for (const auto& key : keys) {
        Camp result;
        bst.search(key, result);
    }
    cout << "Time taken for Binary Search Tree: " << static_cast<double>(clock() - bst_start) / CLOCKS_PER_SEC << " seconds" << endl;

    cout << "Hash Map:" << endl;
    clock_t hashmap_start = clock();
    for (const auto& key : keys) {
        Camp result;
        hashmap.search(key, result);
    }
    cout << "Time taken for Hash Map: " << static_cast<double>(clock() - hashmap_start) / CLOCKS_PER_SEC << " seconds" << endl;
}

void performRedBlackTreeSearch(const vector<Camp>& records, const set<string>& keys) {
    map<string, Camp> red_black_tree;

    for (const auto& record : records) {
        red_black_tree.emplace(record.year, record);
    }

    clock_t rbtree_start = clock();
    for (const auto& key : keys) {
        red_black_tree.find(key);
    }
    cout << "Time taken for Red-Black Tree (std::map): " << static_cast<double>(clock() - rbtree_start) / CLOCKS_PER_SEC << " seconds" << endl;
}

void performAllSearches(const vector<Camp>& records, const set<string>& keys) {
    BinarySearchTree bst;
    clock_t bst_start = clock();
    for (const auto& record : records) {
        bst.insert(record);
    }
    for (const auto& key : keys) {
        Camp result;
        bst.search(key, result);
    }
    cout << "Time taken for Binary Search Tree: " << static_cast<double>(clock() - bst_start) / CLOCKS_PER_SEC << " seconds" << endl;

    HashMap hashmap(100);
    clock_t hashmap_start = clock();
    for (const auto& record : records) {
        hashmap.insert(record);
    }
    for (const auto& key : keys) {
        Camp result;
        hashmap.search(key, result);
    }
    cout << "Time taken for Hash Map: " << static_cast<double>(clock() - hashmap_start) / CLOCKS_PER_SEC << " seconds" << endl;

    performRedBlackTreeSearch(records, keys);
}

void performMultimapSearch(const multimap<string, Camp>& records, const set<string>& keys) {
    cout << "Multimap Search:" << endl;
    clock_t multimap_start = clock();
    for (const auto& key : keys) {
        auto range = records.equal_range(key);
    }
    cout << "Time taken for Multimap Search: " << static_cast<double>(clock() - multimap_start) / CLOCKS_PER_SEC << " seconds" << endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    int sizes[7] = { 100, 500, 1000, 2000, 3000, 5000, 100000 };

    for (auto size : sizes) {
        char buffer[50];
        sprintf_s(buffer, "%d.txt", size);
        vector<Camp> records_vector = readData(buffer, size);
        multimap<string, Camp> records_multimap;

        for (const auto& record : records_vector) {
            records_multimap.emplace(record.name, record);
        }

        set<string> keys; 

        for (const auto& record : records_vector) {
            keys.insert(record.name);
        }

        cout << "Performing search for size: " << size << endl;
        performAllSearches(records_vector, keys);
        performMultimapSearch(records_multimap, keys); 
        cout << endl;
    }
    return 0;
}