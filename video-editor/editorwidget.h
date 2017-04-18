#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>

namespace Ui {
class EditorWidget;
}

class EditorWidget : public QWidget
{
    Q_OBJECT


public slots:
    void changeSize();

public:
    explicit EditorWidget(QWidget *parent = 0);
    ~EditorWidget();



private:
    Ui::EditorWidget *ui;
};

#endif // EDITORWIDGET_H
