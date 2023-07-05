#include <QtGui/QtGui>
#include <QApplication>
#include <QWebEngineView>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QPushButton>
//#include "classBrowser.h"
//#include "main.moc"

class BrowserTabWidget : public QWidget {
    //Q_OBJECT
signals:
    void tabLoadingFinished(const QString& tabTitle);
};

void BrowserTabWidget::tabLoadingFinished(const QString& tabTitle) {

}

BrowserTabWidget* creatNewBrowserWindow() {
    auto *browserWindow = new BrowserTabWidget;
    auto *urlLineEdit = new QLineEdit;
    auto *webView = new QWebEngineView;
    auto *vbox = new QVBoxLayout(browserWindow);

    vbox->addWidget(urlLineEdit);
    vbox->addWidget(webView);
    //

    QObject::connect(urlLineEdit, &QLineEdit::returnPressed, [webView, urlLineEdit] ()
    {
        auto urlToOpen = urlLineEdit->text();
        webView->load(urlToOpen);
    });
    //

    QObject::connect(urlLineEdit, &QLineEdit::returnPressed, [webView, urlLineEdit](){
        auto urlToOpen = urlLineEdit->text();
        webView->load(urlToOpen);
    });
    //
    QObject::connect(webView, &QWebEngineView::loadFinished, [webView, browserWindow] (bool ok){
        if (ok)
            emit browserWindow->tabLoadingFinished(webView->title());
    });
    return browserWindow;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTabWidget tabs;
    //
    QPushButton newTabButton("+");
    tabs.setTabsClosable(true);
    tabs.setCornerWidget(&newTabButton, Qt::BottomLeftCorner);

    QObject::connect(&newTabButton, &QPushButton::clicked, [&tabs](){
        auto newTab = creatNewBrowserWindow();
        QObject::connect(newTab, &BrowserTabWidget::tabLoadingFinished, [&tabs](QString newTitle){
            tabs.setTabText(tabs.currentIndex(), newTitle);
            tabs.setWindowTitle(newTitle);
        });
        tabs.addTab(newTab, "tab" + QString::number(tabs.count() + 1));
    });
    //
    tabs.show();
    return QApplication::exec();
}