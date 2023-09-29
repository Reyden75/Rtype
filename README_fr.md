# R-Type

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) ![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)

<h1 align="center">
  <img src="https://cdn.akamai.steamstatic.com/steam/apps/928390/capsule_616x353.jpg?t=1594713608" alt="Depviz" title="Depviz" height="200px">
  <br>
  
</h1>

<h3 align="center">Jeu vidéo arcade</h3>

<p align="center">
    <a href="https://en.wikipedia.org/wiki/R-Type"><img alt="wiki" src="https://img.shields.io/badge/r.type.wiki-2845a7?logo=internet-explorer&style=flat" /></a>
</p>

# R-Type: vue d'ensemble

R-Type est un classique des jeux d'arcades sorti pour la première fois en 1987. Le jeu consiste à naviguer dans une série de niveaux dangereux remplis d'ennemis et d'obstacles, en utilisant les armes du vaisseau spatial pour vaincre les extraterrestres et détruire leurs vaisseaux. Le jeu est connu pour sa difficulté, son système unique de power-up et ses combats de boss emblématiques. R-Type a été bien accueilli par le public et les critiques à sa sortie, et il est depuis devenu un classique bien-aimé du genre des jeux de tir.

# Table des matières

- [R-Type: vue d'ensemble](#r-type-vue-densemble)
- [Table des matières](#table-des-matières)
- [Démarrage rapide](#démarrage-rapide)
  - [Démarrage rapide: Windows](#démarrage-rapide-windows)
  - [Démarrage rapide: Unix](#démarrage-rapide-unix)
- [Exemples](#exemples)
- [Licence](#licence)

## Démarrage rapide

## Démarrage rapide: Windows

Prérequis :

- Windows 7 ou plus récent
- [Git](https://git-scm.com/downloads)
- [Visual Studio](https://visualstudio.microsoft.com/) 2015 Update 3 ou supérieur avec le pack de langue anglais
- [VCPKG] [VCPKG : Quickstart Windows] (https://github.com/microsoft/vcpkg#quick-start-windows)

Tout d'abord, téléchargez le projet ; il peut être installé n'importe où.

```shell
git clone https://github.com/EpitechPromo2025/B-CPP-500-PAR-5-2-rtype-alexandre.collin-betheuil.git
```

Vous devrez installer le paquet sfml avec VCPKG.

```shell
vcpkg.exe install sfml:x64-windows
```

Note : Vous pouvez configurer VCPKG comme une variable d'environnement pour l'utiliser n'importe où, sinon vous devrez utiliser le chemin complet comme ceci.

```shell
chemin/vers/vcpkg.exe install sfml:x64-windows
```

Configurez la [variable d'environnement](https://docs.oracle.com/en/database/oracle/machine-learning/oml4r/1.5.1/oread/creating-and-modifying-environment-variables-on-windows.html) VCPKG_DIR comme chemin/vers/vcpkg.

Après cela, vous pouvez maintenant ouvrir le dossier cloné avec Visual Studio, attendre qu'il construise le projet et lancer l'exécutable généré.

<img src="img/CMake_tutorial.png">

## Démarrage rapide: Unix

Prérequis :

- [Git](https://git-scm.com/downloads)
- g++ >= 6
- [VCPKG] [VCPKG : Démarrage rapide Unix](https://github.com/microsoft/vcpkg#quick-start-unix)
- [autoconf libtool](https://www.gnu.org/software/autoconf/)

Tout d'abord, téléchargez le projet ; il peut être installé n'importe où.

```shell
git clone https://github.com/EpitechPromo2025/B-CPP-500-PAR-5-2-rtype-alexandre.collin-betheuil.git
```

Vous devrez installer le paquet sfml avec VCPKG.

```shell
vcpkg install sfml:x64-linux
```

Configurez le VCPKG_DIR comme variable d'environnement dans le dossier cloné.

```shell
export VCPKG_DIR=/chemin/vers/vcpkg
```

Construisez le projet avec CMake.

```shell
cmake -B ./build/
```

Compilez le projet.

```shell
cd build/
make
```

Lancez le binaire.

```shell
./r-type_client
```

# Exemples

Voir la [documentation](https://miniature-adventure-y2rz68e.pages.github.io) pour l'utilisation spécifique des fonctions et l'explication des classes.

# Licence

Le code dans ce dépôt est sous la licence [GNU General Public License](LICENSE.md). Les bibliothèques fournies par les ports sont sous licence selon les termes de leurs auteurs originaux.

Traduit avec www.DeepL.com/Translator (version gratuite)
