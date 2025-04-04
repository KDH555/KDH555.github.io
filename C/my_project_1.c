#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 직원 정보 구조체
typedef struct
{
    char userName[20];
    char phoneNum[20];
    char position[20];
    int age;
} Member;

// 제품 정보 구조체
typedef struct
{
    char sellName[50];
    char sellCompany[50];
    char sellDate[20];
    int sellAdult;
    int sellPrice;
    int stock;
} Product;

//제품 입력 가능 개수
#define MAX_PRODUCTS 10

// 전역 변수
int store_money = 1234000;               // 가게 잔고
Product products[MAX_PRODUCTS] = {0};    // 제품 목록
int product_count = 0;                   // 등록된 제품 개수

// 업무 시간 측정을 위한 변수
time_t start_time = 0;        // 시작 시간
time_t end_time = 0;          // 종료 시간
int total_work_time = 0;      // 총 업무 시간   

typedef struct
{
    char id[20];
    char password[20];
} User;

// 직원 정보
Member info = {"홍길동", "010-1111-2222", "사원", 21};
User id_password = {"asd", "1234"};

void startWork();        // 업무 시작 함수
void stopMenu();         // 제품 등록 함수
void listMenu();         // 제품 목록 조회 함수
void sellMenu();         // 제품 판매 함수
void endWork();          // 업무 종료 함수

int main()
{
    char id[20] = {0};
    char password[20] = {0};
    
    printf("아이디 입력: ");
    scanf("%s", id);
    printf("패스워드 입력: ");
    scanf("%s", password);
    
    if (strcmp(id, id_password.id) == 0 && strcmp(password, id_password.password) == 0)
    {
        printf("\n로그인 성공!\n");
        printf("/***** 환영합니다 *****/\n");
        printf("%s 님의 개인정보:\n", info.userName);
        printf("이름: %s \n", info.userName);
        printf("직급: %s \n", info.position);
        printf("번호: %s \n", info.phoneNum);
        printf("나이: %d \n", info.age);
        
        getchar();      // 엔터 대기
        startWork();    // 로그인 성공 후 업무 시작 함수 호출
    }
else
    {
        printf("아이디 또는 패스워드가 잘못되었습니다.\n");
    }
    return 0;
}

void startWork()
{
    start_time = time(NULL);    // 업무 시작 시간 기록
    int choice = 0;

    // 메뉴 출력 및 선택 받기
    while (1)
    {
        printf("\n===== 제품 관리 메뉴 =====\n");
        printf("1. 제품 등록\n");
        printf("2. 제품 목록 조회\n");
        printf("3. 제품 판매\n");
        printf("4. 업무 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        // 사용자의 선택에 따른 분기
        switch (choice)
        {
            case 1:
                stopMenu();        // 제품 등록 함수 호출
                break;
            case 2:
                listMenu();        // 제품 목록 조회 함수 호출
                break;
            case 3:
                sellMenu();        // 제품 판매 함수 호출
                break;
            case 4:
                endWork();        // 업무 종료 함수 호출
                return;
            default:
                printf("\n잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }
}

void stopMenu()
{
    if (product_count >= MAX_PRODUCTS)
    {
        printf("\n더 이상 제품을 등록할 수 없습니다.\n");    // 최대 제품 수에 도달
        return;
    }
    
    printf("제품명 입력: ");
    scanf("%s", products[product_count].sellName);
    printf("제조회사 입력: ");
    scanf("%s", products[product_count].sellCompany);
    printf("유통기한 입력: ");
    scanf("%s", products[product_count].sellDate);
    printf("19금 물품인가요? (0: 아니오, 1: 예): ");
    scanf("%d", &products[product_count].sellAdult);
    printf("가격 입력: ");
    scanf("%d", &products[product_count].sellPrice);
    printf("재고 입력: ");
    scanf("%d", &products[product_count].stock);
    
    product_count++;        // 제품 개수 증가
    printf("\n제품 등록 완료!\n");
}

void listMenu()
{
    if (product_count == 0)
    {
        printf("\n등록된 제품이 없습니다.\n");
        return;
    }
    printf("\n===== 등록된 제품 목록 =====\n");
    for (int i = 0; i < product_count; i++)
    {
        printf("%d. 제품명: %s, 제조사: %s, 유통기한: %s, 가격: %d원, 재고: %.*s (%d개)\n", 
               i + 1, products[i].sellName, products[i].sellCompany, products[i].sellDate, 
               products[i].sellPrice, products[i].stock, "******************************", products[i].stock);
    }
}

void sellMenu()
{
    int choice = 0;
    int payment = 0;
    int cash = 0;
    int age = 0;
    listMenu();                        // 제품 목록 조회 함수 호출
    
    if (product_count == 0) return;    // 제품이 없으면 종료
    
    printf("\n구매할 제품 번호를 선택하세요: ");
    scanf("%d", &choice);
    choice--;                          // 선택한 제품 번호가 0부터 시작하도록 처리
    
    if (choice < 0 || choice >= product_count || products[choice].stock <= 0)
    {
        printf("\n잘못된 선택이거나 재고가 없습니다.\n");
        return;
    }

    if (products[choice].sellAdult)
    {
        printf("19금 제품입니다. 나이를 입력하세요: ");
        scanf("%d", &age);
        if (age < 19)
        {
            printf("\n미성년자는 구매할 수 없습니다.\n");
            return;
        }
    }
    
    printf("결제 방법을 선택하세요 (1: 카드, 2: 현금): ");
    scanf("%d", &payment);
    
    if (payment == 2)
    {
        printf("현금을 입력하세요: ");
        scanf("%d", &cash);
        if (cash < products[choice].sellPrice)
        {
            printf("금액이 부족합니다.\n");
            return;
        }
        printf("거스름돈: %d원\n", cash - products[choice].sellPrice);
    }
    
    store_money += products[choice].sellPrice;
    products[choice].stock--;
    printf("\n%s 구매 완료!\n", products[choice].sellName);
    printf("현재 가게 잔고: %d원\n", store_money);
}

void endWork()
{
    end_time = time(NULL);
    total_work_time = difftime(end_time, start_time) / 60;    // 총 근무 시간(분)

    int work_minutes = (int)total_work_time;
    int pay = work_minutes * 9200;                            // 분당 9200원

    printf("\n=====업무 종료=====\n");
    printf("총 근무 시간: %d분\n", work_miinutes);
    printf("총 급여: %d원\n", pay);
    printf("업무를 종료합니다.\n");
}
