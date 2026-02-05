/*******************************************************************************
 * libretroshare/services/wiki_notify_activation_test.cc                        *
 *                                                                             *
 * Copyright (C) 2026 Retroshare Team <retroshare.team@gmail.com>              *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU Affero General Public License as              *
 * published by the Free Software Foundation, either version 3 of the          *
 * License, or (at your option) any later version.                             *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU Affero General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Affero General Public License    *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                             *
 *******************************************************************************/

#ifndef RS_USE_WIKI
#define RS_USE_WIKI 1
#endif

#ifdef RS_USE_WIKI

#include <gtest/gtest.h>
#include <QStackedWidget>
#include <QApplication>
#include <QWidget>

#include "gui/MainWindow.h"

TEST(WikiNotifyActivation, SetsWikiWidgetOnStack)
{
	int argc = 0;
	char** argv = nullptr;
	QApplication app(argc, argv);

	QStackedWidget stack;
	QWidget wikiPage;
	stack.addWidget(&wikiPage);

	EXPECT_TRUE(MainWindow::activateWikiPage(&stack, &wikiPage));
	EXPECT_EQ(&wikiPage, stack.currentWidget());
}

#endif // RS_USE_WIKI
