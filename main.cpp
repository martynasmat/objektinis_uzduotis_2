#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

struct Studentas {
    string name, last_name;
    vector <int> hw_res;
    int exam_res, n;
    float final_res, final_hw;
};

void readData(vector <Studentas> &stud, int stud_num, bool use_median);
float average(vector <int> &res);
float median(vector <int> &res);
float final(float hw, int exam);
void printData(vector <Studentas> &stud, int num, bool use_median);

int main() {
    vector <Studentas> students;
    int stud_num;
    bool use_median;
    cout << "Naudoti vidurki ar mediana? (0 - vidurkis, 1 - mediana):";
    cin >> use_median;
    cout << endl;
    cout << "Studentu skaicius:";
    cin >> stud_num;
    readData(students, stud_num, use_median);
    printData(students, stud_num, use_median);
    return 0;
}

void readData(vector <Studentas> &stud, int stud_num, bool use_median) {
    for(int i = 0; i < stud_num; i++) {
        Studentas stud_var;
        int hw;
        cout << "Vardas:";
        cin >> stud_var.name;
        cout << "Pavarde:";
        cin >> stud_var.last_name;
        cout << "n: ";
        cin >> stud_var.n;

        for (int j = 0; j < stud_var.n; j++) {
            cout << "Namu darbo nr. " << j + 1 << " rezultatas:";
            cin >> hw;
            stud_var.hw_res.push_back(hw);
        };
        sort(stud_var.hw_res.begin(), stud_var.hw_res.end());
        cout << "Egzamino rezultatas:";
        cin >> stud_var.exam_res;

        if(use_median) {
            stud_var.final_hw = median(stud_var.hw_res);
        }else {
            stud_var.final_hw = average(stud_var.hw_res);
        };

        stud_var.final_res = final(stud_var.final_hw, stud_var.exam_res);
        stud.push_back(stud_var);
        cout << endl;
    }
};

float average(vector <int> &res) {
    int vec_size = res.size();
    int sum = 0;
    for(int i = 0; i < vec_size; i++) {
        sum += res[i];
    };

    if(vec_size > 0) {
        return (float)sum / (float)vec_size;
    }else {
        return 0.0;
    };
};

float median(vector <int> &res) {
    int vec_size = res.size();
    int size_divided = ceil(vec_size / 2.0);
    if(vec_size > 0) {
        if (vec_size % 2 == 0) {
            cout << (float)(res[size_divided - 1] + res[size_divided]) / 2.0 << endl;
            return (float)(res[size_divided - 1] + res[size_divided]) / 2.0;
        } else {

            return (float)res[size_divided - 1];
        };
    }else {
        return 0.0;
    };
};

float final(float hw, int exam) {
    return 0.4 * hw + 0.6 * exam;
};

void printData(vector <Studentas> &stud, int num, bool use_median) {
    string galutinis = use_median ? "Galutinis (med.)" : "Galutinis (vid.)";
    int width = 20;
    cout << left << setw(width) << "Pavarde";
    cout << left << setw(width) << "Vardas";

    cout << left << setw(width) << galutinis << endl;
    cout << "------------------------------------------------------------" << endl;
    for(int i = 0; i < num; i++) {
        cout << left << setw(width) << stud[i].name;
        cout << left << setw(width) << stud[i].last_name;
        cout << left << setw(width) << fixed << setprecision(2) << stud[i].final_res << endl;
    };
};