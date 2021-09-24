#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

int main(){
    int fd[2];
    pipe(fd);

    int pd = fork();

    if (pd == 0) {
        
        int l;
        read(fd[0], &l, sizeof(int));
        char s[l];
        read(fd[0], s, sizeof(char) * l);
        close(fd[0]);

        for (int i = 0; i < l; i++) {
            if (97 <= (int) s[i] <= 122) {
                int m = ((int) s[i]) - 32; 
                s[i] = (char) m;
            }
        }
        write(fd[1], s, sizeof(char) * l);
        close(fd[1]);
        
    } else {
        string m;
        cin >> m;
        int len = m.length() + 1;
        write(fd[1], &len, sizeof(int));
        write(fd[1], m.c_str(), sizeof(char) * len);
        close(fd[1]);

        char s[len];
        read(fd[0], s, sizeof(char) * len);
        close(fd[0]);
        for (int i = 0; i < len; i++) cout << s[i];
        cout << endl;
        close(fd[0]);
    }
    return 0;
}