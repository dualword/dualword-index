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

#ifndef INDEX_H_
#define INDEX_H_

#include <xapian.h>

#include <QList>
#include <QPair>
#include <QScopedPointer>

struct doc{
	int id;
	QString data;
	QList<QPair<QString, int>> v;
	QList<QPair<QString, int>> t;

};

class Index : public QObject{
  Q_OBJECT

public:
	Index(const QString&,QObject* parent = 0);
	virtual ~Index();
	QString which(){return dir;};
	const Xapian::doccount& dcount() const{return dc;}; //document count
	const Xapian::doccount& tcount() const{return tc;}; //term count
	const Xapian::doccount& cindex() const{return index;};

public Q_SLOTS:
	void close();
	void next();
	void back();
	void first();
	void last();
	void open();
	void setQuery(const QString&);

Q_SIGNALS:
	void setDoc(const doc&);

private:
	void getdoc();

private:
	Xapian::Database idx;
	QString dir;
	Xapian::doccount index,dc,tc;
	QScopedPointer<QString> q;

};

#endif /* INDEX_H_ */
