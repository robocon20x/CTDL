#include<iostream>
using namespace std;

int main() {
    int n;
    int* a;
    cin >> n;
    a = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) { //    sort
        int min_i = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_i]) {
                min_i = j;
            }           
        }
        int temp = a[i];
        a[i] = a[min_i];
        a[min_i] = temp;
    }

    int* b; // mang de luu cac so xuat hien trong day
    int* c; // mang de luu so lan xuat hien 
    int count = 1; // de dem co cac so khac nhau
   

    for (int i = 0; i < n-1; i++) { // dung de dem cac so khac nhau trong day
        if (a[i] != a[i + 1]) count++;
    }
    b = new int[count];
    c = new int[count];
    for (int i = 0; i < count; i++) {
        c[i] = 1;
    }
    int k = 1; // dung de dem mang b trong vong lap
 
    b[0] = a[0];
    for (int i = 0; i < n - 1; i++) { 
        
        if (a[i] == a[i + 1]) {
            c[k - 1]++;           
        }
        else {
            b[k] = a[i + 1];
            k++;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
    for (int i = 0; i < count; i++) {
        cout << b[i] << " - " << c[i] << "; ";
    }
}