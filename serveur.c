#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <navalmap.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "serveur.h"
#include "afficher.h"
#include "gestion_actions.h"


void client(WARSHIP croiseur, int idShip, coord_t pos){

  int tube[2];
  char sodfifo[20];
  
  sprintf(sodfifo,"/tmp/sodfifo_%d.0", idShip);
  mkfifo(sodfifo, 0666);
  tube[0] = open(sodfifo, O_WRONLY);

  sprintf(sodfifo,"/tmp/sodfifo_%d.1", idShip);
  mkfifo(sodfifo, 0666);
  tube[1] = open(sodfifo, O_RDONLY);
  

  ACTION act;
  MAJ update;
  while(croiseur.Cmax > 0){
    act.pos.x = 0;
    act.pos.y = 0;


    /////Si le radar ne s'est pas actualisé depuis x tours;
    if(croiseur.radar.timerLoc > 2){ 
      sprintf(act.choix, "SCN");
    }

    /////Si le navire le plus proche est TROP proche, on s'éloigne
    else if(abs(croiseur.radar.Pscn.x - pos.x) + abs(croiseur.radar.Pscn.y - pos.y) < 2){
      sprintf(act.choix, "MOV");
      if(pos.x < croiseur.radar.Pscn.x)
	act.pos.x = -1;
      else if(pos.x == croiseur.radar.Pscn.x)
	act.pos.x = 0;
      else
	act.pos.x = 1;

      if(pos.y < croiseur.radar.Pscn.y)
	act.pos.y = -1;
      else if(pos.y == croiseur.radar.Pscn.y)
	act.pos.y = 0;
      else
	act.pos.y = 1;
    }
    //////Si un navire est à porté d'attaque d'un autre, on attaque
    else if(abs(croiseur.radar.Pscn.x - pos.x) + abs(croiseur.radar.Pscn.y - pos.y) < 4 ){
      sprintf(act.choix, "ATK");
      act.pos = croiseur.radar.Pscn;
    }
    /////Si le navire le plus proche est hors de portée d'attaque, on s'approche
    else{
      sprintf(act.choix, "MOV");
      if(pos.x < croiseur.radar.Pscn.x)
	act.pos.x = 1;
      else if(pos.x == croiseur.radar.Pscn.x)
	act.pos.x = 0;
      else
	act.pos.x = -1;

      if(pos.y < croiseur.radar.Pscn.y)
	act.pos.y = 1;
      else if(pos.y == croiseur.radar.Pscn.y)
	act.pos.y = 0;
      else
	act.pos.y = -1;
    }

    write(tube[0], &act, sizeof(act));
    
    // while(act.sync != 3)
    read(tube[1], &update, sizeof(update));
    croiseur = update.croiseur;
    pos = update.pos;
  }
  close(tube[0]);
  close(tube[1]);
  unlink(sodfifo);
}


void serveur(navalmap_t * navmap, WARSHIP * croiseur){

  pid_t pid;
  
  for(int i = 0; i < navmap->nbShips; i++){
    pid = fork();
    if(pid == 0){
      client(croiseur[i], i, navmap->shipPosition[i]);
      exit(0);
    }
  }

  //----------------------------
  
  int ** tube;
  int * perdu;
  int compteur = navmap->nbShips, fin = 0, winner = -1;
  char sodfifo[20];
  ACTION * act;
  MAJ update;

  perdu = malloc(navmap->nbShips*sizeof(int));
  act = malloc(navmap->nbShips*sizeof(struct action));
  tube = malloc(navmap->nbShips*sizeof(int *));

  for(int i = 0; i < navmap->nbShips; i++) {
    tube[i] = malloc(2*sizeof(int));
    perdu[i] = 0;
  }
  
  for(int i = 0; i < navmap->nbShips; i++){
  sprintf(sodfifo,"/tmp/sodfifo_%d.0", i);
  mkfifo(sodfifo, 0666);
  tube[i][0] = open(sodfifo, O_RDONLY);

  sprintf(sodfifo,"/tmp/sodfifo_%d.1", i);
  mkfifo(sodfifo, 0666);
  tube[i][1] = open(sodfifo, O_WRONLY);

  }
  
  for(int tour = 0; tour < 20 && !fin; tour++){
    printf("\nTour: %d\n", tour);
    ///S'il ne reste qu'un navire ou moins, on amorce l'arret du jeu
    if(compteur <= 1) fin = 1;

    ////On récupère les actions de tous les navires
    for(int i = 0; i < navmap->nbShips; i++){
      if(perdu[i]) continue;
      read(tube[i][0], &(act[i]), sizeof(act[i]) );
      if(!fin);
	//printf("\nReçu: %s\n", act[i].choix);
      else {
	winner = i;
	break;
      }
    }
      

    ///Arret du jeu (si fin = 1)
    if(fin){
      if(compteur == 1){
	croiseur[winner].Cmax = 0;
	write(tube[winner][1], &update, sizeof(update));
      	//wait(NULL);
	printf("\n******Victoire du croiseur %c******\n", winner+'A');
      }
      else
	printf("\n******Aucun survivant******\n");

      break;
    }


    
    ///Etape de résolution, les attaques en premier, puis les mouvements, puis les supports
    for(int i = 0; i < 3; i++){
      if(i==1){
      	deplacementsSimult(navmap, croiseur, act);
      	continue;
      }
      for(int j = 0; j < navmap->nbShips; j++){
	if(perdu[j]) continue;
	if(i==0){
	  if(strcmp(act[j].choix, "ATK") == 0)
	    attaque(navmap, croiseur, j, act[j].pos);
	}
	else if(i==2){
	  if(strcmp(act[j].choix, "SCN") == 0){
	    localise(navmap, croiseur, j);
	  }
	}
      }
    }
    
    //////On renvoie à chaque navire son nouveau statut
    for(int i = 0; i < navmap->nbShips; i++){
      if(perdu[i]) continue;
      printf("\nCroiseur %c: K=%d, C=%d, action= %s\n", i+'A', croiseur[i].Kmax, croiseur[i].Cmax, act[i].choix);
      update.croiseur = croiseur[i];
      update.pos = navmap->shipPosition[i];
      write(tube[i][1], &update, sizeof(update));
      if(!perdu[i] && croiseur[i].Cmax <= 0){
	wait(NULL);
	perdu[i] = 1; 
	compteur--;
	navmap->map[navmap->shipPosition[i].y][navmap->shipPosition[i].x].type = ENT_SEA;
      }
    }
  
    afficher(navmap);
    sleep(1);
  }

  for(int i = 0; i < navmap->nbShips; i++){
    
    close(tube[i][0]);
    close(tube[i][1]);
  }

  for(int i = 0; i < navmap->nbShips; i++){
    free(tube[i]);
  }
  free(tube);
  free(act);
  
  return;
}
