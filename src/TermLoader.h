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


#ifndef TERMLOADER_H_
#define TERMLOADER_H_

#include <xapian.h>

#include <QVariantList>
#include <QVariant>

class TermLoader : public QObject {
    Q_OBJECT

public:
	TermLoader(const QString&, QObject * parent = 0);
	virtual ~TermLoader();

Q_SIGNALS:
	void setTDoc(const QVariantList&);
	void setTCount(const unsigned&);
	void Done();

public Q_SLOTS:
	void run();
	void cancel(){canceled = true;};

private:
    QString dir;
	Xapian::Database idx;
	Xapian::doccount tc;
	bool canceled;

};

#endif /* TERMLOADER_H_ */
