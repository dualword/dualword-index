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

#include "DualWordIndex.h"

DualWordIndex::DualWordIndex(int &argc, char **argv) : QApplication(argc, argv) {
	QCoreApplication::setApplicationName(QString(_DUALWORD));
	QCoreApplication::setOrganizationDomain("dualword-index");

	#ifdef _VER
		QApplication::setApplicationVersion(_VER);
	#endif

	QApplication::setStyle("windows");
	QApplication::setQuitOnLastWindowClosed(true);

}

DualWordIndex::~DualWordIndex() {

}

void DualWordIndex::start() {
    win.show();
}
