#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "heaptree.h"

TreeNode* createNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {  // 메모리 할당이 실패한 경우 처리
        printf("메모리 할당 실패!\n");
        exit(1);  // 프로그램 종료
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
        printf("힙이 비어 있습니다.\n");
        return NULL;
    }

    printf("루트 노드 %d이 삭제되었습니다.\n", root->data);
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
        printf("힙이 비어 있습니다.\n");
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
        printf("\n--- 메뉴를 선택하세요 ---\n");
        printf("1 : 입력을 받아 최대 히프에 추가 \n");
        printf("2 : 최대 히프에서 루트노드 삭제 \n");
        printf("3 : 히프를 루트에서부터 레벨별로 출력 \n");
        printf("4 : 종료 \n");
        printf("메뉴 입력 : ");

        scanf(" %c", &choice);

        switch (choice) {
        case '1':
            printf("추가할 값 입력: ");
            scanf("%d", &value);
            *root = InsertMaxHeapTree(*root, value);  // root의 값을 직접 수정
            printf("값이 힙에 추가되었습니다.\n");
            break;

        case '2':
            if (*root == NULL) {  // 루트가 NULL일 경우 삭제 방지
                printf("삭제할 루트 노드가 없습니다.\n");
            }
            else {
                *root = deleteRoot(*root);  // root의 값을 직접 수정
                if (*root == NULL) {  // 삭제 후 루트가 NULL인 경우 포인터 초기화
                    printf("루트가 NULL로 설정되었습니다.\n");
                }
            }
            break;

        case '3':
            if (*root == NULL) {  // 루트가 NULL일 경우 출력 방지
                printf("힙이 비어 있습니다.\n");
            }
            else {
                printf("힙의 레벨별 출력: ");
                printLevelOrder(*root);  // root를 간접 참조
            }
            break;

        case '4':
            printf("프로그램 종료\n");
            return;

        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }
}