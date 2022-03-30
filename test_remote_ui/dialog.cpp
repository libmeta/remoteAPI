#include "dialog.hpp"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    RemoteApi();
}

Dialog::~Dialog()
{
    delete ui;
}

