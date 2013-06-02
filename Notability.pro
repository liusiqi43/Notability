SOURCES += \
    main.cpp \
    Document.cpp \
    NotesManager.cpp \
    htmlViewer.cpp \
    BaseEditor.cpp \
    NoteFactory.cpp \
    ExportStrategy.cpp \
    NoteTypeSignalAction.cpp \
    NotesException.cpp \
    Note.cpp \
    Article.cpp \
    Binary.cpp \
    AudioNote.cpp \
    VideoNote.cpp \
    ImageNote.cpp \
    ArticleFactory.cpp \
    ImageNoteFactory.cpp \
    AudioNoteFactory.cpp \
    VideoNoteFactory.cpp \
    DocumentFactory.cpp \
    ArticleEditor.cpp \
    BinaryEditor.cpp \
    ImageNoteEditor.cpp \
    HtmlExport.cpp \
    TexExport.cpp \
    TextExport.cpp \
    SaveTextExport.cpp \
    AudioNoteEditor.cpp \
    VideoNoteEditor.cpp \
    DocumentEditor.cpp \
    TexViewer.cpp \
    mainwindow.cpp \
    TextViewer.cpp \
    TreeItem.cpp \
    Tag.cpp \
    TagManager.cpp \
    TreeModel.cpp \
    viewer.cpp \
    AddToDocDialog.cpp \
    ListWidgetItemCheckTag.cpp

HEADERS += \
    NotesManager.h \
    Tag.h \
    TagManager.h \
    htmlViewer.h \
    NoteFactory.h \
    ExportStrategy.h \
    NoteTypeSignalAction.h \
    ArticleEditor.h \
    BinaryEditor.h \
    ImageNoteEditor.h \
    Editor.h \
    ArticleFactory.h \
    ImageNoteFactory.h \
    AudioNoteFactory.h \
    VideoNoteFactory.h \
    DocumentFactory.h \
    HtmlExport.h \
    TexExport.h \
    TextExport.h \
    SaveTextExport.h \
    NotesException.h \
    Article.h \
    Note.h \
    Binary.h \
    ImageNote.h \
    VideoNote.h \
    AudioNote.h \
    Document.h \
    AudioNoteEditor.h \
    VideoNoteEditor.h \
    DocumentEditor.h \
    TexViewer.h \
    mainwindow.h \
    TextViewer.h \
    TreeItem.h \
    TreeModel.h \
    viewer.h \
    CheckComboBox.h \
    AddToDocDialog.h \
    ListWidgetItemCheckTag.h

QT      += widgets \
           webkitwidgets \
           core gui \
           multimedia \
           multimediawidgets \

CONFIG += mobility
MOBILITY = multimedia

FORMS += \
    mainwindow.ui \
    AddToDocDialog.ui

RESOURCES += \
    ressources.qrc
