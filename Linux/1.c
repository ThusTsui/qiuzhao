#include <stdio.h>
#include <math.h>
int main()
{
    unsigned N, a, b, c, d;
    scanf("%u", &N);
    unsigned i = 0, q, w, e;
    while (i <= N)
    {
        for (q = 2; q < N; q++)
            for (w = 2; w < N; w++)
                for (e = 2; e < N; e++)
                    if (q <= w)
                    {
                        if (w <= e)
                        {

                            if (i * i * i == q * q * q + w * w * w + e * e * e)
                            {
                                printf("Cube = %u, Triple = (%u,%u,%u)\n", i, q, w, e);
                            }
                        }
                    }
        i++;
    }
}