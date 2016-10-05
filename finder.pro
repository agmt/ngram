TEMPLATE = app
CONFIG += c++14
TARGET = finder

SOURCES += \
    finder.cpp

QMAKE_LFLAGS += -lhugetlbfs -B/usr/share/libhugetlbfs -Wl,--hugetlbfs-align


