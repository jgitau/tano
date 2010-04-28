/****************************************************************************
* QVlc - Qt and libVLC connector library
* AudioControl.h: Audio controller
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This file may be used under the terms of the
* GNU General Public License version 3.0 as published by the
* Free Software Foundation and appearing in the file LICENSE.GPL
* included in the packaging of this file.
*****************************************************************************/

#ifndef QVLC_AUDIOCONTROL_H_
#define QVLC_AUDIOCONTROL_H_

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGui/QAction>

namespace QVlc
{
	/*! \class AudioControl AudioControl.h QVlc/AudioControl.h
		\brief Audio control class

		This is one of QVlc control classes.
		It provides audio tracks management.
	*/
	class AudioControl : public QObject
	{
	Q_OBJECT
	public:
		/*!
			AudioControl constructor
			\param parent audio controller's parent object
		*/
		AudioControl(QObject *parent = 0);

		/*!
			AudioControl destructor
		*/
		~AudioControl();


		/*!
			Reset all settings and selected audio tracks.
			Usually called on media change.
		*/
		void reset();


	signals:
		/*!
			Signal sending actions for changing audio tracks
			\param QString type of actions
			\param QList<QAction*> list of actions
		*/
		void actions(const QString, QList<QAction*>);


	private slots:
		void update();
		void updateActions();

	private:
		QTimer *_timer;

		QList<QAction*> _actionList;
		QMap<QString,int> _map;
		QActionGroup *_actionGroup;
	};
};

#endif // QVLC_AUDIOCONTROL_H_
