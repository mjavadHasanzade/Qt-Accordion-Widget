#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>
#include <QPropertyAnimation>
#include <QLabel>
#include <QDebug>

class Accordion : public QWidget {
    Q_OBJECT

private:
    QGridLayout mainLayout;
    QToolButton toggleButton;
    QFrame headerLine;
    QParallelAnimationGroup toggleAnimation;
    QScrollArea contentArea;
    int animationDuration{300};

public:
    explicit Accordion(const QString & title = "", int animationDuration = 300, QWidget *parent = nullptr);

    void setContentLayout(QLayout *contentLayout);

private slots:
    void toggle(bool checked);

private:
    void adjustAnimation();
};
