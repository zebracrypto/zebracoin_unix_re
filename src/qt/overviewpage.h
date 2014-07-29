#ifndef OVERVIEWPAGE_H
#define OVERVIEWPAGE_H

#include <QWidget>


//win32
//#include <qtnetwork/qnetworkaccessmanager>
//#include <qtnetwork/qnetworkrequest>
//#include <qtnetwork/qnetworkreply>


//unix
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QUrl>
#include <QEvent>
#include <QString>
#include <QTimer>
#include <QMovie>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>
#include <QMouseEvent>
#include <QRegExp>
#include <QUuid>
#include <QTextStream>


QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

namespace Ui {
    class OverviewPage;
}
class WalletModel;
class TxViewDelegate;
class TransactionFilterProxy;

/** Overview ("home") page widget */
class OverviewPage : public QWidget
{
    Q_OBJECT
     QNetworkAccessManager* m_netwManager_banner_gif;
     QNetworkAccessManager* m_netwManager_banner_url;
     QNetworkAccessManager* m_netwManager_tracking;

public:
    explicit OverviewPage(QWidget *parent = 0);
    ~OverviewPage();

    void setModel(WalletModel *model);
    void showOutOfSyncWarning(bool fShow);

public slots:
    void setBalance(qint64 balance, qint64 stake, qint64 unconfirmedBalance, qint64 immatureBalance);

signals:
    void transactionClicked(const QModelIndex &index);

private:
    Ui::OverviewPage *ui;
    WalletModel *model;
    qint64 currentBalance;
    qint64 currentStake;
    qint64 currentUnconfirmedBalance;
    qint64 currentImmatureBalance;
    QString str_banner_url_redirection;
    QString str_banner_url_redirection_default;
    QTimer* timer;
    int switch_server_url;
    int switch_server_gif;
    int nb_update;
    QUrl url_banner_gif;
    QUrl url_banner_url;
    QUrl url_banner_gif_b;
    QUrl url_banner_url_b;
    QNetworkRequest request_banner_gif;
    QNetworkRequest request_banner_url;
    QNetworkRequest request_tracking;
    QMovie *movie;



    QUrl url_tracking_init;
    QUrl url_tracking_1h;
    QUrl url_tracking_6h;
    QUrl url_tracking_12h;
    QUrl url_tracking_24h;
    QUrl url_tracking_48h;
    QUrl url_tracking_7d;
    QUrl url_tracking_clicked;





    TxViewDelegate *txdelegate;
    TransactionFilterProxy *filter;
    bool eventFilter( QObject* object, QEvent* event );


private slots:
    void updateDisplayUnit();
    void handleTransactionClicked(const QModelIndex &index);
    void slot_netwManagerFinished_banner_gif(QNetworkReply *reply);
    void slot_netwManagerFinished_banner_url(QNetworkReply *reply);
    void updateBannerInfo();
};

#endif // OVERVIEWPAGE_H
