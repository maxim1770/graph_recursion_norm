#include <fstream>
#include <iostream>  
#include <clocale>
#include <set>
#include <vector>
using namespace std;



bool check_has_student_not_my_team(vector<int> team, int _i) { //проверяем есть ли в команде team студент _i (если есть - true, если нет - false)
    for (int i = 0; i < team.size(); i++) {
        if (team[i] == _i)
            return true;
    }
    return false;
}

bool search_(bool** arr, int n, int i, vector<int>* my_team, vector<int>* not_my_team) {
    if (!check_has_student_not_my_team(*not_my_team, i)) {
        my_team->push_back(i);
        for (int j = 0; j < n; j++)
            if ((i != j) && (arr[i][j] == 0) && !check_has_student_not_my_team(*not_my_team, j))
                if (!search_(arr, n, j, not_my_team, my_team))
                    return false;
        return true;
    }
    else {
        // --------------------
        cout << endl;
        cout << "Студента под номером" << i << "сначала был помещен в одну группу, а потом должен быть помещен в другую. Понятно, что в этом случае задача не имеет решения." << endl;
        for (int __i = 0; __i < my_team->size(); __i++) { // это команда в которй нет i, но мы долншы ее туда перепестить
            cout << my_team->at(__i) << " ";
        }
        cout << endl;
        for (int __i = 0; __i < not_my_team->size(); __i++) { // команда в которй есть i
            cout << not_my_team->at(__i) << " ";
        }
        cout << endl;
        // --------------------
        return false;
    }
}


bool def_(bool** arr, int n, vector<int>* _team1, vector<int>* _team2) {
    int n1 = _team1->size();
    int n2 = _team2->size();
    if (n1 + n2 == n)
    {
        if (!(n1 * 2 < n2 || n2 * 2 < n1)) {
            cout << "\n1-я Команда: ";
            for (int __i = 0; __i < _team1->size(); __i++) {
                cout << _team1->at(__i) << " ";
            }
            cout << "\n2-я Команда: ";
            for (int __i = 0; __i < _team2->size(); __i++) {
                cout << _team2->at(__i) << " ";
            }
            cout << endl;

            return true;
        }
        else {
            cout << "Команды распределились, но одна команда более чем в 2 раза больше другой" << endl;
            cout << "Исправить это не получится, если бы была возможнос, то меньшая группа пополнилась бы на этаме выбора меньшего по размеру вектора(team) (пополнилась бы из векторов imaginary_team1, imaginary_team2)" << endl;
            return false;
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            if ((!check_has_student_not_my_team(*_team1, i)) && (!check_has_student_not_my_team(*_team2, i))) {

                vector<int> imaginary_team1;
                vector<int>* _imaginary_team1 = &imaginary_team1;
                vector<int> imaginary_team2;
                vector<int>* _imaginary_team2 = &imaginary_team2;

                bool imaginary_team_flag = search_(arr, n, i, _imaginary_team1, _imaginary_team2);

                if (!imaginary_team_flag) {
                    return false;
                }

                int imaginary_n1 = _imaginary_team1->size();
                int imaginary_n2 = _imaginary_team2->size();
                if (n1 < n2) {
                    if (imaginary_n1 > imaginary_n2) {
                        _team1->insert(_team1->end(), _imaginary_team1->begin(), _imaginary_team1->end());
                        _team2->insert(_team2->end(), _imaginary_team2->begin(), _imaginary_team2->end());
                    }
                    else {
                        _team1->insert(_team1->end(), _imaginary_team2->begin(), _imaginary_team2->end());
                        _team2->insert(_team2->end(), _imaginary_team1->begin(), _imaginary_team1->end());
                    }
                }
                else {
                    if (imaginary_n1 > imaginary_n2) {
                        _team1->insert(_team1->end(), _imaginary_team2->begin(), _imaginary_team2->end());
                        _team2->insert(_team2->end(), _imaginary_team1->begin(), _imaginary_team1->end());
                    }
                    else {
                        _team1->insert(_team1->end(), _imaginary_team1->begin(), _imaginary_team1->end());
                        _team2->insert(_team2->end(), _imaginary_team2->begin(), _imaginary_team2->end());
                    }
                }
                return def_(arr, n, _team1, _team2);
            }
        }
    }
}


