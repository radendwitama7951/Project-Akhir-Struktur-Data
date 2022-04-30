/* Program Pengenalan Pupuh Alit
 * by Raden Dwitama Baliano & Awaludin Nazir
 *
 * */


// System Include
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Program Include
#include "template/utilitas.h"
#include "template/program.h"



// Global
void main_menu (struct Data_tersimpan_t **head, struct Padalingsa_t **root) {
	bool running;
	int pilihan;
	running = true;	


	do {
		clrscr;
		printf("======= MENU ========\n");
		printf("1. Proses teks\n2. Lihat data tersimpan\n3. Hapus data tersimpan\n\n0. Keluar\n\n");
		pilihan = get_range(0, 4, "Masukkan pilihan anda : ");

		switch (pilihan) {
			case 1 :
				input_data(head, root);
				break;
			case 2 :
				show_data(*head);
				break;
			case 3 :
				delete_data(head);
				break;
			case 0 :
				print_n_pause("Terima Kasih telah mencoba :)");
				running = false;
				break;
			default :
				print_n_pause ("Pilihan tidak tersedia :(");
		}

	} while (running);

}

int main (void) {
	struct Data_tersimpan_t *head;
	struct Padalingsa_t *root_template_pupuh;
	head = NULL;
	root_template_pupuh = new_padalingsa();

  /**
   * Data Training
   */	
	init_pupuh(&root_template_pupuh, SINOM, 10, "8a", "8i", "8a", "8i", "8i", "8u", "8a", "8i", "4u", "8a");
	init_pupuh(&root_template_pupuh, GINADA, 7, "8a", "8i", "8a", "8u", "8a"," 4i","8a");
	init_pupuh(&root_template_pupuh, GINANTI, 6, "8u","8i","8a","8i","8a","8i");
	init_pupuh(&root_template_pupuh, SEMARANDANA, 7, "8i", "8a", "8e", "8a", "8a","8u", "8a");
	init_pupuh(&root_template_pupuh, MIJIL, 7, "4u", "6i", "6o", "10e", "10i", "6i", "6u");
	init_pupuh(&root_template_pupuh, PUCUNG, 6, "4u", "8u", "6a", "8i", "4u", "8a");
	init_pupuh(&root_template_pupuh, DURMA, 7, "12a", "7i", "6a", "7a", "8i", "5a", "7i");
	init_pupuh(&root_template_pupuh, MASKUMAMBANG, 5, "4u", "8i", "6a", "8i", "8a");
	init_pupuh(&root_template_pupuh, PANGKUR, 7, "8a", "10i", "8u", "8a", "12u", "8a", "8i");
	init_pupuh(&root_template_pupuh, DANGDANGGULA, 10, "10i", "4a", "6a", "8e", "8u", "8i", "8a", "8u", "8a", "4a", "8i", "8a");

	main_menu(&head, &root_template_pupuh);



	return 0;
}
