#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QComboBox>

class Note;
class MainWindow;
class TreeItem;
class AddToDocDialog;
class AddTagToNoteDialog;

/**
 * @brief The Editor class: Editor::Editor, base class for Article editor, Binary Editor. Abstract class
 */
class Editor : public QWidget
{
    Q_OBJECT
    QWidget * titleWidget;
    QLineEdit * titleEditWidget;
    /*!
     * \brief contentWidget Widget qui accueille tous les contenu qui sera rempli par les sous classes de editor
     */
    QWidget * contentWidget;
    /*!
     * \brief buttonsWidget Widget uniforme qui contenir tous les buttons standards
     */
    QWidget * buttonsWidget;
    Note * ressource;
    QPushButton * btnSave;
    QPushButton * btnClose;
    QPushButton * btnDelete;
    QPushButton * btnTag;
    QPushButton * documentBtn;

    /*!
     * \brief editorBaseLayout Layout de base pour \link<Editor>
     */
    QVBoxLayout * editorBaseLayout;

    /*!
     * \brief docDialog Dialog qui nous permet de recuperer les documents choisi par l'utilisateurs. Les documents choisi seront utilise pour ajouter les notes dans les documents
     */
    AddToDocDialog *docDialog;
    /*!
     * \brief tagDialog Dialog qui nous permet de recuperer les tags choisis par l'utilisateurs. Les tags choisis seront utilises pour associe les notes avec les tags
     */
    AddTagToNoteDialog *tagDialog;

    /*!
     * \brief mainWindow Widget Central du programme. Ceci contient entres autres le sidebar qui contient une hierarchie des Notes, une liste des Tags, et un tabView avec les editeurs et les exports
     */
    MainWindow * mainWindow;
    QHBoxLayout* titleLayout;

    /*!
     * \brief BACKEND_SET_TITLE titleWidget est communes pour tous les editors. On va le traiter donc a ce niveau la.
     */
    void BACKEND_SET_TITLE();

    /*!
     * \brief BACKEND_SET_CONTENT Methode virtuelle pure qui sera definit dans les sous classes.
     */
    virtual void BACKEND_SET_CONTENT() = 0;
    void UI_INFORM_USER_OF_SAVE();

protected:
    /*!
     * \brief contentLayout Attribut protected car cet attribute accueille les contenu des Editeurs specialises. Il est donc prefere de leurs donne un acces directe a cet attribut.
     */
    QVBoxLayout *contentLayout;
    /*!
     * \brief buttonsLayout Attribut protected car cet attribute accueille les buttons specialises des Editeurs de filles. Il est donc prefere de leurs donne un acces directe a cet attribut.
     */
    QHBoxLayout *buttonsLayout;

public:

    /*!
     * \brief Editor Cet constructeur definit la configuration globale du Editor
     * Elle definit les relations entre \link<editorBaseLayout> \link<contentLayout> et \link<buttonsLayout>
     * Elle definit egalement les actions communes pours toutes les sous classes editeurs.
     * \param n Le note a partir de quel on va generer ce editeur
     * \param parent
     */
    explicit Editor(Note *n, QWidget *parent = 0);

    QLineEdit *getTitleWidget() const;
    void setTitleWidget(QLineEdit *value);

    Note *getRessource() const;
    void setRessource(Note *value);

    /*!
     * \brief operator == permet de comparer les deux editeurs avec comme reference le chemin de \link<ressource>
     * \param rhs right hand side
     * \return retourne True si les deux editeurs comporte le meme ressources, false sinon
     */
    bool operator==(const Editor& rhs);

    void setTitleWidgetText(const QString& title);
    void setDocumentBtnText(const QString& doc);
signals:

public slots:
    /*!
     * \brief UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR Cette slot recoit un signal si le contenu de ressource a ete modifie. Ceci provoque l'activation de saveButton et aussi l'actualisation de l'hierarchie de tous les notes dans le sideBar
     */
    void UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR();
    void BACKEND_SAVE();
    /*!
     * \brief BACKEND_SET Design Pattern template methode. Cette methode va sauvegarder deja le titre, et puis delegue le sauvegarde du contenu aux classes filles.
     */
    void BACKEND_SET();

    /*!
     * \brief ADD_TAG_TO_NOTE Cette methode active le \link<tagDialog> qui permet d'associe les tags aux Notes.
     */
    void ADD_TAG_TO_NOTE();

    /*!
     * \brief updateDocBtnWithRessource ceci va actualise les \link<documentBtn> dans les editeurs avec tous les notes a partir d'un TreeItem \link<item>. Par exemple, un double click sur une note contenue dans Document LO21 va etre affiche avec "LO21" sur le \link<documentBtn>
     * \param item le TreeItem double clique.
     */
    void updateDocBtnWithRessource(TreeItem *item);

    /*!
     * \brief FIRE_UP_DOC_DIALOG afficher le \link<docDialog> qui permet aux utilisateurs de choisir les documents qui contient le note associe a cet Editor.
     */
    void FIRE_UP_DOC_DIALOG();
    /*!
     * \brief retrieveDataFromDocDialog Cette slot recuperer les documents active depuis le \link<docDialog>
     */
    void retrieveDataFromDocDialog();
    /*!
     * \brief retrieveDataFromTagDialog Cette slot recuperer les tags active depuis le \link<tagDialog>
     */
    void retrieveDataFromTagDialog();

    /*!
     * \brief REMOVE_NOTE_TO_TRASH deplace le note associe a cet Editor dans la corbeille. Si cet Editor s'agit d'un DocumetEditor, alors tous les sous editeurs seront ferme mais seule le document sera deplace vers la corbeille.
     */
    void REMOVE_NOTE_TO_TRASH();
    /*!
     * \brief CLOSE_NOTE_EDITOR Fermer l'editor actuel
     */
    void CLOSE_NOTE_EDITOR();

};

#endif // EDITOR_H
