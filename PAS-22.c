/***************************************************************
 * Judul             : FinanceMate							   *
 * Kelompok          : 22                                      *
 * Nama Pembuat      : Sihombing Giovano Geraldo               *
 * Nama Pembuat      : Muhammad Zhavier Naufal Rachman         *
 * NPM               : 2206059566                              *
 * Tanggal Pembuatan : 29/05/2023                              *
 * Versi Program     : 1.0.0                                   *                                                     
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct user {
	char namae[20];
	struct user *next;
}add;

struct pengeluaran {
    char kategori[50];
    char merk[50];
    int harga_satuan;
    int jumlah;
    struct pengeluaran *next;
    struct user *user;
};


int tampilkan_menu() {
    int pilihan;
    printf("|=======================================|\n");
    printf("|               FINANCEMATE             |\n");
    printf("|=======================================|\n");
    printf("| 1. Input Pengeluaran                  |\n");
    printf("| 2. Tambahkan Pengeluaran              |\n");
    printf("| 3. Hapus Pengeluaran                  |\n");
    printf("| 4. Tampilkan Seluruh Pengeluaran      |\n");
    printf("| 5. Simpan Pengeluaran ke File         |\n");
    printf("| 6. Search Pengeluaran                 |\n");
    printf("| 7. Tambahkan User                     |\n");
    printf("| 8. Tampilkan Daftar User		|\n");
    printf("| 9. Keluar				|\n");
    printf("|=======================================|\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);
    return pilihan;
}


int hitung_total_pengeluaran(struct pengeluaran *head) {
    int total = 0;
    struct pengeluaran *cur = head;
    while (cur != NULL) {
        total += cur->harga_satuan * cur->jumlah;
        cur = cur->next;
    }
    return total;
}

void search_pengeluaran(struct pengeluaran *head, char *namae) {
    printf("PENGELUARAN BERDASARKAN USER\n");
    printf("User: %s\n", namae);
    printf("             			FINANCEMATE            				   	    \n");
    printf("=====================================================================================\n");
    printf("|%-15s|%-15s|%-18s|%-15s|%-15s|\n", "Kategori", "Merk", "Jumlah", "Pengeluaran", "Tanggal");
    printf("=====================================================================================\n");

    struct pengeluaran *cur = head;
    while (cur != NULL) {
        if (strcmp(cur->user->namae, namae) == 0) {
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            char tanggal[11];
            strftime(tanggal, sizeof(tanggal), "%d/%m/%Y", t);

            printf("|%-15s|%-15s|%-18d|%-15d|%-15s|\n", cur->kategori, cur->merk, cur->jumlah, cur->jumlah * cur->harga_satuan, tanggal);
        }
        cur = cur->next;
    }

    printf("=====================================================================================\n");
}



void tampilkan_pengeluaran_terkini(struct pengeluaran *head, struct user *user_head) {
    printf("PENGELUARAN TERKINI\n");
    printf("             			FINANCEMATE            				   	    \n");
    printf("=====================================================================================\n");
    printf("|%-15s|%-15s|%-18s|%-15s|%-15s|\n", "Kategori", "Merk", "Jumlah", "Pengeluaran", "Tanggal");
    printf("=====================================================================================\n");
    struct pengeluaran *cur = head;
    while (cur != NULL) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char tanggal[11];
        strftime(tanggal, sizeof(tanggal), "%d/%m/%Y", t);

        printf("|%-15s|%-15s|%-18d|%-15d|%-15s|\n", cur->kategori, cur->merk, cur->jumlah, cur->harga_satuan * cur->jumlah, tanggal);
        cur = cur->next;
    }
    printf("=====================================================================================\n");
    printf("Total Pengeluaran: %d\n", hitung_total_pengeluaran(head));
    printf("User: %s\n", user_head->namae);
    printf("=====================================================================================\n");
}


void hapus_pengeluaran(struct pengeluaran **head, char kategori[50], char merk[50]) {
    struct pengeluaran *cur = *head;
    struct pengeluaran *prev = NULL;
    while (cur != NULL && strstr(cur->kategori, kategori) != 0 && strstr(cur->merk, merk) != 0) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("Pengeluaran tidak ditemukan\n");
    }
    else {
        if (prev == NULL) {
            *head = cur->next;
        }
        else {
            prev->next = cur->next;
        }
        free(cur);
        printf("PENGELUARAN BERHASIL DIHAPUS!\n");
    }
}

void simpan_ke_file(struct pengeluaran *head, struct user *user) {
    FILE *f = fopen("pengeluaran.txt", "w");
    if (f == NULL) {
        printf("Gagal membuka file pengeluaran.txt\n");
    }
    else {
     fprintf(f, "PENGELUARAN TERKINI\n");
     fprintf(f, "             			FINANCEMATE            				   	    \n");
     fprintf(f, "=====================================================================================\n");
     fprintf(f, "|%-15s|%-15s|%-18s|%-15s|%-15s|\n", "Kategori", "Merk", "Jumlah", "Pengeluaran", "Tanggal");
     fprintf(f, "=====================================================================================\n");
    struct pengeluaran *cur = head;
    while (cur != NULL) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char tanggal[11];
        strftime(tanggal, sizeof(tanggal), "%d/%m/%Y", t);

        fprintf(f, "|%-15s|%-15s|%-18d|%-15d|%-15s|\n", cur->kategori, cur->merk, cur->jumlah, cur->harga_satuan * cur->jumlah, tanggal);
        cur = cur->next;
    }
     fprintf(f, "=====================================================================================\n");
     fprintf(f, "Total Pengeluaran: %d\n", hitung_total_pengeluaran(head));
     fprintf(f, "User: %s\n", user->namae);
     fprintf(f, "=====================================================================================\n");
     fclose(f);
     printf("Pengeluaran Berhasil Tersimpan dalam file pengeluaran.txt\n");
}
}



void tambahkan_budget(int *budget) {
    printf("Masukkan budget: ");
    scanf("%d", budget);
}

void tambahkan_user(struct user **head) {
    struct user *new_user = malloc(sizeof(struct user));
    printf("Masukkan nama user: ");
    scanf("%s", new_user->namae);
    new_user->next = NULL;
    
    if (*head == NULL) {
        *head = new_user;
    }
    else {
        struct user *cur = *head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new_user;
    }
    
    printf("User berhasil ditambahkan!\n");
}

void tampilkan_user(struct user *head){
	printf("DAFTAR USER\n");
	printf("==================================\n");
	printf("|%-15s|\n", "Nama User");
	printf("==================================\n");
	
	struct user *cur = head;
	while (cur != NULL){
		printf("|%-15s|\n", cur->namae);
		cur = cur->next;
	}
	
	printf("==================================\n");
}

void login(){
	int a=0,i=0;
	char uname[10],c=' ';
	char pword[10],code[10];
	char user[10]="user";
	char pass[10]="pass";
	do {
		system("cls");
		
		printf("\n  =========================  LOGIN FORM  =========================  ");
		printf(" \n                       ENTER USERNAME:-");
		scanf("%s", &uname);
		printf(" \n                       ENTER PASSWORD:-");
		while(i<10){
			pword[i]=getch();
			c=pword[i];
			if(c==13) break;
			else printf("*");
			i++;
		}
		pword[i]='\0';
		//char code=pword;
		i=0;
		//scanf("%s",&pword);
		if (strcmp(uname,"user")==0 && strcmp(pword, "pass")==0){
			printf("  \n\n\n       Selamat Datang Dalam FINANCEMATE !!!! Login Berhasil:)");
			printf("\n\n\n\t\t\t\tPress any key to continue...");
			getch();
			break;
		}
		else{
			printf("\n		SORRY!!! Login Tidak Berhasil");
			a++;
			
			getch();
		}
		
	}
	while(a<=2);
	if (a>2){
		printf("\nSorry anda telah memasukan username dan password yang salah sebanyak empat kali!!!!");
		
		getch();
	}
	system("cls");
}

int main() {
	login();
    struct pengeluaran *head = NULL;
    struct user *user_head = NULL;
    int pilihan = tampilkan_menu();
    int budget = 0; 
    while (pilihan != 9) {
        switch (pilihan) {
            case 1: { 
                if (budget > 0) { 
                    char lanjut_input = 'y';
                    while (lanjut_input == 'y') {
                        struct pengeluaran *new_node = malloc(sizeof(struct pengeluaran));
                        printf("Kategori     : ");
                        scanf("%s", new_node->kategori);
                        printf("Nama Item    : ");
                        scanf("%s", new_node->merk);
                        printf("Harga satuan : ");
                        scanf("%d", &new_node->harga_satuan);
                        printf("Jumlah       : ");
                        scanf("%d", &new_node->jumlah);
                        new_node->next = NULL;
                        if (head == NULL) {
                            head = new_node;
                        }
                        else {
                            struct pengeluaran *cur = head;
                            while (cur->next != NULL) {
                                cur = cur->next;
                            }
                            cur->next = new_node;
                        }
                        printf("Lanjut menginput? (y/n) ");
                        scanf(" %c", &lanjut_input);

                      
                        if (hitung_total_pengeluaran(head) > budget) {
                            printf("Peringatan: Pengeluaran melebihi budget Anda! Segera berhemat.\n");
                        }
                    }
                    tampilkan_pengeluaran_terkini(head, user_head);
                    printf("\n");
                    pilihan = tampilkan_menu();
                }
                else {
                    printf("Masukkan Budget Anda terlebih dahulu!\n");
                    tambahkan_budget(&budget);
                }
                
                break;
            }
            case 2: { 
                if (budget > 0) { 
                    char lanjut_input = 'y';
                    while (lanjut_input == 'y') {
                        struct pengeluaran *new_node = malloc(sizeof(struct pengeluaran));
                        printf("Kategori      : ");
                        scanf("%s", new_node->kategori);
                        printf("Merk          : ");
                        scanf("%s", new_node->merk);
                        printf("Harga satuan  : ");
                        scanf("%d", &new_node->harga_satuan);
                        printf("Jumlah        : ");
                        scanf("%d", &new_node->jumlah);
                        new_node->next = NULL;
                        if (head == NULL) {
                            head = new_node;
                        }
                        else {
                            struct pengeluaran *cur = head;
                            while (cur->next != NULL) {
                                cur = cur->next;
                            }
                            cur->next = new_node;
                        }
                        printf("Lanjut menginput? (y/n) ");
                        scanf(" %c", &lanjut_input);

                        
                        if (hitung_total_pengeluaran(head) > budget) {
                            printf("Peringatan: Pengeluaran melebihi budget Anda! Segera berhemat.\n");
                        }
                    }
                    tampilkan_pengeluaran_terkini(head, user_head);
                    pilihan = tampilkan_menu();
                }
                else {
                    printf("Anda belum menentukan budget. Silakan tambahkan budget terlebih dahulu.\n");
                    tambahkan_budget(&budget);
                }
                break;
            }
            case 3: { 
                char kategori[50];
                char merk[50];
                printf("Masukkan kategori: ");
                scanf("%s", kategori);
                printf("Masukkan merk    : ");
                scanf("%s", merk);
                hapus_pengeluaran(&head, kategori, merk);
                tampilkan_pengeluaran_terkini(head, user_head);
                pilihan = tampilkan_menu();
                break;
            }
            case 4: { 
                tampilkan_pengeluaran_terkini(head, user_head);
                pilihan = tampilkan_menu();
                break;
            }
            case 5: { 
                simpan_ke_file(head, user_head);
                pilihan = tampilkan_menu();
                break;
            }
            case 6: {
			    char namae[20];
			    printf("Masukkan nama user: ");
			    scanf("%s", namae);
			    search_pengeluaran(head, namae);
			    pilihan = tampilkan_menu();
			    break;
			}
			case 7: {
				tambahkan_user(&user_head);
				pilihan = tampilkan_menu();
				break;
			}
			case 8: {
				tampilkan_user(user_head);
				pilihan = tampilkan_menu();
				break;
			}
            default: {
                printf("Pilihan tidak valid\n");
                pilihan = tampilkan_menu();
                break;
            }
        }
    }
    printf("TERIMA KASIH TELAH MENGGUNAKAN FINANCEMATE!\n");
    return 0;
}

