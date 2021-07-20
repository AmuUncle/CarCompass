#include "carcompass.h"
#include <QApplication>
#include "iconhelper.h"
#include "appinit.h"
#include <QFontDatabase>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));
    a.setWindowIcon(QIcon(":/ttf/CarCompass.ico"));

    int nFontId = QFontDatabase::addApplicationFont("F:\\svn_root\\QtProject\\CarCompass\\res\\SourceHanSansCN-Bold.otf");
    QStringList strlistFontName = QFontDatabase::applicationFontFamilies(nFontId);

    if (strlistFontName.count() > 0)
    {
        QFont f = QFont(strlistFontName.at(0), 9);
        a.setFont(f);
    }

    AppInit::Instance()->start();
    IconHelper::Load();

    //加载样式表
    QFile file(":/ttf/CarCompass.css");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }

    CarCompass w;
    w.show();

    return a.exec();
}
