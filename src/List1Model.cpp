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

#include "List1Model.h"

List1Model::List1Model( QObject *parent) :  QAbstractTableModel(parent) {

}

List1Model::~List1Model() {

}

int List1Model::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 3;
}

int List1Model::rowCount ( const QModelIndex &parent ) const {
    Q_UNUSED(parent);
	return terms.size();
}

QVariant List1Model::data(const QModelIndex &index, int role) const {
	if(!index.isValid() || role!=Qt::DisplayRole) return QVariant();

	if(index.column() == 0){
		return terms.at(index.row()).term;
	}else if(index.column() == 1){
		return terms.at(index.row()).dc;
	}else if(index.column() == 2){
		return terms.at(index.row()).tc;
	}

    return QVariant();
}

QVariant List1Model::headerData(int section, Qt::Orientation orientation, int role) const {

	if (role==Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
			case 0:
				return tr("Term");
			case 1:
				return tr("Document");
			case 2:
				return tr("Total");
			default:
				return QVariant();
		}
	}

	return QVariant();
}

void List1Model::sort ( int column, Qt::SortOrder order ) {
	Q_EMIT layoutAboutToBeChanged();

	if(order != Qt::SortOrder::AscendingOrder){
		switch (column){
            case 0: std::sort(terms.begin(), terms.end(), TermL() ); break;
            case 1: std::sort(terms.begin(), terms.end(), dcL() ); break;
            case 2: std::sort(terms.begin(), terms.end(), tcL() ); break;
		}
	}else{
		switch (column){
            case 0: std::sort(terms.begin(), terms.end(), TermG() ); break;
            case 1: std::sort(terms.begin(), terms.end(), dcG() ); break;
            case 2: std::sort(terms.begin(), terms.end(), tcG() ); break;
		}
	}

	Q_EMIT layoutChanged();
}

Qt::ItemFlags List1Model::flags ( const QModelIndex & index ) const {
	Qt::ItemFlags flags = QAbstractItemModel::flags(index);
	if (index.column() == 1 || index.column() == 2)
		flags |= Qt::ItemIsUserCheckable;
	return flags;
}

void List1Model::clear(){
	Q_EMIT layoutAboutToBeChanged();
	terms.clear();
	Q_EMIT layoutChanged();
}

void List1Model::setTDoc(const QVariantList& v) {
	tdoc d;
	d.term = v.at(0).value<QString>();
	d.dc = v.at(1).value<int>();
	d.tc = v.at(2).value<int>();
	terms.push_back(d);
}

void List1Model::refresh(){
	Q_EMIT layoutChanged();
}
