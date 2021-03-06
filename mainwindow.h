#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <stack>
#include <list>
#include <string>
#include <fstream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<std::string> string_split(std::string s);

private slots:
    void on_btn_open_file_clicked();

    void on_btn_verify_connection_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
