// Copyright (c) 2016-2019 The Girauno developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef OPENURIDIALOG_H
#define OPENURIDIALOG_H

#include <QDialog>

namespace Ui {
class OpenURIDialog;
}

class OpenURIDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenURIDialog(QWidget *parent);
    ~OpenURIDialog();

    QString getURI();

protected slots:
    void accept();

private slots:
    void on_selectFileButton_clicked();

private:
    Ui::OpenURIDialog *ui;
};

#endif // OPENURIDIALOG_H
