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
    app.setOrganizationName("TheFreakyGang");

    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        auto *trayIcon = new QSystemTrayIcon(&app);
        trayIcon->setIcon(QIcon::fromTheme("applications-graphics",
                                           app.style()->standardIcon(QStyle::SP_ComputerIcon)));
        trayIcon->setToolTip("The Fabulous Project");

        auto *trayMenu = new QMenu;
        QObject::connect(&app, &QCoreApplication::aboutToQuit, trayMenu, &QObject::deleteLater);
        QAction *quitAction = trayMenu->addAction(QObject::tr("Quit"));
        QObject::connect(quitAction, &QAction::triggered, &app, &QCoreApplication::quit);
        trayIcon->setContextMenu(trayMenu);
        trayIcon->show();
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
