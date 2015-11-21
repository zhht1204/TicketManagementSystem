#ifndef ALTERRUNSWINDOW_H
#define ALTERRUNSWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AlterRunsWindow;
}

class AlterRunsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AlterRunsWindow(QWidget *parent = 0);
    ~AlterRunsWindow();

signals:
    void sendInformation(int,  QString, QString, QString, QString, QString, QString, QString);

private slots:
    void getInformation(int, QString, QString, QString, QString, QString, QString, QString);

    void on_buttonBox_accepted();

private:
    Ui::AlterRunsWindow *ui;
    int index;
};

#endif // ALTERRUNSWINDOW_H
