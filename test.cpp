#include <bits/stdc++.h>

using namespace std;

static void load () {
    ifstream inputFile;
    inputFile.open("font.txt");
    double n;
    vector < double > arr;
    for (int i=0; i<512; ++i) {
      for (int j=0; j<512; ++j) {
        inputFile >> n;
        arr.push_back(n);
      }
    }
    int k = 0;
    for (int i=0; i<512; i+=32) {
      for (int j=0; j<512; j+=32) {
        for (int x=i+1-1; x<=i+30+1; ++x) {
          for (int y=j+1-1; y<=j+30+1; ++y) {
            n = arr[x*512+y];
            n=n!=0?1:0;
            cout << n << ' ';
          }
          cout << '\n';
        }
        cout << '\n';
      }
    }
    return;
}

int main (int argc, char** argv) {
    load();
    return 0;
}