int main()
{
    setlocale(LC_ALL, "rus");

    /*
    Р’С…РѕРґРЅС‹Рµ_РґР°РЅРЅС‹Рµ_1 - СЂР°Р·Р±РёРµРЅРёРµ РІРѕР·РјРѕР¶РЅРѕ!
    Р’С…РѕРґРЅС‹Рµ_РґР°РЅРЅС‹Рµ_2 - С‚Р°РєР°СЏ Р¶Рµ РјР°С‚СЂРёС†Р°, РЅРѕ(4, 7) (7, 4) - 0 - Рё РїРѕСЌС‚РѕРјСѓ СЂР°Р·Р±РёРµРЅРёРµ РЅРµРІРѕР·РјРѕР¶РЅРѕ (РґР»СЏ РїСЂРёРјРµСЂР°)
    Р’С…РѕРґРЅС‹Рµ_РґР°РЅРЅС‹Рµ_3 - СЂР°Р·Р±РёРµРЅРёРµ РІРѕР·РјРѕР¶РЅРѕ!
    Р’С…РѕРґРЅС‹Рµ_РґР°РЅРЅС‹Рµ_4 - СЂР°Р·Р±РёРµРЅРёРµ РІРѕР·РјРѕР¶РЅРѕ!

    Р’С…РѕРґРЅС‹Рµ_РґР°РЅРЅС‹Рµ_1 - СЂР°Р·Р±РёРµРЅРёРµ РІРѕР·РјРѕР¶РЅРѕ!
    СЂР°Р±РѕС‚С‡Р° РјР°С‚СЂРёС†Р° - СЂР°Р·Р±РёРµРЅРёРµ РІРѕР·РјРѕР¶РЅРѕ
    0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
    1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
    1 1 0 0 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1
    1 1 0 0 1 1 1 1 1 0 0 1 1 1 1 1 1 1 0 0
    1 1 1 1 0 1 1 1 0 1 1 1 1 1 1 1 1 1 0 0
    1 1 1 1 1 0 0 1 1 1 1 1 1 1 1 1 1 0 1 1
    1 1 1 1 1 0 0 1 1 0 1 1 1 1 1 1 1 1 1 1
    1 1 0 1 1 1 1 0 0 1 1 0 1 1 1 1 1 1 1 1
    1 1 1 1 0 1 1 0 0 1 1 1 1 1 1 1 1 1 1 1
    1 1 1 0 1 1 0 1 1 0 1 1 1 1 1 1 1 1 1 1
    1 1 1 0 1 1 1 1 1 1 0 1 1 0 0 1 0 1 1 1
    1 1 1 1 1 1 1 0 1 1 1 0 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 1 1 0 1 1
    1 1 1 1 1 1 1 1 1 1 0 1 0 0 1 0 1 1 0 0
    1 1 1 1 1 1 1 1 1 1 0 1 1 1 0 0 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 0 1 1 1
    1 1 1 1 1 0 1 1 1 1 1 1 0 1 1 1 1 0 1 1
    1 1 1 0 0 1 1 1 1 1 1 1 1 0 1 1 1 1 0 1
    1 1 1 0 0 1 1 1 1 1 1 1 1 0 1 1 1 1 1 0

    Р’С…РѕРґРЅС‹Рµ_РґР°РЅРЅС‹Рµ_2 - С‚Р°РєР°СЏ Р¶Рµ РјР°С‚СЂРёС†Р°, РЅРѕ(4, 7) (7, 4) - 0 - Рё РїРѕСЌС‚РѕРјСѓ СЂР°Р·Р±РёРµРЅРёРµ РЅРµРІРѕР·РјРѕР¶РЅРѕ (РґР»СЏ РїСЂРёРјРµСЂР°)
    С‚Р°РєР°СЏ Р¶Рµ РјР°С‚СЂРёС†Р°, РЅРѕ (4,7) (7,4) - 0 - Рё РїРѕСЌС‚РѕРјСѓ СЂР°Р·Р±РёРµРЅРёРµ РЅРµРІРѕР·РјРѕР¶РЅРѕ
    0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
    1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
    1 1 0 0 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1
    1 1 0 0 1 1 1 1 1 0 0 1 1 1 1 1 1 1 0 0
    1 1 1 1 0 1 1 0 0 1 1 1 1 1 1 1 1 1 0 0
    1 1 1 1 1 0 0 1 1 1 1 1 1 1 1 1 1 0 1 1
    1 1 1 1 1 0 0 1 1 0 1 1 1 1 1 1 1 1 1 1
    1 1 0 1 0 1 1 0 0 1 1 0 1 1 1 1 1 1 1 1
    1 1 1 1 0 1 1 0 0 1 1 1 1 1 1 1 1 1 1 1
    1 1 1 0 1 1 0 1 1 0 1 1 1 1 1 1 1 1 1 1
    1 1 1 0 1 1 1 1 1 1 0 1 1 0 0 1 0 1 1 1
    1 1 1 1 1 1 1 0 1 1 1 0 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 1 1 0 1 1
    1 1 1 1 1 1 1 1 1 1 0 1 0 0 1 0 1 1 0 0
    1 1 1 1 1 1 1 1 1 1 0 1 1 1 0 0 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 0 1 1 1
    1 1 1 1 1 0 1 1 1 1 1 1 0 1 1 1 1 0 1 1
    1 1 1 0 0 1 1 1 1 1 1 1 1 0 1 1 1 1 0 1
    1 1 1 0 0 1 1 1 1 1 1 1 1 0 1 1 1 1 1 0

    Р’С…РѕРґРЅС‹Рµ_РґР°РЅРЅС‹Рµ_3 - СЂР°Р·Р±РёРµРЅРёРµ РІРѕР·РјРѕР¶РЅРѕ!
    0 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
    1 0 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1
    1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1
    1 1 1 0 1 0 1 1 1 1 1 1 1 1 1 0 1 1 1 1
    0 1 1 1 0 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1
    1 1 1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 0 1 1
    1 0 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1
    1 1 1 1 1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 0 1 1 1 1
    1 1 1 1 1 1 1 0 1 0 1 1 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 0 0 1
    1 1 1 1 1 1 1 1 1 1 1 0 1 1 0 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 0 0
    1 1 1 1 1 1 1 1 1 1 1 0 1 1 0 1 1 0 1 1
    1 1 1 0 0 1 1 1 0 1 1 1 1 1 1 0 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1
    1 1 0 1 1 0 1 1 1 1 0 1 1 1 0 1 1 0 1 1
    1 1 1 1 1 1 1 1 1 1 0 1 1 0 1 1 1 1 0 1
    1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 0


    Р’С…РѕРґРЅС‹Рµ_РґР°РЅРЅС‹Рµ_4 - СЂР°Р·Р±РёРµРЅРёРµ РІРѕР·РјРѕР¶РЅРѕ!
    0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1
    0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1
    1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0
    1 1 1 0 1 1 1 1 1 0 1 1 1 1 1 0 1 1 0 0
    1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
    1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 0 1 1
    1 1 1 1 1 1 0 1 1 1 1 0 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 0 1 1 1 1 1 0 1 1 0 1 1
    1 1 1 0 1 1 1 1 1 0 1 1 1 1 1 1 0 1 1 1
    1 1 1 1 1 1 1 1 1 1 0 1 1 1 0 0 1 1 1 1
    1 1 1 1 1 1 0 1 1 1 1 0 1 1 1 1 1 0 1 0
    1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 0 1 0 1 1 1 0 1 1 1 1 1
    1 1 1 0 1 1 1 1 1 1 0 1 1 1 1 0 0 1 1 1
    0 1 1 1 1 1 1 1 1 0 1 1 1 1 1 0 0 1 1 1
    1 1 1 1 1 0 1 1 0 1 1 0 1 1 1 1 1 0 1 1
    1 0 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1
    1 1 0 0 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 0
    */
    ifstream fin("Текст.txt");
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла для ввода!" << endl;
        return -1;
    }
    else {
        //размер матрицы инцидентности графа
        int n = 20; //размер графа(матрицы смежности) - количество студентов

        bool** A = new bool* [n];
        for (int i = 0; i < n; i++)
            A[i] = new bool[n];

        char buff[3];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                fin >> buff;
                A[i][j] = atoi(buff);
            }


        cout << "матрица знакомств" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << A[i][j] << " ";
            cout << "\n";
        }

        //команда 1
        vector<int> team1;
        vector<int>* _team1 = &team1;

        //команда 2
        vector<int> team2;
        vector<int>* _team2 = &team2;

        bool team_n = def_(A, n, _team1, _team2);
        if (!team_n)
            cout << "Такой набор студентов не может быть распределен!" << endl;

        for (int i = 0; i < n; i++)
            delete[]A[i];
        delete[]A;

        return 0;
    }
}
