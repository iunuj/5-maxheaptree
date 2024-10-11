#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "heaptree.h"

TreeNode* createNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {  // �޸� �Ҵ��� ������ ��� ó��
        printf("�޸� �Ҵ� ����!\n");
        exit(1);  // ���α׷� ����
    }

	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

TreeNode* InsertMaxHeapTree(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data > root->data) {
        int temp = root->data;
        root->data = data;
        data = temp;
    }

    if (!root->left) {
        root->left = InsertMaxHeapTree(root->left, data);
    }
    else if (!root->right) {
        root->right = InsertMaxHeapTree(root->right, data);
    }
    else {
        root->left = InsertMaxHeapTree(root->left, data);
    }

    return root;
}

TreeNode* deleteRoot(TreeNode* root) {
    if (root == NULL) {
        printf("���� ��� �ֽ��ϴ�.\n");
        return NULL;
    }

    printf("��Ʈ ��� %d�� �����Ǿ����ϴ�.\n", root->data);
    free(root);
    return NULL;
}

TreeNode* generateMaxHeapTree(int inputData[], int size) {
	TreeNode* root = NULL;
		for (int i = 0; i < size; i++) {
			root = InsertMaxHeapTree(root, inputData[i]);
		}
	return root;
}

void printLevelOrder(TreeNode* root) {
    if (root == NULL) {
        printf("���� ��� �ֽ��ϴ�.\n");
        return;
    }

    TreeNode* queue[100]; 
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        TreeNode* currentNode = queue[front++];
        printf("%d ", currentNode->data);

        if (currentNode->left) queue[rear++] = currentNode->left;
        if (currentNode->right) queue[rear++] = currentNode->right;
    }
    printf("\n");
}

void runUserInterface(TreeNode ** root) {
    char choice;
    int value;

    for (;;) {
        printf("\n--- �޴��� �����ϼ��� ---\n");
        printf("1 : �Է��� �޾� �ִ� ������ �߰� \n");
        printf("2 : �ִ� �������� ��Ʈ��� ���� \n");
        printf("3 : ������ ��Ʈ�������� �������� ��� \n");
        printf("4 : ���� \n");
        printf("�޴� �Է� : ");

        scanf(" %c", &choice);

        switch (choice) {
        case '1':
            printf("�߰��� �� �Է�: ");
            scanf("%d", &value);
            *root = InsertMaxHeapTree(*root, value);  // root�� ���� ���� ����
            printf("���� ���� �߰��Ǿ����ϴ�.\n");
            break;

        case '2':
            if (*root == NULL) {  // ��Ʈ�� NULL�� ��� ���� ����
                printf("������ ��Ʈ ��尡 �����ϴ�.\n");
            }
            else {
                *root = deleteRoot(*root);  // root�� ���� ���� ����
                if (*root == NULL) {  // ���� �� ��Ʈ�� NULL�� ��� ������ �ʱ�ȭ
                    printf("��Ʈ�� NULL�� �����Ǿ����ϴ�.\n");
                }
            }
            break;

        case '3':
            if (*root == NULL) {  // ��Ʈ�� NULL�� ��� ��� ����
                printf("���� ��� �ֽ��ϴ�.\n");
            }
            else {
                printf("���� ������ ���: ");
                printLevelOrder(*root);  // root�� ���� ����
            }
            break;

        case '4':
            printf("���α׷� ����\n");
            return;

        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }
}