# Impersonationing App on Choregraphe

## Présentation 
Dans ce dossier, nous avons placé tous les fichiers utilisés pour que PEPPER puisse reproduire les 5 poses mentionnées dans le ReadMe global. 
Cette application est indépendante de tout autre logiciel hormis ceux mentionnés dans la partie "Installation et dépendances".   
Pour fonctionner, elle nécessite l'entrée manuelle d'un chiffre compris entre 0 et 5 (tous deux inclus). La correspondance entre ces chiffres et le 
comportement de PEPPER est la suivante :
- 0 : robot est en attente pour 60 secondes d'un stimulus qui, s'il ne vient pas, entraîne la fin de l'exécution de l'application pour PEPPER ;
- 1 : pose StandInit (bras le long du corps et tête haute) puis attente de 60 secondes avec les mêmes conditions que pour 0 ;
- 2 : pose HandsUp (mains en l'air et corps droit) puis attente de 60 secondes avec les mêmes conditions que pour 0 ;
- 3 : pose ArmsMid (bras tendus vers la gauche et vers la droite) puis attente de 60 secondes avec les mêmes conditions que pour 0 ;
- 4 : pose CrabArms (bras en U à la façon d'un crabe levant ses pinces en l'air) puis attente de 60 secondes avec les mêmes conditions que pour 0 ;
- 5 : pose StandZero (bras tendus droit devant) puis attente de 60 secondes avec les mêmes conditions que pour 0 ;

## Installation et dépendances
Notre application ne fonctionne qu'avec les versions des logiciels suivants :
- Choregraphe 2.8, disponible à l'adresse suivante : https://www.softbankrobotics.com/emea/en/support/nao-6/downloads-softwares
- python 2.7
- NaoQi 2.8 

Pour l'utiliser à partir d'un ordinateur avec un robot virtuel, il suffit, une fois toutes les dépendances installées, d'ouvrir le logiciel Choregraphe, d'aller 
dans le volet "Connection", puis de sélectionner la rubrique "Connection to virtual robot" pour établir la connexion avec un robot virtuel.   
Pour l'utiliser à partir d'un ordinateur avec un véritable robot, il faut de même ouvrir Chorégraphe, puis se rendre dans "Connexion" et "Connect to" et finalement y établir le pont avec le robot physique.  
Enfin, si l'on possède un robot physique avec le système d'exloitation NaoQi 2.8, on peut directement y installer le dossier qui contiendra le 
fichier .pml à exécuter.
