# real-time-plotting-app-with-QCustomPlot-in-C-plus-plus-via-Database-Connection-using-QtSql
A desktop app in C++ using QCustomPlot that connects to a sqlite3 database, checks for new data and updates histogram plots.

See the source code of the plot application under the folder 'application'. Using QtSql, QSqlDatabase and QSqlQuery, the application connects to a database, checks for new data every 2 seconds, and updates the plots accordingly. The application plots two histograms from the data read from the database table named 'Students', plotting the histograms of their grades and initial letters of their names. 

To mock the generation of real time data coming from a database, a C++ application is implemented. See the source code under the folder 'data generation'. This creates a sqlite3 database with a table named 'Students' consisting of three columns (ID, score and name). A new data row is inserted into the table every 2 seconds. To generate this random data normal and uniform distributions are used for scores and initials, respectively.    


