/*
 * Write a Program to check whether a given graph is connected or not
 * using BFS method.
 */

#include <stdio.h>
#include <stdlib.h>

int a[20][20], q[20], visited[20], n, i, j, f = 0, r = -1;

void bfs(int v)
{
    for (i = 1; i <= n; i++) {
        if ( a[v][i] && !visited[i] )
            q[++r] = i;
    }

    if ( f <= r ) { /* if q is not empty */
        visited[q[f]] = 1;
        bfs(q[f++]);
    }
}

int main(void)
{
    int i, j, count = 0;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        q[i] = 0;
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

    bfs(1);

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
