#include <iostream>

int binarySearch(int *array, int l, int r, int target);

int main() {

    int n;
    std::cin >> n;
    int *array = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    int m;
    std::cin >> m;
    int *targets = new int[m];
    for (int i = 0; i < m; i++) {
        std::cin >> targets[i];
    }

    for (int i = 0; i < m; i++) {
        int index = binarySearch(array, 0, n-1, targets[i]);
        index == -1 ? std::cout << "x\n" : std::cout << index << '\n';
    }

    delete[] array;
    delete[] targets;
    return 0;
}

int binarySearch(int *array, int l, int r, int target) {
    while (l <= r) {
        int m = (l+r)/2;
        if (array[m] == target) {
            return m;
        }
        else if (target > array[m]) {
            l = m+1;
        }
        else {
            r = m-1;
        }
    }
    return -1;
}
