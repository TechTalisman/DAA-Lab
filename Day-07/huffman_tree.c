// C program to construct a Huffman Tree using a Min-Priority Queue and display its inorder traversal

#include <stdio.h>
#include <stdlib.h>

typedef struct SYMBOL {
    char alphabet;
    int frequency;
    struct SYMBOL *left, *right;
} SYMBOL;

SYMBOL* createNode(char alphabet, int frequency) {
    SYMBOL* node = (SYMBOL*)malloc(sizeof(SYMBOL));
    node->alphabet = alphabet;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

void swap(SYMBOL** a, SYMBOL** b) {
    SYMBOL* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(SYMBOL* heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left]->frequency < heap[smallest]->frequency)
        smallest = left;
    if (right < size && heap[right]->frequency < heap[smallest]->frequency)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, size, smallest);
    }
}

SYMBOL* extractMin(SYMBOL* heap[], int *size) {
    SYMBOL* minNode = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify(heap, *size, 0);
    return minNode;
}

void insertHeap(SYMBOL* heap[], int *size, SYMBOL* node) {
    (*size)++;
    int i = *size - 1;
    heap[i] = node;

    while (i && heap[(i - 1) / 2]->frequency > heap[i]->frequency) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

SYMBOL* buildHuffmanTree(SYMBOL* heap[], int size) {
    while (size > 1) {
        SYMBOL* left = extractMin(heap, &size);
        SYMBOL* right = extractMin(heap, &size);

        SYMBOL* top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertHeap(heap, &size, top);
    }
    return heap[0];
}

void inorderTraversal(SYMBOL* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    if (root->alphabet != '$') 
        printf("%c ", root->alphabet);
    inorderTraversal(root->right);
}

int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    char alphabets[n];
    int freq[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++) 
        scanf(" %c", &alphabets[i]);

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &freq[i]);

    SYMBOL* heap[n];
    int size = 0;
    for (int i = 0; i < n; i++) {
        heap[i] = createNode(alphabets[i], freq[i]);
        size++;
    }

    for (int i = (size - 1) / 2; i >= 0; i--)
        heapify(heap, size, i);

    SYMBOL* root = buildHuffmanTree(heap, size);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
