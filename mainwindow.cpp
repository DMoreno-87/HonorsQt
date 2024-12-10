#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LogManager.h"
#include "Tutorials.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString backgroundImagePath = "C:/Users/LtWea/OneDrive/HonorsApp/icons/Background.jpg";
    this->setStyleSheet("background-image: url(" + backgroundImagePath + ");");

    ui->EditProfile->setIcon(QIcon("C:/Users/LtWea/OneDrive/HonorsApp/icons/Pencil.png"));
    ui->EditProfile->setIconSize(QSize(100, 100));
    ui->Exit->setIcon(QIcon("C:/Users/LtWea/OneDrive/HonorsApp/icons/9-97279_door-vector-png-transparent-background-door-icon.png"));
    ui->Exit->setIconSize(QSize(100, 100));
    ui->LogExercise->setIcon(QIcon("C:/Users/LtWea/OneDrive/HonorsApp/icons/body-building-muscle-icon-vector-47093237.jpg"));
    ui->LogExercise->setIconSize(QSize(100, 100));
    ui->LogFood->setIcon(QIcon("C:/Users/LtWea/OneDrive/HonorsApp/icons/fork-and-knife-in-circle-icon-vector-14409094.jpg"));
    ui->LogFood->setIconSize(QSize(100, 100));
    ui->SetCaloricMacroGoals->setIcon(QIcon("C:/Users/LtWea/OneDrive/HonorsApp/icons/pie-chart-icon.jpg"));
    ui->SetCaloricMacroGoals->setIconSize(QSize(100, 100));
    ui->ViewFoodExerciseDay->setIcon(QIcon("C:/Users/LtWea/OneDrive/HonorsApp/icons/Calendar.JPG"));
    ui->ViewFoodExerciseDay->setIconSize(QSize(100, 100));
    ui->ViewProfile->setIcon(QIcon("C:/Users/LtWea/OneDrive/HonorsApp/icons/default-profile-picture-avatar.jpg"));
    ui->ViewProfile->setIconSize(QSize(100, 100));
    ui->viewTutorials->setIcon(QIcon("C:/Users/LtWea/OneDrive/HonorsApp/icons/vector-dumbbell-icon2.jpg"));
    ui->viewTutorials->setIconSize(QSize(100, 100));

    ui->gifLabel->setVisible(false);
    ui->descriptionLabel->setVisible(false);
    ui->closeButton->setVisible(false);
    ui->comboBox->setVisible(false);

    logManager = new LogManager(ui->textEdit);
    tutorials = new Tutorials();

    connect(ui->viewTutorials, SIGNAL(clicked()), this, SLOT(on_viewTutorialsButton_clicked()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_exerciseSelected(int)));

    connect(ui->SetCaloricMacroGoals, &QPushButton::clicked, this, &MainWindow::on_setGoalsButton_clicked);
    connect(ui->LogFood, &QPushButton::clicked, this, &MainWindow::on_logFoodButton_clicked);
    connect(ui->LogExercise, &QPushButton::clicked, this, &MainWindow::on_logExerciseButton_clicked);
    connect(ui->ViewProfile, &QPushButton::clicked, this, &MainWindow::on_viewProfileButton_clicked);
    connect(ui->Exit, &QPushButton::clicked, this, &MainWindow::on_exitButton_clicked);
    connect(ui->ViewFoodExerciseDay, &QPushButton::clicked, this, &MainWindow::on_viewFoodExerciseButton_clicked);
    connect(ui->EditProfile, &QPushButton::clicked, this, &MainWindow::on_editProfileButton_clicked);
    connect(ui->viewTutorials, &QPushButton::clicked, this, &MainWindow::on_viewTutorialsButton_clicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::on_closeTutorialButton_clicked);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_exerciseSelected(int)));
}
MainWindow::~MainWindow()
{
    delete ui;
    delete logManager;
    delete tutorials;
}

void MainWindow::on_setGoalsButton_clicked() {
    // Logic from case 1 (Set Caloric and Macronutrient Goals)
    logManager->setCaloricGoals();  // Call LogManager method that corresponds to this option
}

void MainWindow::on_logFoodButton_clicked() {
    // Logic from case 2 (Log Food Intake for a Specific Day)
    logManager->logFoodIntake();  // Call LogManager method for food intake logging
}

void MainWindow::on_logExerciseButton_clicked() {
    // Logic from case 3 (Log Exercise for a Specific Day)
    logManager->logExercise();  // Call LogManager method for exercise logging
}

void MainWindow::on_viewFoodExerciseButton_clicked() {
    // Logic from case 4 (View Food and Exercise for a Specific Day)
    logManager->displaySummary();  // Call LogManager method for viewing summary
}

void MainWindow::on_viewProfileButton_clicked() {
    // Logic from case 5 (View User Profile)
    logManager->displayProfile();  // Call LogManager method for viewing user profile
}

void MainWindow::on_editProfileButton_clicked() {
    // Logic from case 6 (Edit User Profile)
    logManager->editProfile();  // Call LogManager method for editing profile
}

void MainWindow::on_exitButton_clicked() {
    // Logic from case 7 (Exit)
    logManager->exitApp();  // Call LogManager method for exiting
}

void MainWindow::on_viewTutorialsButton_clicked()
{
    // Clear previous data in the ComboBox, if any
    ui->comboBox->clear();

    // Get the list of exercise names from the tutorials object
    QStringList exercises = tutorials->getExerciseNames();  // This returns a QStringList

    // Add items to the ComboBox
    ui->comboBox->addItems(exercises);

    // Make the ComboBox visible
    ui->comboBox->setVisible(true);
    ui->closeButton->setVisible(true);
}

void MainWindow::on_exerciseSelected(int index)
{
    if (index >= 0 && index < tutorials->getExerciseNames().size()) {
        // Get the GIF and description for the selected exercise
        QMovie* gif = tutorials->getExerciseGif(index);  // Assuming getExerciseGif returns a QMovie pointer
        QString description = tutorials->getExerciseDescription(index);  // Get the description

        // Set the GIF in the gifLabel (QLabel)
        ui->gifLabel->setMovie(gif);
        gif->start();  // Start the animation of the GIF
        ui->gifLabel->setVisible(true);
        ui->descriptionLabel->setVisible(true);

        // Set the exercise description in the descriptionLabel
        ui->descriptionLabel->setText(description);  // Set the description text
    }
    else {
        // Handle error (e.g., index is out of bounds)
        qWarning() << "Invalid exercise index: " << index;
    }
}

void MainWindow::on_closeTutorialButton_clicked()
{
    // Hide the gifLabel and descriptionLabel when the Close button is pressed
    ui->gifLabel->setVisible(false);
    ui->descriptionLabel->setVisible(false);
    ui->closeButton->setVisible(false);
    ui->comboBox->setVisible(false);

}
