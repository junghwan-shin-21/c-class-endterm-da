
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    char color[20];
    int price;
} Fruit;

// -----------------------------------------------------------------------------
// 파일 생성 함수 (테스트를 위해 필요하며, 실제 문제의 일부는  아님) 
// -----------------------------------------------------------------------------
void create_source_file() {
    FILE *fp;
    Fruit fruits[5] = {
        {"Apple", "Red", 20000},
        {"Banana", "Yellow", 15000},
        {"Melon", "Green", 32000},
        {"Grape", "Purple", 22000},
        {"Kiwi", "Brown", 19000},     
    };

    fp = fopen("fruits.txt", "w");
    if (fp == NULL) {
        perror("Error creating fruits.txt");
        return;
    }

    for (int i = 0; i < 5; i++) {
        fprintf(fp, "%s %s %d\n", fruits[i].name, fruits[i].color, fruits[i].price);
    }
    fclose(fp);
}

// -----------------------------------------------------------------------------
// 메인 로직 함수
// -----------------------------------------------------------------------------
int main() {
    // 1. 소스 파일 생성 (실습을 위해 필요)
    create_source_file();

    FILE *fin, *fout;
    Fruit current_fruit;
    Fruit cheapest_fruit;
    int min_price = 999999;
    int cheapest_index = -1;
    int count = 0;

    // 2. 입력 파일 열기
    fin = fopen("fruits.txt", "r");
    if (fin == NULL) {
        perror("Error opening fruits.txt");
        return 1;
    }

    // 3. 파일에서 구조체를 읽어 최저가 검색
    while (fscanf(fin, "%s %s %d", 
                  current_fruit.name, 
                  current_fruit.color, 
                  &current_fruit.price) == 3) {
        
        if (current_fruit.price < min_price) {
            min_price = current_fruit.price;
            cheapest_fruit = current_fruit; // 최저가 정보 갱신
            cheapest_index = count;         // 배열 offset (index) 저장
        }
        count++;
    }
    fclose(fin);

    // 4. 최저가 과일 정보 출력 파일 저장
    if (cheapest_index == -1) {
        // 읽은 과일 정보가 없는 경우
        return 0;
    }

    fout = fopen("fruit_info.txt", "w");
    if (fout == NULL) {
        perror("Error creating fruit_info.txt");
        return 1;
    }

    fprintf(fout, "offset: %d\n", cheapest_index);
    fprintf(fout, "name: %s\n", cheapest_fruit.name);
    fprintf(fout, "color: %s\n", cheapest_fruit.color);
    fprintf(fout, "price: %d\n", cheapest_fruit.price);
    
    fclose(fout);

    return 0;
}

