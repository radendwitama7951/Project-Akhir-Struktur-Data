/* Program Logic
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include "../template/utilitas.h"
#include "../template/program.h"

const char *pupuh[16] = {	
	"Tidak Dikenali",
	"Sinom",
	"Ginada",
	"Ginanti",
	"Semarandana",
	"Mijil",
	"Pucung",
	"Durma",
	"Maskumambang",
	"Pangkur",
	"Dangdanggula"
};

// Temp
struct Padalingsa_baris_t {
	char padalingsa[4];
	struct Padalingsa_baris_t *next;
};

static void insert_padalingsa_pupuh (struct Padalingsa_baris_t **head, struct Padalingsa_baris_t **tail, struct Padalingsa_baris_t *new) {
	if (*head != NULL) {
		(*tail)->next = new;
		*tail = (*tail)->next;
	}
	else
		*head = *tail = new;
}

// Constructor
static struct Padalingsa_baris_t *new_padalingsa_pupuh (const char *padalingsa) {
	struct Padalingsa_baris_t *new = (struct Padalingsa_baris_t*) malloc(sizeof(struct Padalingsa_baris_t));
	if (!new) {
		print_n_pause("Gagal membaca padalingsa baru ! :(");
		exit(EXIT_FAILURE);
	}
	
	strcpy(new->padalingsa, padalingsa);
	new->next = NULL;

	return new;
}
//
static int labuh_suara_to_int (char labuh_suara) {
	int res;
	switch (labuh_suara) {
		case 'a' : case 'A' :
			res = 0;
			break;
		case 'i' : case 'I' :
			res = 1;
			break;
		case 'u' : case 'U' :
			res = 2;
			break;
		case 'e' : case 'E' :
			res = 3;
			break;
		case 'o' : case 'O' :
			res = 4;
			break;
		default :
			res = -1;
	}
	return res;
}

static int get_labuh_suara (const char padalingsa[4]) {
	int res;
	if (isalpha(padalingsa[2]))
		res = labuh_suara_to_int(padalingsa[2]);
	else if (isalpha(padalingsa[1]))
		res = labuh_suara_to_int(padalingsa[1]);
	else
		res = -1;

	return res;
}

// New Padalingsa
struct Padalingsa_t *new_padalingsa () {
	struct Padalingsa_t *new;
	new = (struct Padalingsa_t*) malloc(sizeof(struct Padalingsa_t));
	if (!new) {
		print_n_pause("Gagal membuat Padalingsa baru ! :(");
		exit(EXIT_FAILURE);
	}

	new->guru_wilang = (struct Padalingsa_t**) calloc(13, sizeof(struct Padalingsa_t*));
	if (!new->guru_wilang) {
		print_n_pause("Gagal membuat Padalingsa baru ! :(");
		exit(EXIT_FAILURE);
	}

	memset(new->guru_dingdong, 0, 5*sizeof(int));

	return new;
}

// INIT PUPUH
void init_pupuh (struct Padalingsa_t **root, enum Pupuh_t jenis, int jumlah_baris, ...) {
	va_list ap;
	va_start(ap, jumlah_baris);
	struct Padalingsa_t *tmp;
	int tmp_guru_wilang, tmp_guru_dingdong;
	char tmp_padalingsa[4];

	tmp = *root;	
	for (int i = 0; i < jumlah_baris; i++) {
		strcpy(tmp_padalingsa, va_arg(ap, char*));

		tmp_guru_wilang = atoi(tmp_padalingsa);
		tmp_guru_dingdong = get_labuh_suara(tmp_padalingsa);
		if (tmp_guru_dingdong == -1) {
			print_n_pause("Input %s tidak valid ! :(", tmp_padalingsa);
			return;
		}
		// ELSE Continue
		if (tmp->guru_wilang[tmp_guru_wilang] == NULL)
			tmp->guru_wilang[tmp_guru_wilang] = new_padalingsa();
		// ELSE Continue
		tmp = tmp->guru_wilang[tmp_guru_wilang];
		tmp->guru_dingdong[tmp_guru_dingdong] = 1;
		tmp->jenis = UNDEFINED;	
	}
	tmp->jenis = jenis;
}

// PROSES PENGENALAN PUPUH
static enum Pupuh_t search_pupuh (struct Padalingsa_t **root, struct Padalingsa_baris_t *head) {
	struct Padalingsa_t *tmp_padalingsa_root;
	struct Padalingsa_baris_t *tmp_padalingsa_baris;
	enum Pupuh_t res;
	int tmp_guru_wilang, tmp_guru_dingdong;
	tmp_padalingsa_root = *root;

	for (tmp_padalingsa_baris = head; tmp_padalingsa_baris != NULL; tmp_padalingsa_baris = tmp_padalingsa_baris->next) {

		tmp_guru_wilang = atoi(tmp_padalingsa_baris->padalingsa);
		tmp_guru_dingdong = get_labuh_suara(tmp_padalingsa_baris->padalingsa);
		tmp_padalingsa_root = tmp_padalingsa_root->guru_wilang[tmp_guru_wilang];

		if (tmp_padalingsa_root != NULL) {
			if (tmp_padalingsa_root->guru_dingdong[tmp_guru_dingdong] == 1) {
				continue;
			}
			else
				return UNDEFINED;
		} else
			return UNDEFINED;	
	}

	res = tmp_padalingsa_root->jenis;
	return res;
}

static struct Data_t *new_data (const char *filename, FILE *fp, enum Pupuh_t jenis, const char *waktu_proses) {
	struct Data_t *new;
	new = (struct Data_t*) malloc(sizeof(struct Data_t));
	if (!new) {
		print_n_pause("Tidak dapat membuat data baru ! :(");
		return new;
	} else {
	
		strcpy(new->filename, filename);
		fseek(fp, 0, SEEK_END);
		size_t fsize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		fread(new->teks, 1, fsize, fp);
		strcpy(new->waktu_proses, waktu_proses);
		new->jenis = jenis;
		return new;
	}
}

static struct Data_tersimpan_t *new_data_tersimpan (struct Data_t *data) {
	struct Data_tersimpan_t *new;
	new = (struct Data_tersimpan_t*) malloc(sizeof(struct Data_tersimpan_t));
	if (!new) {
		print_n_pause("Tidak dapat membuat data tersimpan baru ! :(");
		return new;
	} else {
		new->data = data;
		new->next = NULL;
		new->prev = NULL;
		return new;
	}
}

// Cari guru wilang & guru dingdong
char *get_padalingsa (char str[256]) {
	int chasc, i, j=1, voc = 0, /*line[13],*/ kons;
	char /*ch,*/ lastvoc/*, lastvocal[13]*/;
	char *hasil = malloc(4);
	// printf("Masukkan kata :\n");
	// scanf("%[^\n]s", str);
	for(i=0; str[i]!='\0'; i++){
		chasc=str[i];
		
		if(chasc=='\n'){
			//line[j]=voc;
			//lastvocal[j]=lastvoc;
			j++;
			//voc=0;
		}
		
		switch(chasc){
			case 'a': case 'A':
				lastvoc='a';
				voc++;
			break;
			case 'e': case 'E':
				lastvoc='e';
				voc++;
			break;
			case 'i': case 'I':
				lastvoc='i';
				voc++;
			break;
			case 'o': case 'O':
				lastvoc='o';
				voc++;
			break;
			case 'u': case 'U':
				lastvoc='u';
				voc++;
			break;
			default:
			kons++;
			break;
		}
	}
	//printf("\n\nGuru Wilangan-Guru Gatra\n");
	//for(i=1;i<=j;i++){
		//printf("%d%c", voc, lastvoc);
		// if(i+1>j)
		// 	continue;
		// else
		// 	printf("-");
	//}

	snprintf(hasil, 4, "%d%c", voc, lastvoc);
	//printf("\n======\n%d%c\n=======\n\n", voc, lastvoc);

	return hasil;
}

