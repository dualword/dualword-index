/*
 * Copyright (C) 2013-2025 Alexander Busorgin
 *
 *	This file is part of DualWord-index. Website: https://github.com/dualword/dualword-index/
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


#include "Table.h"
#include "Index.h"
#include "TermLoader.h"
#include "List1Model.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget* p) : QMainWindow(p){
	setWindowTitle(qApp->applicationName());
    statusBar();
    statusBar()->setSizeGripEnabled(false);

    //toolbar
    QToolBar *toolbar;
    toolbar = addToolBar( tr("File") );
    toolbar->setMovable(false);
    bOpen = new QAction(tr("O"), this);
    bOpen->setToolTip("Open");
    bOpen->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon, 0, this));
    bReload = new QAction(tr("R"), this);
    bReload->setToolTip("Reload");
    bReload->setIcon(style()->standardIcon(QStyle::SP_DirLinkIcon, 0, this));
    bReload->setEnabled(false);
    bClose = new QAction(tr("C"), this);
    bClose->setToolTip("Close");
    bClose->setIcon(style()->standardIcon(QStyle::SP_DirClosedIcon, 0, this));
    bClose->setEnabled(false);
    bAbout = new QAction(tr("A"), this);
    bAbout->setToolTip("About");
    bAbout->setIcon(style()->standardIcon(QStyle::SP_FileDialogInfoView, 0, this));

    toolbar->addAction(bOpen);
    toolbar->addAction(bReload);
    toolbar->addAction(bClose);
    toolbar->addAction(bAbout);

    //search
    QHBoxLayout *spnl = new QHBoxLayout();
	search = new QLineEdit();
	bSearch = new QPushButton("&Search");
	bClear = new QPushButton("&Clear");
	QObject::connect(search, SIGNAL(returnPressed()), SLOT(doSearch()));
	spnl->addWidget(search);
	spnl->addWidget(bSearch);
	spnl->addWidget(bClear);

	//buttons
	lDocid=new QLabel();
	QHBoxLayout *pnl = new QHBoxLayout();
	bFirst = new QPushButton("&First");
	bBack = new QPushButton("&Back");
	bNext = new QPushButton("&Next");
	bLast = new QPushButton("&Last");
	pnl->addWidget(bFirst);
	pnl->addWidget(bBack);
	pnl->addWidget(bNext);
	pnl->addWidget(bLast);

	QWidget* w = new QWidget();
    QGridLayout* grid = new QGridLayout();
    w->setLayout(grid);

    //terms
	QHBoxLayout *tpnl = new QHBoxLayout();
	bLoad = new QToolButton();
	bLoad->setToolTip("Load Terms");
	bLoad->setIcon(style()->standardIcon(QStyle::SP_MediaPlay, 0, this));
	QObject::connect(bLoad,SIGNAL(clicked()), this, SLOT(load()));
	bStop = new QToolButton();
	bStop->setToolTip("Stop");
	bStop->setEnabled(false);
	bStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop, 0, this));
	QObject::connect(bStop,SIGNAL(clicked()), this, SLOT(cancel()));
	bar = new QProgressBar();
	bar->setTextVisible(false);
	check = new QCheckBox();
	check->setToolTip("Load every time");
	check->setEnabled(false);
	check->setChecked(true);
	tpnl->addWidget(bar);
	tpnl->addWidget(bLoad);
	tpnl->addWidget(bStop);
	tpnl->addWidget(check);
	bLoad->setEnabled(false);
	bStop->setEnabled(false);

	QVBoxLayout *vbox = new QVBoxLayout();
	QStringList list;

    //list1
	list1 = new QTableView(this);
	list1->setSelectionBehavior(QAbstractItemView::SelectRows);
	list1->verticalHeader()->hide();
	list1->setEditTriggers(QAbstractItemView::NoEditTriggers);
	list1->setSelectionMode(QAbstractItemView::SingleSelection);
	list1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	list1->setSortingEnabled(true);
	m =new List1Model(this);
	list1->setModel(m);

	vbox->addLayout(tpnl);
	vbox->addWidget(list1);

	//document
	list2 = new Table(1,2,this);
	list.push_back("Term");
	list.push_back("Wdf");
	list2->setHorizontalHeaderLabels(list);
	list.clear();

	list3 = new Table(1,2,this);
	list3->setSortingEnabled(false);
	list.push_back("Value");
	list.push_back("Slot");
	list3->setHorizontalHeaderLabels(list);

	area = new QTextEdit(this);
	area->setFixedHeight(150);
	area->setReadOnly(true);

	grid->addLayout(vbox,0,0,4,1);
	grid->addLayout(spnl,0,1,1,2);
	grid->addLayout(pnl,1,1,1,1);
	grid->addWidget(lDocid,1,2,1,1);
	grid->addWidget(area,2,1,1,2);
	grid->addWidget(list2,3,1);
	grid->addWidget(list3,3,2);

	grid->setColumnStretch(0,30);
	grid->setColumnStretch(1,35);
	grid->setColumnStretch(2,35);

	QObject::connect(bOpen,SIGNAL(triggered()), this, SLOT(open()));
	QObject::connect(bReload,SIGNAL(triggered()), this, SLOT(reload()));
	QObject::connect(bClose,SIGNAL(triggered()), this, SLOT(close()));
	QObject::connect(bAbout,SIGNAL(triggered()), this, SLOT(showAbout()));

	setCentralWidget(w);
	showMaximized();
	clear();
	bSearch->setEnabled(false);
	bClear->setEnabled(false);
	bFirst->setEnabled(false);
	bBack->setEnabled(false);
	bNext->setEnabled(false);
	bLast->setEnabled(false);
	search->setEnabled(false);

	QObject::connect(bFirst,SIGNAL(clicked()), this, SLOT(first()));
	QObject::connect(bBack,SIGNAL(clicked()), this, SLOT(back()));
	QObject::connect(bNext,SIGNAL(clicked()), this, SLOT(next()));
	QObject::connect(bLast,SIGNAL(clicked()), this, SLOT(last()));
	QObject::connect(bSearch,SIGNAL(clicked()), this, SLOT(doSearch()));
	QObject::connect(bClear,SIGNAL(clicked()), this, SLOT(doClear()));

}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent *event){
	if(thread1 && thread1->isRunning()){
		th->cancel();
		thread1->exit();
	}
	if(idx) idx->close();
    event->accept();
}

void MainWindow::showAbout(){
	QString str;
	str.append(qApp->applicationName());
	str.append(" ").append(qApp->applicationVersion()).append("<br>");
    str.append("License: GPL v3+ <br/>");
    str.append("Website: <a href='https://github.com/dualword/dualword-index/'>dualword-index</a> <br/>");
    str.append("&copy; 2013-2025 Alexander Busorgin <br/>");
	QMessageBox::about(this, tr("About"), str );
}

void MainWindow::open(){
	QFileDialog d(this,tr("Choose directory"), QDir::homePath());
	d.setFilter(QDir::Dirs | QDir::Hidden);
    d.setFileMode(QFileDialog::Directory);
	d.setViewMode(QFileDialog::List);
	d.setOption(QFileDialog::ShowDirsOnly,true);
	d.setOption(QFileDialog::ReadOnly,true);

    if (d.exec() == QDialog::Accepted) {
        dir = QString(d.selectedFiles().value(0));
        reload();
    }
}

void MainWindow::openIndex(){
	try {
		idx.reset(new Index(dir));
		idx->open();
		statusBar()->showMessage(QString("Loading ").append(QString::number(idx->dcount()))
				.append(" documents..."));
		QObject::connect(idx.get(),SIGNAL(setDoc(const doc&)), this, SLOT(setDoc(const doc&)));
		first();
		bReload->setEnabled(true);
		bClose->setEnabled(true);
		bOpen->setEnabled(false);
		bSearch->setEnabled(true);
		bClear->setEnabled(false);
		bFirst->setEnabled(true);
		bBack->setEnabled(true);
		bNext->setEnabled(true);
		bLast->setEnabled(true);
		search->setEnabled(true);
		bReload->setToolTip(QString("Reload ").append(dir));
		bStop->setEnabled(false);
		bLoad->setEnabled(true);
		check->setEnabled(true);
		QString msg;
		msg.append("Documents:").append(QString::number(idx->dcount()));
		statusBar()->showMessage(msg.append(" Index:").append(idx->which()));
		if(check->isChecked()) load();
	}catch (Xapian::Error& e) {
		QMessageBox::critical(this,"Error",e.get_msg().c_str() );
		close();
	}
}

void MainWindow::reload(){
	if(idx) close();
	bOpen->setEnabled(false);
	openIndex();
}

void MainWindow::close(){
	statusBar()->showMessage("");
	QObject::disconnect(idx.data(),SIGNAL(setDoc(const doc&)), this, SLOT(setDoc(const doc&)));
	idx->close();
	clear();
	m->clear();

	bReload->setEnabled(true);
	bClose->setEnabled(false);
	bOpen->setEnabled(true);
	bSearch->setEnabled(false);
	bClear->setEnabled(false);
	bFirst->setEnabled(false);
	bBack->setEnabled(false);
	bNext->setEnabled(false);
	bLast->setEnabled(false);
	search->setEnabled(false);
	bStop->setEnabled(false);
	bLoad->setEnabled(false);
	check->setEnabled(false);

}

void MainWindow::clear(){
	lDocid->clear();
	area->clear();
	list2->clear();
	list3->clear();
}

void MainWindow::doSearch(){
	try{
		clear();
		bClear->setEnabled( search->text().trimmed().length() > 0 );
		idx->setQuery(search->text().trimmed());
		first();
	}catch (Xapian::Error& e) {
		QMessageBox::critical(this,"Error",e.get_msg().c_str() );
	}
}

void MainWindow::doClear(){
	search->clear();
	bClear->setEnabled(false);
	bSearch->click();

}

void MainWindow::setDoc(const doc& d){
	clear();

	QString tmp(QString::number(idx->cindex()+1));
	tmp.append("/");
	tmp.append(QString::number(idx->dcount()));
	tmp.append(QString(" Id:")).append(QString::number(d.id));

	lDocid->setText(tmp);
	area->setText(d.data);
	list2->filltable(d.t);
	list3->filltable(d.v);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case (Qt::Key_F):  if(idx) idx->first(); break;
		case (Qt::Key_N): if(idx) idx->next(); break;
		case (Qt::Key_B): if(idx) idx->back(); break;
		case (Qt::Key_L): if(idx) idx->last(); break;
		case (Qt::Key_S): if(idx) doSearch(); break;
		case (Qt::Key_C): if(idx) doClear(); break;
		default: QWidget::keyPressEvent(event); break;
	}
}

void MainWindow::next(){
	try{
		idx->next();
	}catch (Xapian::Error& e) {
		QMessageBox::critical(this,"Error",e.get_msg().c_str() );
	}
}

void MainWindow::back(){
	try{
		idx->back();
	}catch (Xapian::Error& e) {
		QMessageBox::critical(this,"Error",e.get_msg().c_str() );
	}
}

void MainWindow::first(){
	try{
		idx->first();
	}catch (Xapian::Error& e) {
		QMessageBox::critical(this,"Error",e.get_msg().c_str() );
	}
}

void MainWindow::last(){
	try{
		idx->last();
	}catch (Xapian::Error& e) {
		QMessageBox::critical(this,"Error",e.get_msg().c_str() );
	}
}

void MainWindow::load(){
	QString msg;
	msg.append("Documents:").append(QString::number(idx->dcount()));
	statusBar()->showMessage(msg.append(" Index:").append(idx->which()));
	m->clear();
	thread1.reset(new QThread());
	th.reset(new TermLoader(dir));
	th.data()->moveToThread(thread1.data());
	QObject::connect(th.data(),SIGNAL(setTDoc(const QVariantList&)), list1->model(), SLOT(setTDoc(const QVariantList&)));
	QObject::connect(th.data(),SIGNAL(setTCount(const unsigned&)), this, SLOT(setTCount(const unsigned&)));
	QObject::connect(thread1.data(), SIGNAL(started()), th.data(), SLOT(run()));
	QObject::connect(th.data(), SIGNAL(Done()), thread1.data(), SLOT(quit()));
	QObject::connect(th.data(), SIGNAL(Done()), this, SLOT(stop()));
	QObject::connect(th.data(), SIGNAL(Done()), m, SLOT(refresh()));
	thread1->start();
	bar->setMinimum(0);
	bar->setMaximum(0);
	bStop->setEnabled(true);
	bLoad->setEnabled(false);
	check->setEnabled(false);
	bReload->setEnabled(false);
	bClose->setEnabled(false);

}

void MainWindow::cancel(){
	th->cancel();
	bStop->setEnabled(false);
}

void MainWindow::stop(){
	bar->reset();
	bar->setMaximum(1);
	bStop->setEnabled(false);
	bLoad->setEnabled(true);
	check->setEnabled(true);
	bReload->setEnabled(true);
	bClose->setEnabled(true);

	if(thread1 && thread1->isRunning()){
		QObject::disconnect(th.data(),SIGNAL(setTDoc(const QVariantList&)), list1->model(), SLOT(setTDoc(const QVariantList&)));
		QObject::disconnect(th.data(),SIGNAL(setTCount(const unsigned&)), this, SLOT(setTCount(const unsigned&)));
		QObject::disconnect(thread1.data(), SIGNAL(started()), th.data(), SLOT(run()));
		QObject::disconnect(th.data(), SIGNAL(Done()), thread1.data(), SLOT(quit()));
		QObject::disconnect(th.data(), SIGNAL(Done()), this, SLOT(stop()));
		thread1->exit();
	}

}

void MainWindow::setTCount(const unsigned& u){
	QString msg("");
	msg.append("Documents:").append(QString::number(idx->dcount()));
	msg.append(" Unique terms:");
	msg.append(QString::number(u));
	msg.append(" Index:").append(idx->which());
	statusBar()->showMessage(msg);
}
