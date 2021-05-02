		
LIBS += -lxapian

isEmpty(PREFIX) {
	PREFIX = /usr
}
DATADIR =$$PREFIX/share
DEFINES += DATADIR=\\\"$$DATADIR\\\"

INSTALLS += target desktop icon icon2 man
target.path = $$PREFIX/bin
desktop.path = $$DATADIR/applications/
desktop.files = ../pkg/$${TARGET}.desktop
icon.path = $$DATADIR/icons/hicolor/48x48/apps
icon.files += ../pkg/$${TARGET}.png
icon2.path = $$DATADIR/pixmaps/
icon2.files += ../pkg/$${TARGET}.xpm
man.path = $$DATADIR/man/man1
man.files = ../pkg/dualword-index.1
