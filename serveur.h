#include <navalmap.h>
#include <string.h>
#include "gestion_actions.h"

#ifndef __SERVEUR
#define __SERVEUR

typedef struct maj{
  WARSHIP croiseur;
  coord_t pos;
} MAJ;

void serveur(navalmap_t *, WARSHIP *);
void client(WARSHIP, int, coord_t);

#endif
