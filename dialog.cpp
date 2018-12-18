/**
 * @brief  Created by civen163@163.com
 * @date   yyyy-MM-dd
 * @author Civen
 */
#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>
#include "prompt_dialog.h"

#ifndef QStringLiteral
# define QStringLiteral(str) QString::fromUtf8("" str "", sizeof(str) - 1)
#endif
#define TR(v) QStringLiteral(v)

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize( size() );

    initButtons();
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::initButtons()
{
    m_byLeftData.clear();
    m_byRightData.clear();
    m_listPushButtons.clear();
    m_listPushButtons = findChildren<QPushButton *>();

    foreach ( QPushButton *pButton, m_listPushButtons )
    {
        connect( pButton, SIGNAL(clicked()), this, SLOT(clickedButton()) );
    }

    return;
}


bool Dialog::getInputString( QString &strOutPutBuffer, const DIRECT eDirect )
{
    QString strPrompt;

    strOutPutBuffer.clear();
    strPrompt.clear();

    if ( D_LEFT == eDirect )
    {
        strOutPutBuffer = ui->rawTextEdit->toPlainText();
        m_byLeftData = strOutPutBuffer.toLatin1();
        strPrompt = "请在左侧编辑框输入数据!";
    }
    else if ( D_RIGHT == eDirect )
    {
        strOutPutBuffer = ui->aimTextEdit->toPlainText();
        m_byRightData = strOutPutBuffer.toLatin1();
        strPrompt = "请在右侧编辑框输入数据!";
    }

    if ( strOutPutBuffer.isEmpty() )
    {
        QMessageBox::warning( this, "提示", strPrompt );

        return false;
    }

    return true;
}


void Dialog::setResult( const QByteArray &bydataBuffer, const DIRECT eDirect )
{
    if ( D_LEFT == eDirect )
    {
        m_byLeftData = bydataBuffer;
        ui->rawTextEdit->clear();
        ui->rawTextEdit->setText( QString(bydataBuffer.constData()) );
    }
    else if ( D_RIGHT == eDirect )
    {
        m_byRightData = bydataBuffer;
        ui->aimTextEdit->clear();
        ui->aimTextEdit->setText( QString(bydataBuffer.constData()) );
    }

    return;
}


void Dialog::encBase64()
{
    QString strData;

    if ( getInputString(strData, D_LEFT) )
    {
        QByteArray byResultData = strData.toLatin1();
        setResult( byResultData.toBase64(), D_RIGHT );
    }

    return;
}


void Dialog::decBase64()
{
    QString strData;

    if ( getInputString(strData, D_RIGHT) )
    {
        QByteArray byResultData = strData.toLatin1();
        setResult( QByteArray::fromBase64(byResultData), D_LEFT );
    }

    return;
}


void Dialog::encHex()
{
    QString strData;

    if ( getInputString(strData, D_LEFT) )
    {
        QByteArray byResultData = strData.toLatin1();
        setResult( byResultData.toHex(), D_RIGHT );
    }

    return;
}


void Dialog::decHex()
{
    QString strData;

    if ( getInputString(strData, D_RIGHT) )
    {
        QByteArray byResultData = strData.toLatin1();
        setResult( QByteArray::fromHex(byResultData), D_LEFT );
    }

    return;
}


void Dialog::calcHash( const QCryptographicHash::Algorithm eType, const bool bIsFile )
{
    QByteArray byData;
    QString strMd5( "" );

    byData.clear();

    if ( bIsFile )
    {
        QString strFile = QFileDialog::getOpenFileName( this, "请选择需要计算的文件" );

        if ( !strFile.isEmpty() )
        {
            QFile file( strFile );
            file.open( QIODevice::ReadOnly );
            if ( file.isOpen() )
            {
                byData = file.readAll();
                file.close();

                if ( !byData.isEmpty() )
                {
                    strMd5 = "文件 \"" + strFile + "\" 的 " + ui->comboBox->currentText() + " 计算结果为：\n---------------\n";
                }
            }
        }
        else
        {
            PromptDialog(  "未指定目标文件!" );
        }
    }
    else
    {
        QString strData( "" );
        getInputString( strData, D_LEFT );

        if ( !strData.isEmpty() )
        {
            byData = QByteArray( strData.toStdString().c_str() );
        }
    }

    if ( !byData.isEmpty() )
    {
        QCryptographicHash hash( eType );
        hash.addData( byData );
        strMd5 +=  hash.result().toHex();
        QByteArray byResultData = QByteArray( strMd5.toStdString().c_str() );
        setResult( byResultData , D_RIGHT );
    }

    return;
}


