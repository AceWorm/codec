/**
 * @brief  Created by civen163@163.com
 * @date   yyyy-MM-dd
 * @author Civen
 */
#include "prompt_dialog.h"
#include "ui_prompt_dialog.h"
#include <QTime>

//static void delay( const int iSecs )
//{
//    QTime dieTime= QTime::currentTime().addSecs( iSecs );

//    while( dieTime > QTime::currentTime() )
//    {
//        QCoreApplication::processEvents( QEventLoop::AllEvents, 10 );
//    }

//    return;
//}


PromptDialog::PromptDialog( QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::PromptDialog )
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool );
    setAttribute( Qt::WA_TranslucentBackground );
//    setFixedSize( size() );
    connect( &m_fadeTimer, SIGNAL(timeout()), this, SLOT(autoClose()) );
    hide();
}


PromptDialog::PromptDialog( const QString strPrompt ) :  ui( new Ui::PromptDialog )
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool );
    setAttribute( Qt::WA_TranslucentBackground );
    setFixedSize( size() );
    connect( &m_fadeTimer, SIGNAL(timeout()), this, SLOT(autoClose()) );
    showPrompt( strPrompt );
}


PromptDialog::~PromptDialog()
{
    disconnect();
    delete ui;
}

#include <QDebug>
void PromptDialog::showPrompt( const QString strPrompt )
{
    int iStrLen = strPrompt.length();

    ui->promptLabel->resize( iStrLen * (ui->promptLabel->fontInfo().pixelSize() + 4), height() );
    setFixedSize( iStrLen * (ui->promptLabel->fontInfo().pixelSize() + 4), height() );

    QPoint pt = cursor().pos() - QPoint( width() / 2, height() );

    move( pt );
    m_iCounter = 0;
    m_fadeTimer.start( 100 );
    ui->promptLabel->setText( strPrompt );
    exec();

    return;
}


void PromptDialog::autoClose()
{
    if ( 5 > m_iCounter )
    {
        m_iCounter++;

        return;
    }

    close();

    return;
}
