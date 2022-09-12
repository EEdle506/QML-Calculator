#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QIcon>

#include "Calculator.h"
#include "Converter.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Calculator QML");
#endif

	QGuiApplication app(argc, argv);
	app.setWindowIcon(QIcon("qrc:/app/assets/images/calculator.png"));

    QScopedPointer<History> instance(new History());

    qmlRegisterSingletonInstance("Calculator.History", 1, 0, "History", instance.get());

    qmlRegisterType<Standart>("Calculator.Standart", 1, 0, "Standart");
    qmlRegisterType<Converter>("Calculator.Converter", 1, 0, "Converter");

    QQmlApplicationEngine engine;

	engine.load(QUrl("qrc:/app/qml/main.qml"));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
