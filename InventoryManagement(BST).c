#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 

typedef struct Node { 
    char name[20]; 
    int current_stock; 
    int reorder_point; 
    int max_stock; 
    struct Node* left; 
    struct Node* right; 
} Node; 
 

Node* createNode(char name[], int current_stock, int reorder_point, int max_stock) { 
    Node* node = (Node*)malloc(sizeof(Node)); 
    strcpy(node->name, name); 
    node->current_stock = current_stock; 
    node->reorder_point = reorder_point; 
    node->max_stock = max_stock; 
    node->left = NULL; 
    node->right = NULL; 
    return node; 
} 
 

Node* insertNode(Node* root, char name[], int current_stock, int reorder_point, int max_stock) { 
    if (root == NULL) { 
        return createNode(name, current_stock, reorder_point, max_stock); 
    } 
 
    if (strcmp(name, root->name) < 0) { 
        root->left = insertNode(root->left, name, current_stock, reorder_point, max_stock); 
    } else if (strcmp(name, root->name) > 0) { 
        root->right = insertNode(root->right, name, current_stock, reorder_point, max_stock); 
    } 
 
    return root; 
}
 

int calculate_reorder_point(int current_stock, int reorder_point) { 
    if (current_stock <= reorder_point) { 
        return 1; 
    } else { 
        return 0;  
    } 
} 
 

int calculate_optimal_order_quantity(int current_stock, int max_stock, int reorder_point) { 
    int order_quantity = max_stock - current_stock; 
    if (order_quantity < 0) { 
        order_quantity = 0; 
    } 
    return order_quantity; 
} 
 

void traverseTree(Node* root) { 
    if (root == NULL) { 
        return; 
    } 
 
    traverseTree(root->left); 
 
    int reorder_needed = calculate_reorder_point(root->current_stock, root->reorder_point); 
    int order_quantity = calculate_optimal_order_quantity(root->current_stock, root->max_stock, 
root->reorder_point); 
 
    printf("Product %s:\n", root->name); 
    printf("Current stock: %d\n", root->current_stock); 
    printf("Reorder point: %d\n", root->reorder_point); 
    printf("Maximum stock: %d\n", root->max_stock); 
    printf("Reorder needed: %s\n", reorder_needed ? "Yes" : "No"); 
    printf("Optimal order quantity: %d\n\n", order_quantity); 
 
    traverseTree(root->right); 
} 
 
int main() { 
	int i;
    Node* root = NULL; 
 
    
    int num_products; 
    printf("Enter the number of products: "); 
    scanf("%d", &num_products); 
 
    for (i = 0; i < num_products; i++) { 
        char name[20]; 
        int current_stock, reorder_point, max_stock; 
        printf("Enter data for Product %d:\n", i + 1); 
        printf("Name: "); 
        scanf("%s", name); 
        printf("Current stock: "); 
        scanf("%d", &current_stock); 
        printf("Reorder point: "); 
        scanf("%d", &reorder_point); 
        printf("Maximum stock: "); 
        scanf("%d", &max_stock); 
        printf("\n"); 
 
        root = insertNode(root, name, current_stock, reorder_point, max_stock); 
    } 
 
    
    printf("Inventory Management System Results:\n"); 
    traverseTree(root); 
 
    return 0; 
}

