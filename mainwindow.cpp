#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int** matrix;
int nods = 0;
int edges = 0;

void MainWindow::on_btn_open_file_clicked()
{
    int line = 1;
    QString matrixLine;

    vector<string> values;
    QMessageBox msg;
    string fileName = string(QFileDialog::getOpenFileName(this, "Abrir Arquivo", "D://").toStdString());
    string value;
    ifstream read;

    read.open(fileName);
    if (read.fail()) {
        msg.setWindowTitle("Erro em arquivo");
        msg.setText(strerror(errno));
        msg.exec();
        return;
    }

    ui->lw_grafo->clear();
    ui->lw_matrix->clear();
    ui->lbl_file_name->setText(QString::fromStdString(fileName));

    if (getline(read, value)) {
        const QString data = QString::fromStdString(value);
        ui->lw_grafo->addItem(data);

        values = string_split(value);

        if (line == 1) {
            nods = std::stoi(values.at(0));
            edges = std::stoi(values.at(1));
        }

        line++;
    }

    matrix = new int*[nods];
    for (int i = 0; i < nods; i++) {
        matrix[i] = new int[nods];
    }

    for (int i = 0; i < nods; i++) {
        for (int j = 0; j < nods; j++) {
            matrix[i][j] = 0;
        }
    }

    while(getline(read, value)) {
        const QString data = QString::fromStdString(value);
        ui->lw_grafo->addItem(data);
        values = string_split(value);

        int x = std::stoi(values.at(0)) - 1;
        int y = std::stoi(values.at(1)) - 1;

        matrix[x][y] = 1;
        matrix[y][x] = 1;
    }

    for (int i = 0; i < nods; i++) {
        matrixLine = "";
        for (int j = 0; j < nods; j++) {
            matrixLine.append(" ");
            matrixLine.append(QString::number(matrix[i][j]));
        }
        ui->lw_matrix->addItem(matrixLine);
    }

    read.close();
}

void MainWindow::on_btn_verify_connection_clicked()
{
    QMessageBox msg;
    int position1 = int(ui->le_first_field->text().toInt());
    int position2 = int(ui->le_second_field->text().toInt());
    vector<int> connections;
    vector<int> path;

    for (int i = 0; i < nods; i++) {
        if (matrix[position1][i] == 1) {
            connections.push_back(i);
        }
    }

    if (connections.size() == 0) {
        msg.setWindowTitle("Sem conexão");
        msg.setText("O nó apresentado não tem nenhuma conexão");
        msg.exec();

        return;
    }

    // Verificando se o segundo elemento foi encontrado como conexão no primeiro nível
    if (std::find(connections.begin(), connections.end(), position2) != connections.end()) {
        msg.setWindowTitle("Conexões");
        msg.setText("Existe conexão entre " + QString::number(position1) + " e " + QString::number(position2));
        msg.exec();

        return;
    }

    msg.setWindowTitle("Sem conexão");
    msg.setText("Não existem conexões entre os dois nós");
    msg.exec();

    return;
}

/**
 * @brief string_split
 * @param s
 * @return
 */
vector<string> MainWindow::string_split(string s)
{
    vector<string> values;
    int pos = s.find_first_of(' ');

    values.push_back(s.substr(0, pos));
    values.push_back(s.substr(pos + 1));

    return values;
}
