#include <stdio.h>
#include <stdlib.h>
#include <navalmap.h>

void afficher(navalmap_t * navmap){

  int i, j, k;
  printf("\n\n");
  for(j = 0; j < navmap->size.y; j++){
    for(k = 0; k < navmap->size.x; k++) printf(" + -");
    printf(" +\n");

    for(i = 0; i < navmap->size.x; i++){
      printf(" | ");
      if((int)navmap->map[j][i].type == 1) printf("%c", navmap->map[j][i].id+'A');
      else printf(" ");
    }
    printf(" |\n");
  }
  for(k = 0; k < navmap->size.x; k++) printf(" + -");
  printf(" +\n");
}
