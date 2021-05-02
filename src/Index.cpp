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

#include "Index.h"

Index::Index(const QString& d,QObject* p) : QObject(p),dir(d){
	index=0,dc=-1,tc=0;
	q.reset(new QString(""));
}

Index::~Index() {

}

void Index::open(){
	idx = Xapian::Database(dir.toStdString());
	dc = idx.get_doccount();
}

void Index::close(){
	idx.close();
}

void Index::next(){
	if(dc <= 0 || index >= dc-1) return;
	++index;
	getdoc();
}

void Index::back(){
	if(dc <= 0 || index <= 0) return;
	--index;
	getdoc();
}

void Index::first(){
	if(dc > 0){
		index = 0;
		getdoc();
	}
}

void Index::last(){
	if(dc > 0){
		index = dc - 1;
		getdoc();
	}
}

void Index::setQuery(const QString& s){
	q.reset(new QString(s));
	index = 0;

	if(q->length() > 0){
		Xapian::Enquire enquire(idx);
		Xapian::QueryParser qp;
		qp.set_database(idx);
		Xapian::Query query;
		query = qp.parse_query(q->toStdString());
		enquire.set_query(query);
		Xapian::MSet matches = enquire.get_mset(0, idx.get_doccount());
		dc=matches.size();
	}else{
		dc = idx.get_doccount();
	}
}

void Index::getdoc(){
	doc d;
	Xapian::Enquire enquire(idx);
	Xapian::QueryParser qp;
	qp.set_database(idx);

	Xapian::Query query;
	if(q->length() > 0){
		query = qp.parse_query(q->toStdString());
	}else{
		query = Xapian::Query("");
	}
	enquire.set_query(query);

	Xapian::MSet matches = enquire.get_mset(index, 1);
    if(matches.size() == 1){
    	Xapian::Document ddd = matches[0].get_document();
    	d.id = ddd.get_docid();
    	d.data = QString::fromUtf8(ddd.get_data().c_str());

    	for(Xapian::TermIterator t = ddd.termlist_begin();
    			t != ddd.termlist_end(); t++){
			d.t.push_back( qMakePair(QString::fromUtf8((*t).c_str()), (int)t.get_wdf()) );
    	}

    	for(Xapian::ValueIterator t = ddd.values_begin();
    			t != ddd.values_end(); t++){
			d.v.push_back( qMakePair(QString::fromUtf8((*t).c_str()), (int)t.get_valueno()) );
    	}
    	Q_EMIT setDoc(d);
    }
}
