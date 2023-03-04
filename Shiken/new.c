#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[5];
    float area;
    int dieuhoa;
} hotel;

hotel phongtro[100], temp;
int slPhong = 0, loaiDieuHoa[4];

int kiemTraTen(char *s){
    int i, thoaman = 1;
    for (i = 0; i < 4; i++){
        if (!(('a' <= *(s+i) && *(s+i) <= 'z') || ('A' <= *(s+i) && *(s+i) <= 'Z'))) thoaman = 0;
    }
    if (*(s+4) != '\0') thoaman = 0;
    return thoaman;
}

void nhapThongTin(int thamso){
    int i, themPhong;
    do {
        if (thamso == 0) {
            printf("Nhap so luong phong tro: ");
        } else {
            printf("Nhap so luong phong tro muon them: ");
        }
        scanf("%d", &themPhong);
    } while (themPhong <= 0);

    slPhong += themPhong;

    if (thamso == 0) i = 0; else i = slPhong - themPhong;
    for (; i < slPhong; i++){
        printf("Nhap thong tin phong so %d (nhap sai se phai nhap lai)\n", i+1);
        do {
            fflush(stdin);
            printf("Nhap ten phong: ");
            scanf("%[^\n]", phongtro[i].name);
        } while (kiemTraTen(phongtro[i].name) ==0);

        do {
            fflush(stdin);
            printf("Nhap dien tich: ");
            scanf("%f", &phongtro[i].area);
        } while (phongtro[i].area < 10 || phongtro[i].area > 40);

        do {
            fflush(stdin);
            printf("Co dieu hoa khong? (1 la co, 0 la khong): ");
            scanf("%d", &phongtro[i].dieuhoa);
        } while (phongtro[i].dieuhoa != 1 && phongtro[i].dieuhoa != 0);
    }
}

void main(){
    int i, j, chucnang, daChon1 = 0;
    do {
        printf("==================\n");
        printf("1. Nhap thong tin phong tro\n");
        printf("2. In thong tin cac phong tro\n");
        printf("3. Tim kiem theo dien tich\n");
        printf("4. Sap xep\n");
        printf("5. Thong ke so luong dieu hoa can bo sung\n");
        printf("6. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &chucnang);
        switch (chucnang){
            case 1:
                nhapThongTin(daChon1);
                daChon1 = 1;
                break;
            case 2:
                printf("%-15s%-15s%-15s\n", "Ten phong", "Dien tich", "Dieu hoa");
                for (i = 0; i < slPhong; i++){
                    printf("%-15s%-15.2f", phongtro[i].name, phongtro[i].area);
                    if (phongtro[i].dieuhoa == 1) printf("%s", "Co"); else printf("%s", "Khong");
                    printf("\n");
                }
                break;
            case 3:
                printf("Nhap vao dien tich muon tim: ");
                int k, slthoaman = 0;
                scanf("%d", &k);
                printf("%-15s%-15s%-15s\n", "Ten phong", "Dien tich", "Dieu hoa");
                for (i = 0; i < slPhong; i++){
                    if (phongtro[i].area >= (k-5) && phongtro[i].area <= (k+5)) {
                        slthoaman++;
                        printf("%-15s%-15.2f", phongtro[i].name, phongtro[i].area);
                        if (phongtro[i].dieuhoa == 1) printf("%s", "Co"); else printf("%s", "Khong");
                        printf("\n");
                    }
                }
                if (slthoaman == 0) printf("KHONG TIM THAY\n");
                break;
            case 4:
                printf("\n");
                for (i = 0; i < slPhong - 1; i++){
                    for (j = i+1; j < slPhong; j++){
                        if (phongtro[i].area < phongtro[j].area){
                            temp = phongtro[i];
                            phongtro[i] = phongtro[j];
                            phongtro[j] = temp;
                        }
                    }
                }
                printf("%-15s%-15s%-15s\n", "Ten phong", "Dien tich", "Dieu hoa");
                for (i = 0; i < slPhong; i++){
                    printf("%-15s%-15.2f", phongtro[i].name, phongtro[i].area);
                    if (phongtro[i].dieuhoa == 1) printf("%s", "Co"); else printf("%s", "Khong");
                    printf("\n");
                }

                break;
            case 5:
                for (i = 0; i < 4; i++) loaiDieuHoa[i] = 0;
                for (i = 0; i < slPhong; i++){
                    if (phongtro[i].dieuhoa == 0) {
                        if (phongtro[i].area < 15) loaiDieuHoa[0]++;
                        if (phongtro[i].area >= 15 && phongtro[i].area < 22) loaiDieuHoa[1]++;
                        if (phongtro[i].area >= 22 && phongtro[i].area <= 30) loaiDieuHoa[2]++;
                        if (phongtro[i].area >= 30 && phongtro[i].area <= 40) loaiDieuHoa[3]++;
                    }
                }
                printf("9000BTU: %d\n", loaiDieuHoa[0]);
                printf("12000BTU: %d\n", loaiDieuHoa[1]);
                printf("18000BTU: %d\n", loaiDieuHoa[2]);
                printf("21000BTU: %d\n", loaiDieuHoa[3]);
                break;
            case 6:
                return;
        }
    } while (1);
}