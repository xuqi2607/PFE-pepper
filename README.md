# Projet de Fin d'Étude (PFE) : Reproduction de poses d'un humain en temps-réel avec le robot PEPPER

## Origine et contexte du projet 
Dans le milieu hospitalier, les patients-enfants atteints d’autismes présentes des difficultés à échanger avec d'autres humains. Or, à travers divers projets utilisant le robot Nao et mêlant la médecine, l’ingénierie et la psychologie, il a été possible de créer un vecteur de communication entre ces patients et le personnel hospitalier. Cependant, ce robot a du mal à maintenir son équilibre ce qui peut entraîner des cas de chutes et une incapacité à se relever. 
L’alternative envisagée est donc d’utiliser le robot PEPPER possèdant une meilleure stabilité. 
Notre projet consiste à réaliser un jeu entre le patient atteint d'autisme et le robot où ce dernier devrait reproduire l'une des 5 poses prises par le patient.
Nous avons donc réalisé ici, un démonstrateur comprenant deux parties indépendantes mais qui, s'il était possible de les relier constituraient un démonstrateur complet : une partie de reconnaissance de poses et une partie de robotique pour que le robot humanoïde PEPPER puisse prendre ces poses.  
    
PEPPER doit être capable de reproduire 5 poses déterminées que peut prendre une persone en temps-réel :
- une position neutre (StandInit) où l'individu est droit et laisse ses bras pendre le long du corps ;
- une position (ArmsUp) où ils gardent les bras tendus avec les mains en l'air, au dessus de sa tête ;
- une encore (ArmsMid) où ses bras sont également tendus et forment un T ;
- une position (CrabArms) où il forme un U avec ses bras à la façon d'un crabe qui lèverait ses pinces en l'air pour marcher ;
- la dernière (StandZero) où il tend les bras droits devant lui.  

Ce projet se décompose en trois parties indépendantes les unes des autres, faute de pouvoir créer une interface entre le robot PEPPER
et un ordinateur dans le langage Python 2.7 ou le langage C :
- la première partie est celle gérant tout ce qui concerne la reconnaissance de poses à partir d'un ordinateur grâce à une intelligence artificielle .............. et la réalisation d'un interface avec la caméra Kinect 1, toutes deux contenues dans le dossier .............;
- les deuxièmes et troisièmes parties concernent l'aspect robotique de notre proejt. Le dossier *Impersonationing_Application* contient la réalisation d'une application sur le logiciel Choregraphe 2.8. Le dossier ROS contient une ébauche de réalisation d'un programme ayant le même comportement et les mêmes fonctionnalités que celui de Choregraphe mais où il serait possible, une fois un robot virtuel obtenu sur Gazebo, d'établir une connexion entre l'ordinateur et le robot virtuel.


## Contenu
Ce Github contient trois dossiers correspondant aux trois parties produites.  
Dans un premier dossier, intitulé "Impersonationing_Application", nous avons rangé tous les éléments nécessaires à l'installation de l'application sur 
l'environnement de développement Chorégraphe. Dans un second, nommé ........ se tout ce qui concerne l'intelligence artificielle et l'interface avec la caméra Kinect 1. Dans un dernier, appelé ......., nous avons mis l'ébauche du travail permettant d'utiliser un robot virtuel sur ROS sur le logiciel RVIZ et contenant toutes les dépendances nécessaires à son bon fonctionnement. 

## Installation et dépendances
Les dépendances de chacunes des trois parties sont rappelées dans le fichier README.md qui leur est associé. 
