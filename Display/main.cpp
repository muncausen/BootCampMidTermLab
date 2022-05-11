#include <QtQml/qqml.h>

#include <QtCore/QStringListModel>
#include <QtCore/QCommandLineParser>
#include <QtCore/QProcess>
#include <QtCore/QUrlQuery>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include <iostream>

#include "your_stuff.hpp"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QCoreApplication::setApplicationName("AVIC");
  QCoreApplication::setApplicationVersion("0.3");
  QCommandLineParser parser;
  parser.setApplicationDescription("ALTEN Virtual Instrument Cluster [AVIC]");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addOptions({{{"c", "can-interface"},
                      QCoreApplication::translate("main", "CAN interface"),
                      QCoreApplication::translate("main", "CANBUS interface name e.g. vcan0")}});
  parser.process(app);
  if (!parser.isSet("can-interface")) parser.showHelp();

  QQmlApplicationEngine engine;

  engine.load(QUrl(QStringLiteral("qrc:/cluster-gauges.qml")));
  QList<QObject *> mobjs = engine.rootObjects();
  QObject *vs = mobjs.first()->findChild<QObject *>("valueSource");
  /***** Your Code Goes Below Here ******/
  yourStuff _(parser.value("can-interface").toStdString(), vs);

  /***** Do Not Block Executation  ******/
  return app.exec();
}