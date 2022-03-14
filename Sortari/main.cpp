#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

ifstream fin("date.txt");

bool Test_Sort(vector<long long> v, int N) {
    for(int i = 1; i < N ; i++) {
        if (v[i] < v[i-1]) {
            return false;
        }
    }
    return true;
}

vector<long long> BubbleSort(vector<long long> v, long long N) {
    for (long long i = 0; i < N - 1; i++)  {
        for (long long j = 0; j < N -i -1; j++) {
            if (v[j] > v[j+1]) {
                swap(v[j], v[j+1]);
            }
        }
    }
    return v;
}

void CountSort(vector<long long> &v, long long N, long long Max) {
    vector<long long> frecv(Max + 1);
    for(long long i = 0; i < N; i++) {
        frecv[v[i]]++;
    }
    v.clear();

    for(long long i = 0; i <= Max; i++) {
        if(frecv[i] != 0) {
            while(frecv[i] != 0) {
                v.push_back(i);
                frecv[i]--;
            }
        }
    }
}

void ShellSort(vector<long long> &v, long long N) {
    int gap = 0;
    while (gap < N) {
        gap = gap * 3 + 1;
    }
    gap = gap / 3;
    while (gap > 0)
    {
        for(int i = gap; i < N; i ++) {
            for(int j = i; j >= gap && v[j] < v[j - gap] ; j = j - gap) {
                swap(v[j], v[j - gap]);
            }
        }
        gap = gap / 3;
    }
}

void Merge(vector<long long> &v, int l, int m, int r) {
    long long i = l;
    long long j = m + 1;
    vector<long long> mg;

    while(i <= m && j <= r) {
        if(v[i] < v[j]) {
            mg.push_back(v[i++]);
        } else {
            mg.push_back(v[j++]);
        }
    }
    while(i <= m) {
        mg.push_back(v[i++]);
    }

    while(j <= r) {
        mg.push_back(v[j++]);
    }
    for(long long i = l; i <= r; i++) {
        v[i] = mg[i-l];
    }
}

void MergeSort(vector<long long> &v, int l, int r) {
    int m;
    if(l < r) {
        m = (l+r)/2;
        MergeSort(v, l, m);
        MergeSort(v, m+1, r);
        Merge(v, l, m, r);
    }
}

void RadixSortB16(vector<long long> &v, long long N) {
    queue<long long> s[16];
    int a;
    for(long long i = 0; i <= 24; i += 4) {
        for(long long j = 0; j < N; j++) {
            s[(v[j]>>i)&15].push(v[j]);
        }
        a = 0;
        for(long long j = 0; j <= 15 && a < N; j++) {
            while(!s[j].empty()) {
                v[a++] = s[j].front();
                s[j].pop();
            }
        }
    }
}

int main()
{
    vector<long long> v;
    int Tests;
    fin >> Tests;

    for(int test = 1; test <= Tests; test++) {
        v.clear();
        long long N, Max;
        fin >> N >> Max;
        cout << "Testul numarul " << test << " cu N = " << N << " si Max = " << Max << "\n";

        for(long long i = 0; i < N; ++i) {
            v.push_back(rand() % Max + 1);
        }
        vector<long long> aux;

// STL Sort Test
        if(N > 9999999999) {
            cout << "STL Eroare: numarul este prea mare! \n";
        }
        else
        {
            aux = v;
            auto inceput = high_resolution_clock::now();
            sort(aux.begin(), aux.end());
            auto final = high_resolution_clock::now();
            if(Test_Sort(aux, N)) {
                auto timp = duration_cast<milliseconds>(final-inceput);
                cout << "STL Sort: OK " << timp.count() << " ms\n";
            }
            else cout << "STL Sort: Not OK \n";
        }

// Bubble Sort Test
        if(N > 99999) {
            cout << "Bubble Sort Eroare: numarul este prea mare! \n";
        }
        else
        {
            auto inceput = high_resolution_clock::now();
            aux = BubbleSort(v, N);
            auto final = high_resolution_clock::now();
            if(Test_Sort(aux, N)) {
                auto timp = duration_cast<milliseconds>(final - inceput);
                cout << "Bubble Sort: OK " << timp.count() << " ms\n";
            }
            else
                cout << "Bubble Sort: Not OK \n";
        }

// Count Sort Test
        aux = v;
        auto inceput = high_resolution_clock::now();
        CountSort(aux, N, Max);
        auto final = high_resolution_clock::now();
        if(Test_Sort(aux, N)) {
            auto timp = duration_cast<milliseconds>(final-inceput);
            cout << "Count Sort: OK " << timp.count() << " ms\n";
        }
        else
            cout << "Count Sort: Not OK \n";

// Shell Sort Test
        if(N > 9999999999) {
            cout << "Shell Sort Eroare: numarul este prea mare! \n";
        }
        else
        {
            aux = v;
            auto inceput = high_resolution_clock::now();
            ShellSort(aux, N);
            auto final = high_resolution_clock::now();
            if(Test_Sort(aux, N)) {
                auto timp = duration_cast<milliseconds>(final-inceput);
                cout << "Shell Sort: OK " << timp.count() << " ms\n";
            }
            else
                cout << "Shell Sort: Not OK \n";
        }

// Merge Sort Test
        if(N > 9999999999) {
            cout << "Merge Sort Eroare: numarul este prea mare!";
        }
        else
        {
            aux = v;
            auto inceput = high_resolution_clock::now();
            MergeSort(aux, 0, N-1);
            auto final = high_resolution_clock::now();
            if(Test_Sort(aux, N)) {
                auto timp = duration_cast<milliseconds>(final-inceput);
                cout << "Merge Sort: OK " << timp.count() << " ms\n";
            }
            else
                cout << "Merge Sort: Not OK \n";
        }

// Radix Sort (Baza 16) Test
        if(N > 9999999999) {
            cout << "Radix Sort Eroare: numarul este prea mare!";
        }
        else
        {
            aux = v;
            auto inceput = high_resolution_clock::now();
            RadixSortB16(aux, N);
            auto final = high_resolution_clock::now();
            if(Test_Sort(aux, N)) {
                auto timp = duration_cast<milliseconds>(final-inceput);
                cout << "Radix Sort: OK " << timp.count() << " ms\n";
            }
            else
                cout << "Radix Sort: Not OK \n";
        }
        cout<<"\n";
    }

    cout <<"-------Testul s-a terminat-------";

    return 0;
}
