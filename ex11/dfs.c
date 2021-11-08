/*
 * Write a Program to implement Depth First Search(DFS).
 */

#include <stdio.h>
#include <stdlib.h>

int a[20][20], visited[20], n;

void dfs(int v) {
    int i;
    visited[v] = 1;
    for (i = 1; i <= n; i++) {
        if ( a[v][i] && !visited[i] ) {
            printf("%d -> %d\n", v, i);
            dfs(i);
        }
    }
}

int main(void)
{
    int i, j, count = 0;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        visited[i] = 0;
        for (j = 1; j <= n; j++) {
            a[i][j] = 0;
        }
    }

    printf("\nEnter the adjacency matrix:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    putchar('\n');
    dfs(1);

    for ( i = 1; i <= n; i++) {
        if( visited[i] )
            count++;
    }

    if ( count == n ) {
        printf("\nGraph is connected.\n");
    } else {
        printf("\nGraph is not connected.\n");
    }

    return EXIT_SUCCESS;
}
