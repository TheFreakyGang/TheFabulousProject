#include <QAction>
#include <QApplication>
#include <QIcon>
#include <QMenu>
#include <QQmlApplicationEngine>
#include <QStyle>
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("The Fabulous Project");
    app.setApplicationVersion("0.1");
    app.setOrganizationName("The Fabulous Project");

    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        QSystemTrayIcon trayIcon;
        trayIcon.setIcon(QIcon::fromTheme("applications-graphics",
                                          app.style()->standardIcon(QStyle::SP_ComputerIcon)));
        trayIcon.setToolTip("The Fabulous Project");

        QMenu trayMenu;
        QAction quitAction("Quitter", &app);
        QObject::connect(&quitAction, &QAction::triggered, &app, &QCoreApplication::quit);
        trayMenu.addAction(&quitAction);
        trayIcon.setContextMenu(&trayMenu);
        trayIcon.show();
    }

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("TheFabulousProject", "Main");

    return app.exec();
}
