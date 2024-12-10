#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>   // For buttons
#include <QLabel>        // For labels
#include <QLineEdit>     // For text input
#include <QSpinBox>      // For numerical input (e.g., calorie goal)
#include <QComboBox>     // For dropdown menus
#include <QVBoxLayout>   // Layout manager to arrange widgets
#include <ctime>
#include "LogManager.h"
#include "Tutorials.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_setGoalsButton_clicked();
    void on_logFoodButton_clicked();
    void on_logExerciseButton_clicked();
    void on_viewProfileButton_clicked();
    void on_exitButton_clicked();
    void on_viewFoodExerciseButton_clicked();
    void on_editProfileButton_clicked();
    void on_viewTutorialsButton_clicked();
    void on_closeTutorialButton_clicked();
    void on_exerciseSelected(int index);

private:
    Ui::MainWindow *ui;
    LogManager *logManager;
    Tutorials *tutorials;

};
#endif // MAINWINDOW_H
