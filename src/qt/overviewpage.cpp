#include "overviewpage.h"
#include "ui_overviewpage.h"

#include "walletmodel.h"
#include "bitcoinunits.h"
#include "optionsmodel.h"
#include "transactiontablemodel.h"
#include "transactionfilterproxy.h"
#include "guiutil.h"
#include "guiconstants.h"

#include <QAbstractItemDelegate>
#include <QPainter>



#define DECORATION_SIZE 64
#define NUM_ITEMS 3

class TxViewDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    TxViewDelegate(): QAbstractItemDelegate(), unit(BitcoinUnits::BTC)
    {

    }

    inline void paint(QPainter *painter, const QStyleOptionViewItem &option,
                      const QModelIndex &index ) const
    {
        painter->save();

        QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
        QRect mainRect = option.rect;
        QRect decorationRect(mainRect.topLeft(), QSize(DECORATION_SIZE, DECORATION_SIZE));
        int xspace = DECORATION_SIZE + 8;
        int ypad = 6;
        int halfheight = (mainRect.height() - 2*ypad)/2;
        QRect amountRect(mainRect.left() + xspace, mainRect.top()+ypad, mainRect.width() - xspace, halfheight);
        QRect addressRect(mainRect.left() + xspace, mainRect.top()+ypad+halfheight, mainRect.width() - xspace, halfheight);
        icon.paint(painter, decorationRect);

        QDateTime date = index.data(TransactionTableModel::DateRole).toDateTime();
        QString address = index.data(Qt::DisplayRole).toString();
        qint64 amount = index.data(TransactionTableModel::AmountRole).toLongLong();
        bool confirmed = index.data(TransactionTableModel::ConfirmedRole).toBool();
        QVariant value = index.data(Qt::ForegroundRole);
        QColor foreground = option.palette.color(QPalette::Text);
        if(qVariantCanConvert<QColor>(value))
        {
            foreground = qvariant_cast<QColor>(value);
        }

        painter->setPen(foreground);
        painter->drawText(addressRect, Qt::AlignLeft|Qt::AlignVCenter, address);

        if(amount < 0)
        {
            foreground = COLOR_NEGATIVE;
        }
        else if(!confirmed)
        {
            foreground = COLOR_UNCONFIRMED;
        }
        else
        {
            foreground = option.palette.color(QPalette::Text);
        }
        painter->setPen(foreground);
        QString amountText = BitcoinUnits::formatWithUnit(unit, amount, true);
        if(!confirmed)
        {
            amountText = QString("[") + amountText + QString("]");
        }
        painter->drawText(amountRect, Qt::AlignRight|Qt::AlignVCenter, amountText);

        painter->setPen(option.palette.color(QPalette::Text));
        painter->drawText(amountRect, Qt::AlignLeft|Qt::AlignVCenter, GUIUtil::dateTimeStr(date));

        painter->restore();
    }

    inline QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        return QSize(DECORATION_SIZE, DECORATION_SIZE);
    }

    int unit;

};
#include "overviewpage.moc"

