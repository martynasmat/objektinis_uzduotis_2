#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Studentas {
    string vardas, pavarde;
    vector <int> nd_rez;
    int egz_rez, n;
    float gal_rez;
};

void readData(vector <Studentas> &stud);

int main() {
    vector <Studentas> studentai;
    readData(studentai);
    return 0;
}

void readData(vector <Studentas> &stud) {
    cout << "Vardas: ";
    cin >> stud[0].vardas;
    cout << "Pavarde: ";
    cin >> stud[0].pavarde;
    cout << "n: ";
    cin >> stud[0].n;
    for(int i = 0; i = stud[0].n; i++) {
        cout << "Namu darbo nr. " << i << " rezultatas: ";
        cin >> stud[0].nd_rez[i];
    };
    cout << "Egzamino rezultatas: ";
    cin >> stud[0].gal_rez;
    return;
};