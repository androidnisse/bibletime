/*********
*
* This file is part of BibleTime's source code, http://www.bibletime.info/.
*
* Copyright 1999-2015 by the BibleTime developers.
* The BibleTime source code is licensed under the GNU General Public License version 2.0.
*
**********/

#include "btwelcomedialog.h"

#include "bibletime.h"
#include "frontend/messagedialog.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "util/btconnect.h"
#include "util/bticons.h"
#include "util/cresmgr.h"

void BtWelcomeDialog::openWelcome() {
    BtWelcomeDialog dlg(BibleTime::instance());
    dlg.exec();
}

BtWelcomeDialog::BtWelcomeDialog(QWidget *parent, Qt::WindowFlags wflags)
    : QDialog(parent, wflags)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowIcon(CResMgr::mainMenu::help::tipOfTheDay::icon());
    resize(500, 250);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_iconLabel = new QLabel(this);
    m_iconLabel->setPixmap(BtIcons::instance().icon_bibletime.pixmap(48));
    mainLayout->addWidget(m_iconLabel, 0, Qt::AlignHCenter);

    m_label = new QLabel(this);
    m_label->setWordWrap(true);
    mainLayout->addWidget(m_label);

    mainLayout->addStretch();

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Close,
                                       Qt::Horizontal, this);
    message::prepareDialogBox(m_buttonBox);
    m_installButton = m_buttonBox->addButton(
                "", QDialogButtonBox::AcceptRole);
    mainLayout->addWidget(m_buttonBox);

    setLayout(mainLayout);

    retranslateUi();

    BT_CONNECT(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    BT_CONNECT(m_buttonBox, SIGNAL(accepted()), this, SLOT(slotAccept()));

}

void BtWelcomeDialog::slotAccept() {
    hide();
    accept();
    BibleTime::instance()->slotBookshelfWizard();
}

void BtWelcomeDialog::retranslateUi() {
    setWindowTitle(tr("Welcome to BibleTime"));

    QString msg("<p>");
    msg += tr("BibleTime is an easy to use but powerful Bible study tool.");
    msg += "</p><p>";
    msg += tr("Various works such as Bibles, books, commentaries, and lexicons are available. ");
    msg += tr("Choose the \"Install works\" button to download works. ");
    msg += tr("The menu \"Settings > Bookshelf Manager\" also installs works.");
    m_label->setText(msg);

    m_installButton->setText(tr("Install works..."));
}

//void BtWelcomeDialog::linkClicked(const QUrl& url) {
//    QDesktopServices::openUrl(url);
//}