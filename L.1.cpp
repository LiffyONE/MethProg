#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

struct Camp
{
    string squad;
    string year;
    string name;
    string date;
    string shift_number;

    bool operator == (const Camp& camp)
    {
        return this->year == camp.year && this->squad == camp.squad && this->shift_number == camp.shift_number && this->name == camp.name;
    }

    bool operator < (const Camp& camp)
    {
        if (this->year == camp.year)
            if (this->squad == camp.squad)
                if (this->shift_number == camp.shift_number)
                    return this->name < camp.name;
                else return this->shift_number < camp.shift_number;
            else return this->squad < camp.squad;
        else return this->year < camp.year;
    }

    bool operator <= (const Camp& camp)
    {
        return *this < camp || *this == camp;
    }

    bool operator > (const Camp& camp)
    {
        return !(*this <= camp);
    }

    bool operator >= (const Camp& camp)
    {
        return !(*this < camp);
    }
    friend ostream& operator<<(ostream& os, const Camp& camp);
};

ostream& operator<<(ostream& os, const Camp& camp)
{
    os << camp.year << ' ' << camp.squad << ' ' << camp.shift_number << ' ' << camp.name;
    return os;
}



vector<Camp> readData(string file, int size)
{
    ifstream inputFile(file);
    vector<Camp> result(size);
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

void selectionSort(vector<Camp>& camps) {
    int n = camps.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (camps[j] < camps[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(camps[i], camps[min_idx]);
        }
    }
}


void insertionSort(vector<Camp>& camps) {
    int n = camps.size();
    for (int i = 1; i < n; ++i) {
        Camp key = camps[i];
        int j = i - 1;
        while (j >= 0 && camps[j] > key) {
            camps[j + 1] = camps[j];
            j = j - 1;
        }
        camps[j + 1] = key;
    }
}

void shakerSort(vector<Camp>& camps) {
    int left = 0;
    int right = camps.size() - 1;
    bool swapped;
    do {
        swapped = false;
        for (int i = left; i < right; ++i) {
            if (camps[i] > camps[i + 1]) {
                swap(camps[i], camps[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }

        --right;

        swapped = false;
        for (int i = right; i > left; --i) {
            if (camps[i - 1] > camps[i]) {
                swap(camps[i - 1], camps[i]);
                swapped = true;
            }
        }

        ++left;
    } while (swapped);
}


int main() {
    int sizes[7]{ 100, 500, 1000, 2000, 3000, 5000, 100000 };
    for (auto i : sizes) {
        char buffer[50];
        sprintf_s(buffer, "%d.txt", i);
        vector<Camp> camps1 = readData(buffer, i);
        vector<Camp> camps2 = readData(buffer, i);
        vector<Camp> camps3 = readData(buffer, i);

        clock_t start_time1 = clock();
        selectionSort(camps1);
        clock_t end_time1 = clock();
        cout << "Selection sort " << i << ": " << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC << endl;

        clock_t start_time2 = clock();
        insertionSort(camps2);
        clock_t end_time2 = clock();
        cout << "Insertion sort " << i << ": " << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC << endl;

        clock_t start_time3 = clock();
        shakerSort(camps3);
        clock_t end_time3 = clock();
        cout << "Shaker sort " << i << ": " << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC << endl;

        cout << endl;
        sprintf_s(buffer, "data_%d_sorted.txt", i);
        ofstream outputFile(buffer);
        for (int j = 0; j < camps1.size(); ++j)
            outputFile << camps2[j] << endl;
        outputFile.close();
    }
    return 0;
}
