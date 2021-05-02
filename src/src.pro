include("dualword-index.version.pri")

TARGET = dualword-index
TEMPLATE = app
CONFIG += qt no_keywords release

message(Building: = $${TARGET} - $${VERSION})

QMAKE_CXXFLAGS += $$CFLAGS $$CPPFLAGS $$CXXFLAGS
QMAKE_LFLAGS += $$LDFLAGS

QMAKE_CXXFLAGS += -std=c++0x

HEADERS = \
	Table.h \
	Index.h	\
	TermLoader.h \
	List1Model.h \
	MainWindow.h \
	DualWordIndex.h
		
SOURCES = \
	main.cpp \
	Table.cpp \
	Index.cpp \
	TermLoader.cpp \
	List1Model.cpp \
	MainWindow.cpp \
	DualWordIndex.cpp	
						
OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
		
unix {
	include("dualword-index.unix.pri")
}

win32 {
	INCLUDEPATH += "c:/MinGW/include"
	LIBS += -lxapian
}
