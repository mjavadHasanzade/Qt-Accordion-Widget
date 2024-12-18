#include "mainwindow.h"
#include "accordion.h"
#include "ui_mainwindow.h"

#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    for (int i = 0; i < 3; ++i) {
        Accordion *accordion = new Accordion(QString("Accordion %1").arg(i + 1), 300);

        QVBoxLayout *contentLayout = new QVBoxLayout();


        contentLayout->addWidget(new QLabel(QString("This is the content of Accordion %1.").arg(i + 1)));
        contentLayout->addWidget(new QLabel("You can add more widgets here."));

        accordion->setContentLayout(contentLayout);

        layout->addWidget(accordion);
    }

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
