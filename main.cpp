/**
 * @brief  Created by civen163@163.com
 * @date   yyyy-MM-dd
 * @author Civen
 */
#include "dialog.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName( "UTF-8" );
    QTextCodec::setCodecForTr( codec );
    QTextCodec::setCodecForLocale( codec );
    QTextCodec::setCodecForCStrings( codec );
    Dialog w;
    w.show();

    return a.exec();
}
