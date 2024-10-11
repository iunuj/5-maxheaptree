#include <stdio.h>
#include <stdlib.h>
#include "heaptree.h"

int main() {
	int inputData[] = {90 , 89,	70, 36, 75, 63, 13, 21, 18, 5};
	int size = sizeof(inputData) / sizeof(inputData[0]);

	TreeNode* root = generateMaxHeapTree(inputData, size);

	runUserInterface(&root);

	free(root);

	return 0;
}