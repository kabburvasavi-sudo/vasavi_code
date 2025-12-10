#include <iostream>
using namespace std;

int logValue[1000];
int sparse[10][1000];
int arr[1000];
int n;

/* --------------------------
        MERGE SORT
---------------------------*/
void mergeSort(int l, int r) {
    if (l >= r) return;

    int mid = (l + r) / 2;

    mergeSort(l, mid);
    mergeSort(mid + 1, r);

    int temp[1000];
    int i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r) {
        if (arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    for (i = l, k = 0; i <= r; i++)
        arr[i] = temp[k++];
}

/* --------------------------
      PREPARE LOG VALUES
---------------------------*/
void buildLog() {
    logValue[1] = 0;

    for (int i = 2; i <= n; i++)
        logValue[i] = logValue[i / 2] + 1;
}

/* --------------------------
      BUILD SPARSE TABLE
---------------------------*/
void buildSparse() {
    int K = logValue[n] + 1;

    for (int i = 0; i < n; i++)
        sparse[0][i] = arr[i];

    for (int k = 1; k < K; k++) {
        for (int i = 0; i + (1 << k) <= n; i++) {
            sparse[k][i] =
                (sparse[k-1][i] < sparse[k-1][i + (1 << (k-1))]) ?
                sparse[k-1][i] : sparse[k-1][i + (1 << (k-1))];
        }
    }
}

/* --------------------------
       RANGE QUERY
---------------------------*/
int rangeQuery(int L, int R) {
    int j = logValue[R - L + 1];

    int x = sparse[j][L];
    int y = sparse[j][R - (1 << j) + 1];

    return (x < y) ? x : y;
}

/* --------------------------
          MAIN
---------------------------*/
int main() {
    n = 7;

    int input[7] = {40,10,55,23,12,90,33};

    for (int i = 0; i < n; i++)
        arr[i] = input[i];

    cout << "Original Data: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    mergeSort(0, n-1);

    cout << "Sorted Data: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    buildLog();
    buildSparse();

    int L = 1, R = 5;

    cout << "Range Query [" << L << "," << R << "] = "
         << rangeQuery(L, R);

    return 0;
}