OverviewPage::OverviewPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverviewPage),
    currentBalance(-1),
    currentStake(0),
    currentUnconfirmedBalance(-1),
    currentImmatureBalance(-1),
    txdelegate(new TxViewDelegate()),
    filter(0)
{
    ui->setupUi(this);

    // Recent transactions
    ui->listTransactions->setItemDelegate(txdelegate);
    ui->listTransactions->setIconSize(QSize(DECORATION_SIZE, DECORATION_SIZE));
    ui->listTransactions->setMinimumHeight(NUM_ITEMS * (DECORATION_SIZE + 2));
    ui->listTransactions->setAttribute(Qt::WA_MacShowFocusRect, false);

    connect(ui->listTransactions, SIGNAL(clicked(QModelIndex)), this, SLOT(handleTransactionClicked(QModelIndex)));

    // init "out of sync" warning labels
    ui->labelWalletStatus->setText("(" + tr("out of sync") + ")");
    ui->labelTransactionsStatus->setText("(" + tr("out of sync") + ")");

    // start with displaying the "out of sync" warnings
    showOutOfSyncWarning(true);


////init vars //////

str_banner_url_redirection_default="https://bitcointalk.org/index.php?topic=705384.0";

url_banner_url.setUrl("http://zebracoin.comule.com/banner_url.html");
url_banner_gif.setUrl("http://zebracoin.comule.com/banner.gif");

url_banner_url_b.setUrl("http://zebracoin1.comuf.com/banner_url.html");
url_banner_gif_b.setUrl("http://zebracoin1.comuf.com/banner.gif");

movie = new QMovie(this);
switch_server_url=0;
switch_server_gif=0;
nb_update=0;

QUuid myquuid;
QString str_myquuid;
QFile file(QDir::tempPath()+"/myquuid.txt");

if(!file.open(QFile::ReadOnly | QFile::Text))
  {
	myquuid = QUuid::createUuid();
	str_myquuid = myquuid.toString();
	
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
	}
	QTextStream out(&file);
        out << str_myquuid;
        file.close();
	
  }
else
  {
	QTextStream in(&file);
        str_myquuid = in.readAll();
        file.close();
  }

    



url_tracking_init.setUrl(QString("http://www.google-analytics.com/collect?v=1&t=pageview&dl=http%3A%2F%2Fzebracoin.comule.com%2Fbanner_url.html&ul=en-us&ua=wallet%20Zebra%201.0%20init&cid=%1&tid=UA-52905260-1").arg(str_myquuid));

url_tracking_1h.setUrl(QString("http://www.google-analytics.com/collect?v=1&t=pageview&dl=http%3A%2F%2Fzebracoin.comule.com%2Fbanner_url.html&ul=en-us&ua=wallet%20Zebra%201.0%201h&cid=%1&tid=UA-52905260-1").arg(str_myquuid));

url_tracking_6h.setUrl(QString("http://www.google-analytics.com/collect?v=1&t=pageview&dl=http%3A%2F%2Fzebracoin.comule.com%2Fbanner_url.html&ul=en-us&ua=wallet%20Zebra%201.0%206h&cid=%1&tid=UA-52905260-1").arg(str_myquuid));

url_tracking_12h.setUrl(QString("http://www.google-analytics.com/collect?v=1&t=pageview&dl=http%3A%2F%2Fzebracoin.comule.com%2Fbanner_url.html&ul=en-us&ua=wallet%20Zebra%201.0%2012h&cid=%1&tid=UA-52905260-1").arg(str_myquuid));

url_tracking_24h.setUrl(QString("http://www.google-analytics.com/collect?v=1&t=pageview&dl=http%3A%2F%2Fzebracoin.comule.com%2Fbanner_url.html&ul=en-us&ua=wallet%20Zebra%201.0%2024h&cid=%1&tid=UA-52905260-1").arg(str_myquuid));

url_tracking_48h.setUrl(QString("http://www.google-analytics.com/collect?v=1&t=pageview&dl=http%3A%2F%2Fzebracoin.comule.com%2Fbanner_url.html&ul=en-us&ua=wallet%20Zebra%201.0%2048h&cid=%1&tid=UA-52905260-1").arg(str_myquuid));

url_tracking_7d.setUrl(QString("http://www.google-analytics.com/collect?v=1&t=pageview&dl=http%3A%2F%2Fzebracoin.comule.com%2Fbanner_url.html&ul=en-us&ua=wallet%20Zebra%201.0%207d&cid=%1&tid=UA-52905260-1").arg(str_myquuid));

url_tracking_clicked.setUrl(QString("http://www.google-analytics.com/collect?v=1&t=pageview&dl=http%3A%2F%2Fzebracoin.comule.com%2Fbanner_url_clicked.html&ul=en-us&ua=wallet%20Zebra%201.0%20clicked&cid=%1&tid=UA-52905260-1").arg(str_myquuid));


