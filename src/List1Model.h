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

#ifndef LIST1MODEL_H_
#define LIST1MODEL_H_

#include <xapian.h>

#include <QAbstractTableModel>

using namespace std;

struct tdoc {
    QString term;
    int dc, tc;
};

struct TermG {
    bool operator()(const tdoc & a, const tdoc & b) const {
        return a.term > b.term;
    }
};
struct TermL {
    bool operator()(const tdoc & a, const tdoc & b) const {
        return a.term < b.term;
    }
};
struct dcG {
    bool operator()(const tdoc & a, const tdoc & b) const {
        return a.dc > b.dc;
    }
};
struct dcL {
    bool operator()(const tdoc & a, const tdoc & b) const {
        return a.dc < b.dc;
    }
};
struct tcG {
    bool operator()(const tdoc & a, const tdoc & b) const {
        return a.tc > b.tc;
    }
};
struct tcL {
    bool operator()(const tdoc & a, const tdoc & b) const {
        return a.tc < b.tc;
    }
};

class List1Model : public QAbstractTableModel {
     Q_OBJECT

public:
	List1Model(QObject *parent=0);
	virtual ~List1Model();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder );
    Qt::ItemFlags flags ( const QModelIndex & index ) const;

public Q_SLOTS:
	void setTDoc(const QVariantList&);
    void clear();
    void refresh();

private:
	  QList<tdoc> terms;
};

#endif /* LIST1MODEL_H_ */
