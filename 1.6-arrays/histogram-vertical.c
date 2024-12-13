#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100

static
int compute_number_length(int nb)
{
    int count = 0;

    if (nb == 0)
        return 0;
    for (; nb > 0; nb /= 10)
        count++;
    return count;
}

static
void collect_word_sizes(int *wlen)
{
    int c;
    int current_len = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (current_len > 0 && current_len < MAX_WORD_LENGTH) {
                wlen[current_len]++;
                current_len = 0;
            }
        } else {
            current_len++;
        }
    }
}

static
void draw_graph_bar(int *wlen, int bar_pad)
{
    bool gap = false;
    // Get the height of the biggest bar to know how much lines to draw
    int max = *wlen;
    for (int i = 1; i < MAX_WORD_LENGTH; i++)
        if (wlen[i] > max)
            max = wlen[i];

    // Draw the vertical bars
    for (int col = max; col > 0; col--) {
        gap = false; // use to set 1 space gap between each column
        for (int i = 0; i < MAX_WORD_LENGTH; i++) {
            if (!wlen[i]) continue;
            if (gap) printf(" ");

            for (int j = 1; j < bar_pad; j++)
                printf(" ");

            printf("%c", wlen[i] >= col ? '*' : ' ');
            gap = true;
        }
        printf("\n");
    }
}

static
void draw_graph_labels(int *wlen, int bar_pad)
{
    // label separation
    bool gap = false;
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        if (!wlen[i]) continue;
        for (int j = 0; j < bar_pad + gap; j++)
            printf("-");
        gap = true;
    }
    printf("\n");

    // labels
    gap = false;
    int num_size;
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        if (!wlen[i]) continue;
        if (gap) printf(" ");

        num_size = compute_number_length(i);
        for (int j = num_size; j < bar_pad; j++)
            printf(" ");
        printf("%d", i);
        gap = true;
    }
    printf("\n");

}

static
void render_graph(int *wlen)
{
    // Get the last datapoint of the graph
    int lastword = 0;
    for (int i = 0; i < MAX_WORD_LENGTH; i++)
        if (wlen[i] != 0)
            lastword = i;

    // the bar pad is meant to keep bar within each label, with words size >9
    int bar_pad = compute_number_length(lastword);

    draw_graph_bar(wlen, bar_pad);
    draw_graph_labels(wlen, bar_pad);
}

int main(void)
{
    int wlen[MAX_WORD_LENGTH] = { 0 };

    collect_word_sizes(wlen);
    render_graph(wlen);
    return EXIT_SUCCESS;
}
