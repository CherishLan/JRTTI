/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created: Wed Dec 14 15:13:19 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_endEA;
    QTableWidget *tableWidget_filter;
    QLabel *label;
    QPushButton *pushButton_add;
    QLineEdit *lineEdit_beginEA;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_targetDir;
    QToolButton *toolButton_showFileDialog;
    QPushButton *pushButton_generateFiles;
    QTextBrowser *textBrowser_rtti;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(1099, 650);
        MainWidget->setInputMethodHints(Qt::ImhUppercaseOnly);
        gridLayout_2 = new QGridLayout(MainWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(MainWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, -1, -1, -1);
        lineEdit_endEA = new QLineEdit(groupBox);
        lineEdit_endEA->setObjectName(QString::fromUtf8("lineEdit_endEA"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_endEA->sizePolicy().hasHeightForWidth());
        lineEdit_endEA->setSizePolicy(sizePolicy1);
        lineEdit_endEA->setInputMethodHints(Qt::ImhUppercaseOnly);

        gridLayout->addWidget(lineEdit_endEA, 1, 3, 1, 1);

        tableWidget_filter = new QTableWidget(groupBox);
        tableWidget_filter->setObjectName(QString::fromUtf8("tableWidget_filter"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidget_filter->sizePolicy().hasHeightForWidth());
        tableWidget_filter->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(tableWidget_filter, 0, 0, 1, 5);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 2, 1, 1);

        pushButton_add = new QPushButton(groupBox);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));

        gridLayout->addWidget(pushButton_add, 1, 4, 1, 1);

        lineEdit_beginEA = new QLineEdit(groupBox);
        lineEdit_beginEA->setObjectName(QString::fromUtf8("lineEdit_beginEA"));
        sizePolicy1.setHeightForWidth(lineEdit_beginEA->sizePolicy().hasHeightForWidth());
        lineEdit_beginEA->setSizePolicy(sizePolicy1);
        lineEdit_beginEA->setInputMethodHints(Qt::ImhUppercaseOnly);

        gridLayout->addWidget(lineEdit_beginEA, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(MainWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_targetDir = new QLineEdit(groupBox_2);
        lineEdit_targetDir->setObjectName(QString::fromUtf8("lineEdit_targetDir"));
        sizePolicy1.setHeightForWidth(lineEdit_targetDir->sizePolicy().hasHeightForWidth());
        lineEdit_targetDir->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lineEdit_targetDir);

        toolButton_showFileDialog = new QToolButton(groupBox_2);
        toolButton_showFileDialog->setObjectName(QString::fromUtf8("toolButton_showFileDialog"));

        horizontalLayout->addWidget(toolButton_showFileDialog);

        pushButton_generateFiles = new QPushButton(groupBox_2);
        pushButton_generateFiles->setObjectName(QString::fromUtf8("pushButton_generateFiles"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_generateFiles->sizePolicy().hasHeightForWidth());
        pushButton_generateFiles->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(pushButton_generateFiles);


        gridLayout_2->addWidget(groupBox_2, 1, 1, 1, 1);

        textBrowser_rtti = new QTextBrowser(MainWidget);
        textBrowser_rtti->setObjectName(QString::fromUtf8("textBrowser_rtti"));

        gridLayout_2->addWidget(textBrowser_rtti, 0, 0, 2, 1);

        QWidget::setTabOrder(lineEdit_targetDir, toolButton_showFileDialog);
        QWidget::setTabOrder(toolButton_showFileDialog, pushButton_generateFiles);
        QWidget::setTabOrder(pushButton_generateFiles, lineEdit_beginEA);
        QWidget::setTabOrder(lineEdit_beginEA, lineEdit_endEA);
        QWidget::setTabOrder(lineEdit_endEA, pushButton_add);
        QWidget::setTabOrder(pushButton_add, tableWidget_filter);
        QWidget::setTabOrder(tableWidget_filter, textBrowser_rtti);

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWidget", "\350\277\207\346\273\244\345\231\250", 0, QApplication::UnicodeUTF8));
        lineEdit_endEA->setPlaceholderText(QApplication::translate("MainWidget", "endEA: ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWidget", "-", 0, QApplication::UnicodeUTF8));
        pushButton_add->setText(QApplication::translate("MainWidget", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        lineEdit_beginEA->setPlaceholderText(QApplication::translate("MainWidget", "beginEA: ", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWidget", "\347\224\237\346\210\220\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        toolButton_showFileDialog->setText(QApplication::translate("MainWidget", "...", 0, QApplication::UnicodeUTF8));
        pushButton_generateFiles->setText(QApplication::translate("MainWidget", "\347\224\237\346\210\220", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
