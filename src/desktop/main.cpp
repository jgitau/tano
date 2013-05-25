/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtSingleApplication>

#include <QtCore/QTextCodec>

#include "Config.h"
#include "core/Arguments.h"
#include "core/Common.h"
#include "core/Log.h"
#include "core/Out.h"
#include "core/Resources.h"
#include "widgets/MainWindow.h"
#include "widgets/dialogs/PasswordDialog.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName(Tano::name());
    QCoreApplication::setApplicationVersion(Tano::version());

    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

#if QT_VERSION < 0x050000
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

#if LOGGING
    Tano::Log::setup();
#endif

    QtSingleApplication instance(argc, argv);
    if(instance.sendMessage(""))
        return 0;

    Out::welcome();

    Arguments *args = new Arguments(argc, argv);

    if (args->isValid()) {
        Tano::Resources::setIconPaths();
        Tano::Resources::setIconName();

#if PASSWORD
        QString password;
        PasswordDialog dialog;
        switch (dialog.exec())
        {
        case QDialog::Accepted:
            password = dialog.password();
            break;
        default:
            return -10;
        }

        MainWindow mainWindow(args, password);
#else
        MainWindow mainWindow(args);
#endif

        instance.setActivationWindow(&mainWindow);

        mainWindow.show();

        return instance.exec();
    } else {
        return -100;
    }
}
