# Installation de l'outil

L'outil est développé de manière à fonctionner sur différents noyaux (cf README.md). Dans ce document, vous pourrez trouver les prérequis nécessaires à la compilation du projet pour un systeme debian et pour un buildroot Qemu.


## Librairies annexes et intallation

- **libcurl** : librairie permettant de télécharger en ligne de commande.
installation debian: `sudo apt install libcurl4`
- **nlohmann/json.hpp** : librairie permettant de manipuler des fichiers JSON en C++
installation debian: `sudo apt install nlohmann-json3-dev`
- **gd** : librairie graphique C++
installation debian: `sudo apt install libgd-dev`


## Buildroot

L'archive .tar.gz de buildroot est disponible à l'adresse: https://buildroot.org/

1. Accédez à votre répertoire "téléchargements": `cd /home/username/Downloads`
2. Décompressez l'archive Buildroot : `tar -axvf buildroot-2023.02.4.tar.gz`
3. Accédez à votre répertoire Buildroot : `cd buildroot-2023.08`
4. Lancez la commande `make qemu_aarch64_virt_defconfig`
5. Lancez la commande `make xconfig`.
6. Activez les options suivantes :
- `Enable C++ support` BR2_TOOLCHAIN_BUILDROOT_CXX
- `libcurl` BR2_PACKAGE_LIBCURL
- BR2_PACKAGE_JSON_FOR_MODERN_CPP et BR2_PACKAGE_LIBJSON
   - Bibliothèque `gd` (BR2_PACKAGE_GD) et `gdtopng`BR2_PACKAGE_GD_GDTOPNG
   - indiquez le repertoire d'overlay BR2_ROOTFS_OVERLAY
7. Lancez la compilation : `make`.

La Compilation peut prendre un certain temps selon le materiel que vous utilisez.



## Debian

1. Clonez le dépôt: `git clone https://github.com/zaackcloud/projetEmbarque.git`
2. Accédez aux sources `cd parking\`
3. **Compilez: `g++ -o parkingDebian main.cpp init.cpp datamanager.cpp graphics.cpp -lgd -lcurl -ljsoncpp`**
4. Executez le programme :`./parkingDebian`

## Compilation croisée

le but est d'utiliser un compilateur spécialement prévu pour faire fonctionner le projet sur Qemu. Ce compilateur est contenu dans le repertoire buildroot/output/host/bin/.

Pour la compilation croisée : `~/buildroot-2023.08/output/host/bin/aarch64-buildroot-linux-gnu-g++ ~/parking/main.cpp ~/parking/init.cpp  ~/OpenData/datamanager.cpp ~/parking/graphics.cpp -o ~/parking/parkingBuildroot -lgd -lcurl -ljsoncpp `


## Copie du programme et exécution

1. Créez l'arborescence d'overlay `mkdir overlay` et `mkdir overlay/bin`
2. Copiez le programme : `parkingBuildroot` dans l'overlay : `cp projetEmbarque/parking/parkingBuildroot overlay/bin`
3. Relancez la commande `make` (elle devra etre plus rapide que la dernière fois)
4. Demarrez votre Qemu : `./output/images/start-qemu.sh`
5. Dans Buildroot, naviguez vers `/bin` et exécutez : `./parkingBuildroot`.



