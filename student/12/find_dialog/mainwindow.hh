#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

const QString FILE_NOT_FOUND = "File not found";
const QString FILE_FOUND = "File found";
const QString WORD_NOT_FOUND = "Word not found";
const QString WORD_FOUND = "Word found";

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;

    QString file_name_ = "";
    QString word_ = "";

    bool find_string(std::string& text,
                     std::string& word,
                     bool& match);
    void change_to_upper(std::string& content);
};
#endif // MAINWINDOW_HH
