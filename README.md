# Z-war

>**Zwar** est un jeux de combat 2d en mode arène.

### Créateurs :

- Yahaya Bathily (*Propriétaire et développeur du jeux*)
- Fawzi Ouaheb (*Support design visuel*) 

> Le jeux est conçu de manière à ce que chaque joueur puisse personnaliser son jeux ainsi que ses personnages.

### Description du format d'un personnage / Création d'un personnage

> *Trouvez le dossier contenant les personnages dans l'emplacement d'installation puis dans le dossier **resources > characters***

#### Dans le dossier 'chararacters'
  - Créez un dossier portant le nom du personnage pour plus de lisibilité

#### Dans le dossier 'characters > votre_dossier_personnage'
  - Créez deux dossier
    - **sprites** (*Le nom est arbitraire, le dossier également. Ce dossier a pour but de contenir les images du personnage. Toutefois ces images peuvent être placés dans différents dossiers par forme à différents emplacements dans le dossier qui contient le personnage*)
    - **config** (*Le nom doit être le même*)
  - De la même manière il est connseilé de créer un dossier qui servira à contenir les différentes formes du personnage (*exemple : **forms***)

> Avant de poursuivre renseignez-vous sur le format yaml via ce lien : [Syntaxe YAML](https://docs.ansible.com/ansible/latest/reference_appendices/YAMLSyntax.html)\
> A partir de là tous les chemins demandés ont comme racine virtuelle le dossier du personnage *ex: /config considéré comme /resources/characters/votre_dossier_personnage/config*

#### Dans le dossier 'characters > votre_dossier_personnage > config' 

- Créez un fichier nommé **config.yaml** (*ce fichier servira à décrire les configurations du personnage*)
- Dans ce fichier rajouter les clés :
  - **controllers** (*cette clé sert à définir / nommer les différentes manières de controller votre personnage*)
    - ex: 
        ```
        controllers: ["Clavier","Manette-ps3"]
        ``` 
  - **forms** (*cette clé sert à lister les différents formes du personnages (ssj1,ssj2...)*)
    - ex:
        ```
        # le nom de la forme doit être unique sinon la forme sera remplacé
        forms:
          - name: "Forme de base"
            path: "/config/forms/base-form/config.yaml"
          - name: "Forme de base 2"
            path: "/config/forms/base-form-2/config.yaml"
        ```
      - La clé **name** désigne le nom donné à la forme
      - La clé **path** est un chemin vers un fichier **'.yaml**' le nom est arbitraire , ce fichier contiendra la configuration de la forme (créer un dossier par forme est recommandé comme dans l'exemple)
  - **presentation-image-path** (*cette clé sert à donner le chemin de l'image poster du personnage, c'est l'image qui est affiché au choix du personnage*)
  - **presentation-animation** : (*cette clé sert à décrire l'animation du personnage quand il est utilisé pour animer*)
    - ex:
      ```
      presentation-animation:
        # nom de la forme de l'animation
        form: "Forme de base"

        # liste des actions au chargement requis pour l'animation
        required-actions: ["static-jump","roulade-left","roulade-right"]

        # action à éxécuter pour l'animation dans l'ordre
        animation: ["static-jump","static-jump","roulade-right","roulade-left","jump-to-right"]
      ```
      > Le principe des actions sera défini plus bas (*une action représente une action ex: sauter aller,à gauche,...*)
      - La clé **form** défini le nom de forme qui sera utilisé pour l'animation
      - La clé **required-actions** défini le nom des actions qui seront utilisé pour définir l'animation
      - La clé **animation** défini une liste de noms d'actions (**les actions doivent avoir été définis dans required-actions**) à éxécuter à la suite pour faire l'animation du personnage
#### Configuration d'une forme du personnage

> La configuration d'une forme requiert un certains nombre de clés mais doit obligatoirement commencer par celle des images.\
> Une image représente une action ou une partie d'une action.\
> Sur la même image peut se tenir à la suite les différentes images qui représentent la séquence d'une action 
> ex:\
![](https://media.istockphoto.com/id/1157350801/fr/vectoriel/ex%C3%A9cution-man-animation-sprite-set-8-boucle-de-cadre.jpg?s=170667a&w=0&k=20&c=vW-Sp57b-MW2QSJMM7XOhI8ZbFz8V1UqP46aIMr8BaI=)\
> En délimitant le premier personnage puis le deuxième puis le 3 eme puis le 4 eme les 4 images à la suite forment une course\
> x = 0 équivaux en haut à gauche de l'image - y = 0 représente aussi en haut à gauche de l'image - width = la largeur de l'endroit à utiliser - height = la hauteur à utiliser pour cette section de l'image, [Renseignez vous sur les axes x y en cliquant ici](https://www.splashlearn.com/math-vocabulary/x-and-y-axis#:~:text=The%20x%2Daxis%20is%20a,axis%20is%20called%20the%20ordinate.)\
> Sur l'image d'exemple pour découper le premier bonhomme on pourrait avoir x = 0 - y = 0 - width = 70 - height = 160, pour le second bonhomme à sa droite x = 75 - y = 0 - width = 70 - height 160 ...  

#### Dans le fichier de configuration de la forme rajoutez les clés :

- **images** cette clé défini une map des images de la forme dans le format décrit au dessus
  - ex :
    ```
    images:
      position-debout:
        path: "/chemin/image-debout.png"
        contentConfig:
          - x: 0
            y: 0
            width: 200
            height: 300
          - x: 300
            y: 0
            width: 200
            height: 100
      marche:
        path: "/chemin/image-marche.png"
        contentConfig:
          - x: 0
            y: 0
            width: 200
            height: 300
    ```
  >La map a comme clé un nom arbitraire unique (il est conseillé de choisir un nom qui décrit le contenu de l'image sans espace)\
  >La valeur est une map contenant les clés **path** qui est le chemin vers l'image *les chemins suivent toujours la même logique* et *contentConfig* qui répresente liste de découpage comme expliqué au dessus l'ordre de découpage est important, ce découpage constitura la suite sera joué
- **name** cette clé défini le nom de la forme du personnage
  - ex: name: "Super sayan"
- **energy** cette clé défini l'énergie requise pour lancer cette forme du personnage (*une énergie à 0 définiera la forme de base du personnage*)
  - ex: energy: 0
> Les variables sont listé dans un tableau à la fin de description, leur format y est également décris.
- **duration** cette clé défini la durée du personnage en secondes , variables de durée autorisé sur ce personnage
  - ex: duration : {INFINITE}
- **combo-gain-formula** cette clé défini une formule mathématique définissant les points d'énergie gagné par un combo réalisé , accès aux variables {COUNT_OF_HITS} et {ATTACK_SPEED}
  - ex: combo-gain-formula: "{COUNT_OF_HITS} * {ATTACK_SPEED}"
- **shield-points** cette clé défini les points de base du bouclier du personnage (*quand il se protège*)
  - ex: shield-points: 300
- **shield-images** cette clé défini le/les noms d'images configurés plus haut sur la forme à utiliser pour faire la séquence bouclier
  ex: shield-images : ["image_bouclier"] ou shield-images : ["image_seul_bouclier_1","image_seul_bouclier_2"]
- **fell-images** cette clé défini le/les noms d'images configurés plus haut dans la forme à utiliser pour faire la séquence de chute
  - ex: même principes shield-images
- **victory-images** cette clé défini une liste d'animation possible pour la victoire du personnage, chacune des listes contient le nom d'une ou plusieurs images configuré au plus haut dans la forme à utiliser pour faire la séquence
  - ex: 
  ````
  victory-images: [
    ["victoire_image"],
    ["victoire_image_bleue_1","victoire_image_blue_2"],
    ["victoire_image_rouge"]
  ]
  ````

- **head-hit-images** cette clé défini le/les noms d'images configurés plus haut dans la forme à utiliser pour faire la séquence de coup pris à la tête
  - ex: même principes shield-images
- **body-hit-images** cette clé défini le/les noms d'images configurés plus haut dans la forme à utiliser pour faire la séquence de coup pris au corps
  - ex: même principes shield-images
- **get-up-images** cette clé défini le/les noms d'images configurés plus haut dans la forme à utiliser pour faire la séquence de se relever
  - ex: même principes shield-images
  
- **actions-map** cette clé mappe les actions du personnage 
  - ex:
  ````
  actions-map:
    crouch : "/config/forms/base-form/actions/crouch.yaml"
    go-left: "/config/forms/base-form/actions/go-left.yaml"
    go-right: "/config/forms/base-form/actions/go-right.yaml"
    jump-to-left: "/config/forms/base-form/actions/jump-to-left.yaml"
    jump-to-right : "/config/forms/base-form/actions/jump-to-right.yaml"
    roulade-left : "/config/forms/base-form/actions/roulade-left.yaml"
    roulade-right : "/config/forms/base-form/actions/roulade-right.yaml"
    static-jump: "/config/forms/base-form/actions/static-jump.yaml"
  ````
  La clé est le nom donné à l'action et la valeur le chemin vers un fichier **'.yaml'** servant à définir l'action
#### Configuration d'une action d'un personnage