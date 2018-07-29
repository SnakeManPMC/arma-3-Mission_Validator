#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_pushButton_clicked();

	void on_pushButton_Scan_clicked();

private:
	Ui::MainWindow *ui;
	QString sqmDir;
	void scanSqm(QString sqm);
	void scanDescriptionExt(QString dext);
	void checkDescriptionExtLine(QString line);
	QString pmcVersion = "v0.0.1";
};

#endif // MAINWINDOW_H
