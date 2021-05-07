#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "navalmap.h"
#include "gestion_actions.h"
#include "lire_fichier.h"

void lire_fichier(char *nom, navalmap_t ** navmap, WARSHIP ** croiseur){
 	
  int fd;
  
  fd = open(nom, O_RDONLY);
  if(!fd) exit(11);
  char buf[256];

  char typeCarte[10] = {0}, tailleX[10] = {0}, tailleY[10] = {0}, nbJoueurs[10] = {0}, Cmax[10] = {0}, Kmax[10] = {0}, nbTours[10] = {0};
  if((read(fd,buf,256))< 0)
  {
	 perror("read");
	 exit(11);
  } 

  buf[255] = '\0';
  sscanf(buf, "%[^;];%[^;];%[^\n]%*c%[^;];%[^;];%[^;];%[^;];", typeCarte, tailleX, tailleY, nbJoueurs, Cmax, Kmax, nbTours);
  

  close(fd);
  
  printf("typeCarte: %s \n", typeCarte);
  printf("tailleX: %s \n", tailleX);
  printf("tailleY: %s \n", tailleY);
  printf("nbJoueurs: %s \n", nbJoueurs);
  printf("Cmax: %s \n", Cmax);
  printf("Kmax: %s \n", Kmax);
  printf("nbTours: %s \n", nbTours);

  //COORDONNES
  coord_t coord;
  coord.x = atoi(tailleX);
  coord.y = atoi(tailleY);

  printf("coordx = %d\n", coord.x);
  printf("coordy = %d\n", coord.y);

  //TYPECARTE
  map_t carte;
  if(!strcmp(typeCarte, "rectangle")) carte = MAP_RECT;
  else carte = MAP_TOTAL;

  printf("carte = %d\n", (int)carte);

  //INIT MAP
  *navmap = init_navalmap(carte, coord, atoi(nbJoueurs));

  //INIT WARSHIP
  int nbj = atoi(nbJoueurs);
  *croiseur = malloc(nbj * sizeof(WARSHIP));
  if(!croiseur) exit(12);
  for(int k = 0; k < atoi(nbJoueurs); k++){
    (*croiseur)[k].Cmax = atoi(Cmax);
    (*croiseur)[k].Kmax = atoi(Kmax);
    (*croiseur)[k].radar.Cscn = -1;
    (*croiseur)[k].radar.Pscn.x = -1;
    (*croiseur)[k].radar.Pscn.y = -1;
    (*croiseur)[k].radar.timerLoc = MAXTOURS;
    (*croiseur)[k].radar.timerRadar = MAXTOURS;
    
  }
}


void freeShips(WARSHIP * croiseur, int nbShips){
  free(croiseur);
}


void majRadar(DATARADAR *radar, int ind, coord_t position, entityid_t occupant){

  radar->zone[ind].occupant = occupant;
  radar->zone[ind].position = position;

}
