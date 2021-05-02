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

#ifndef TABLE_H_
#define TABLE_H_

#include <QTableWidget>

class Table : public QTableWidget {
     Q_OBJECT

public:
	Table(int row, int col, QWidget *p = 0);
	virtual ~Table();
	void filltable(const QList<QPair<QString, int>>&);
	void filltable(const QList<QPair<QString, QPair<int, int> >>&);
	void clear();

};

#endif /* TABLE_H_ */
