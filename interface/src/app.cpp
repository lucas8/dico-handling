
#include "app.hpp"
#include "sexpr.hpp"

#include <nodes/NodeStyle>
#include <nodes/FlowViewStyle>
#include <nodes/ConnectionStyle>

#include <QtWidgets/QPushButton>

using namespace std::chrono_literals;

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;
using QtNodes::FlowViewStyle;
using QtNodes::NodeStyle;
static void setStyle();

App::App(int argc, char *argv[])
    : QApplication(argc, argv), m_root(new QWidget)
    , m_scene(nullptr), m_line(nullptr), m_server(4444)
{
    ::setStyle();
    m_root->setWindowTitle("FCG/Framenet annotator");
    m_root->resize(800,600);
    m_root->show();
    const size_t n = 10;

    QGridLayout* layout = new QGridLayout(m_root);
    m_root->setLayout(layout);

    m_scene = new FrameScene(m_root);
    layout->addWidget(m_scene, 0, 0, n, n+1);

    m_line = new QLineEdit(m_root);
    layout->addWidget(m_line, n, 0, 1, n);

    QPushButton* button = new QPushButton("Compute", m_root);
    layout->addWidget(button, n, n, 1, 1);

    QObject::connect(button, SIGNAL(clicked()),
            this, SLOT(compute()));
}

App::~App() {
    /* Nothing to do */
}

int App::exec() {
    SExpr expr;

    /* TODO detect closing of gui */
    while(true) {
        processEvents();
        if(m_server.receive(expr, 16ms)) m_scene->reset(expr);
    }

    return 0;
}
        
void App::compute() {
    /* TODO */
    std::cout << m_line->displayText().toUtf8().constData() << std::endl;
}

static void setStyle()
{
  ConnectionStyle::setConnectionStyle(
    R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");

  FlowViewStyle::setStyle(
   R"(
   {
     "FlowViewStyle": {
       "BackgroundColor": [255,255,240],
       "FineGridColor":   [245,245,230],
       "CoarseGridColor": [235,235,220]
     }
   }
   )");

  NodeStyle::setNodeStyle(
   R"(
   {
     "NodeStyle": {
       "NormalBoundaryColor": "darkgray",
       "SelectedBoundaryColor": "deepskyblue",
       "GradientColor0": "mintcream",
       "GradientColor1": "mintcream",
       "GradientColor2": "mintcream",
       "GradientColor3": "mintcream",
       "ShadowColor": [200, 200, 200],
       "FontColor": [10, 10, 10],
       "FontColorFaded": [100, 100, 100],
       "ConnectionPointColor": "white",
       "PenWidth": 2.0,
       "HoveredPenWidth": 2.5,
       "ConnectionPointDiameter": 10.0,
       "Opacity": 1.0
     }
   }
   )");
}


