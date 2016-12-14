#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "jbcbrtti.h"
#include "jclsfile.h"

#include <QDir>
#include <QMessageBox>
#include <QKeyEvent>
#include <QWidget>
#include <QFileDialog>
#include "ui_mainwidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void paintEvent(QPaintEvent *);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    bool eventFilter(QObject *obj, QEvent *event);

private:
    void showClsList();

    void tableWidgetInit();

    void newRow(ea_t beginEA, ea_t endEA);

    inline void clsListFilter();

    inline JEAList getEAList() const;

    void createActions();

    void generateFiles(const QString &targetDirPath);

private:
    QT::Ui::MainWidget *ui;

	JClassInfoList				m_clsList;
    JClassInfoList				m_clsListFilter;

    //QMenu						m_popMenu;

public slots:
private slots:
    void on_pushButton_add_clicked();

    void on_lineEdit_beginEA_textChanged(const QString &);
    void on_lineEdit_endEA_textChanged(const QString &);
    void on_lineEdit_targetDir_textChanged(const QString &arg1);
    void on_toolButton_showFileDialog_clicked();
    void on_pushButton_generateFiles_clicked();
};

#endif // MAINWIDGET_H