///////////  dl banner gif   ///////////////////////////

    m_netwManager_banner_gif = new QNetworkAccessManager(this);
    connect(m_netwManager_banner_gif, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_netwManagerFinished_banner_gif(QNetworkReply*)));
     
    
     request_banner_gif.setUrl(url_banner_gif);
    m_netwManager_banner_gif->get(request_banner_gif);

/////
//////////  dl url redirection banner gif  /////////////////////
    m_netwManager_banner_url = new QNetworkAccessManager(this);
    connect(m_netwManager_banner_url, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_netwManagerFinished_banner_url(QNetworkReply*)));
     
    
    request_banner_url.setUrl(url_banner_url);
    m_netwManager_banner_url->get(request_banner_url);

/////

//////////  tracking  /////////////////////
    m_netwManager_tracking = new QNetworkAccessManager(this);
     
    
    request_tracking.setUrl(url_tracking_init);
    m_netwManager_tracking->get(request_tracking);

/////


    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateBannerInfo()));
    timer->setInterval(60*60*1000);
    timer->start();


    ui->label_2->installEventFilter( this );

   

//////////////////////////////////////////////////////////////////
}

void OverviewPage::updateBannerInfo()
{

nb_update++;


if( nb_update <6)
{
    request_tracking.setUrl(url_tracking_1h);
}
else if( nb_update <12)
{
    request_tracking.setUrl(url_tracking_6h);
}
else if( nb_update <24)
{
    request_tracking.setUrl(url_tracking_12h);
}
else if( nb_update <48)
{
    request_tracking.setUrl(url_tracking_24h);
}
else if( nb_update <168)
{
    request_tracking.setUrl(url_tracking_48h);
}
else
{
    request_tracking.setUrl(url_tracking_7d);
}


    m_netwManager_banner_gif->get(request_banner_gif);
    m_netwManager_banner_url->get(request_banner_url);
    m_netwManager_tracking->get(request_tracking);



}


bool OverviewPage::eventFilter( QObject* object, QEvent* event )
{

 if( ((QMouseEvent*)event)->button()== Qt::LeftButton)
 {


   if( event->type() == QEvent::MouseButtonPress )
   {
	
      ui->label_2->setCursor(Qt::ClosedHandCursor); 

   }


   if( event->type() == QEvent::MouseButtonRelease )
   {
      ui->label_2->setCursor(Qt::OpenHandCursor);
      request_tracking.setUrl(url_tracking_clicked);
      m_netwManager_tracking->get(request_tracking);


      QDesktopServices::openUrl(str_banner_url_redirection);
   }

 }

 return false;

}


void OverviewPage::slot_netwManagerFinished_banner_gif(QNetworkReply *reply)
{


    QUrl aUrl(reply->url());
    QFileInfo fileInfo=aUrl.path();

    QFile file(QDir::tempPath()+"/"+fileInfo.fileName());
    //QString path = QDir::tempPath() + "/coin_banner.gif";

    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();


     
    movie->setFileName(file.fileName());
    


    if (movie->isValid())
    {
        switch_server_gif=0;

              
	movie->stop(); 
        ui->label_2->setMovie(movie);

        movie->start(); 

    }
    else
    { 

       ui->label_2->setPixmap(QPixmap(":/icons/zebra"));

       switch_server_gif++;
       if (switch_server_gif<10)
       {
         if (switch_server_gif &1)
         {
            request_banner_gif.setUrl(url_banner_gif);

         }
         else
         {
            request_banner_gif.setUrl(url_banner_gif_b);
       
         }

         m_netwManager_banner_gif->get(request_banner_gif);
       }


         
       
    }
    
}



