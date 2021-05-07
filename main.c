#include <stdio.h>
#include <stdlib.h>
#include <navalmap.h>
#include <unistd.h>
#include "lire_fichier.h"
#include "afficher.h"
#include "gestion_actions.h"
#include "serveur.h"

int main(int argc, char *argv[]){

  navalmap_t * navmap;
  WARSHIP * croiseur;

  initNavalMapLib();
  lire_fichier(argv[1], &navmap, &croiseur);
  sleep(2);
  placeRemainingShipsAtRandom(navmap);
  serveur(navmap, croiseur);

  
  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Kmax); */

  /* //////////////////////////////// */
  /* //demo Alpha */
  /* //////////////////////////////// */
  
  /* //  tour 0 */
  /* coord_t move; */
  /* char trash; */
  
  /* move.x = 1; move.y = 2; */
  /* placeShip(navmap, 0, move); */

  /* move.x = 8; move.y = 7; */
  /* placeShip(navmap, 1, move); */
  

  /* /\* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); *\/ */
  /* /\* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); *\/ */
  /* /\* printf("\nCroiseur %d, T: %d", 0, croiseur[0].infoRadar->timer); *\/ */
  /* /\* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); *\/ */
  /* /\* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); *\/ */

  
  /* //tour 1 */
  
  /* scanf("%c", &trash); */
  
  /* move.x = 1; move.y = 0; */
  /* deplace(navmap, croiseur, 0, move); */

  /* move.x = 0; move.y = 2; */
  /* deplace(navmap, croiseur, 1, move); */
  /* afficher(navmap); */


  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */

  
  /* //tour 2 */
  
  /* scanf("%c", &trash); */
  
  /* move.x = 0; move.y = -1; */
  /* deplace(navmap, croiseur, 0, move); */

  /* move.x = 1; move.y = 0; */
  /* deplace(navmap, croiseur, 1, move); */
  /* afficher(navmap); */


  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */

  
  /* //Tour 3 */
  /* scanf("%c", &trash); */

  /* move.x = 3; move.y = 3; */
  /* attaque(navmap, croiseur, 0, move); */

  /* move.x = 0; move.y = -2; */
  /* deplace(navmap, croiseur, 1, move); */
  /* afficher(navmap); */

  
  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */

  
  /* //Tour 4 */
  /* scanf("%c", &trash); */

  /* move.x = 2; move.y = 0; */
  /* deplace(navmap, croiseur, 0, move); */

  /* move.x = 0; move.y = -2; */
  /* deplace(navmap, croiseur, 1, move); */
  /* afficher(navmap); */

  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Kmax); */

  
  /* //Tour 5 */
  /* scanf("%c", &trash); */

  /* move.x = 1; move.y = 0; */
  /* deplace(navmap, croiseur, 0, move); */

  /* move.x = -2; move.y = 0; */
  /* deplace(navmap, croiseur, 1, move); */
  /* afficher(navmap); */

  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */


  
  /* //Tour 6 */
  /* scanf("%c", &trash); */

  /* move.x = 7; move.y = 3; */
  /* attaque(navmap, croiseur, 0, move); */

  /* move.x = 0; move.y = -1; */
  /* deplace(navmap, croiseur, 1, move); */
  /* afficher(navmap); */

  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */

  
  /* /\* //Tour 7 *\/ */
  /* scanf("%c", &trash); */

  /* move.x = 0; move.y = 1; */
  /* deplace(navmap, croiseur, 0, move); */

  /* move.x = -1; move.y = 0; */
  /* deplace(navmap, croiseur, 1, move); */
  /* afficher(navmap); */

  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, T: %d", 0, croiseur[0].radar.timerLoc); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */


  
  /* //Tour 8 */
  /* scanf("%c", &trash); */

  /* move.x = 5; move.y = 6; */
  /* localise(navmap, croiseur, 0); */

  /* move.x = 5; move.y = 2; */
  /* attaque(navmap, croiseur, 1, move); */
  /* afficher(navmap); */

  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, T: %d", 0, croiseur[0].radar.timerLoc); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */

  
  /* //Tour 9 */
  /* scanf("%c", &trash); */

  /* move.x = 0; move.y = 2; */
  /* deplace(navmap, croiseur, 0, move); */

  /* move.x = 0; move.y = -1;   */
  /* deplace(navmap, croiseur, 1, move); */
  /* afficher(navmap); */

  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, T: %d", 0, croiseur[0].infoRadar->timer); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */


  
  /* //Tour 10 */
  /* scanf("%c", &trash); */

  /* move.x = -2; move.y = 0; */
  /* deplace(navmap, croiseur, 0, move); */

  /* move.x = 5; move.y = 4;   */
  /* attaque(navmap, croiseur, 1, move); */
  /* afficher(navmap); */

  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, T: %d", 0, croiseur[0].infoRadar->timer); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */


  
  /* //Tour 11 */
  /* scanf("%c", &trash); */

  /* move.x = 6; move.y = 3; */
  /* attaque(navmap, croiseur, 0, move); */

  /* move.x = 0; move.y = 2;   */
  /* deplace(navmap, croiseur, 1, move); */
  /* afficher(navmap); */

  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, T: %d", 0, croiseur[0].infoRadar->timer); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */


  
  /* //Tour 12 */
  /* scanf("%c", &trash); */

  /* move.x = 6; move.y = 2; */
  /* localise(navmap, croiseur, 0); */

  /* move.x = 4; move.y = 5;   */
  /* localise(navmap, croiseur, 1); */
  /* afficher(navmap); */

  /* printf("\nCroiseur %d, C: %d", 0, croiseur[0].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 0, croiseur[0].Kmax); */
  /* printf("\nCroiseur %d, T: %d", 0, croiseur[0].infoRadar->timer); */
  /* printf("\nCroiseur %d, C: %d", 1, croiseur[1].Cmax); */
  /* printf("\nCroiseur %d, K: %d", 1, croiseur[1].Kmax); */

  ///////////////////////////

  
  freeShips(croiseur, navmap->nbShips);
  free_navalmap(navmap);
  return 0;
}
