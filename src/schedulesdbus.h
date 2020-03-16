/*
 * Copyright (C) 2015 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DCalendarDBus -p dcalendardbus com.deepin.api.LunarCalendar.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef SCHEDULESDBUS_H
#define SCHEDULESDBUS_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "schedulestructs.h"

/*
 * Proxy class for interface com.deepin.api.LunarCalendar
 */
class CSchedulesDBus: public QDBusAbstractInterface
{
    Q_OBJECT

    Q_SLOT void __propertyChanged__(const QDBusMessage &msg)
    {
        QList<QVariant> arguments = msg.arguments();
        if (3 != arguments.count())
            return;
        QString interfaceName = msg.arguments().at(0).toString();
        if (interfaceName != "com.deepin.api.LunarCalendar")
            return;
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        foreach (const QString &prop, changedProps.keys()) {
            const QMetaObject *self = metaObject();
            for (int i = self->propertyOffset(); i < self->propertyCount(); ++i) {
                QMetaProperty p = self->property(i);
                if (p.name() == prop) {
                    Q_EMIT p.notifySignal().invoke(this);
                }
            }
        }
    }
public:
    static inline const char *staticInterfaceName()
    {
        return "com.deepin.daemon.Calendar.Scheduler";
    }

public:
    CSchedulesDBus(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~CSchedulesDBus();
    QString toconvertIGData(QDateTime date);
    QDateTime fromconvertiIGData(QString str);
private:
    QString createScheduleDtailInfojson(const ScheduleDtailInfo &info);
    QString createScheduleTypejson(const ScheduleType &info);
    ScheduleType parsingScheduleTypejson(QJsonObject &object);
    ScheduleDtailInfo parsingScheduleDtailInfojsonID(QJsonObject &obj);
    QString createScheduleRRule(const ScheduleDtailInfo &info);
    void parsingScheduleRRule(QString str, ScheduleDtailInfo &info);
    QString createScheduleRemind(const ScheduleDtailInfo &info);
    void parsingScheduleRemind(QString str, ScheduleDtailInfo &info);
    QString toconvertData(QDateTime date);
    QDateTime fromconvertData(QString str);
public Q_SLOTS: // METHODS

    qint64 CreateJob(const ScheduleDtailInfo &info);
    bool GetJobs(int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay, QVector<ScheduleDateRangeInfo> &out);
    bool GetJob(qint64 jobId, ScheduleDtailInfo &out);
    bool UpdateJob(const ScheduleDtailInfo &info);
    bool DeleteJob(qint64 jobId);
    bool QueryJobs(QString key, QDateTime starttime, QDateTime endtime, QVector<ScheduleDateRangeInfo> &out);
    bool QueryJobs(QString key, QDateTime starttime, QDateTime endtime, QString &out);


    bool GetTypes(QVector<ScheduleType> &out);
    bool GetType(qint64 jobId, ScheduleType &out);
    qint64 CreateType(const ScheduleType &info);
    bool DeleteType(qint64 jobId);
    bool UpdateType(const ScheduleType &info);

Q_SIGNALS: // SIGNALS
// begin property changed signals
//private:
//    QMutex m_mutex;
};
#endif
