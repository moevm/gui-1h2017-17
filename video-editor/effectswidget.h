#ifndef EFFECTSWIDGET_H
#define EFFECTSWIDGET_H

#include <QWidget>

namespace Ui {
class EffectsWidget;
}

class EffectsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EffectsWidget(QWidget *parent = 0);
    ~EffectsWidget();

private:
    Ui::EffectsWidget *ui;
};

#endif // EFFECTSWIDGET_H
