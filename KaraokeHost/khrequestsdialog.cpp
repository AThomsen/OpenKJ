#include "khrequestsdialog.h"
#include "ui_khrequestsdialog.h"

KhRequestsDialog::KhRequestsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KhRequestsDialog)
{
    ui->setupUi(this);
    requestsModel = new RequestsTableModel(this);
    ui->treeViewRequests->setModel(requestsModel);
}

KhRequestsDialog::~KhRequestsDialog()
{
    delete ui;
}

void KhRequestsDialog::on_pushButtonClose_clicked()
{
    close();
}