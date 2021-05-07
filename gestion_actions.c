#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <navalmap.h>
#include "gestion_actions.h"
#include "lire_fichier.h"

void attaque(navalmap_t * navmap, WARSHIP * croiseur, int idShip, coord_t cible){
 
  croiseur[idShip].radar.timerLoc++;
  croiseur[idShip].radar.timerRadar++;
  
  if((abs(cible.x - navmap->shipPosition[idShip].x) + abs(cible.y - navmap->shipPosition[idShip].y)) < 2 || (abs(cible.x - navmap->shipPosition[idShip].x) + abs(cible.y - navmap->shipPosition[idShip].y)) > 4){
    printf("Croiseur %d: Cible hors de portée.\n", idShip);
    return;
  }

  else{
    for(int k = 0; k < navmap-> nbShips; k++){
      if(croiseur[k].Cmax <= 0) continue;
      if(navmap->shipPosition[k].x == cible.x && navmap->shipPosition[k].y == cible.y)
	croiseur[k].Cmax -= 40;

      else if(navmap->shipPosition[k].x == cible.x){
	if(navmap->shipPosition[k].y == cible.y+1 || navmap->shipPosition[k].y == cible.y-1)
	  croiseur[k].Cmax -= 20;
      }
      else if(navmap->shipPosition[k].y == cible.y){
	if(navmap->shipPosition[k].x == cible.x+1 || navmap->shipPosition[k].x == cible.x-1)
	  croiseur[k].Cmax -= 20;
      } 
    }
    croiseur[idShip].Kmax -= 5;
  }
}


void bombardier(navalmap_t * navmap, WARSHIP * croiseur, int idShip, coord_t cible){
 
  croiseur[idShip].radar.timerLoc++;
  croiseur[idShip].radar.timerRadar++;
  
  if((abs(cible.x) + abs(cible.y)) < 1 || (abs(cible.x) + abs(cible.y)) > 5){
    printf("Croiseur %d: Attaque impossible.\n", idShip);
    return;
  }

  else{
    for(int k = 0; k < navmap-> nbShips; k++){

      if(navmap->shipPosition[k].x == cible.x+navmap->shipPosition[idShip].x && navmap->shipPosition[k].y == cible.y+navmap->shipPosition[idShip].y)
	croiseur[k].Cmax -= 30;

    }
    croiseur[idShip].Kmax -= 3;
  }
}


void deplace(navalmap_t * navmap, WARSHIP * croiseur, int idShip, coord_t cible){

  if(navmap->map[navmap->shipPosition[idShip].y + cible.y][navmap->shipPosition[idShip].x + cible.x].type == ENT_SEA){
    moveShip(navmap, idShip, cible);
  }

  else if(navmap->map[navmap->shipPosition[idShip].y + cible.y][navmap->shipPosition[idShip].x + cible.x].type == ENT_SHIP){
    if(navmap->isMovePossible(navmap, idShip, cible)){
      croiseur[idShip].Cmax -= 5;
      croiseur[navmap->map[navmap->shipPosition[idShip].y + cible.y][navmap->shipPosition[idShip].x + cible.x].id].Cmax -= 5;
    }
  }

  croiseur[idShip].Kmax -= 2;
  croiseur[idShip].radar.timerLoc++;
  croiseur[idShip].radar.timerRadar++;
}


void deplacementsSimult(navalmap_t * navmap, WARSHIP * croiseur, ACTION * act){
  const int tailletab = navmap->nbShips;
  int conflit[tailletab];
  int puni[tailletab];
  for(int i = 0; i < navmap->nbShips; i++){
    conflit[i] = 0;
    puni[i] = 0;
  }
  
  
  for(int i = 0; i < navmap->nbShips; i++){
    if(puni[i] || strcmp(act[i].choix, "MOV") != 0) continue;

    for(int j = 0; j < navmap->nbShips; j++){
      if(j == i) continue;

      if(navmap->shipPosition[j].x + act[j].pos.x == navmap->shipPosition[i].x + act[i].pos.x && navmap->shipPosition[j].y + act[j].pos.y == navmap->shipPosition[i].y + act[i].pos.y){
	conflit[j]++;
	conflit[i]++;
      }
    }

    for(int k = 0; k < navmap->nbShips; k++){
      if(conflit[k]){
	croiseur[k].Cmax -= 10;
	croiseur[k].Kmax -= 2;
	puni[k]++;
	conflit[k] = 0;
      }
    }
  }

  for(int i = 0; i < navmap->nbShips; i++){
    if(!puni[i] && strcmp(act[i].choix, "MOV") == 0) deplace(navmap, croiseur, i, act[i].pos);
  }
  
}


