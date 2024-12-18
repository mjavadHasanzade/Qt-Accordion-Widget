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

    // Create a central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create multiple Accordion widgets
    for (int i = 0; i < 3; ++i) {
        // Create a Accordion with a unique title
        Accordion *accordion = new Accordion(QString("Accordion %1").arg(i + 1), 300);

        // Create content for the Accordion
        QVBoxLayout *contentLayout = new QVBoxLayout();


        contentLayout->addWidget(new QLabel(QString("This is the content of Accordion %1.").arg(i + 1)));
        contentLayout->addWidget(new QLabel("You can add more widgets here."));

        // Set the content layout in the Accordion
        accordion->setContentLayout(contentLayout);

        // Add the Accordion to the main layout
        layout->addWidget(accordion);
    }

    // Set the central widget's layout
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
