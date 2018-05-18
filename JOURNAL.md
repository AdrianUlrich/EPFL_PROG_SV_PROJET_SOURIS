#PROJET PROGRAMMATION SV SIMULATION SOURIS
#JOURNAL du groupe 41 (Adrian SCHEMEL, Iris GROSLAMBERT) 

*************************************************
## 13.03 (mardi)

- inscription du groupe
- Partie 1
 - AI: début et fin de Collider.[hpp][cpp]

*************************************************
## 16.03 (vendredi)

 - AI: début de Substance.[hpp][cpp]

*************************************************
## 17-18.03 (weekend)

 - A: fin de Substance.[hpp][cpp] :
> Choix conceptuel dans Substance:
> Stockage non pas du *total et des fractions* mais des trois *quantités*
> étant donné que les méthodes demandées modifiaient presque exclusivement
> les quantités et non les fractions des substances

- Partie 2
 - I: début de Box.[hpp][cpp]

*************************************************
## 20.03 (mardi)

 - I: fin de Box.[hpp][cpp]
 - A: début et fin de:
  1. SimulatedEntity.[hpp][cpp]
  2. Animal.[hpp][cpp]
  3. Mouse.[hpp][cpp]
  4. Cheese.[hpp][cpp]
> Choix conceptuel dans 1,2,3,4:
> Stockage de pointeurs vers `sf::Sprite`s dans les objets
> au lieu de re-création à chaque `drawOn()`
 - AI: début de Lab.[hpp][cpp]
> Modification de Box pour stocker les `sf::RectangleShape`s dans les `Box`
> puisqu'on ne souhaite pas les modifier apès leur création dans `Box::Box()`

***SIGSEV lors de l'exectution du programme***

*************************************************
## 24-25.03 (weekend)

***SIGSEV etait causé par des accès aux*** `nullptr`
 - Partie 2 corrigée et fonctionnelle

*************************************************
## 27.03 (mardi)

 - Finition de Partie 2 (fonctionnalités de débug etc.)
> textes de débug volontairement bloqués à l'horizontale pour une meilleure lisibilité
- Partie 3
 - Implémentation du polymorphisme et possibilité de créer jusqu'à n entités
>  n choisi comme 100, faute d'indication dans l'énoncé d'une quelconque autre limite

*************************************************
## 10.04 (mardi)

- Partie 3.1 debut et fin
		 3.2 debut

*************************************************
## 17.04 (mardi)

- Partie 3.2 continuation
		 3.3 debut et fin
		 3.4 debut
> 3.2: les souris rebondissent sur les murs par rappor
> à leur angle d'incidence au lieu de simplement faire demi-tour

*************************************************
## 26.04 (jeudi)

- Merge des parties incomplètes de A et I pour rendu intermédiaire
- Compile et fonctionne, mais les souris sortent instantanément du cadre
> On peut quand même les voir avec pause(espace)

*************************************************
## 01.05 (mardi)

- Partie 3.2 fin
		 3.4 continuation 
		 
*************************************************
## 08.05 (mardi)

- Partie 3.4 continuation
		 4.1 début

*************************************************
## 09.05 (mercredi)

- Partie 3.4 continuation
		 4.1 continuation
