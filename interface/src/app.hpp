
#pragma once

#include <vector>
#include <string>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "frameScene.hpp"
#include "server.hpp"
#include "xmlView.hpp"
#include "treeSequence.hpp"

class App : public QApplication {
    Q_OBJECT

    public:
        App() = delete;
        App(int argc, char *argv[]);
        virtual ~App();

        int exec();

    private slots:
        void compute();
        void copy();
        void recompute();
        void valid();
        void lineCursor(int oldPos, int newPos);

    private:
        void reset();

        QWidget* m_root;
        FrameScene* m_scene;
        QLineEdit* m_line;
        XmlView* m_xml;
        QPushButton *m_compute, *m_copy, *m_recompute, *m_valid;
        Server m_server;

        std::vector<std::pair<size_t,size_t>> m_lexBounds;
        std::vector<std::string> m_lexemes;
        TreeSequence<QtNodes::Node*,size_t> m_treeSeq;
};

