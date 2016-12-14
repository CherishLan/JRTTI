#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new QT::Ui::MainWidget)
{
    ui->setupUi(this);
    ui->pushButton_add->setDisabled(true);
    ui->pushButton_generateFiles->setDisabled(true);

    ui->lineEdit_beginEA->installEventFilter(this);
    ui->lineEdit_endEA->installEventFilter(this);

    QString filename = QFileDialog::getOpenFileName(this, tr("打开RTTI信息文件"));
    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly))
        {
            return;
        }

        QByteArray lineData;
        while (!file.atEnd())
        {
            lineData = file.readLine();
            if (!lineData.isEmpty())
            {
                if (QString(lineData).indexOf("C++class") != -1 && QString(lineData).simplified().section(" ", -1, -1) == "C++class")
                {
                    ea_t ea = QString(lineData).section(" ", 0, 0).section(":", -1, -1).toLong(NULL, 16);
                    //msg("Seaching ea: [%x]\n", ea);

                    JClassInfo cls = JBcbRtti::getClassInfo(ea);
                    if (cls.isValid())
                    {
                        m_clsList.append(cls);
                    }
                    else
                    {
                        msg("cls: %x is invalid.", cls.beginEA);
                    }
                }
            }
        }

        file.close();
    }
    tableWidgetInit();

    showClsList();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent *)
{
    int width = ui->tableWidget_filter->width();

    int colCount = ui->tableWidget_filter->columnCount();
    for (int i = 0; i < colCount; ++i)
    {
        ui->tableWidget_filter->setColumnWidth(i, width / colCount);
    }
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if (ui->tableWidget_filter->hasFocus() && event->key() == Qt::Key_Delete)
    {
        event->accept();
        QList<QTableWidgetItem *> items = ui->tableWidget_filter->selectedItems();
        QList<int> rows;
        foreach (const QTableWidgetItem *item, items)
        {
            rows.append(item->row());
        }

        qSort(rows.begin(), rows.end(), qGreater<int>());
        foreach (int row, rows)
        {
            ui->tableWidget_filter->removeRow(row);
        }

        showClsList();
    }
    else if (event->key() == Qt::Key_Enter)
    {
        if (ui->lineEdit_beginEA->hasFocus() || ui->lineEdit_endEA->hasFocus())
        {
            event->accept();
            on_pushButton_add_clicked();
            ui->tableWidget_filter->setFocus();
        }
        else if (ui->lineEdit_targetDir->hasFocus() || ui->toolButton_showFileDialog->hasFocus())
        {
            event->accept();
            on_pushButton_generateFiles_clicked();
        }
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (ui->tableWidget_filter->hasFocus() && event->key() == Qt::Key_Delete)
    {
        event->accept();
    }
    else if ((ui->lineEdit_beginEA->hasFocus() || ui->lineEdit_endEA->hasFocus()) && event->key() == Qt::Key_Enter)
    {
        event->accept();
    }
}

bool MainWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEdit_beginEA || obj == ui->lineEdit_endEA)
    {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() >= Qt::Key_G && keyEvent->key() <= Qt::Key_Z)
            {
                event->accept();
                return true;
            }
        }
    }

    return QWidget::eventFilter(obj, event);
}

void MainWidget::showClsList()
{
    clsListFilter();

    QString text;
    msg("Current count for class list: %d\n", m_clsListFilter.size());
    foreach (const JClassInfo &cls, m_clsListFilter)
    {
        text += QString("\n\n[%1]%2").arg(QString::number(cls.beginEA, 16).toUpper()).arg(cls.name);
        text += cls.inheritList.toText();
    }

    ui->textBrowser_rtti->setText(text);
}

