#include <navalmap.h>
#include "gestion_actions.h"

#ifndef __LIRE_FICHIER_H
#define __LIRE_FICHIER_H

void lire_fichier(char *, navalmap_t **, WARSHIP **);
void freeShips(WARSHIP *, int);
//ListeRadar * init_radar();
//void majRadar(DATARADAR *, int, coord_t, entityid_t);
/* void supprimer(ListeRadar *); */
/* void cleanRadar(ListeRadar *); */
/* void freeRadar(ListeRadar *); */

#endif
