#include <iostream>

int binarySearch(int *array, int l, int r, int target);

int main() {

    int array[5] = {1, 2, 3, 5, 7};
    int index1 = binarySearch(array, 0, 4, 5);
    int index2 = binarySearch(array, 0, 4, 0);
    std::cout << index1 << ' ' << index2 << '\n';
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
