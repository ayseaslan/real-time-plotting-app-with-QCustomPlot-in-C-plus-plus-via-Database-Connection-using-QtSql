#ifndef DATABASEPLOT_H
#define DATABASEPLOT_H

#include <QMainWindow>
#include <iostream>
#include <QTimer>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

#include "qcustomplot.h" // change the path accordingly

QT_BEGIN_NAMESPACE
namespace Ui { class DatabasePlot; }
QT_END_NAMESPACE

class DatabasePlot : public QMainWindow
{
    Q_OBJECT

public:
    DatabasePlot(QWidget *parent = nullptr) : QMainWindow(parent)
    {
        // Set up the UI
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
      

        centralWidget->setFixedSize(600, 800); // size the application window 

        QVBoxLayout *layout = new QVBoxLayout(centralWidget);
        plotWidget = new QCustomPlot(centralWidget); // to plot scores

        plotWidget1 = new QCustomPlot(centralWidget); // to plot name initials 

        layout->addWidget(plotWidget);  layout->addWidget(plotWidget1);

        QPushButton *startButton = new QPushButton("Stop/Start", centralWidget);
        layout->addWidget(startButton);

        // Connect button click to start/stop data extraction
        connect(startButton, &QPushButton::clicked, this,  &DatabasePlot::toggleDataExtraction);

        // Set up the timer for data extraction
        dataTimer = new QTimer(this);
        connect(dataTimer, &QTimer::timeout, this, &DatabasePlot::updatePlot);

        // Initialize the database connection
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("data generation\\studentage_database.db"); // Replace with your database file path


        if (!db.open())
        {
            qDebug() << "Error opening the database";
        }
        else{
             qDebug() << "Database opened successfully!";

        }

      

        // Start the timer with a 2-second interval
        dataTimer->start(2000);
    }

private slots:
    void toggleDataExtraction()
    {
        if (dataTimer->isActive())
        {
            dataTimer->stop();
        }
        else
        {
            dataTimer->start(2000);
        }
    }

    void updatePlot()
    {
        // Extract data from the database and update the bar plot
        QVector<double> dataX;
       
        QVector<std::string> dataN;

        QSqlQuery query=db.exec("SELECT * FROM Students "); 

      
        if(!query.lastError().isValid())
        {
            while (query.next())
            {
                QString value = query.value(0).toString(); 
                dataX.push_back(query.value(1).toDouble()); 
                QString valuen = query.value(2).toString();
                dataN.push_back(valuen.toStdString());

                qDebug() << "Value from column_name: " << valuen;
            }
        }
        else
        {
            qDebug() << "Error executing query: " << query.lastError().text();

        }


        QCPBars* histogram = new QCPBars(plotWidget->xAxis, plotWidget->yAxis);
       
        QVector<double>freqs(10, 0.0); // 10 score labels
        QVector<double>w(10, 1); // key data
        for (int i = 0; i < 10; i++)
            w[i] = i + 1;

        for (int i = 0; i < dataX.size(); i++) { // value data, frequencies 
            freqs[dataX[i] - 1]+=1.0;
        }


        histogram->setData(w, freqs); // Assign equal weights for each data point

        plotWidget->xAxis->setLabel("Scores (1-10)");
        plotWidget->yAxis->setLabel("Current Frequencies");

        QCPBars* histogramN = new QCPBars(plotWidget1->xAxis, plotWidget1->yAxis);

        QVector<double>freqsN(26, 0.0); // 26 score labels
        QVector<double>wN(26, 1); // key data
        for (int i = 0; i < 26; i++)
            wN[i] = i + 1;

        for (int i = 0; i < dataN.size(); i++) { // value data, frequencies 
            char first = 'a';
            char letter = dataN[i].std::string::at(0); //.toLation();
            int order = letter - first; // get the letter order
            freqsN[order] += 1.0;
        }

        histogramN->setData(wN, freqsN); // Assign equal weights for each data point

        plotWidget1->xAxis->setLabel("Name --Initial Letters--(a-z)");
        plotWidget1->yAxis->setLabel("Current Frequencies");

        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

       // textTicker->addTick(1, "a");
       // textTicker->addTick(26, "z");
        QVector<QString>labels_alph = { "a", "b", "c" ,"d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
        textTicker->addTicks(wN, labels_alph);
        plotWidget1->xAxis->setTicker(textTicker);
   
        plotWidget->rescaleAxes();
        plotWidget->replot();
        plotWidget1->rescaleAxes();
        plotWidget1->replot();


    }

public:
    QCustomPlot *plotWidget;  QCustomPlot* plotWidget1;
    QTimer *dataTimer;
    QSqlDatabase db;


};
#endif // DATABASEPLOT_H
