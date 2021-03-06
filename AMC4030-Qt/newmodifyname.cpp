#include "newmodifyname.h"
#include "ui_newmodifyname.h"

#include "amc4030.h"
#include "newprogrameditor.h"
#include "newsavefile.h"

#include <QDebug>
#include <QMessageBox>
#include <QDir>

newModifyName::newModifyName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newModifyName)
{
    ui->setupUi(this);
}

newModifyName::~newModifyName()
{
    delete ui;
}

void newModifyName::on_pushButton_clicked()
{
    QString pattern("[\\\\ /:|*?\"<>]|[cC][oO][mM][1-9]|[lL][pP][tT][1-9]|[cC][oO][nM]|[pP][rR][nN]|[aA][uU][xX]|[nN][uU][lL]");
    QRegExp rx(pattern);
    int match = ui->lineEdit->text().indexOf(rx);
    if(match >= 0)
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("文件命名不规范，不能包含特殊字符和空格！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
    else if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("文件名不能为空！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
    else
    {
        QString FileName=ui->lineEdit->text();

        //检查当前文件夹路径下是否存在文件File_Name,如果有就停止操作。
        QString currentDir=QApplication::applicationDirPath()+"/Program";//获取应用程序所在的文件夹的路径+tr("/Program")

        QFile *tempFile = new QFile;
        if(tempFile->exists(currentDir+"/"+FileName+".txt"))
        {
            QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("此位置已有同名文件，请重新输入！"));
            mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
            mBox.exec();
            delete tempFile;
        }
        else
        {
            New_FileName = FileName;
            this->close();
        }
    }
}

void newModifyName::changeEvent(QEvent *e)    //重写的事件处理方法
{
    QDialog::changeEvent(e);    //让基类执行事件处理方法
    switch (e->type()) {        //根据事件类型判别
    case QEvent::LanguageChange:  //如果是语言改变事件
        ui->retranslateUi(this);    //更新UI的语言（看方法字面的，用户自定义方法）
        break;
    default:
        break;
    }
}
