#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Car {
	char plate[10];
	int time;
	struct Car* next;
} Car;

Car* head = NULL;

void add(char* plate, int time) {
	Car* newCar = (Car*)malloc(sizeof(Car));
	strcpy(newCar->plate, plate);
	newCar->time = time;
	newCar->next = head;
	head = newCar;
	printf("차량 %s 추가 완료!\n", plate);
}

void show() {
	Car* temp = head;
	if (!temp) {
		printf("주차된 차량이 없습니다.\n");
		return;
	}
	printf("현재 주차된 차량 목록:\n");
	while (temp) {
		printf("번호: %s, 시간: %d분\n", temp->plate, temp->time);
		temp = temp->next;
	}
}

void del(char* plate) {
	Car* temp = head, *prev = NULL;
	while (temp && strcmp(temp->plate, plate) != 0) {
		prev = temp;
		temp = temp->next;
	}
	if (!temp) {
		printf("해당 차량이 없습니다.\n");
		return;
	}
	if (!prev) head = temp->next;
	else prev->next = temp->next;
	free(temp);
	printf("차량 %s 삭제 완료.\n", plate);
}

int main() {
	int choice;
	char plate[10];
	int time;

	while (1) {
		printf("\n1. 차량 추가\n2. 차량 조회\n3. 차량 삭제\n4. 종료\n선택: ");
		scanf("%d", &choice);

		if (choice == 1) {
			printf("차량 번호 입력: ");
			scanf("%s", plate);
			printf("주차 시간 입력(분): ");
			scanf("%d", &time);
		} else if (choice == 2) {
			show();
		} else if (choice == 3) {
			printf("삭제할 차량 번호 입력: ");
			scanf("%s", plate);
			del(plate);
		} else if (choice == 4) {
			printf("프로그램 종료.\n");
			break;
		} else {
			printf("잘못된 입력입니다. 다시 시도하세요.\n");
		}
	}
	return 0;
}
