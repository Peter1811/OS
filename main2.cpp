#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <algorithm>
#include <cctype>


using namespace std;

int main(){

    int fd1[2]; // parent -> child_a
    int fd2[2]; // child_a -> child_b
    int fd3[2]; //child_b -> parent
    if ((pipe(fd1) == -1) or (pipe(fd2) == -1) or (pipe(fd3) == -1)) {
        cout << "Error with pipes" << endl;
        return 1;
    }

    int child_a = fork();

    if (child_a == -1) {
        cout << "Error with child_a fork" << endl;
        return 2;
    } else if (child_a == 0) { // Child A code
        close(fd1[1]);        
        close(fd2[0]); 
        close(fd3[0]); 
        close(fd3[1]);
        int kol_a;
        if (read(fd1[0], &kol_a, sizeof(int)) == -1) {
            cout << "Error with reading in child_a" << endl;
            return 5;
        }
        if (write(fd2[1], &kol_a, sizeof(int)) == -1) {
            cout << "Error with writing in child_a" << endl;
            return 5;
        }
        for (int v = 0; v < kol_a; v++){

            int l;
            if (read(fd1[0], &l, sizeof(int)) == -1) {
                cout << "Error with reading child_a" << endl;
                return 5;
            }
            if (write(fd2[1], &l, sizeof(int)) == -1) {
                cout << "Error with writing child_a" << endl;
                return 6;
            }
            char *c = new char[l];
            if (read(fd1[0], c, sizeof(char) * l) == -1) {
                cout << "Error with reading child_a" << endl;
                return 5;
            }

            for (int i = 0; i < l; i++) {
                if (( c[i] >= 'a') and (c[i] <= 'z')) {
                    c[i] = c[i]-'a'+'A';
                }
            }
            if (write(fd2[1], c, sizeof(char) * l) == -1) {
                cout << "Error with writing child_a" << endl;
                return 6;
            }
            delete [] c;
        }

        close(fd1[0]);
        close(fd2[1]);
    
    } else {
        int child_b = fork();
        if (child_b == -1) {
            cout << "Error with child_b fork" << endl;
            return 3;
        } else if (child_b == 0) { //Child B code
            close(fd1[1]); 
            close(fd1[0]); 
            close(fd2[1]); 
            close(fd3[0]);
            int kol_b;
            if (read(fd2[0], &kol_b, sizeof(int)) == -1) {
                cout << "Error with reading in child_b" << endl;
                return 7;
            }
            for (int gh = 0; gh < kol_b; gh++){
                int len_b;
                if (read(fd2[0], &len_b, sizeof(int)) == -1) {
                    cout << "Error with reading in child_b" << endl;
                    return 7;
                }
                if (write(fd3[1], &len_b, sizeof(int)) == -1) {
                    cout << "Error with writing in child_b" << endl;
                    return 8;
                }
                char *c_b = new char[len_b];
                if (read(fd2[0], c_b, sizeof(char) * len_b) == -1) {
                    cout << "Error with reading in child_b" << endl;
                    return 7;
                }
                for (int j = 0; j < len_b; j++) {
                    if (c_b[j] == ' ') {
                        c_b[j] = '_';
                    }
                }
                if (write(fd3[1], c_b, sizeof(char) * len_b) == -1) {
                    cout << "Error with writing in child_b" << endl;
                    return 8;
                }
                delete [] c_b;
            }
            close(fd2[0]);
            close(fd3[1]);
            
            
        } else { //Parent code
            close(fd1[0]);
            close(fd2[1]); 
            close(fd2[0]); 
            close(fd3[1]);
            int k; cin >> k;
            
            if (write(fd1[1], &k, sizeof(int)) == -1) {
                cout << "Error with writing in parent" << endl;
                return 4;
            }
            
            for (int m = 0; m < k; m++) {
                string new_s;
                char c;
                while ((c = getchar()) != EOF){
                    new_s += c;
                }
                int t = new_s.length();
                if (write(fd1[1], &t, sizeof(int)) == -1) {
                    cout << "Error with writing in parent" << endl;
                    return 4;
                }
                if (write(fd1[1], new_s.c_str(), sizeof(char) * t) == -1) {
                    cout << "Error with writing in parent" << endl;
                    return 4;
                }
            }
            
            for (int p = 0; p < k; p++) {
                int len_p;
                if (read(fd3[0], &len_p, sizeof(int)) == -1) {
                    cout << "Error with writing in child_b";
                    return 9;
                }
                char *c_par = new char[len_p];
                if (read(fd3[0], c_par, sizeof(char) * len_p) == -1) {
                    cout << "Error with reading in parent" << endl;
                    return 9;
                }

                for (int nn = 0; nn < len_p; nn++) {
                    cout << c_par[nn];
                }
                
                delete [] c_par;
            }
            close(fd1[1]);
            close(fd3[0]);
        }
    
    }
    return 0;
}