void charge(navalmap_t * navmap, WARSHIP * croiseur, int idShip, coord_t cible){
  coord_t backup;

  backup.x = -cible.x; backup.y = -cible.y;
  croiseur[idShip].radar.timerLoc++;
  croiseur[idShip].radar.timerRadar++;
  
  if(cible.x == 0 || cible.y == 0){
    if(abs(cible.y) == 4 || abs(cible.y) == 5 || abs(cible.x) == 4 || abs(cible.x) == 5){
      deplace(navmap, croiseur, idShip, cible);
      for(int k = 0; k < navmap->nbShips; k++){
	if(k == idShip) continue;
	if(navmap->shipPosition[idShip].x == navmap->shipPosition[k].x && navmap->shipPosition[idShip].y == navmap->shipPosition[k].y){
	  croiseur[k].Cmax -= 50;
	  croiseur[idShip].Cmax -= 5;
	  croiseur[idShip].Kmax -= 3;
	  deplace(navmap, croiseur, idShip, backup);
	}
      }
    }
  }
}


void reparation(WARSHIP * croiseur, int idShip){
  if(croiseur[idShip].Kmax < 20){
    printf("Croiseur %d, pas assez de carburant pour une reparation.", idShip);
    return;
  }
  croiseur[idShip].radar.timerLoc++;
  croiseur[idShip].radar.timerRadar++;
  croiseur[idShip].Cmax += 25;
  croiseur[idShip].Kmax -= 20;
  if(croiseur[idShip].Cmax > CMAX)
    croiseur[idShip].Cmax = CMAX;

}

void localise(navalmap_t * navmap, WARSHIP * croiseur,  int idShip){
 
  int min = navmap->size.x + navmap->size.y;
  int idmin = idShip;
  croiseur[idShip].radar.timerLoc = 0;
  croiseur[idShip].radar.timerRadar++;
  
  for(int k = 0; k < navmap->nbShips; k++){
    if(k == idShip) continue;
    if(croiseur[k].Cmax > 0){
      if(abs(navmap->shipPosition[k].x - navmap->shipPosition[idShip].x) + abs(navmap->shipPosition[k].y - navmap->shipPosition[idShip].y) <= min){
	idmin = k;
	min = abs(navmap->shipPosition[k].x - navmap->shipPosition[idShip].x) + abs(navmap->shipPosition[k].y - navmap->shipPosition[idShip].y);
      }
    }
    
  }

  //printf("\nidmin: %d\n", idmin);
  croiseur[idShip].radar.Cscn = croiseur[idmin].Cmax;
  croiseur[idShip].radar.Pscn.x = navmap->shipPosition[idmin].x;
  croiseur[idShip].radar.Pscn.y = navmap->shipPosition[idmin].y;
  //printf("Croiseur %c: Croiseur de Coque %d localisé en %d;%d\n", idShip + 'A', croiseur[idShip].radar.Cscn, croiseur[idShip].radar.Pscn.x, croiseur[idShip].radar.Pscn.y);
}

void radar(navalmap_t * navmap, WARSHIP * croiseur, int idShip){
  int i, j, k=0;
  croiseur[idShip].radar.timerRadar = 0;
  croiseur[idShip].radar.timerLoc++;
  for(int h = 0; h < 24; h++) {
    croiseur[idShip].radar.zone[h].occupant.type = ENT_SEA;
    croiseur[idShip].radar.zone[h].occupant.id = 0;
    croiseur[idShip].radar.zone[h].position.x = 0;    
    croiseur[idShip].radar.zone[h].position.y = 0;
  }
  
  for(j = -3; j < 4; j++){
    for(i = -3; i < 4; i++){

      if(j == 0 || i == 0 || abs(i)+abs(j) > 3) continue;
      if(j + navmap->shipPosition[idShip].y > navmap->size.y || j + navmap->shipPosition[idShip].y < 0 || i + navmap->shipPosition[idShip].x > navmap->size.x || i + navmap->shipPosition[idShip].x < 0) continue;
      
      if(navmap->map[j + navmap->shipPosition[idShip].y][i + navmap->shipPosition[idShip].x].type != ENT_SEA){
	majRadar(&croiseur[idShip].radar, k, navmap->shipPosition[navmap->map[j + navmap->shipPosition[idShip].y][i + navmap->shipPosition[idShip].x].id], navmap->map[j + navmap->shipPosition[idShip].y][i + navmap->shipPosition[idShip].x]);

	printf("Croiseur %c: Entitée détectée en %d;%d", idShip+'A', croiseur[idShip].radar.zone[k].position.x, croiseur[idShip].radar.zone[k].position.y);
	k++;
      }
    }
  }
}
