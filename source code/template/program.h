/* Program Interface
 *
 *
 * */
#ifndef __PROGRAM__H__
#define __PROGRAM__H__
enum Pupuh_t {
	UNDEFINED,
	SINOM,
	GINADA,
	GINANTI,
	SEMARANDANA,
	MIJIL,
	PUCUNG,
	DURMA,
	MASKUMAMBANG,
	PANGKUR,
	DANGDANGGULA
};

struct Data_t {
	char filename[128];
	char teks[1024];
	char padalingsa[64];
	enum Pupuh_t jenis;
	char waktu_proses[32];	
};

struct Data_tersimpan_t {
	struct Data_t *data;
	struct Data_tersimpan_t *next;
	struct Data_tersimpan_t *prev;
};

struct Padalingsa_t {
	enum Pupuh_t jenis;
	int guru_dingdong[5];
	struct Padalingsa_t **guru_wilang;
};

struct Padalingsa_t *new_padalingsa ();
void init_pupuh (struct Padalingsa_t **root, enum Pupuh_t jenis, int jumlah_baris, ...);
void input_data (struct Data_tersimpan_t **head, struct Padalingsa_t **root);
void show_data (struct Data_tersimpan_t *head);
void delete_data (struct Data_tersimpan_t **head);

#endif /* __PROGRAM__H__ */
