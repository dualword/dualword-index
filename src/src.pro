include("dualword-index.version.pri")

TARGET = dualword-index
TEMPLATE = app
message(Building: = $${TARGET} - $${VERSION})
CONFIG += qt no_keywords debug
QT += widgets

QMAKE_CXXFLAGS += -std=c++17

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

unix {
        include("dualword-index.unix.pri")
}

win32 {
        INCLUDEPATH += "c:/MinGW/include"
	LIBS += -lxapian
}

OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
