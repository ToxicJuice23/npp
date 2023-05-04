#include "notepad.h"

NotePad::NotePad(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600, 400);
    central_widget = new QWidget();
    main_layout = new QGridLayout();
    menu_bar = new QMenuBar();
    buttons = new QHBoxLayout();
    editor = new QTextEdit();
    central_widget->setLayout(main_layout);
    main_layout->addWidget(menu_bar, 0, 0);
    main_layout->addLayout(buttons, 1, 0);
    main_layout->addWidget(editor, 2, 0);

    // layout attributes
    buttons->setAlignment(Qt::AlignLeft);

    // buttons
    open_image = QPixmap("/home/jujur/Documents/npp/open.png");
    QIcon OpenIcon = QIcon(open_image);
    open_b = new QPushButton();
    save_image = QPixmap("/home/jujur/Documents/npp/save.png");
    QIcon ButtonIcon = QIcon(save_image);
    save_b = new QPushButton();
    new_image = QPixmap("/home/jujur/Documents/npp/new.png");
    QIcon NewIcon = QIcon(new_image);
    new_b = new QPushButton();
    undo_image = QPixmap("/home/jujur/Documents/npp/undo.png");
    QIcon UndoIcon = QIcon(undo_image);
    undo_b = new QPushButton();
    redo_image = QPixmap("/home/jujur/Documents/npp/redo.png");
    QIcon RedoIcon = QIcon(redo_image);
    redo_b = new QPushButton();
    save_b->setToolTip("Save File");
    new_b->setToolTip("New File");
    open_b->setToolTip("Open File");
    undo_b->setToolTip("Undo");
    redo_b->setToolTip("Redo");

    file_b = new QMenu("File");
    edit_b = new QMenu("Edit");
    view_b = new QMenu("View");
    help_b = new QMenu("Help");
    window_b = new QMenu("Window");
    for (QMenu* button : {file_b, edit_b, view_b, help_b, window_b}) {
        button->setStyleSheet("border: none;");
        menu_bar->addMenu(button);
    }

    // set icons
    save_b->setIcon(ButtonIcon);
    new_b->setIcon(NewIcon);
    open_b->setIcon(OpenIcon);
    undo_b->setIcon(UndoIcon);
    redo_b->setIcon(RedoIcon);
    save_b->setIconSize(save_image.rect().size()/15);
    new_b->setIconSize(QSize(20, 20));
    open_b->setIconSize(QSize(20, 20));
    undo_b->setIconSize(QSize(20, 20));
    redo_b->setIconSize(QSize(20, 20));
    buttons->addWidget(open_b);
    buttons->addWidget(new_b);
    buttons->addWidget(save_b);
    buttons->addWidget(undo_b);
    buttons->addWidget(redo_b);
    save_b->setStyleSheet("border: none;");
    new_b->setStyleSheet("border: none;");
    open_b->setStyleSheet("border: none");
    undo_b->setStyleSheet("border: none");
    redo_b->setStyleSheet("border: none");


    setCentralWidget(central_widget);

    // object connects
    connect(save_b, SIGNAL(clicked()), this, SLOT(on_save_clicked()));
    connect(new_b, SIGNAL(clicked()), this, SLOT(on_new_clicked()));
    connect(open_b, SIGNAL(clicked()), this, SLOT(on_open_clicked()));
    connect(undo_b, SIGNAL(clicked()), this, SLOT(on_undo_clicked()));
    connect(redo_b, SIGNAL(clicked()), this, SLOT(on_redo_clicked()));
    current_file = "/home/jujur/Untitled";
    setWindowTitle(("Npp | "+current_file).c_str());
    generate_actions();
}

NotePad::~NotePad()
{
}

void NotePad::on_save_clicked() {
    qDebug("Save File");
    QFile file(current_file.c_str(), this);
    file.open(QIODevice::ReadWrite);
    file.write(editor->toPlainText().toStdString().c_str());
    if (current_file == "/home/jujur/Untitled") {
        on_open_clicked();
        return;
    }
}

void NotePad::on_new_clicked() {
    qDebug("new file");
    current_file = "/home/jujur/Untitled";
    editor->clear();
}

void NotePad::on_open_clicked() {
    qDebug("open file");
    QFileDialog* fd = new QFileDialog(nullptr, "Choose a file", "/home/jujur", "*");
    QString fn = fd->getOpenFileName();
    QFile file(fn, this);
    file.open(QIODevice::ReadOnly);
    QString fc = file.read(100000);
    if (!fc.isEmpty()) {
        editor->setText(fc);
        current_file = fn.toStdString();
    }
}

void NotePad::on_undo_clicked() {
    editor->undo();
}

void NotePad::on_redo_clicked() {
    editor->redo();
}

void NotePad::generate_actions() {
    // file buttons
    new_file_action = new QAction("New File");
    open_file_action = new QAction("Open File");
    save_file_action = new QAction("Save File");
    print_file_action = new QAction("Print");

    // edit buttons
    copy_action = new QAction("Copy");
    paste_action = new QAction("Paste");
    cut_action = new QAction("Cut");
    select_all_action = new QAction("Select All");
    undo_action = new QAction("Undo");
    redo_action = new QAction("Redo");

    // add to menu
    file_b->addAction(new_file_action);
    file_b->addAction(open_file_action);
    file_b->addAction(save_file_action);
    file_b->addAction(print_file_action);

    edit_b->addAction(copy_action);
    edit_b->addAction(paste_action);
    edit_b->addAction(cut_action);
    edit_b->addAction(select_all_action);
    edit_b->addAction(undo_action);
    edit_b->addAction(redo_action);

    connect(new_file_action, SIGNAL(triggered()), this, SLOT(on_new_file_action_triggered()));
    connect(open_file_action, SIGNAL(triggered()), this, SLOT(on_open_file_action_triggered()));
    connect(save_file_action, SIGNAL(triggered()), this, SLOT(on_save_file_action_triggered()));
    connect(print_file_action, SIGNAL(triggered()), this, SLOT(on_print_file_action_triggered()));

    connect(undo_action, SIGNAL(triggered()), this, SLOT(on_undo_clicked()));
    connect(redo_action, SIGNAL(triggered()), this, SLOT(on_redo_clicked()));
    connect(copy_action, SIGNAL(triggered()), editor, SLOT(copy()));
    connect(paste_action, SIGNAL(triggered()), editor, SLOT(paste()));
    connect(cut_action, SIGNAL(triggered()), editor, SLOT(cut()));
    connect(select_all_action, SIGNAL(triggered()), editor, SLOT(selectAll()));
}

void NotePad::on_new_file_action_triggered() {
    on_new_clicked();
}

void NotePad::on_open_file_action_triggered() {
    on_open_clicked();
}

void NotePad::on_save_file_action_triggered() {
    on_save_clicked();
}

void NotePad::on_print_file_action_triggered() {
    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print");

    if (dialog->exec() != QDialog::Accepted)
        return;

    QPainter painter;
    painter.begin(&printer);

    painter.drawText(100, 100, 500, 500, Qt::AlignLeft|Qt::AlignTop, editor->toPlainText());
}
