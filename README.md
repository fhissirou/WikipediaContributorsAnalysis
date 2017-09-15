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

## Introduction générale
### Introduction
Wikipédia est une très grande plateforme avec des millions d’utilisateurs. 
Il est écrit dans une centaine de langues différentes, et fait partie des sites les plus utilisés au monde. 
On peut considérer Wikipédia comme une plateforme sociale, où tous les utilisateurs peuvent  interagir entre eux. 
Toute personne utilisant le site Wikipédia appartient forcement à deux types de catégories:

..* La première catégorie est celle des utilisateurs simples. 
Ils utilisent les ressources de Wikipédia pour tirer profit et non pour contribuer à l’édition des articles. 
Ils sont composés de toute sorte catégories de sociaux professionnels (étudiant, enseignant, employé, ouvrier ...) à la rechercher d’information.

..* La deuxième catégorie représente les contributeurs. 
Ce sont des personnes volontaires participant à l’édition des pages de Wikipédia. 
Ces contributeurs sont dotés d’un esprit de partage de connaissances. 
Ils sont composés soit par les personnes travaillant au sein de Wikipédia tel que les administrateurs, 
ou par d’autres personnes (étudiant, enseignant, chercheurs, employés ...) possédant des connaissances approfondies et la capacité d’écrire comme rédacteur web. 
Les contributeurs de Wikipédia ne cessent de croître et c’est avant tout grâce à eux que Wikipédia a une très grande influence sur la société, 
surtout les étudiants en particulier.

De nos jours, Wikipédia possède de nombreuses applications facilitant l’utilisation directe ou indirecte de ses données. 
Ces applications sont d’une part développées par la fondation elle-même mais aussi d’autre part elles sont faites par des bénévoles. 
Il est bien de souligner que les personnes éditant les articles ou développant des applications ne sont pas les seuls contributeurs. 
Il existe d'autres moyens d’aider la fondation. Certains de ces moyens peuvent être purement technologiques 
comme par exemple des espaces des stockages de données ou les moyens financières pour aider la fondation à maintenir son statut sans être commercialisée.

L’ensemble de ces facteurs donne l’envie d’apporter une contribution à l’édifice d’où la croissance des contributeurs. 
Il permet l’utilisation gratuite de ses ressources par les lecteurs ou par les chercheurs pour le développement de leur projet. 
Cette simplicité permet de la considérer comme une plateforme collaborative. 
Chaque utilisateur peut participer aux discussions, de créer des articles, de modifier ou de supprimer le contenu des pages, 
d’avoir des interactions entre la plateforme Wikipédia avec d’autres sites web.


### Problématique
Toute action réalisée sur un article Wikipédia correspond à une sauvegarde des informations dans sa base donnée. 
Or des dizaines de milliers d'interactions se font sur la plateforme, cela constitue une énorme quantité de données. 
Il est donc important d’analyser ces données pour mieux comprend le fonctionnement de Wikipédia.

Il se trouve que de nos jours, Wikipédia figure dans la plupart des recherches effectuées sur l'internet. 
Il est donc important que les utilisateurs s’engagent à l’amélioration de la qualité du contenu. 
Quand un contributeur crée une page, cela donne la possibilité aux autres de participer à l’amélioration de cette page. 
Cela peut être vu comme travaille collaboratif basé sur le partage des connaissances, et correspond aux objectifs visés par Wikipédia.

La guerre des Malouines où guerre de l’Atlantique Sud est un conflit opposant l’Argentine au Royaume-Uni dans les iles Malouines, Géorgie du Sud et Sandwich du Sud. 
Ce type de guerre existe sur Wikipédia sous une autre forme qui est la guerre d’édition des pages Wikipédia. 
Car l’objectif de certains contributeurs n’est pas d’améliorer la qualité de l’article, mais de dégrader volontairement son contenu. 
Parfois ces fausses informations peuvent rester sur Wikipédia pendant de longues périodes. 
Ce type d’action est souvent considéré comme étant un vandalisme, et est de plus en plus fréquent sur la plateforme.

Or, les administrateurs de Wikipédia ont le pouvoir de supprimer ou de rejeter des commentaires ou des articles auxquels ils ne sont pas d'accord. 
Donc, ils peuvent soit supprimer ces informations erronées et réglées par des discussions publiques, ou soit de blacklist l’adresse Ip de l’utilisateur.

Ces comportements sont non collaboratifs et peuvent souvent prendre de l’ampleur, où plusieurs contributeurs participent à la discussion pour trouver un point d’attente. 
L’ensemble de ces actions, laisse une trace dans l’historique des pages et génère données.

### Sujet
Wikipédia est une plateforme très intéressante avec des problèmes de classifications différentes. 
Par exemple, on peut catégoriser les éditeurs en tant qu'humains ou robots, et classer les articles comme controversés, 
fiables ou même les profils d'utilisateurs comme vandalisme. l’ensemble de ces taches peut être considéré comme un problème de classification. 
C'est dans ce cadre que ce projet consiste à classifier les contributeurs.

Le sujet principal de ce projet consiste à explorer l'historique d'un ensemble de pages Wikipédia. Pour cela:

..* Récupérer un échantillon du dump Wikipédia et analyser son contenue pour identifier les contributeurs.
..* Créer un dataset simplifié en ne prenant en compte que les révisions effectuées par des contributeurs enregistrés ou non enregistrés.
..* Combiner des paramètres pour créer des champs utiles comme le nombre de modifications par jour, mois...
..* Faire un nettoyage des données à l'aide de DSS de dataiku pour remplir des champs vides, de détecter les valeurs aberrantes.
..* Faire une étude statistique et visualiser les données.
..* Pour chaque contributeur, trouver la liste des pages modifiées pour créer un cluster des contributeurs c'est-à-dire le cluster de pages en fonction 
des contributeurs. La réalisation de toutes ces tâches implique à faire l'analyse des réseaux sociaux en utilisant les données le dump de Wikipédia.
