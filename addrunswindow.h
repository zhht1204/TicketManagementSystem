#ifndef ADDRUNSWINDOW_H
#define ADDRUNSWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddRunsWindow;
}

class AddRunsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddRunsWindow(QWidget *parent = 0);
    ~AddRunsWindow();
private:
    Ui::AddRunsWindow *ui;
signals:
    void sendInformation(QString, QString, QString, QString, QString, QString, QString);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // ADDRUNSWINDOW_H
