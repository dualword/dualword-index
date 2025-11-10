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

Table::Table(int row, int col, QWidget *p) : QTableWidget(row,col,p){
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	setSortingEnabled(true);
	sortByColumn(0,Qt::SortOrder::AscendingOrder);
}

Table::~Table() {

}

void Table::clear(){
	clearContents();
	setRowCount(1);
}

void Table::filltable(const QList<QPair<QString, int>>& l){
	bool sort = isSortingEnabled();
	setSortingEnabled(false);
	int row=0;
	setRowCount(l.size());
	for(int i=0;i<l.size();i++,row++){
		QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(l.at(i).first));
		setItem(row, 0, item);
		item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, l.at(i).second);
		setItem(row, 1, item);
	}
	setSortingEnabled(sort);
}

void Table::filltable(const QList<QPair<QString, QPair<int, int> >>& l){
	bool sort = isSortingEnabled();
	setSortingEnabled(false);
	int row=0;
	setRowCount(l.size());
	for(int i=0;i<l.size();i++,row++){
		QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(l.at(i).first));
		setItem(row, 0, item);
		item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, l.at(i).second.first);
		setItem(row, 1, item);
		item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, l.at(i).second.second);
		setItem(row, 2, item);
	}
	setSortingEnabled(sort);
}
