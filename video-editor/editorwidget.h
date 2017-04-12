#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>

namespace Ui {
class EditorWidget;
}

class EditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditorWidget(QWidget *parent = 0);
    ~EditorWidget();

    //void changeSize();

private:
    Ui::EditorWidget *ui;
};

#endif // EDITORWIDGET_H
