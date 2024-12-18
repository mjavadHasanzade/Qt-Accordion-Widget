#include "accordion.h"

Accordion::Accordion(const QString &title, int animationDuration, QWidget *parent)
    : QWidget(parent), animationDuration(animationDuration) {


    toggleButton.setStyleSheet("QToolButton { border: none; margin: 0; padding: 0; }");
    toggleButton.setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toggleButton.setArrowType(Qt::ArrowType::RightArrow);
    toggleButton.setText(title);
    toggleButton.setCheckable(true);
    toggleButton.setChecked(false);
    toggleButton.setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
    toggleButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    headerLine.setFrameShape(QFrame::HLine);
    headerLine.setFrameShadow(QFrame::Sunken);
    headerLine.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    contentArea.setStyleSheet("QScrollArea { background-color: white; border: none; }");
    contentArea.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    contentArea.setMaximumHeight(0);
    contentArea.setMinimumHeight(0);
    contentArea.setFrameShape(QFrame::NoFrame);

    // animation
    for (int i = 0; i < 3; ++i) {
        toggleAnimation.addAnimation(new QPropertyAnimation(this, "minimumHeight"));
    }
    toggleAnimation.addAnimation(new QPropertyAnimation(&contentArea, "maximumHeight"));

    mainLayout.addWidget(&toggleButton, 0, 0, 1, 1, Qt::AlignLeft);
    mainLayout.addWidget(&headerLine, 0, 1, 1, 1);
    mainLayout.addWidget(&contentArea, 1, 0, 1, 2);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setLayout(&mainLayout);

    connect(&toggleButton, &QToolButton::clicked, this, &Accordion::toggle);
}

void Accordion::setContentLayout(QLayout *contentLayout) {
    delete contentArea.layout();
    contentArea.setLayout(contentLayout);
    adjustAnimation();
}

void Accordion::toggle(bool checked) {
    toggleButton.setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
    toggleAnimation.setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
    toggleAnimation.start();
}

void Accordion::adjustAnimation() {
    const auto collapsedHeight = sizeHint().height() - contentArea.maximumHeight();
    auto contentHeight = contentArea.layout()->sizeHint().height();

    for (int i = 0; i < toggleAnimation.animationCount() - 1; ++i) {
        QPropertyAnimation *animation = static_cast<QPropertyAnimation *>(toggleAnimation.animationAt(i));
        animation->setDuration(animationDuration);
        animation->setStartValue(collapsedHeight);
        animation->setEndValue(collapsedHeight + contentHeight);
    }

    QPropertyAnimation *contentAnimation = static_cast<QPropertyAnimation *>(toggleAnimation.animationAt(toggleAnimation.animationCount() - 1));
    contentAnimation->setDuration(animationDuration);
    contentAnimation->setStartValue(0);
    contentAnimation->setEndValue(contentHeight);
}