void Dialog::saveData( const DIRECT eType )
{
    QString strSaveFile = QFileDialog::getSaveFileName( this, "请设置存放目标文件的路径" );

    if ( !strSaveFile.isEmpty() )
    {
        QFile file( strSaveFile );

        file.open( QIODevice::WriteOnly );

        if ( file.isOpen() )
        {
            int iRet = -1;
            QString strPrompt( "" );

            if ( D_LEFT == eType )
            {
                iRet = file.write( m_byLeftData );
                strPrompt = "保存左侧数据成功！";
            }
            else if ( D_RIGHT == eType )
            {
                iRet = file.write( m_byRightData );
                strPrompt = "保存右侧数据成功！";
            }

            file.close();

            if ( 0 > iRet )
            {
                QMessageBox::warning( this, "错误", "保存数据错误！" );
            }
            else
            {
                QMessageBox::information( this, "提示", strPrompt );
            }
        }
    }

    return;
}


QCryptographicHash::Algorithm Dialog::getProperType( const int iIndex )
{
    QCryptographicHash::Algorithm eType = QCryptographicHash::Md4;

    switch ( iIndex )
    {
        case 1:
        {
            eType = QCryptographicHash::Md5;

            break;
        }

        case 2:
        {
            eType = QCryptographicHash::Sha1;

            break;
        }

        default:
        {
            break;
        }
    }

    return eType;
}


void Dialog::clickedButton()
{
    QString strObjectName = sender()->objectName();

    if ( "encBase64PushButton" == strObjectName )
    {
        encBase64();
    }
    else if ( "decBase64PushButton" == strObjectName )
    {
        decBase64();
    }
    else if ( "encHexPushButton" == strObjectName )
    {
        encHex();
    }
    else if ( "decHexPushButton" == strObjectName )
    {
        decHex();
    }
    else if ( "calcInputHashPushButton" == strObjectName )
    {
        QCryptographicHash::Algorithm eType = QCryptographicHash::Md4;
        eType = getProperType( ui->comboBox->currentIndex() );
        calcHash( eType, false );
    }
    else if ( "calcFileHashPushButton" == strObjectName )
    {
        QCryptographicHash::Algorithm eType = QCryptographicHash::Md4;
        eType = getProperType( ui->comboBox->currentIndex() );
        calcHash( eType, true );
    }
    else if ( "clearLeftTextEditPushButton" == strObjectName )
    {
        m_byLeftData.clear();
        ui->rawTextEdit->clear();
        PromptDialog(  "已清空!" );
    }
    else if ( "saveLeftTextEditPushButton" == strObjectName )
    {
        if ( m_byLeftData.isEmpty() )
        {
            if ( !ui->rawTextEdit->toPlainText().isEmpty() )
            {
                m_byLeftData = ui->rawTextEdit->toPlainText().toLatin1();
            }
        }

        if ( !m_byLeftData.isEmpty() )
        {
            saveData( D_LEFT );
        }
        else
        {
            PromptDialog(  "无可存储的数据!" );
        }
    }
    else if ( "clearRightTextEditPushButton" == strObjectName )
    {
        m_byRightData.clear();
        ui->aimTextEdit->clear();
        PromptDialog(  "已清空!" );
    }
    else if ( "saveRightTextEditPushButton" == strObjectName )
    {
        if ( m_byRightData.isEmpty() )
        {
            if ( !ui->aimTextEdit->toPlainText().isEmpty() )
            {
                m_byRightData = ui->aimTextEdit->toPlainText().toLatin1();
            }
        }

        if ( !m_byRightData.isEmpty() )
        {
            saveData( D_RIGHT );
        }
        else
        {
            PromptDialog(  "无可存储的数据!" );
        }
    }

    return;
}