void simpan_data (struct Data_tersimpan_t **head, struct Data_t *new_data) {
	struct Data_tersimpan_t *new;
	new = new_data_tersimpan(new_data);
	
	if (*head != NULL) {
		(*head)->prev = new;
		new->next = *head;
		*head = new;
	} else {
		*head = new;
	}

}

// INPUT
void input_data (struct Data_tersimpan_t **head, struct Padalingsa_t **root) {
	FILE *fp;
  char *dir = "data/";
	char *filename;
  char *target; 
	int ulangi, is_simpan_data;

  target = malloc(128);

	do {	
		ulangi = 0;
		filename = get_string(32, "\nMasukkan nama file yang ingin diproses : "); 
    memcpy(target, dir, 6);
    strncat(target, filename, 32);


		fp = fopen(target, "r");
		if (fp == NULL) {
			print_n_pause("\nTidak dapat membuka file %s :(\nPeriksa folder \"data/\"\n", target);
      ulangi = 1;
      /*
			ulangi = get_int(NONEGATIVE, "Masukkan 1 untuk coba lagi : ");
			if (ulangi == 1)
				continue;
			else
				return;
      */
		}
		else ulangi = 0;
	} while (ulangi);

	
	struct Data_t *new;

	struct Padalingsa_baris_t *head_padalingsa_pupuh, *tail_padalingsa_pupuh, *tmp_padalingsa_baris, *tmp_hapus;
	head_padalingsa_pupuh = tail_padalingsa_pupuh = NULL;
	char tmp_line[256];
	int counter = 0;
	fseek(fp, 0, SEEK_SET);
	while (fgets(tmp_line, sizeof(tmp_line), fp)) {
		tmp_padalingsa_baris = new_padalingsa_pupuh(get_padalingsa(tmp_line));		
		insert_padalingsa_pupuh(&head_padalingsa_pupuh, &tail_padalingsa_pupuh, tmp_padalingsa_baris);
	}
	
	// Inisiasi Data baru
	new = new_data(filename, fp, search_pupuh(root, head_padalingsa_pupuh), get_time(FULL));

	tmp_padalingsa_baris = head_padalingsa_pupuh;
	while (tmp_padalingsa_baris != NULL) {
		counter += sprintf(new->padalingsa + counter, "%s%s", tmp_padalingsa_baris->padalingsa, (tmp_padalingsa_baris->next == NULL) ? "" : "-");
		tmp_hapus = tmp_padalingsa_baris;
		tmp_padalingsa_baris = tmp_padalingsa_baris->next;
		free(tmp_hapus);
	}

	print_n_pause("\n\n%s\nBerhasil membaca file %s\n\nTeks :\n%s\n\nPadalingsa : %s\nJenis : %s\n", new->waktu_proses, new->filename, new->teks, new->padalingsa, pupuh[new->jenis]);
	
	
	is_simpan_data = get_range(0, 2, "Simpan data ? (input 1 jika iya, 0 jika tidak) : ");
	if (is_simpan_data)
		simpan_data(head, new);


  free(filename);
  free(target);

}