void MainWidget::tableWidgetInit()
{
    ui->tableWidget_filter->setColumnCount(2);
    ui->tableWidget_filter->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_filter->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_filter->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void MainWidget::newRow(ea_t beginEA, ea_t endEA)
{
    if (beginEA == BADADDR || beginEA == 0 || endEA == BADADDR || endEA == 0)
    {
        QMessageBox msg(QMessageBox::Warning, tr("错误"), tr("区间值不正确!"), QMessageBox::Ok, this);

        msg.exec();
        return;
    }
    QTableWidget *tw = ui->tableWidget_filter;

    int row = tw->rowCount();
    QTableWidgetItem *itemBegin = new QTableWidgetItem(QString::number(beginEA, 16).toUpper());
    QTableWidgetItem *itemEnd = new QTableWidgetItem(QString::number(endEA, 16).toUpper());

    tw->insertRow(row);
    tw->setItem(row, 0, itemBegin);
    tw->setItem(row, 1, itemEnd);
}

void MainWidget::clsListFilter()
{
    JEAList list = getEAList();
    m_clsListFilter = m_clsList;

    for (int i = 0; i < m_clsListFilter.count();)
    {
        JClassInfo cls = m_clsListFilter.at(i);

        for (int j = 0, count = list.count(); j < count; ++j)
        {
            const JEA &ea = list.at(j);
            ea_t beginEA = (ea.beginEA < ea.endEA ? ea.beginEA : ea.endEA);
            ea_t endEA = (ea.beginEA > ea.endEA ? ea.beginEA : ea.endEA);
            if (cls.beginEA >= beginEA && cls.beginEA <= endEA)
            {
                m_clsListFilter.removeAt(i);

                --i;
                break;
            }
        }
        ++i;
    }
}

JEAList MainWidget::getEAList() const
{
    int rowCount = ui->tableWidget_filter->rowCount();
    JEAList list;

    QTableWidgetItem *itemBegin = NULL;
    QTableWidgetItem *itemEnd = NULL;
    for (int i = 0; i < rowCount; ++i)
    {
        itemBegin = ui->tableWidget_filter->item(i, 0);
        itemEnd = ui->tableWidget_filter->item(i, 1);

        JEA ea;
        ea.beginEA = itemBegin->text().toLong(NULL, 16);
        ea.endEA = itemEnd->text().toLong(NULL, 16);
        //msg("beginea: %x, endEA: %x\n", ea.beginEA, ea.endEA);
        list.append(ea);
    }

    return list;
}

void MainWidget::createActions()
{
    // m_popMenu = new QMenu;
}

void MainWidget::generateFiles(const QString &targetDirPath)
{
    msg("Starting to generate class files.");

    JClsFile::generateFiles(m_clsListFilter, targetDirPath);

    msg("Class files has finished.");
}

void MainWidget::on_pushButton_add_clicked()
{
    newRow(ui->lineEdit_beginEA->text().toLong(NULL, 16), ui->lineEdit_endEA->text().toLong(NULL, 16));
    showClsList();

    ui->lineEdit_beginEA->clear();
    ui->lineEdit_endEA->clear();
}

void MainWidget::on_lineEdit_beginEA_textChanged(const QString &)
{
    if (ui->lineEdit_beginEA->text().isEmpty() || ui->lineEdit_endEA->text().isEmpty())
    {
        ui->pushButton_add->setDisabled(true);
    }
    else
    {
        ui->pushButton_add->setEnabled(true);
    }
}

void MainWidget::on_lineEdit_endEA_textChanged(const QString &)
{
    if (ui->lineEdit_beginEA->text().isEmpty() || ui->lineEdit_endEA->text().isEmpty())
    {
        ui->pushButton_add->setDisabled(true);
    }
    else
    {
        ui->pushButton_add->setEnabled(true);
    }
}

void MainWidget::on_lineEdit_targetDir_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        ui->pushButton_generateFiles->setDisabled(true);
    }
    else
    {
        ui->pushButton_generateFiles->setEnabled(true);
    }
}

void MainWidget::on_toolButton_showFileDialog_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("指定存放目录"));
    if (!dirPath.isEmpty())
    {
        ui->lineEdit_targetDir->setText(dirPath);
    }
}

void MainWidget::on_pushButton_generateFiles_clicked()
{
    QString targetDirPath = ui->lineEdit_targetDir->text();
    QDir dir;
    if (!dir.exists(targetDirPath))
    {
        if (!dir.mkpath(targetDirPath))
        {
            QString text = tr("创建路径[") + targetDirPath + tr("]失败! ");
            QMessageBox msg(QMessageBox::Warning, tr("错误"), text, QMessageBox::Ok, this);
            msg.exec();

            return;
        }
    }

    generateFiles(targetDirPath);
}
