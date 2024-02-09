#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Studentas {
    string name, last_name;
    vector <int> hw_res;
    int exam_res, n;
    float final_res, avg_hw;
};

void readData(vector <Studentas> &stud);
float average(vector <int> &res);
float final(float hw, int exam);

int main() {
    vector <Studentas> studentai;
    readData(studentai);
    return 0;
}

void readData(vector <Studentas> &stud) {
    Studentas stud_var;
    int hw;
    cout << "Vardas: ";
    cin >> stud_var.name;
    cout << "Pavarde: ";
    cin >> stud_var.last_name;
    cout << "n: ";
    cin >> stud_var.n;
    for(int i = 0; i < stud_var.n; i++) {
        cout << "Namu darbo nr. " << i + 1 << " rezultatas: ";
        cin >> hw;
        stud_var.hw_res.push_back(hw);
    };
    cout << "Egzamino rezultatas: ";
    cin >> stud_var.exam_res;

    stud_var.avg_hw = average(stud_var.hw_res);
    cout << stud_var.avg_hw << endl;
    stud.push_back(stud_var);

    stud_var.final_res = final(stud_var.avg_hw, stud_var.exam_res);
    cout << " fin " << stud_var.final_res << endl;

    return;
};

float average(vector <int> &res) {
    int vec_size = res.size();
    int sum = 0;
    for(int i = 0; i < vec_size; i++) {
        sum += res[i];
    };

    if(vec_size > 0) {
        return (float) sum / vec_size;
    }else {
        return 0.0;
    };
};

float final(float hw, int exam) {
    return (float) 0.4 * hw + 0.6 * exam;
}