// SHOW
void show_data (struct Data_tersimpan_t *head) {
	if (!head) {
		print_n_pause("Head kosong ! :(");
		return;
	} else {
		struct Data_tersimpan_t *tmp = head;
		int i = 0;
		while (tmp != NULL) {
			printf(" %d. %s\t", ++i, tmp->data->waktu_proses);
			printf("Filename : %s\n", tmp->data->filename);
			
			tmp = tmp->next;
		}
		int lihat = get_range(1, i+1, "\n\nMasukkan nomor data yang hendak dilihat : ");
		tmp = head;
		for (int i = 1; i < lihat; i++) {
			tmp = tmp->next;
		}
		print_n_pause("\n\n%s\nMembaca data %s\n\nTeks :\n%s\n\nPadalingsa : %s\nJenis : %s\n", tmp->data->waktu_proses, tmp->data->filename, tmp->data->teks, tmp->data->padalingsa, pupuh[tmp->data->jenis]);

	}
}

// DELETE
void delete_data (struct Data_tersimpan_t **head) {
	struct Data_tersimpan_t *tmp = *head;
	int i = 0;
	while (tmp != NULL) {
		printf("%d. Filename : %s\t\t", ++i, tmp->data->filename);
		printf("Waktu : %s\n", tmp->data->waktu_proses);
		tmp = tmp->next;
	}

	if (!(*head)) {
		print_n_pause("List Kosong ! :(");
		return;
	} else  {
		int hapus = get_range(1, i+1, "Masukkan nomor data yang ingin dihapus : ");
		tmp = *head;
		for (int i = 1; i < hapus; i++) {
			tmp = tmp->next;
		}

		if (tmp == *head) {
			*head = (*head)->next;
			free(tmp);
		} else {
			if (tmp->next != NULL) {
				tmp->next->prev = tmp->prev;
				tmp->prev->next = tmp->next;
				free(tmp);
			} else {
				tmp->prev->next = NULL;
				free(tmp);
			}
		}
	}
}
