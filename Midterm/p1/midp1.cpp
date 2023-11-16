#include <cstdio>
#include <cmath>

using namespace std;

int N;
const int MAX_N = 1e5 + 20;
int primes[MAX_N];
int count = 0;

void find_prime() {
    for (int i = 2; i <= N; ++i) {
        bool is_prime = true;

        for (int j = 2; j <= (int) sqrt(i); ++j) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            primes[++count] = i;
        }
    }
}

int main() {
    scanf("%d", &N);

    find_prime();

    printf("prime: ");
    for (int i = 1; i <= count; ++i) {
        printf("%d ", primes[i]);
    }
    putchar('\n');

    printf("count: %d\n", count);

    return 0;
}
