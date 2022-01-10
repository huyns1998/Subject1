#include<stdio.h>
#include<stdlib.h>
struct item
{
	char* itemName;
	int quantity;
	float price;
};
struct item* readItem();
void printItem(struct item* it);

struct item* readItem()
{
	static struct item i;
	struct item* res = &i;
	res->itemName = (char*)malloc(30 * sizeof(char));
	printf("Nhap vao ten mat hang: ");
	fgets(res->itemName, 30, stdin);
	printf("Nhap vao so luong: ");
	scanf("%d", &res->quantity);
	printf("Nhap vao gia: ");
	scanf("%f", &res->price);
	return res;
}
void printItem(struct item* it)
{
	printf("Ten mat hang: %s\n", it->itemName);
	printf("So luong: %d\n", it->quantity);
	printf("Gia mat hang: %.2f\n", it->price);
}
int main()
{
	struct item* res = readItem();
	printItem(res);

	printf("--------------------------------------\n");

	free(res->itemName);
	return 0;
};