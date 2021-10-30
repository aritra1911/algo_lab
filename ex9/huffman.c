/* Note: Not entirely written by me. I got the core functions and data
 * structures already implemented by a friend. Just hacked the menu in
 * place and got it working enough to get a test case output. I don't
 * like deadlines and wasn't feeling like writing this at all. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    char ch;
    int freq;
    struct _Node *left;
    struct _Node *right;
} Node;

Node *heap[100];
int heapSize = 0;

void Insert(Node *element)
{
    heapSize++;
    heap[heapSize] = element;
    int now = heapSize;
    while (heap[now / 2]->freq > element->freq) {
        heap[now] = heap[now / 2];
        now /= 2;
    }
    heap[now] = element;
}
Node *DeleteMin() {
    Node *minElement, *lastElement;
    int child, now;
    minElement = heap[1];
    lastElement = heap[heapSize--];
    for (now = 1; now * 2 <= heapSize; now = child) {
        child = now * 2;
        if (child != heapSize && heap[child + 1]->freq < heap[child]->freq) {
            child++;
        }
        if (lastElement->freq > heap[child]->freq) {
            heap[now] = heap[child];
        } else {
            break;
        }
    }
    heap[now] = lastElement;
    return minElement;
}
void print(Node *temp, char *code) {
    if (temp->left == NULL && temp->right == NULL) {
        printf("char %c code %s\n", temp->ch, code);
        return;
    }
    int length = strlen(code);
    char leftcode[10], rightcode[10];
    strcpy(leftcode, code);
    strcpy(rightcode, code);
    leftcode[length] = '0';
    leftcode[length + 1] = '\0';
    rightcode[length] = '1';
    rightcode[length + 1] = '\0';
    print(temp->left, leftcode);
    print(temp->right, rightcode);
}
void print_traversal(Node *node) {
    if (node == NULL) return;
    if (node->ch != '\0') {
        printf("%c ", node->ch);
    }
    print_traversal(node->left);
    print_traversal(node->right);
}
char *get_code(Node *node, char ch, const char *prefix, char *code) {
    if ( node->left == NULL && node->right == NULL ) {
        if ( node->ch == ch ) {
            strcpy(code, prefix);
            return code;
        }
        return NULL;
    }

    int length = strlen(prefix);
    char leftcode[10], rightcode[10];
    strcpy(leftcode, prefix);
    strcpy(rightcode, prefix);
    leftcode[length] = '0';
    leftcode[length + 1] = '\0';
    rightcode[length] = '1';
    rightcode[length + 1] = '\0';

    char *ret;
    if ( (ret = get_code(node->left, ch, leftcode, code)) )
        return ret;
    return get_code(node->right, ch, rightcode, code);
}
int main() {
    heap[0] = (Node *)malloc(sizeof(Node));
    heap[0]->freq = 0;
    int n;
    printf(
        "------------------------------------------------------------------\n"
        "                  HUFFMAN CODE GEBERATION MENU\n"
        " 0. Quit\n"
        " 1. Input n unique characters with their frequencies into an array\n"
        " 2. Display the Array\n"
        " 3. Generate Huffman Tree and Traverse the tree with pre-order.\n"
        " 4. Generate Huffman Codes for n charachers and display the same.\n"
        " 5. Compare Huffman code with Fixed-Length Code\n"
        "------------------------------------------------------------------\n"
    );
    int ch;
    Node *arr;
redo:
    printf("Your choice: ");
    ch = getchar(); getchar();
    switch(ch) {
    case '0': return EXIT_SUCCESS;
    case '1':
        printf("Enter n: ");
        scanf("%d", &n);
        getchar();
        arr = malloc(n * sizeof (Node));
        for (int i = 0; i < n; i++) {
            scanf("%c %d", &arr[i].ch, &arr[i].freq);
            getchar();
            arr[i].right = arr[i].left = NULL;
        }
        break;
    case '2':
        for (int i = 0; i < n; i++) {
            printf("[ { %c, %d }, ", arr[i].ch, arr[i].freq);
        }
        printf("]\n");
        break;
    case '3':
        for (int i = 0; i < n; i++) {
            Node *temp = (Node *)malloc(sizeof(Node));
            temp->ch = arr[i].ch;
            temp->freq = arr[i].freq;
            temp->left = temp->right = NULL;
            Insert(temp);
        }
        for (int i = 0; i < n - 1; i++) {
            Node *left = DeleteMin();
            Node *right = DeleteMin();
            Node *temp = (Node *)malloc(sizeof(Node));
            temp->ch = 0;
            temp->left = left;
            temp->right = right;
            temp->freq = left->freq + right->freq;
            Insert(temp);
        }
        print_traversal(heap[heapSize]);
        putchar('\n');
        break;
    case '4':
        if (n == 1) {
            printf("char %c code 0\n", ch);
            break;
        }
        //Node *tree = DeleteMin();
        Node *tree = heap[heapSize];
        char code[10];
        code[0] = '\0';
        print(tree, code);
        break;
    case '5':
        printf("Char   Huffman Code   Fixed-length Code   Delta\n"
               "----   ------------   -----------------   -----\n");
        for (int i = 0; i < n; i++) {
            char code[10], fix_code[10];
            int j=i, x=n, bits=0, delta;

            while ( x &= x - 1 ) bits++;
            if ( bits ) bits = 1;
            x = n;
            while ( x >>= 1 ) bits++;

            fix_code[bits] = '\0';
            char *p = &fix_code[bits - 1];
            while ( p >= fix_code ) {
                *p = j & 1 ? '1' : '0';
                j >>= 1;
                p--;
            }

            if ( get_code(heap[heapSize], arr[i].ch, "\0", code) ) {
                delta = strlen(fix_code) - strlen(code);
                printf("%-4c   %-12s   %-17s   %d\n",
                        arr[i].ch, code, fix_code, delta);
            }
        }
        break;
    case EOF:
        return EXIT_SUCCESS;
    }
    goto redo;
    return EXIT_SUCCESS;
}
