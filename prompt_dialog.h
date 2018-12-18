/**
 * @brief  Created by civen163@163.com
 * @date   yyyy-MM-dd
 * @author Civen
 */
#ifndef PROMPT_DIALOG_H
#define PROMPT_DIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class PromptDialog;
}

class PromptDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PromptDialog( QWidget *parent = 0 );
    PromptDialog( const QString strPrompt );
    ~PromptDialog();

private:
    Ui::PromptDialog *ui;
    QTimer m_fadeTimer;
    int m_iCounter;

private:
    void showPrompt(const QString strPrompt );

private slots:
    void autoClose();
};

#endif // PROMPT_DIALOG_H
