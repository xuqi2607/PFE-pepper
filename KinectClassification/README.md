# La classification de posture
On utilise un modèle Inception-V3 pour faire la detection des postures. Il y a 5 postures. Vous téléchargez ce dossier, vous pourriez visualiser la classification de postures en temps réel. Le résultat de detection de posture s’affiche sur en haut à gauche de la fenêtre.

## Contenu
- main.cpp : codes C++
- KinectClassification.exe : fichier exécutable pour faire la detection en temps réel
- model.onnx : modèle entrainé en Python puis transformé en format onnx
- opencv_world455.dll : bibliothèque de OpenCV
- training_inception_v3.ipynb : python notebook de l'entraînement de reconnaissance de posture

## Installation des pré-requis
Il faut installer Kinect v1.8 SDK: https://www.microsoft.com/en-us/download/details.aspx?id=40278

## Les étapes d'utilisation
- Brancher le Kinect xbox 360 sur le PC avec USB 3.0.
- Placer la caméra à une distance d’entre 1m65 et 1m80
- Mettre devant un fond blanc et assurer une bonne luminosité
- Cliquer sur KinectDetection.exe pour lancer la visualisation
