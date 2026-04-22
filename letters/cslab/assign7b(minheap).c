#include <stdio.h>
#include <stdlib.h>

#define MAX_PACKAGES 100

struct Package {
    int packageID;
    int destinationCode;
    int deadline;
};

struct Package heap[MAX_PACKAGES];
int heapSize = 0;

// Helper to swap two packages
void swap(struct Package *a, struct Package *b) {
    struct Package temp = *a;
    *a = *b;
    *b = temp;
}

// Restore heap property from bottom to top
void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].deadline < heap[parent].deadline) {
            swap(&heap[index], &heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// Restore heap property from top to bottom
void heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && heap[left].deadline < heap[smallest].deadline)
        smallest = left;
    if (right < heapSize && heap[right].deadline < heap[smallest].deadline)
        smallest = right;

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapifyDown(smallest);
    }
}

void addPackage() {
    if (heapSize >= MAX_PACKAGES) {
        printf("Queue is full!\n");
        return;
    }
    struct Package p;
    printf("Enter Package ID: ");
    scanf("%d", &p.packageID);
    printf("Enter Destination Code: ");
    scanf("%d", &p.destinationCode);
    printf("Enter Deadline (hours): ");
    scanf("%d", &p.deadline);

    heap[heapSize] = p;
    heapifyUp(heapSize);
    heapSize++;
    printf("Package added successfully.\n");
}

void dispatchPackage() {
    if (heapSize == 0) {
        printf("No packages to dispatch.\n");
        return;
    }
    struct Package root = heap[0];
    printf("Dispatching Package:\nPackage ID: %d\nDestination: %d\nDeadline: %d hours\n", 
            root.packageID, root.destinationCode, root.deadline);

    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
}

void updateDeadline() {
    int id, newDeadline, found = -1;
    printf("Enter Package ID: ");
    scanf("%d", &id);
    
    for (int i = 0; i < heapSize; i++) {
        if (heap[i].packageID == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Package ID not found.\n");
        return;
    }

    printf("Enter New Deadline (hours): ");
    scanf("%d", &newDeadline);
    int oldDeadline = heap[found].deadline;
    heap[found].deadline = newDeadline;

    if (newDeadline < oldDeadline) {
        heapifyUp(found);
    } else {
        heapifyDown(found);
    }
    printf("Package updated successfully.\n");
}

void viewNext() {
    if (heapSize == 0) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Next Package to Dispatch:\nPackage ID: %d\nDestination: %d\nDeadline: %d hours\n", 
            heap[0].packageID, heap[0].destinationCode, heap[0].deadline);
}

void displayQueue() {
    if (heapSize == 0) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Current Package Queue:\nIndex\tPackageID\tDestination\tDeadline\n");
    for (int i = 0; i < heapSize; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i, heap[i].packageID, heap[i].destinationCode, heap[i].deadline);
    }
}

void checkHeapProperty() {
    int id, idx = -1;
    printf("Enter Package ID to check: ");
    scanf("%d", &id);

    for (int i = 0; i < heapSize; i++) {
        if (heap[i].packageID == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Package not found.\n");
        return;
    }

    int pIdx = (idx - 1) / 2;
    int lIdx = 2 * idx + 1;
    int rIdx = 2 * idx + 2;

    if (idx > 0) printf("Parent Package: %d (Deadline %d)\n", heap[pIdx].packageID, heap[pIdx].deadline);
    else printf("Parent Package: None\n");

    if (lIdx < heapSize) printf("Left Child Package: %d (Deadline %d)\n", heap[lIdx].packageID, heap[lIdx].deadline);
    else printf("Left Child Package: None\n");

    if (rIdx < heapSize) printf("Right Child Package: %d (Deadline %d)\n", heap[rIdx].packageID, heap[rIdx].deadline);
    else printf("Right Child Package: None\n");

    // Verification logic
    int valid = 1;
    if (idx > 0 && heap[idx].deadline < heap[pIdx].deadline) valid = 0;
    if (lIdx < heapSize && heap[idx].deadline > heap[lIdx].deadline) valid = 0;
    if (rIdx < heapSize && heap[idx].deadline > heap[rIdx].deadline) valid = 0;

    if (valid) printf("Min Heap property is satisfied for this node.\n");
    else printf("Min Heap property is VIOLATED for this node.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Menu ---\n1. Add Package\n2. Dispatch Next Package\n3. Update Deadline\n4. View Next Package\n5. Display Queue\n6. Check Heap Property\n7. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPackage(); break;
            case 2: dispatchPackage(); break;
            case 3: updateDeadline(); break;
            case 4: viewNext(); break;
            case 5: displayQueue(); break;
            case 6: checkHeapProperty(); break;
            case 7: printf("Program terminated.\n"); exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}