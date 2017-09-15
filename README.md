# Analyse des contributeurs de wikipédia
---

|       Fodé HISSIROU          |
---

## Résumé 
Dans le cadre de la réalisation de projet de fin d’étude en master 1 Big Data et fouille des données, chaque étudiant doit choisir un sujet. 
De ce fait, mon sujet porte sur Wikipédia qui est une importante source d'information, 
ce qui fait qu'il est un excellent corpus d'essai pour le cadre universitaire. 
Il est gratuit et facile à obtenir, il porte une licence appropriée pour la recherche.

Wikipédia est également l’un des dix sites les plus populaires dans le monde. 
Son contenu ainsi que celui de tous les autres projets Wikimédia sont créés, améliorés et mis en ligne par des bénévoles. 
Cela le rend plus pertinent dans la recherche d'information.

Le modèle de réseau neuronal que j'utilise met en place une structure de SOM parallèle croissante pour toute entrée et toute dimension de sortie. 
L'avantage de cet algorithme est sa capacité de traiter l'ensemble des données en parallèle et des façons hiérarchiques au fil du temps. 
La raison principale du traitement des données en parallèle réside dans le fait que la connaissance peut être utilisée 
pour reconnaître des parties de modèles dans l'espace d'entrée qui ont déjà été apprises et aussi une taille de données assez considérables.

Pendant la formation, chaque connexion entre les neurones des couches d'entrée/sortie est considérée 
comme un processeur indépendant et sont organisés de façon hiérarchique. 
Les neurones d'activation du SOM de la couche inférieure sont considéré comme les données d’entrée du SOM de la couche supérieur de façon parallèle. 
De cette façon, tous les éléments de chaque matrice sont calculés simultanément. 
Cette fonction de synchronisation améliore sensiblement la séquence de mise à jour du poids.

## Objectif
Dans le cadre de la réalisation de projet de fin d’étude en Master 1 Big Data et fouille des données, chaque étudiant doit choisir un sujet. De ce fait, ce sujet porte sur Wikipédia qui est une importante source d'information, ce qui fait qu'il est un excellent corpus d'essai pour le cadre universitaire. Il est gratuit et facile à obtenir, il porte une licence appropriée pour la recherche. Wikipédia est également l’un des dix sites les plus populaires dans le monde. Son contenu ainsi que celui de tous les autres projets Wikimédia sont créés, améliorés et mis en ligne par des bénévoles. Cela le rend plus pertinent pour de nombreuses applications qui sont réalisées dans le domaine de la recherche.

## Contexte
- Au sein de Wikipédia tous les contributeurs ont la possibilité de créer ou de modifier une page. Or, de nos jours des milliers de modifications se font sur Wikipédia qui est due à différentes raisons comme par exemple le vandalisme qui est plus fréquent et qui consiste à dégrader volontairement la qualité d'un article en introduisant des fausses informations. Par contre lorsque ses actions sont détectées, ils sont ensuite supprimé. Cependant, lorsqu'on ajoute ou supprime l'information d'une page Wikipédia, cette action figure automatique sur la page des contributeurs, et fait que l'historique d’édition s'accroître et cela constitue une quantité de données importantes jusqu’au point ne pas pouvoir connaître les contributeurs, ou encore de pouvoir classifier manuellement les pages en fonction des Contributeurs.

- La guerre des Malouines où guerre de l'Atlantique Sud est un conflit opposant l'Argentine au Royaume-Uni dans les îles Malouines, Géorgie du Sud et Sandwich du Sud. Ce type de guerre existe sur Wikipédia sous une autre forme qui est la guerre d’édition des pages Wikipédia \cite{WikiGEdition} auquel deux ou plusieurs utilisateurs expriment un profond désaccord sur un point particulier (le contenu, le titre...) d'un article. Ces comportements non collaboratifs entre les utilisateurs qui annulent ou supprimer les modifications de l’autre sont par la suite réglés par des discussions. Cependant, lorsque le conflit se déplace du contenu pour toucher aux personnes(agressivités, insultes, ....), il se trouve que d'autres contributeurs tentent une médiation en rendant le débat public. Cela fait que beaucoup de personnes y participent à la discussion et qui est par conséquent difficile d'attribuer cette modification à un contributeur. Toute cette discussion figures dans la liste des historiques d'édition de la page.

## Sujet
Le sujet principal de ce projet de fin d’étude consiste à explorer l'historique d'un ensemble de pages Wikipédia. Cela consiste à récupérer un dump complet de Wikipédia et analyser son contenue pour identifier les contributeurs. Pour chaque contributeur faire une liste des pages modifiées, qui va nous permettre de faire un cluster des contributeurs c'est-à-dire le cluster de pages en fonction des contributeurs. La réalisation de toutes ces tâches implique à faire l'analyse des réseaux sociaux en utilisant les données contributeurs de Wikipédia.

## Le DUMP Wikipédia
- Les données contiennent l'historique complet de l'édition (toutes les révisions, toutes les pages) de tout Wikipédia depuis sa création jusqu'à nos jours. Le jeu de données contient des métadonnées traitées pour toutes les révisions de tous les articles extraits du dump xml. Cependant, l'échantillon utilisé est celui de Wikipédia français dont les données sont divisées en plusieurs catégorie historique et chacune d'elle est contienne en plusieurs sous-catégories: title, ns, id, revision. Pour chaque page on a une ou plusieurs révisions, donc dans notre cas, c'est le tilte et la partie révision qui nous intéresse le plus, la révision est aussi une métadonnée qui dont on peut trouver des sous informations sur chaque édition effectuent sur une page. Dans la table de révision on a: id, timestamp, contributor, comment, modèle, format, text, sha1. Dans la partie "contributor" on a aussi l'id et le username. Donc le travail consiste à faire une liste des pages modifiés pour chaque contributeur et faire une classification par la suite.

Wikipédia propose des dumps de son contenu, constitués d'une sauvegarde des fichiers et d'une sauvegarde de la base de donnée, à l'adresse: http://download.wikimedia.org/