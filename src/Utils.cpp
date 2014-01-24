/*=======================================================================
*
*   Copyright (C) 2013 Lysine.
*
*   Filename:    Utils.cpp
*   Time:        2013/05/10
*   Author:      Lysine
*
*   Lysine is a student majoring in Software Engineering
*   from the School of Software, SUN YAT-SEN UNIVERSITY.
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.

*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
=========================================================================*/

#include "Utils.h"

QJsonObject Utils::config;

Utils::Site Utils::getSite(QString url)
{
	if(url.startsWith("http://www.bilibili.tv")||url.startsWith("http://bilibili.kankanews.com")){
		return Bilibili;
	}
	else if(url.startsWith("http://www.acfun.tv")||url.startsWith("http://api.acfun.tv")){
		return AcFun;
	}
	else if(url.startsWith("http://comic.letv.com")){
		return Letv;
	}
	else if(url.startsWith("http://api.acplay.net")){
		return AcPlay;
	}
	else{
		return Unknown;
	}
}

void Utils::setCenter(QWidget *widget)
{
	QPoint center;
	QWidget *parent=widget->parentWidget();
	if(parent==NULL){
		center=QApplication::desktop()->screenGeometry(widget).center();
	}
	else if(widget->isWindow()){
		center=parent->geometry().center();
	}
	else{
		center=parent->rect().center();
	}
	QRect rect=widget->geometry();
	rect.moveCenter(center);
	widget->setGeometry(rect);
}

void Utils::setGround(QWidget *widget,QColor color)
{
	widget->setAutoFillBackground(true);
	QPalette palette=widget->palette();
	palette.setColor(QPalette::Window,color);
	widget->setPalette(palette);
}

QString Utils::defaultFont(bool monospace)
{
	if(monospace){
#ifdef Q_OS_LINUX
		return "文泉驿等宽正黑";
#endif
#ifdef Q_OS_WIN32
#ifdef Q_CC_MSVC
		return QString::fromLocal8Bit("黑体");
#else
		return "黑体";
#endif
#endif
#ifdef Q_OS_MAC
		return "";
#endif
	}
	else{
#ifdef Q_OS_LINUX
		return "文泉驿正黑";
#endif
#ifdef Q_OS_WIN32
#ifdef Q_CC_MSVC
		return QString::fromLocal8Bit("微软雅黑");
#else
		return "微软雅黑";
#endif
#endif
#ifdef Q_OS_MAC
		return "华文黑体";
#endif
	}
}

QString Utils::splitString(QString text,int width)
{
	QStringList result;
	QTextBoundaryFinder finder(QTextBoundaryFinder::Word,text);
	int sta=0,lst=0,end;
	while((end=finder.toNextBoundary())!=-1){
		QString line=text.mid(sta,end-sta);
		if(qApp->fontMetrics().width(line)>width){
			result.append(line);
			sta=lst;
		}
		lst=end;
	}
	result.append(text.mid(sta));
	return result.join('\n');
}

void Utils::loadConfig()
{
	QFile conf("./Config.txt");
	conf.open(QIODevice::ReadOnly|QIODevice::Text);
	config=QJsonDocument::fromJson(conf.readAll()).object();
	conf.close();
}

void Utils::saveConfig()
{
	QFile conf("./Config.txt");
	conf.open(QIODevice::WriteOnly|QIODevice::Text);
	conf.write(QJsonDocument(config).toJson());
	conf.close();
}

