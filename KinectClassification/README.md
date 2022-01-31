# La classification de posture
Pour la reconnaissance de 5 postures pré-définies, nous avons construit un modèle Inception-V3. Dans ce dossier, sont contenus tous les programmes essentiels au fonctionnement de cette IA, un Notebook contenant les entraînements successifs et un document récapitulatif des différentes architectures d'IA testées, avec une analyse comparative de leurs performances ainsi qu'un état de l'art.

Une fois le dossier téléchargé, il suffit d'exécuter le fichier KinectClassification.exe, une fenêtre composée de la vue de la caméra et du résultat de détection de l'IA en haut à gauche s'ouvrira alors. La personne placée dans le champ de vision de la caméra pourra alors prendre les poses. 

## Contenu
- KinectClassification.exe : fichier exécutable réalisant la détection en temps réel
- main.cpp : code C++
- model.onnx : modèle entrainé en Python puis converti au format onnx (compatible avec le C++)
- opencv_world455.dll : bibliothèque de OpenCV
- training_inception_v3.ipynb : python notebook de l'entraînement de reconnaissance de posture

## Installation des pré-requis
Il faut installer Kinect v1.8 SDK: https://www.microsoft.com/en-us/download/details.aspx?id=40278

## Les étapes d'utilisation
- Brancher la caméra Kinect Xbox 360 version 1 dans le port USB 3.0 de votre ordinateur
- Placer ensuite la caméra à une distance comprise entre 1m65 et 1m80 face à un fond blanc
- Placer le patient devant le fond blanc et augmenter la luminosité au maximum
- Cliquer sur KinectDetection.exe pour lancer la visualisation
