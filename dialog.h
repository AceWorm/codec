/**
 * @brief  Created by civen163@163.com
 * @date   yyyy-MM-dd
 * @author Civen
 */
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCryptographicHash>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

    typedef enum direct{ D_LEFT, D_RIGHT }DIRECT;

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    void initButtons();
    void saveData( const DIRECT eType );
    bool getInputString( QString &strOutPutBuffer, const DIRECT eDirect );
    void setResult( const QByteArray &bydataBuffer, const DIRECT eDirect );
    QCryptographicHash::Algorithm getProperType( const int iIndex );

    void encBase64();
    void decBase64();
    void encHex();
    void decHex();
    void calcHash( const QCryptographicHash::Algorithm eType, const bool bIsFile = false );

private:
    Ui::Dialog *ui;
    QByteArray m_byLeftData, m_byRightData;
    QList <QPushButton *> m_listPushButtons;

private slots:
    void clickedButton();
};

#endif // DIALOG_H
