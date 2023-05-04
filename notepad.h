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
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QtPrintSupport/QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <iostream>
#include <stdio.h>
using namespace std;

class NotePad : public QMainWindow
{
    Q_OBJECT
    QSpacerItem* spacer;
    QWidget* central_widget;
    QHBoxLayout* buttons;
    QGridLayout* main_layout;
    QTextEdit* editor;
    QMenu *file_b, *edit_b, *view_b, *help_b, *window_b;
    QMenuBar* menu_bar;
    QPushButton/**/ *save_b, *new_b, *open_b, *undo_b, *redo_b;
    QPixmap save_image, new_image, open_image, undo_image, redo_image;
    string current_file;
    // actions
    QAction* new_file_action, *open_file_action, *undo_action, *redo_action,
        *save_file_action, *print_file_action, *cut_action, *copy_action,
        *paste_action, *select_all_action, *full_screen_action, *minimize_action,
        *open_new_window_action, *about_action, *contact_action;
public:
    NotePad(QWidget *parent = nullptr);
    ~NotePad();
private:
    void generate_actions();
private slots:
    void on_save_clicked();
    void on_new_clicked();
    void on_open_clicked();
    void on_undo_clicked();
    void on_redo_clicked();

    void on_new_file_action_triggered();
    void on_open_file_action_triggered();
    void on_save_file_action_triggered();
    void on_print_file_action_triggered();
};
#endif // NOTEPAD_H
