	A. Présentation du programme:

Notre programme permet de simuler l'évolution d'une souris et de son foie. Nous pouvons ajouter de souris ainsi que des fromages dans le laboratoire, les souris peuvent manger les fromages quand leur énergie est insuffisante, la taille du fromage en sera réduite.

On dispose aussi d'une vision interne sur l'organe de la souris. Les cellules du foie peuvent se diviser et consommer du glucose pour remplir leurs réserves d'atp qui leur est vital.

Il est possible d'implanter des cellules hépatiques cancéreuses aux souris. Celles-ci vont se diviser et supplanter les cellules hépatiques, le cancer va donc se propager. Pour arrêter cela et étouffer le cancer, il faut alors augmenter la quantité de bromopyruvate qui rend leur glycolyse moins efficace. Les cellules saines survivent car elles Font le cycle de Krebs et sont donc moins impactées par l'inhibiteur

Il est également possible de faire varier la quantité de glucose et de VGEF. L'augmentation du glucose va permettre la régénération plus rapide des cellules hépatiques. 


	B. Compilation du programme:

Pour compiler/exécuter le programme général (FinalApplication), il est nécessaire de lancer la commande:
			"scons application-run --cfg=fichier_de_configuration.json"
depuis le répertoire contenant sconscript.


	C. Utilisation du programme :

Pour le programme général (à lancer avec app.json ou appSmall.json):
	
appStarving.json rend l'organe plus petit pour faciliter l'exception du programme
app.json crée des situations standard 

1. Pour ajouter une souris, placer la souris dans une boite et appuyer sur "m" sur le 	clavier.

2. Pour ajouter des fromages, placer la souris dans une boite et appuyer sur "f" sur le clavier.

3. Pour traquer une souris, placer le curseur sur une souris et appuyer sur "t" sur le clavier.

4. Pour passer sur la vue interne de la souris traquée, appuyer sur "o" sur le clavier.	

5. Pour ajouter mettre le cancer sur la souris traquée, placer le curseur sur un endroit du foie et appuyer sur "x" sur le clavier.

6. Pour ajouter des substances à l'organe, sélectionner sur la substance voulue (Glucose, Bromopyruvate ou VGEF) en appuyant sur "n" sur le clavier pour pouvoir changer de substance. Une fois sur la bonne substance, appuyer sur page up ou 2 pour augmenter le gradient de diffusion de la substance et appuyer sur page up ou 3 pour le diminuer. Les substances se diffusent exclusivement depuis des cellules sanguines capillaires 

7. Pour repasser sur la vue externe, soit la vue du laboratoire, appuyer sur "l" sur le clavier.	



		
Autres entrées clavier :
	Reset : appuyer sur "r" (dans le laboratoire) pour recommencer la simulation.
	Indication : cliquer dans la simulation d'organe affiche le niveau de glucose de la cellule de matrice extra-cellulaire à cette position
	
Fonctionnalités disponibles :

	Mode "pause" : appuyer sur l'espace sur le clavier pour mettre la simulation en pause.
	Mode "debug" : appuyer sur la touche "d" au clavier pour afficher l'énergie de la souris et celle du fromage, le cercle collider de la souris et du fromage, le champ de vision de la souris.

		