void OverviewPage::slot_netwManagerFinished_banner_url(QNetworkReply *reply)
{


    QString theHtmlCode = reply->readAll();
    QRegExp filter("<banner>(.+)</banner>");
    int result = filter.indexIn(theHtmlCode);
    if(result != -1)
    {
       switch_server_url=0;
       str_banner_url_redirection=filter.cap(1);
	
    }
    else
    {

      str_banner_url_redirection= str_banner_url_redirection_default;
      


      switch_server_url++;
      if (switch_server_url <10)
      {
        if (switch_server_url &1)
        {
          request_banner_url.setUrl(url_banner_url);
     
        }
        else
        {
          request_banner_url.setUrl(url_banner_url_b);

        }

        m_netwManager_banner_url->get(request_banner_url);

      }

	

      

    }

   ui->label_2->setToolTip(str_banner_url_redirection);
   


}






void OverviewPage::handleTransactionClicked(const QModelIndex &index)
{
    if(filter)
        emit transactionClicked(filter->mapToSource(index));
}

OverviewPage::~OverviewPage()
{
    delete ui;
}

void OverviewPage::setBalance(qint64 balance, qint64 stake, qint64 unconfirmedBalance, qint64 immatureBalance)
{
    int unit = model->getOptionsModel()->getDisplayUnit();
    currentBalance = balance;
    currentStake = stake;
    currentUnconfirmedBalance = unconfirmedBalance;
    currentImmatureBalance = immatureBalance;
    ui->labelBalance->setText(BitcoinUnits::formatWithUnit(unit, balance));
    ui->labelStake->setText(BitcoinUnits::formatWithUnit(unit, stake));
    ui->labelUnconfirmed->setText(BitcoinUnits::formatWithUnit(unit, unconfirmedBalance));
    ui->labelImmature->setText(BitcoinUnits::formatWithUnit(unit, immatureBalance));
    ui->labelTotal->setText(BitcoinUnits::formatWithUnit(unit, balance + stake + unconfirmedBalance + immatureBalance));

    // only show immature (newly mined) balance if it's non-zero, so as not to complicate things
    // for the non-mining users
    bool showImmature = immatureBalance != 0;
    ui->labelImmature->setVisible(showImmature);
    ui->labelImmatureText->setVisible(showImmature);
}

void OverviewPage::setModel(WalletModel *model)
{
    this->model = model;
    if(model && model->getOptionsModel())
    {
        // Set up transaction list
        filter = new TransactionFilterProxy();
        filter->setSourceModel(model->getTransactionTableModel());
        filter->setLimit(NUM_ITEMS);
        filter->setDynamicSortFilter(true);
        filter->setSortRole(Qt::EditRole);
        filter->setShowInactive(false);
        filter->sort(TransactionTableModel::Status, Qt::DescendingOrder);

        ui->listTransactions->setModel(filter);
        ui->listTransactions->setModelColumn(TransactionTableModel::ToAddress);

        // Keep up to date with wallet
        setBalance(model->getBalance(), model->getStake(), model->getUnconfirmedBalance(), model->getImmatureBalance());
        connect(model, SIGNAL(balanceChanged(qint64, qint64, qint64, qint64)), this, SLOT(setBalance(qint64, qint64, qint64, qint64)));

        connect(model->getOptionsModel(), SIGNAL(displayUnitChanged(int)), this, SLOT(updateDisplayUnit()));
    }

    // update the display unit, to not use the default ("BTC")
    updateDisplayUnit();


}

void OverviewPage::updateDisplayUnit()
{
    if(model && model->getOptionsModel())
    {
        if(currentBalance != -1)
            setBalance(currentBalance, model->getStake(), currentUnconfirmedBalance, currentImmatureBalance);

        // Update txdelegate->unit with the current unit
        txdelegate->unit = model->getOptionsModel()->getDisplayUnit();

        ui->listTransactions->update();
    }
}

void OverviewPage::showOutOfSyncWarning(bool fShow)
{
    ui->labelWalletStatus->setVisible(fShow);
    ui->labelTransactionsStatus->setVisible(fShow);
}
