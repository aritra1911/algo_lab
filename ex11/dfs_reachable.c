/*
 * Write a program to print all the nodes reachable from a given
 * starting node in a given digraph using DFS method.
 */

#include <stdio.h>
#include <stdlib.h>

int a[20][20], visited[20], n;

static void dfs(int v)
{
    visited[v] = 1;
    for (int i = 1; i <= n; i++) {
        if ( a[v][i] && !visited[i] ) {
            printf("%d -> %d\n", v, i);
            dfs(i);
        }
    }
}

int main(void)
{
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
        for (int j = 1; j <= n; j++) {
            a[i][j] = 0;
        }
    }

    printf("\nEnter graph data in matrix form:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int v;
    printf("\nEnter the starting vertex: ");
    scanf("%d", &v);

    dfs(v);

    printf("\nThe node which are reachable are:\n");
    for (int i = 1; i <= n; i++) {
        if ( visited[i] ) {
            printf("%i ", i);
        }
    }
    putchar('\n');

    return EXIT_SUCCESS;
}
