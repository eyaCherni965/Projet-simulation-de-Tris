Ce projet simule les 6 algorithmes de tris suivants 
: tri-cocktail (une variante du tri-bulle), tri par sélection, tri par insertion,
tri de Shell (shellsort), tri par monceau (heapsort) et le tri rapide (quicksort).
Pour chacun des algorithmes, nous allons comptabiliser tous les accès au tableau 
de données, soit en lecture ou en écriture, dans une file d’opérations.  Et après
avoir générer les 6 files d’opérations pour les 6 algorithmes, nous vidons le 
contenu des 6 files en parallèle, côte-à-côte, en affichant chaque opération à l’écran. 
L’algorithme avec la file la plus courte sera le gagnant de cette « course » virtuelle !

informations importantes:
1)Pour compiler les modules WinBGlm et Affichages : allez dans les menus de votre compilateur (Visual Studio) : Propriétés du projet -> menu de gauche -> Paramètres avancés.
Dans Jeu de caractères, choisissez Jeu de caractères multioctets (MBCS) -> Appliquer.

2)Lors de la compilation, assurez-vous d'avoir un affichage écran réglé à 100 % et que votre fenêtre de sortie soit en plein écran.
