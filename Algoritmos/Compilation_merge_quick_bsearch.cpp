#include <iostream>
#include <vector>

using namespace std;

void mergesort(vector<int> &vet, int l, int r);
void merge(vector<int> &vet, int l, int r);

void quicksort(vector<int> &vet, int l, int r);
int partition(vector<int> &vet, int l, int r);
void swap(int &a, int &b);

int binary_search(vector<int> vet, int l, int r, int target);

int main() {

    int n;
    cin >> n;
    vector<int> vet(n);

    for (int i = 0; i < vet.size(); i++) {
        cin >> vet[i];
    }

    quicksort(vet, 0, n-1);

    for (auto x : vet) {
        cout << x << ' ';
    } cout << '\n';
    cout << binary_search(vet, 0, n-1, 2) << '\n';


    return 0;
}

void mergesort(vector<int> &vet, int l, int r) {
    if (l < r) {
        int m = (l+r)/2;
        mergesort(vet, l, m);
        mergesort(vet, m+1, r);
        merge(vet, l, r);
    }
}   
void merge(vector<int> &vet, int l, int r) {
    vector<int> temp;
    for (auto x : vet) {
        temp.push_back(x);
    }
    
    int m = (l+r)/2;
    int i = l;
    int j = m+1;

    for(int curr = l; curr <= r; curr++) {
        if (i == m+1) {
            vet[curr] = temp[j++];
        }
        else if (j > r) {
            vet[curr] = temp[i++];
        }
        else if (temp[i] <= temp[j]) {
            vet[curr] = temp[i++];
        }
        else {
            vet[curr] = temp[j++];
        }
    }
}

void quicksort(vector<int> &vet, int l, int r) {
    if (l < r) {
        int p = partition(vet, l, r);
        quicksort(vet, l, p-1);
        quicksort(vet, p+1, r);
    }
}
int partition(vector<int> &vet, int l, int r) {
    int pivot = vet[l];
    int i = l;
    int j = r+1;

    do {
        do {
            i++;
        } while (vet[i] < pivot && i < r);
        do {
            j--;
        } while(vet[j] > pivot);
        swap(vet[i], vet[j]);
    } while (i < j);
    swap(vet[i], vet[j]);
    swap(vet[l], vet[j]);
    
    return j;
}
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int binary_search(vector<int> vet, int l, int r, int target) {
    while (l <= r) {
        int m = (l+r)/2;
        if (vet[m] == target) {
            return m;
        }
        else if (target > vet[m]) {
            l = m+1;
        }
        else {
            r = m-1;
        }
    }
    return -1;
}
