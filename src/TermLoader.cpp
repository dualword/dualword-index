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

#include "TermLoader.h"

TermLoader::TermLoader(const QString& d, QObject * p) :
QObject(p), dir(d), tc(0), canceled(false) {

}

TermLoader::~TermLoader() {
    idx.close();
}

void TermLoader::run() {
	try{
        idx = Xapian::Database(dir.toStdString());
        for(Xapian::TermIterator t = idx.allterms_begin();
                t != idx.allterms_end(); t++, tc++){

            QVariantList list;
            QVariant str;
            str.setValue(QString::fromUtf8((*t).c_str()));

            QVariant tf;
            tf.setValue(t.get_termfreq());
            QVariant cf;
            cf.setValue(idx.get_collection_freq((*t).c_str()));

            list.push_back(str);
            list.push_back(tf);
            list.push_back(cf);

            Q_EMIT setTDoc(list);
            if(canceled) break;
        }
	}catch (Xapian::Error& e) {
		//
	}

	Q_EMIT setTCount(tc);
	Q_EMIT Done();

}

