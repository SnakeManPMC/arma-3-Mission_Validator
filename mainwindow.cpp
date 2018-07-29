#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("Mission Validator " + pmcVersion + " (c) PMC");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	sqmDir = QFileDialog::getExistingDirectory();

	ui->lineEdit->setText(sqmDir);
}

void MainWindow::on_pushButton_Scan_clicked()
{
	QDirIterator it(sqmDir, QDirIterator::Subdirectories);

	bool pmcSqmFound = false;

	while (it.hasNext())
	{
		if (it.fileName().contains("mission.sqm"))
		{
			//ui->textEdit->append("Path: " + it.fileInfo().absolutePath() + "\nSQM: " + it.filePath());
			ui->textEdit->append(it.fileInfo().path());
			pmcSqmFound = true;
			scanSqm(it.filePath());
			scanDescriptionExt(it.fileInfo().absolutePath());
		}

		//if (it.fileName().contains("description.ext")) ui->textEdit->append("Hey we have description.ext too!");

		it.next();
	}

	if (!pmcSqmFound)
		ui->textEdit->append("No mission.sqm files found, sorry.");
	else
		ui->textEdit->append("All done, thank you.");
}

void MainWindow::scanSqm(QString sqm)
{
	QFile File(sqm);
	File.open(QIODevice::ReadOnly);
	QTextStream stream(&File);
	QString contents = stream.readAll();
	File.close();

	if (!contents.contains("briefingName"))
	{
		ui->textEdit->append("briefingname missing!");
	}

	// isPlayer=1; and isPlayable=1;
	ui->textEdit->append("isPlayable: " + QString::number(contents.count("isPlayable=1;")));
}

void MainWindow::scanDescriptionExt(QString dext)
{
	dext.append("/description.ext");
	QFile File(dext);
	//ui->textEdit->append("scanDescriptionExt() path:\n" + dext);

	if (!File.open(QIODevice::ReadOnly))
	{
		//QMessageBox::information(this, tr("Unable to open description.ext file"), File.errorString());
		ui->textEdit->append("No description.ext file found.");
		return;
	}
	else
	{
		QTextStream in(&File);
		QString line = in.readAll();
		checkDescriptionExtLine(line);

		File.close();
	}
}

void MainWindow::checkDescriptionExtLine(QString line)
{
	line = line.toLower();
	if (!line.contains("disabledai")) ui->textEdit->append("Missing description.ext/disabledAI");
	if (!line.contains("overviewtext")) ui->textEdit->append("Missing description.ext/overviewText");
	if (!line.contains("overviewpicture")) ui->textEdit->append("Missing description.ext/overviewPicture");
	if ((!line.contains("respawn=") && !line.contains("respawn ="))) ui->textEdit->append("Missing description.ext/respawn type");
	if (!line.contains("respawndelay")) ui->textEdit->append("Missing description.ext/respawndelay");
	if (!line.contains("gametype")) ui->textEdit->append("Missing description.ext/gameType");
	if (!line.contains("minplayers")) ui->textEdit->append("Missing description.ext/minPlayers");
	if (!line.contains("maxplayers")) ui->textEdit->append("Missing description.ext/maxPlayers");
	if (!line.contains("onloadname")) ui->textEdit->append("Missing description.ext/onLoadName");
	if (!line.contains("onloadmission")) ui->textEdit->append("Missing description.ext/onLoadMission");
	if (!line.contains("onloadintro")) ui->textEdit->append("Missing description.ext/onLoadIntro");
	if (!line.contains("author")) ui->textEdit->append("Missing description.ext/author");
	if (!line.contains("class cfgdebriefing")) ui->textEdit->append("Missing description.ext/class cfgdebriefing");
}
