#include <navalmap.h>

#ifndef __GESTION_ACTIONS_H
#define __GESTION_ACTIONS_H

#define CMAX 50
#define KMAX 100
#define MAXTOURS 20

typedef struct element{
  coord_t position;
  entityid_t occupant;
} ELEMENT;


typedef struct dataRadar{

  ELEMENT zone[24];
  int timerRadar;
  int timerLoc;
  int Cscn;
  coord_t Pscn;

} DATARADAR;

typedef struct warship{

  int Cmax;
  int Kmax;
  DATARADAR radar;
} WARSHIP;

typedef struct action{
  char choix[4];
  coord_t pos;
} ACTION;


void attaque(navalmap_t *, WARSHIP *, int, coord_t);
void bombardier(navalmap_t *, WARSHIP *, int, coord_t);
void deplace(navalmap_t *, WARSHIP *, int, coord_t);
void deplacementsSimult(navalmap_t *, WARSHIP *, ACTION *);
void charge(navalmap_t *, WARSHIP *, int, coord_t);
void reparation(WARSHIP *, int);
void localise(navalmap_t *, WARSHIP *, int);
void radar(navalmap_t *, WARSHIP *, int);
void majRadar(DATARADAR *, int, coord_t, entityid_t);

#endif
