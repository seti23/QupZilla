/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2011  nowrep
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "webtab.h"
#include "qupzilla.h"
#include "webview.h"
#include "tabbar.h"

WebTab::WebTab(QupZilla* mainClass, QWidget* parent)
    :QWidget(parent)
    ,p_QupZilla(mainClass)
    ,m_view(0)
    ,m_pinned(false)
{
    m_layout = new QVBoxLayout(this);
    setLayout(m_layout);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    m_view = new WebView(p_QupZilla, this);
    m_layout->addWidget(m_view);

    setAutoFillBackground(true); // We don't want this transparent

    connect(m_view, SIGNAL(showNotification(QWidget*)), this, SLOT(showNotification(QWidget*)));
}

void WebTab::showNotification(QWidget* notif)
{
    if (m_layout->count() > 1)
        delete m_layout->itemAt(0)->widget();

    m_layout->insertWidget(0, notif);
    notif->show();
}

int WebTab::tabIndex()
{
    return m_view->tabIndex();
}

void WebTab::pinTab(int index)
{
    TabWidget* tabWidget = p_QupZilla->tabWidget();
    if (!tabWidget)
        return;

    if (m_pinned) { //Unpin tab
        m_pinned = false;
        tabWidget->setTabText(index, m_view->title());
        tabWidget->getTabBar()->updateCloseButton(index);
    } else { // Pin tab
        m_pinned = true;
        tabWidget->setCurrentIndex(0); //             <<-- those 2 lines fixes
        tabWidget->getTabBar()->moveTab(index, 0);    // | weird behavior with bad
        tabWidget->setTabText(0, "");                 // | tabwidget update if we
        tabWidget->setCurrentIndex(0); //             <<-- are moving current tab
        tabWidget->getTabBar()->updateCloseButton(0);
    }
}

WebTab::~WebTab()
{
    delete m_view;
}
