#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QSpacerItem>
#include <QIcon>
#include <QBitmap>
#include <QFileDialog>
#include <iostream>
#include <stdio.h>
using namespace std;

class NotePad : public QMainWindow
{
    Q_OBJECT
    QSpacerItem* spacer;
    QWidget* central_widget;
    QHBoxLayout* menu_bar;
    QHBoxLayout* buttons;
    QGridLayout* main_layout;
    QTextEdit* editor;
    QPushButton *file_b, *edit_b, *view_b, *help_b, *window_b, /**/ *save_b, *new_b, *open_b;
    QPixmap save_image, new_image, open_image;
    string current_file;
public:
    NotePad(QWidget *parent = nullptr);
    ~NotePad();
private slots:
    void on_save_clicked();
    void on_new_clicked();
    void on_open_clicked();
};
#endif // NOTEPAD_H
