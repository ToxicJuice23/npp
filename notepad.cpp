#include "notepad.h"

NotePad::NotePad(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600, 400);
    central_widget = new QWidget();
    main_layout = new QGridLayout();
    menu_bar = new QHBoxLayout();
    buttons = new QHBoxLayout();
    editor = new QTextEdit();
    central_widget->setLayout(main_layout);
    main_layout->addLayout(menu_bar, 0, 0);
    main_layout->addLayout(buttons, 1, 0);
    main_layout->addWidget(editor, 2, 0);

    // layout attributes
    buttons->setAlignment(Qt::AlignLeft);
    menu_bar->setAlignment(Qt::AlignLeft);

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
    save_b->setToolTip("Save File");
    new_b->setToolTip("New File");
    open_b->setToolTip("Open File");

    file_b = new QPushButton("File");
    edit_b = new QPushButton("Edit");
    view_b = new QPushButton("View");
    help_b = new QPushButton("Help");
    window_b = new QPushButton("Window");
    for (QPushButton* button : {file_b, edit_b, view_b, help_b, window_b}) {
        button->setStyleSheet("border: none;");
        menu_bar->addWidget(button);
    }
    spacer = new QSpacerItem(400, 1);
    menu_bar->addSpacerItem(spacer);

    save_b->setIcon(ButtonIcon);
    new_b->setIcon(NewIcon);
    open_b->setIcon(OpenIcon);
    save_b->setIconSize(save_image.rect().size()/15);
    new_b->setIconSize(QSize(20, 20));
    open_b->setIconSize(QSize(20, 20));
    buttons->addWidget(open_b);
    buttons->addWidget(new_b);
    buttons->addWidget(save_b);
    save_b->setStyleSheet("border: none;");
    new_b->setStyleSheet("border: none;");
    open_b->setStyleSheet("border: none");

    setCentralWidget(central_widget);

    // object connects
    connect(save_b, SIGNAL(clicked()), this, SLOT(on_save_clicked()));
    connect(new_b, SIGNAL(clicked()), this, SLOT(on_new_clicked()));
    connect(open_b, SIGNAL(clicked()), this, SLOT(on_open_clicked()));
    current_file = "/home/jujur/Untitled";
    setWindowTitle(("Npp | "+current_file).c_str());
}

NotePad::~NotePad()
{
}

void NotePad::on_save_clicked() {
    qDebug("Save File");
    if (current_file == "/home/jujur/Untitled") {
        on_open_clicked();
        return;
    }
    QFile file(current_file.c_str(), this);
    file.open(QIODevice::ReadWrite);
    file.write(editor->toPlainText().toStdString().c_str());
}

void NotePad::on_new_clicked() {
    qDebug("new file");
    current_file = "~/Untitled";
    editor->clear();
}

void NotePad::on_open_clicked() {
    qDebug("open file");
    QFileDialog* fd = new QFileDialog(nullptr, "Choose a file", "/home/jujur", "*");
    QString fn = fd->getOpenFileName();
    current_file = fn.toStdString();
    QFile file(fn, this);
    file.open(QIODevice::ReadOnly);
    QString fc = file.read(100000);
    editor->setText(fc);
}
