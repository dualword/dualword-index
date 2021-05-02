/*
 * Copyright (C) 2013 Alexander Busorgin
 *
 *	This file is part of DualWord-index. Website: http://github.com/dualword/dualword-index/
 *
 *	DualWord-index is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	DualWord-index is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with DualWord-index.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui>
#include <QScopedPointer>
#include <QApplication>

class TermLoader;
class List1Model;
class Table;
class Index;
struct doc;

class MainWindow : public QMainWindow
{
  Q_OBJECT

protected:
  void keyPressEvent(QKeyEvent *event);

public:
	MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

public Q_SLOTS:
	void setDoc(const doc&);
	void load();
	void stop();
	void setTCount(const unsigned&);

private Q_SLOTS:
	void open();
	void openIndex();
	void reload();
	void close();
	void clear();
	void showAbout();
	void doSearch();
	void doClear();
	void next();
	void back();
	void first();
	void last();
	void cancel();

private:
	QScopedPointer<Index> idx;
	QString dir;
	Table *list2, *list3;
	QTableView *list1;
	QAction *bOpen,*bClose, *bReload, *bAbout;
	QPushButton *bBack,*bNext,*bFirst,*bLast,*bSearch,*bClear;
	QLabel *lDocid;
	QTextEdit *area;
	QLineEdit *search;
	QToolButton *bLoad,*bStop;
	QProgressBar *bar;
	QScopedPointer<TermLoader> th;
	QScopedPointer<QThread> thread1;
	List1Model *m;
	QCheckBox *check;

};

#endif /* MAINWINDOW_H_ */
