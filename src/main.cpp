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

#include <QApplication>
#include <QTimer>

#include "DualWordIndex.h"

int main(int argc, char *argv[]) {

	DualWordIndex app(argc, argv);
	QTimer::singleShot(0,&app,SLOT(start()));
	return app.exec();

}
