// Menu-driven C program to manage student records using min-heap (age) and max-heap (weight) with dynamic memory allocation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct person {
    int id;
    char name[100];
    int age;
    int height;
    int weight;
};

struct person *people = NULL;
struct person *heap = NULL;
int n = 0;       
int heapSize = 0; 

static void rstrip(char *s) {
    size_t len = strlen(s);
    while (len && (s[len-1] == ' ' || s[len-1] == '\t' || s[len-1] == '\n' || s[len-1] == '\r'))
        s[--len] = '\0';
}

void swap(struct person *a, struct person *b) {
    struct person t = *a; *a = *b; *b = t;
}

void minHeapify(int i) {
    int smallest = i, l = 2*i + 1, r = 2*i + 2;
    if (l < heapSize && heap[l].age < heap[smallest].age) smallest = l;
    if (r < heapSize && heap[r].age < heap[smallest].age) smallest = r;
    if (smallest != i) { swap(&heap[i], &heap[smallest]); minHeapify(smallest); }
}
void buildMinHeap() { for (int i = heapSize/2 - 1; i >= 0; --i) minHeapify(i); }

void maxHeapify(int i) {
    int largest = i, l = 2*i + 1, r = 2*i + 2;
    if (l < heapSize && heap[l].weight > heap[largest].weight) largest = l;
    if (r < heapSize && heap[r].weight > heap[largest].weight) largest = r;
    if (largest != i) { swap(&heap[i], &heap[largest]); maxHeapify(largest); }
}
void buildMaxHeap() { for (int i = heapSize/2 - 1; i >= 0; --i) maxHeapify(i); }

void insertMinHeap(struct person p) {
    heapSize++;
    heap = realloc(heap, heapSize * sizeof *heap);
    int i = heapSize - 1;
    heap[i] = p;
    while (i && heap[(i-1)/2].age > heap[i].age) {
        swap(&heap[i], &heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

void deleteOldest() {
    if (!heapSize) { printf("Heap is empty.\n"); return; }
    buildMinHeap(); 

    int maxIdx = 0;
    for (int i = 1; i < heapSize; ++i) if (heap[i].age > heap[maxIdx].age) maxIdx = i;

    printf("Deleting oldest person: %s (Age %d)\n", heap[maxIdx].name, heap[maxIdx].age);
    heap[maxIdx] = heap[heapSize-1];
    heapSize--;
    if (heapSize) {
        heap = realloc(heap, heapSize * sizeof *heap);
        buildMinHeap();
    } else {
        free(heap); heap = NULL;
    }
}

void displayWeightOfYoungest() {
    if (!heapSize) { printf("Heap is empty.\n"); return; }
    buildMinHeap();
    struct person y = heap[0];
    double kg = y.weight * 0.453592;
    printf("Weight of youngest student: %.2f kg\n", kg);
}

void readData(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { printf("Error opening file.\n"); return; }

    if (fscanf(fp, "%d", &n) != 1 || n <= 0) {
        printf("Invalid count on first line.\n");
        fclose(fp);
        return;
    }
    int c;
    while ((c = fgetc(fp)) != '\n' && c != EOF) {}

    free(people); people = malloc(n * sizeof *people);
    free(heap);   heap   = malloc(n * sizeof *heap);
    heapSize = 0;

    char line[512];
    for (int i = 0; i < n; ) {
        if (!fgets(line, sizeof line, fp)) {
            printf("Unexpected end of file at record %d.\n", i);
            break;
        }
        
        int only_ws = 1;
        for (char *p=line; *p; ++p) if (!isspace((unsigned char)*p)) { only_ws = 0; break; }
        if (only_ws) continue;

        int id, age, height, weight;
        char name[100];

        int matched = sscanf(line, "%d %99[^0-9\n] %d %d %d", &id, name, &age, &height, &weight);
        if (matched != 5) {
            printf("Bad line %d: %s", i+1, line);
            continue;
        }
        rstrip(name);

        people[i].id = id;
        strncpy(people[i].name, name, sizeof(people[i].name));
        people[i].name[sizeof(people[i].name)-1] = '\0';
        people[i].age = age;
        people[i].height = height;
        people[i].weight = weight;

        heap[i] = people[i];
        ++i; heapSize = i;
    }
    fclose(fp);

    printf("Data successfully read from file.\n");
    printf("Id\tName\t\t\tAge\tHeight\tWeight(pound)\n");
    for (int i = 0; i < heapSize; ++i) {
        printf("%d\t%-20s\t%d\t%d\t%d\n",
               people[i].id, people[i].name, people[i].age, people[i].height, people[i].weight);
    }
}

int main() {
    int option;
    char filename[64] = "students.txt";

    do {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter option: ");
        if (scanf("%d", &option) != 1) { 
            
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {} 

        if (option == 1) {
            readData(filename);
        } else if (option == 2) {
            buildMinHeap(); printf("Min-heap created based on age.\n");
        } else if (option == 3) {
            buildMaxHeap(); printf("Max-heap created based on weight.\n");
        } else if (option == 4) {
            displayWeightOfYoungest();
        } else if (option == 5) {
            struct person p;
            printf("Enter Id: "); scanf("%d", &p.id); while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Enter Name (with spaces): "); fgets(p.name, sizeof p.name, stdin); rstrip(p.name);
            printf("Enter Age Height Weight: "); scanf("%d %d %d", &p.age, &p.height, &p.weight);
            insertMinHeap(p); printf("Person inserted into Min-heap.\n");
        } else if (option == 6) {
            deleteOldest();
        } else if (option == 7) {
            printf("Exiting...\n");
        } else {
            printf("Invalid option.\n");
        }
    } while (option != 7);

    free(people);
    free(heap);
    return 0;
}
