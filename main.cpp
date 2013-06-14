#include <QApplication>
#include <QDebug>
#include <QSettings>
#include "mainwindow.h"

/*! \mainpage Notability Projet LO21 - [Siqi Liu] & [Marion Depuydt]
 *
 * \section Introduction
 *

    *Architecture du programme:


 * [NoteManager description]
 * @type {[type]}
 *

* La partie centrale du programme est le NoteManager, qui gere la creation, duplication, suppression de tous les notes, et aussi l'hierarchie de tous les notes. Pour cela, il dispose d'un Document Racine ("~"), 5 NoteFactory, 4 ExportStrategy. Il dispose en outre des methodes qui permet de parcourir l'ensemble des notes, et de sauvegarder les notes(ou les documents).

*Factory:
*Les notesFactories gere la creation des notes. Il s'agit d'une tache delegue par NoteManager. En utilisant le principe de substitution et la polymorphisme, on arrive à sous classer cette classer pour fournir des Factory de différentes types de notes. Manque de la possibilité d'utilise la polymorphisme pour créer des duplication des notes, nous avons choisi à ajouter toutes les méthodes de duplication du notes dans la classes de bases.

*Les noms du fichiers sont généré de manière polymorphiques, et l'identité des notes se base sur le chemin des fichiers. Il est à noter qu'au début de la conception, nous avons décidé de générer une ID à partir du horloge du système (avec précision de 1ms). Ceci n'est pourtant pas suffisant au moment de duplication des notes (changement de espace de travail). Nous avons finalement décidé de ajouter 1 à chaque notes afin d'être sûr de unicité de id.

*ExportStrategy:
*On compte en tout 4 ExportStrategy pour l'instant dont un est le SaveTextStrategy. En effet, tous les strategies fournissent une interface communes, imposé par la classes de base et chaque strategy fournit leurs propre implémentation. On compte pour cela une méthode header/footer, et aussi un méthode ExportNote() qui prend un argument level signifiant le niveau d'indentation du export. Ceci permet d'appeler cette méthode récursivement pour générer les indentation correcte.

*root Docuement:
*Lors de la conception du projet, nous n'avons pas prévu cette attribut. Ceci nous paraît pourant indispensable lors de l'implémentation car ça facilite considérablement le changement de l'espace de travail, et la gestion de TreeView (gestion de l'hierarchie des notes). Nous avons donc créé cet attribut qui se charge de englober tous les notes créé par NoteManager.


 * TagManager
 *

*Tag:
*Pour gérer les tags, nous avons choisi d'implémenter une classe Tag qui a comme attribut un QSet<Note*>. Cela permet d'avoir accès à partir du tag à toutes les notes qui y sont associées. Nous pouvons dans cette classe avoir accès et changer le nom du tag. Nous pouvons aussi d'insérer et de supprimer une note du QSet. Pour avoir un access directe au tous les tags d'une note, nous avons concu egalement un attribut qui désigne tous les tags associé à une note dans la classe Note. Pour assurer la cohérence entre les tags et les notes, nous avons donc décidé de passer toujours par TagManager pour gérér les tags. Ces deux attributs sont donc étroitement associé via TagMananger.


*TagManager:
*La classe TagManager quant à elle permet de contrôler l'accès aux tags ainsi dans n'importe quelle classe si l'on veut rajouter un tag ou un tag lié à une note, nous sommes obligés de passer par le TagManager. La classe TagManager étant un singleton elle ne peut être instanciée qu'une seule fois.

*Quant à l'interface, nous avons choisi de présenter les tags sous la forme d'une liste de checkBox. Un tag peut être créé à l'aide du bouton + sans avoir de lien avec une note. Par contre, il est interdit de créer 2 tags de même noms, cela n'aurait pas de sens. En effet, si 2 tags ont les même noms comment différencier les notes qui s'y référent ?

*Nous pouvons changer son nom directement en double cliquant dessus. Quand un tag est selectionné, nous pouvons le supprimer à l'aide du bouton -.


*Dans l'éditeur, pour chaque note nous trouvons un bouton Tag qui permet d'associer la note éditée à un des tags existants.

*Par défaut tous les tags sont cochés, cela permet de voir l'ensemble des notes à l'ouverture de l'application dans le TreeView. Quand on décoche un tag, cela enlève de la liste des notes toutes celles qui n'y sont pas associées. Cela permet de filtrer les notes.



 * Note et Editor
 *

*Une autre classe qui est au centre du programme est la classe Note. Cette classe fournit des fonctionalité communes aux toutes les notes et impose une interface unique aux toutes les notes.

*Lors de l'implémentation du programme, nous avons choisi qu'à chaque niveau de héritage, la classe correspondante doit s'occuper et seulement s'occuper de sa spéricialisatoin. Ceci conduit à le fait que l'objet Note s'occupe de tous les titres alors que un Article s'occupe de son attribut text sans se soucier de l'attribut titre.

*Nous avons décidé en outre de créer une classe Binary, qui fournit une description et un chemin vers le média.

*Pour avoir une couplage étroite entre la note et l'editeur qui lui est associé, nous avons introduit une méthode template dans la classe de base Note, qui fait appeler à une méthode virtuelle pure createEditor(), et puis, stocke le pointeur retourner dans un attribut editor de la classe Note. Tous les Editor sont ainsi créer par les notes lui même. L'avantage réside donc dans le fait qu'une note connais sa propre type lors de l'appel à cette fonction. Ceci est donc très utile pour simplifie le code. En effet, pour créer un editeur à partir d'une note, il suffit d'appeler note->createAndAttachEditor(). Ceci nous retourne un pointeur sur un Editeur de bon type.

*La classe de base Editeur s'occupe de tous les fonctionablité communes et aussi la mise en forme de tous les editeurs. En précisant à ce niveau là les layouts qui existent, et leurs ordre dans l'editeur: titleLayout; tagLayout; contentLayout; buttonLayout, nous pouvons donc très facilement unifie ces configuration et laisse les sous classe de remplir seulement la partie spécialisée. Cette partie spécialisée sera donc principalement ajouté dans le contentLayout.

*Un cas spéciale est la classe DocumentEditeur. En effet, grâce à cette conception, nous avons pu appeler successivement la méthode createAndAttachEditor() de tous les notes contenues dans le DocumentEditor(y compris les documents contenus dans le document courant), et puis l'ajouter simplement dans le contentLayout. Ceci facilite énormément la configuration des Editeurs, tout en gardant une configuration unifié au niveau de l'interface Utilisateurs.


 * Filters
 *

*Afin d'améliorer la recherche d'un document, nous avons aussi décidé d'implémenter une recherche par nom d'article dans le TextEdit Search for notes en plus de filtre par tag.

*Pour pouvoir facilement gérer les Filtres et prévoir l'ajout des nouveau filtre dans le futur, nous avons prévus une architecture comme suit: Une classe Filtre qui fournit une interface communes à tous les Filtres, à savoir la fonction shallBeFiltered(Note* item) qui retourne True si item doit etre filtre, False sinon. Ainsi, chaque sous classes de Filtres est un Filtre, et elle doit pouvoir répondre à cette question: doit je filtrer cet item passé en argument selon les infos enreigistre dans mes attribut?

*Pour gérer un ensemble des Filtres, nous avons concu également une classe singleton FilterKit qui est une casse à outils des filtres. En fait, à chaque changement du tag ou du search for text, nous allons acutalise cette instance FilterKit en lui passant les nouveaux informations pour que les Filtres puissent repondre a la question avec les informations à jours. Cette classe possède donc une multimap des Filtres, et elle est capable de répondre si un item est filtre par au moins un filtres?

*L'avantage est donc très visible, c'est à dire dans le futur, si on ajoute un nouveau type de Filter, il nous suffit de simplement implémenter la fonction shallBeFiltered(item), et puis l'ajouter dans le multimap de FilterKit lors qu'il y a un chagement dans les infos de filtre. On n'a absolument pas à tous le code de TreeView ou de FilterKit pour filtrer les notes.


 * UndoableCommand
 *

*Cette fonctionalité n'a pas été concu lors de la conception du programme, et c'est pour cela nous avons pas eu le temps de reporter cette fonctionalité aux toutes les commandes. Nous avons pourant implémenté un ensemble des commandes pour la manipulation des tags.

*En effet, l'idée de base est de créer une pile d'exécution des actions et fournir à chaque actions une méthode inverse. A chaque actions, on doit donc fournir une méthode redo() et une méthode undo(). À chaque exécution de l'action, on fait un push de cette action sur le pile, et puis l'enlever si on a fait un undo. Ainsi, nous avons pu implémenter cette fonctionalité de manière assez fiable.

*Il est à noter que cette foncionalité nécessite une conception dès le début. Si on n'a pas prévu cette foncitonalité, le cout de la migration vers un programme omni undoable sera insupportable. Nous avons ici implément cette fonctionalité pour les Tags à titre exemple.


 * Trash
 *
*Quant à la recyclage et la suppression des notes, nous avons prévu un mécanisme de Trash qui fournit simplement trois méthodes de base: 1. recycle(Note *) 2. remove(DeletedNote *) 3. restore(DeletedNote*)

*Ces trois méthodes permet de 1. Englober une note dans un deletedNote où on disassocie cette note avec tous les Documents en relation avec Note courant et stocke les information nécessaire pour restaurer cette note à l'état initiale. 2. Exposer et restaurer une note à son état initiale étant donnée un deletedNote valid. 3. Supprimer définitivement le fichier sur le disque et néttoyer les traces de cette Note.

*Remarquons ici DeletedNote n'est pas dans l'hierarchie des Notes car justement on ne veut pas qu'elle soit traitée de la même manière que les autres notes. On a utilisé ici plutôt une composition à la place.

*Toutes les méthodes de deletedNote sont mis en privée pour la raison de sécurité. Seul la classe Trash et TrashDialog qui sont déclarés comme amis y ont accès. Ceci assure l'intégrité de la gestion de la corbeille.


 * Chargement des données
 *
*Lors de chargement des données, nous allons charger toutes les notes dans la mémoire. Au cours du chargement, nous allons "trier" les notes dans la corbeille (si isDeleted est vrai), et ajouter les tags dans la liste des tags au fur et a mesure. Ceci permet une représentation plutôt centralisé et qu'on ne risque pas d'avoir une incohérence si on a stocké les fichiers notes et une fichier tags séparément.

*Au moment du chargement, on ne charge que des text. Le chargement du text simple est très négligeable face au tous les traitement qui ont lieu au niveau de calcul graphiques (le cout de calcul de l'animation pour animer un clique sur un button est bien plus supérieur que charger quelques notes purement textuelle depuis le disk). Nous avons donc décidé de ne pas séparer le chargement de titre et le chargement des autres attribut textuel.

*Le chargement des médias se fait sur la demande, c'est à dire les données sont chargés lorque l'utilise déclencher une action spécifique aux multimédia.


 * Miscelleneuous
 *

*Au cours d'utilisation de Qt, nous avons tenté d'utilisé des structures de l'interface plus avancé et plus compliqué proposé par le framework de Qt. Nous avons ainsi pu implémenter un TreeView à partir de l'hierarchie des Notes en utilisant le modèle MVC proposé par Qt.

*Nous avons également implémenter une interface personnalisé de Trash. Où chaque item de Trash comporte également deux buttons.

*Le framework Qt est donc très enrichissant au niveau de compréhension de Orienté Objet et il nous permet d'apprécier la force d'une librairie POO très bien conçu.

*Améliorations

*Pour améliorer ce logiciel de prise de notes, nous pourrions :

*1. remplacer les parcours recursifs par des iterateurs profondeur qu'on a implementé dans Document.h
*2. ajouter le undo, redo pour toutes les actions du programme
*3. ajouter un correcteur orthographique
*4. modifier la typographie -avoir une reconnaissance vocale
*5. chargement des images/musique à partir d'internet
*6. migration vers un gestionnaire de doneés plus avance comme par exemple Sqlite.
*7. migration vers une autre forme plus lisible de stockage des notes comme par exemple json ou xml.
*8. Trouver une librairie bien adapté à Qt5 pour affichier de la video. (ceci est facilement avec Phonon sur Qt4, qui n'est plus compatible avec Qt5. Le widgetMultimédia comporte malheureusement encore des erreurs qui fait que le videoWidget de Qt5 n'est pas encore utilisable (ça marche pas sous window mais ça marche sous Mac, sauf qu'il fait lagger complétement le programme et empêche des clicks sur buttons))
*9. Implémenter un système de partages directe depuis logiciel.
*10. Implémenter un enreigistrement du sons dans AudioNoteEditeur.
*11. Implémenter des outils d'edition du richText plus avancé dans l'articleEditor.
 *
 *
 * \section UML
 * \image html ../UMLf.png
 * \image html ../UMLf2.png
 */

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Notability");
    QCoreApplication::setOrganizationDomain("notability.fr");
    QCoreApplication::setApplicationName("Notability");

    MainWindow *editor = MainWindow::getInstance();
    editor->show();

    return a.exec();
}
