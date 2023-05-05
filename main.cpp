
#include "console-style.h"
#include <bits/stdc++.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    FILE* fd = fopen(".log", "ab+)");
    if(!fd) return -1;

    for (size_t i = 0; i <= 100; i++)
    {
        printf("helsdfsjflsejflsen 1\n");
        printf("helsdfsjflsejflsen 2\n");
        printf("helsdfsjflsejflsen 3\n");
        printf("helsdfsjflsejflsen 4\n");
        printf("helsdfsjflsejflsen 5\n");
        usleep(10000);
        printf("helsdfsjflsejflsen 6\n");
        printf("helsdfsjflsejflsen 7\n");
        // BLOCK_PROGRESS_BAR_UPDATE(stdout, "BLOCK PROGRESS BAR", 100, i);
        PROGRESS_BAR_UPDATE(stdout, "BLOCK PROGRESS BAR", 100, i, (SET_BACKGROUND_COLOR_S + GREEN), COLOR_NONE, '*');
        usleep(100000);
    }
    fclose(fd);
    return 0;
}
