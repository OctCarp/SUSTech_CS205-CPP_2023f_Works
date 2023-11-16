#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 1e5 + 10;
char str[MAX_N];
int len;

int search_first(char first) {
    int count0 = 0;
    int count1 = 0;
    int max_v = 0;
    bool stop0 = false;
    for (int i = 0; i < len; ++i) {
        char ch = str[i];
        if (!stop0) {
            if (ch == first) {
                ++count0;
            } else {
                stop0 = true;
                ++count1;
            }
        } else {
            if (ch != first) {
                ++count1;
            } else {
                max_v = max(max_v, min(count0, count1));
                stop0 = false;
                count0 = 1;
                count1 = 0;
            }
        }
    }
    max_v = max(max_v, min(count0, count1));
    return max_v;
}

int main() {
    scanf("%s", &str);
    len = strlen(str);

    printf("%d", max(search_first('0'), search_first('1')) << 1);

    return 0;
}