#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSortFilterProxyModel>

#include <QMainWindow>

//#include <QDate>
//#include <QDialog>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>

#include <QSqlError>
#include <QtDebug>

#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QTextStream>
#include <QTextDocument>
#include <QFileDialog>
#include <QTextDocumentWriter>

#include "db.h"
#include "model/incomingtable.h"
#include "model/spendtable.h"

#include "r_d.h"
#include "d_edit.h"
#include "r_edit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectToSql();
}

void MainWindow::connectToSql()
{
    if(DB::conection()) {
        modelIncoming = new IncomingTable(this);
        modelSpend = new SpendTable(this);

        modelSpend->select();
        modelSpend->setHeader();

        modelIncoming->select();
        modelIncoming->setHeader();

        ui->tableViewIncoming->setModel(modelIncoming);
        ui->tableViewIncoming->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        ui->tableViewIncoming->setColumnHidden(0, true);
        ui->tableViewIncoming->setColumnHidden(3, true);
        ui->tableViewIncoming->setColumnHidden(4, true);
        ui->tableViewIncoming->setColumnHidden(5, true);

        ui->tableViewSpend->setModel(modelSpend);
        ui->tableViewSpend->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        ui->tableViewSpend->setColumnHidden(0, true);
        ui->tableViewSpend->setColumnHidden(3, true);
        ui->tableViewSpend->setColumnHidden(4, true);
        ui->tableViewSpend->setColumnHidden(5, true);
    } else {
        QMessageBox::critical(this,"Error", DB::db().lastError().text());
    }

    sumUpdate();
}

MainWindow::~MainWindow()
{
    delete modelSpend;
    delete modelIncoming;

    delete ui;

    DB::disconection();
}

void MainWindow::on_dohod_triggered()
{
    R_d dial(modelIncoming, "доход");
    dial.exec();

    modelIncoming->select();
    sumUpdate();
}

void MainWindow::on_rashod_triggered()
{
    R_d dial(modelSpend, "расход");
    dial.exec();

    modelSpend->select();
    sumUpdate();
}

void MainWindow::on_searc_d_clicked()
{
    int day = ui->day_d->text().toInt();
    int month = ui->month_d->text().toInt();
    int year = ui->year_d->text().toInt();

    modelIncoming->setFilter(day, month, year);
    modelIncoming->select();
    sumUpdate();
}

void MainWindow::on_searc_r_clicked()
{
    int day = ui->day_r->text().toInt();
    int month = ui->month_r->text().toInt();
    int year = ui->year_r->text().toInt();

    modelSpend->setFilter(day, month, year);
    modelSpend->select();
    sumUpdate();
}

void MainWindow::on_print_d_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableViewIncoming->model()->rowCount();
    const int columnCount = ui->tableViewIncoming->model()->columnCount();

    out << "<html>\n" << "<head>\n" << "meta Content=\"Text/html;charset=Windows-1215\">\n" <<
           QString("<title>%1</title>\n").arg("Report")<<
           "</head\n"
           "<body bgcolor = #ffffff link=#5000A0>\n"
           "<table border = 1 cellspacing=0 cellpadding=2\n";

    out << "<thead><tr bgcolor=#f0f0f0>";

    for(int column = 0; column < columnCount; column++){
        if(!ui->tableViewIncoming->isColumnHidden(column)){
            out << QString("<th>%1</th>")
                   .arg(ui->tableViewIncoming->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++){

            if (!ui->tableViewIncoming->isColumnHidden(column)){

                QString data = ui->tableViewIncoming->model()
                        ->data(ui->tableViewIncoming->model()->index(row, column))
                        .toString().simplified();
                out << QString("<td bkcolor=0>%1</td>")
                       .arg( (!data.isEmpty())? data:QString("&nbsp;") );
            }
        }
        out << "</tr>\n";
    }
    out << "</table>\n""</body>\n""</html>\n";

    QTextDocument *document = new QTextDocument;
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer,0);
    if (dialog->exec() == QDialog::Accepted){
        QString filename = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Текстовый документ (*.pdf)");
        printer.setOutputFileName(filename);
        document->print(&printer);
    }
    delete document;
}

void MainWindow::on_print_r_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableViewSpend->model()->rowCount();
    const int columnCount = ui->tableViewSpend->model()->columnCount();

    out << "<html>\n" << "<head>\n" << "meta Content=\"Text/html;charset=Windows-1215\">\n" <<
           QString("<title>%1</title>\n").arg("Report")<<
           "</head\n"
           "<body bgcolor = #ffffff link=#5000A0>\n"
           "<table border = 1 cellspacing=0 cellpadding=2\n";

    out << "<thead><tr bgcolor=#f0f0f0>";

    for(int column = 0; column < columnCount; column++){

        if(!ui->tableViewSpend->isColumnHidden(column)){
            out << QString("<th>%1</th>").arg(ui->tableViewSpend->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {

        out << "<tr>";
        for (int column = 0; column < columnCount; column++){

            if (!ui->tableViewSpend->isColumnHidden(column)){

                QString data = ui->tableViewSpend->model()->data(ui->tableViewSpend->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty())? data:QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out << "</table>\n""</body>\n""</html>\n";

    QTextDocument *document = new QTextDocument;
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer,0);
    if (dialog->exec() == QDialog::Accepted){
        QString filename = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Текстовый документ (*.pdf)");
        printer.setOutputFileName(filename);
        document->print(&printer);
    }
    delete document;
}

void MainWindow::on_update_clicked()
{
}

void MainWindow::sumUpdate() {
    int incoming = modelIncoming->sum();
    int spend = modelSpend->sum();

    ui->sum_d->setText(QString::number(incoming));
    ui->sum_r->setText(QString::number(spend));

    ui->sum->setText(QString::number(incoming - spend));
}
