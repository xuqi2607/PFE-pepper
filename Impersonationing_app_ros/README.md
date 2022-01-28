# Impersonationing code for ROS

## Présentation 

## Pré-requis 
Pour utiliser les packages ROS de PEPPER, il est nécessaire d'avoir installé au préalable les versions des logiciels suivants :
- Ubuntu 16.04 Xenial Xerus, 64 bits
- ROS Kinetic avec le Full-Desktop comprenant Rviz et Gazebo (suivre le tutoriel ici : http://wiki.ros.org/kinetic/Installation/Ubuntu)
- Python 2.7.12

De plus, une fois cela fait, il faut procéder à l'installation des *SDK* et du logiciel *PyNaoQi* dont l'adresse de téléchargement a changé :
- naoqi-sdk version 2.5.7.1 pour linux 64 bits, malheureusement plus disponible en ligne
- pynaoqi version 2.5.7.1 pour linux 64 bits, disponible ici : https://www.softbankrobotics.com/emea/en/support/nao-6/downloads-softwares

Ensuite, avant de procéder à l'installation de notre robot virtuel, le tutoriel à l'adresse suivante doit être suivi : http://wiki.ros.org/pepper/Tutorials

## Installation 
Pour obtenir une version de PEPPER virtuel utilisable dans Rviz, il faut ensuite (après avoir crée son workspace, comme mentionné dans le tutoriel, il est possible d'ajouter les fichiers contenus dans Impersonationing_app_ROS puis, dans son terminal :
- se placer dans son workspace avec la commande **cd ~/catkin_ws**
- compiler en tapant : **catkin_make**
- sourcer : . ~/catkin_ws/devel/setup.bash

Il est ensuite possible de lancer la commande depuis le terminal en tapant :
**roslaunch pepper_description display.launch**

Une fenêtre Rviz doit alors s'ouvrir avec le robot PEPPER au centre d'un monde vide.


## Ce qu'il reste à faire
Malheureusement, il n'est pas possible de contrôler le robot depuis Rviz en publiant sur le topic *joint_state_publisher* dû au fonctionnement de Rviz. Il a seulement été possible de calculer les valeurs visées des paramètres des liaisons articulaires grâce à l'interface *joint-state-publisher-gui* grâce à laquelle, nous avons pu établir les valeurs pour les joints d'interêts :

[LShoulderPitch, LShoulderRoll, LElbowYaw, LElbowRoll, RShoulderPitch, RShoulderRoll, RElbowYaw, RElbowRoll]

dont les valeurs respectives sont pour les positions cibles :
- 1 : [1.50,  0.01, -2.09, -0.01,  1.50, -0.01, 2.09, 0.01] 
- 2 : [-1.41, 0.01, -2.09, -0.01, -1.41, -0.01, 2.09, 0.01]
- 3 : [1.50,  1.56, -2.09, -0.01,  1.50, -1.56, 2.09, 0.01]
- 4 : [-1.41, 1.56,  0.00, -1.56, -1.41, -1.56, 0.00, 1.56]
- 5 : [0.00,  0.01, -2.09, -0.01,  0.00, -0.01, 2.09, 0.01]

Toutefois, il est possible, si l'on a accès à un véritable robot PEPPER physique, de générer un fichier Xacro automatiquement avec tous les services et topic nécessaires au bon fonctionnement de PEPPER ré-utilisable dans le logiciel de virtualisation **Gazebo**.



