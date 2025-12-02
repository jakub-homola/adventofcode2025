#include "../helpers/helpers.hpp"



int64_t get_num_digits(int64_t x)
{
    int result = 0;
    while(x > 0) {
        result++;
        x /= 10;
    }
    return result;
}

int64_t get_power(int64_t x, int64_t n)
{
    int64_t result = 1;
    for(int64_t i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}



int main()
{
    timer tm;
    tm.start();

    int64_t result = 0;

    while(true) {
        int64_t l, r;
        int res = scanf("%ld-%ld", &l, &r);
        if(res != 2) break;
        getchar();

        for(int64_t i = l; i <= r; i++) {
            int64_t num_digits = get_num_digits(i);
            for(int64_t j = 1; j <= num_digits/2; j++) {
                if(num_digits % j != 0) continue;
                int64_t power = get_power(10, j);
                int64_t repeats = num_digits / j;
                int64_t num = i;
                bool ok = true;
                int64_t lower = num % power;
                num /= power;
                while(num > 0) {
                    int64_t curr = num % power;
                    num /= power;
                    if(curr != lower) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    result += i;
                    break;
                }
            }
        }
    }

    printf("%ld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
