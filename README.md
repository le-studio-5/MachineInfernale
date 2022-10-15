# La Machine Sonore Infernale
La Machine Sonore infernale est un dispositif interactif et open source inventé par le Le Labo. Sous la forme d’un tableau de bord de vaisseau spatial, la MSI pour les intimes, permet à un groupe de 9 personnes de jouer de la musique en live.

Après avoir prototypé la Machine au Labo plusieurs partenaires sont intervenus sur le projet :
* Le studio [Kreactive](http://studiokreactive.com/) pour le design des modules
* Le [Creuset](https://creuset47asso.wixsite.com/blog) pour la partie menuiserie
* Gaël Jaton, à la réalisation électronique

Le projet a été financé par la Région Nouvelle Aquitaine ainsi que la DRAC Nouvelle Aquitaine.
Contact pierre-mary[at]le-florida.org

![Licence Creative Commons](https://licensebuttons.net/l/by-sa/4.0/88x31.png)
Ce(tte) œuvre est mise à disposition selon les termes de la [Licence Creative Commons Attribution - Partage dans les Mêmes Conditions 4.0 International.](http://creativecommons.org/licenses/by-sa/4.0/)

## Module I
### Matériel nécessaire :
* 9 boutons arcade
* 2 potentiomètres 10k Lin
* 1 joystick logitech
* 2 cartes teensy 3.6
* 1 carte sd
* alimentation mean well rs-50-5
* alimentation IRM-60-12ST
* 2x tda 2050 mono amplifier
* 2x 8ohm HP
* ruban cuivre

### Cablage
Les boutons d'arcade sont cablés sur les entrées 0-8 de la teensy
Les potentiomètres sur les entrées A8 et A9
Le capteur capacitif est cablé sur l'entrée 30 après une résistance de 10kohm
