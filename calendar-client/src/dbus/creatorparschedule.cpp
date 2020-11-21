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
 * Command line was: qdbusxml2cpp -c DCalendarDBus -p dcalendardbus com.deepin.dataserver.Calendar.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "creatorparschedule.h"
#include "scheduledatamanage.h"

CreatOrParSchedule::CreatOrParSchedule()
{

}

CreatOrParSchedule::~CreatOrParSchedule()
{

}
QString CreatOrParSchedule::createScheduleDtailInfojson(const ScheduleDtailInfo &info)
{
    QJsonObject json;
    json.insert("ID", info.id);
    json.insert("AllDay", info.allday);
    json.insert("Remind", createScheduleRemind(info));
    json.insert("RRule", createScheduleRRule(info));
    json.insert("Title", info.titleName);
    json.insert("Description", info.description);
    json.insert("Type", info.type.ID);
    json.insert("Start", toconvertData(info.beginDateTime));
    json.insert("End", toconvertData(info.endDateTime));
    json.insert("RecurID", info.RecurID);
    QJsonArray jsonarry;
    for (int i = 0; i < info.ignore.count(); i++) {
        jsonarry.append(toconvertData(info.ignore.at(i)));
    }
    json.insert("Ignore", jsonarry);
    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    return strJson;
}

QString CreatOrParSchedule::createScheduleTypejson(const ScheduleType &info)
{
    QJsonObject json;
    json.insert("ID", info.ID);
    json.insert("Name", info.typeName);
    QString colorName =  QString("#%1%2%3").arg(info.color.red(), 2, 16, QChar('0')).arg(info.color.green(), 2, 16, QChar('0')).arg(info.color.blue(), 2, 16, QChar('0'));
    json.insert("Color", info.color.name());
    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    return strJson;
}

ScheduleType CreatOrParSchedule::parsingScheduleTypejson(QJsonObject &object)
{
    ScheduleType type;
    QJsonObject &rootObj = object;

    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    if (rootObj.contains("ID")) {
        type.ID = rootObj.value("ID").toInt();
    }
    if (rootObj.contains("Name")) {
        type.typeName = rootObj.value("Name").toString();
    }
    if (rootObj.contains("Color")) {
        QString str = rootObj.value("Color").toString();
        type.color = QColor(rootObj.value("Color").toString());
    }
    return type;
}

ScheduleDtailInfo CreatOrParSchedule::parsingScheduleDtailInfojsonID(QJsonObject &obj)
{

    ScheduleDtailInfo info;

    QJsonObject &rootObj = obj;
    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    if (rootObj.contains("ID")) {
        info.id = rootObj.value("ID").toInt();
    }
    if (rootObj.contains("AllDay")) {
        info.allday = rootObj.value("AllDay").toBool();
    }
    if (rootObj.contains("Remind")) {
        parsingScheduleRemind(rootObj.value("Remind").toString(), info);
    }
    if (rootObj.contains("Title")) {
        info.titleName = rootObj.value("Title").toString();
    }
    if (rootObj.contains("Description")) {
        info.description = rootObj.value("Description").toString();
    }
    if (rootObj.contains("Type")) {
        CScheduleDataManage::getScheduleDataManage()->getscheduleDataCtrl()->GetType(rootObj.value("Type").toInt(), info.type);
    }
    if (rootObj.contains("Start")) {
        info.beginDateTime = fromconvertData(rootObj.value("Start").toString());
    }
    if (rootObj.contains("End")) {
        info.endDateTime = fromconvertData(rootObj.value("End").toString());
    }
    if (rootObj.contains("RecurID")) {
        info.RecurID = rootObj.value("RecurID").toInt();
    }
    if (rootObj.contains("RRule")) {
        parsingScheduleRRule(rootObj.value("RRule").toString(), info);
    }
    if (rootObj.contains("Ignore")) {
        QJsonArray subArray = rootObj.value("Ignore").toArray();
        for (int i = 0; i < subArray.size(); i++) {
            QString subObj = subArray.at(i).toString();
            info.ignore.append(fromconvertData(subObj));
        }
    }
    return info;
}

QString CreatOrParSchedule::createScheduleRRule(const ScheduleDtailInfo &info)
{
    if (info.rpeat == 0) return QString();
    QString str;
    switch (info.rpeat) {
    case 1: {
        str += "FREQ=DAILY";
    }
    break;
    case 2: {
        str += "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR";
    }
    break;
    case 3: {
        str += "FREQ=WEEKLY";
    }
    break;
    case 4: {
        str += "FREQ=MONTHLY";
    }
    break;
    case 5: {
        str += "FREQ=YEARLY";
    }
    break;
    }
    switch (info.enddata.type) {
    case 1: {
        str += QString(";COUNT=%1").arg(info.enddata.tcount + 1);
    }
    break;
    case 2: {
        QDateTime datetime = info.enddata.date.addDays(-1);
        str += ";UNTIL=" + datetime.toString("yyyyMMddThhmmss") + "Z";
    }
    break;
    }
    return str;
}

void CreatOrParSchedule::parsingScheduleRRule(QString str, ScheduleDtailInfo &info)
{
    if (str.isEmpty()) {
        info.rpeat = 0;
        return;
    }
    QString rrulestrs = str;
    QStringList rruleslist = rrulestrs.split(";", QString::SkipEmptyParts);
    if (rruleslist.count() > 0) {
        if (rruleslist.contains("FREQ=DAILY") && rruleslist.contains("BYDAY=MO,TU,WE,TH,FR")) info.rpeat = 2;
        else if (rruleslist.contains("FREQ=DAILY")) {
            info.rpeat = 1;
        } else if (rruleslist.contains("FREQ=WEEKLY")) {
            info.rpeat = 3;
        } else if (rruleslist.contains("FREQ=MONTHLY")) {
            info.rpeat = 4;
        } else if (rruleslist.contains("FREQ=YEARLY")) {
            info.rpeat = 5;
        }
        info.enddata.type = 0;
        for (int i = 0; i < rruleslist.count(); i++) {
            if (rruleslist.at(i).contains("COUNT=")) {
                QStringList liststr = rruleslist.at(i).split("=", QString::SkipEmptyParts);
                info.enddata.type = 1;
                info.enddata.tcount = liststr.at(1).toInt() - 1;
            }

            if (rruleslist.at(i).contains("UNTIL=")) {
                QStringList liststr = rruleslist.at(i).split("=", QString::SkipEmptyParts);
                info.enddata.type = 2;
                info.enddata.date = QDateTime::fromString(liststr.at(1).left(liststr.at(1).count() - 1), "yyyyMMddThhmmss");
                info.enddata.date = info.enddata.date.addDays(1);
            }
        }
    }
}

QString CreatOrParSchedule::createScheduleRemind(const ScheduleDtailInfo &info)
{
    if (!info.remind) return QString();
    QString str;
    if (info.allday) {
        str = QString::number(info.remindData.n) + ";" + info.remindData.time.toString("hh:mm");
    } else {
        str = QString::number(info.remindData.n);
    }
    return str;
}

void CreatOrParSchedule::parsingScheduleRemind(QString str, ScheduleDtailInfo &info)
{
    if (str.isEmpty()) {
        info.remind = false;
        return;
    }
    info.remind = true;
    if (info.allday) {
        QStringList liststr = str.split(";", QString::SkipEmptyParts);
        info.remindData.n = liststr.at(0).toInt();
        info.remindData.time = QTime::fromString(liststr.at(1), "hh:mm");
    } else {
        info.remindData.n = str.toInt();
    }
}

QString CreatOrParSchedule::toconvertData(QDateTime date)
{
    QDateTime datetimeutc11 = date;
    datetimeutc11.setTimeSpec(Qt::UTC);
    QString strss = datetimeutc11.toString(Qt::ISODate);
    datetimeutc11.setTimeSpec(Qt::OffsetFromUTC);
    strss = datetimeutc11.toString(Qt::ISODateWithMs);
    QDateTime datetimeutc = QDateTime::fromTime_t(0);
    QString str = date.toString("yyyy-MM-ddThh:mm:ss") + "+" + datetimeutc.toString("hh:mm");
    return  str;
}

QDateTime CreatOrParSchedule::fromconvertData(QString str)
{
    QStringList liststr = str.split("+", QString::SkipEmptyParts);
    return QDateTime::fromString(liststr.at(0), "yyyy-MM-ddThh:mm:ss");
}

QString CreatOrParSchedule::toconvertIGData(QDateTime date)
{
    QDateTime datetimeutc11 = date;
    datetimeutc11.setTimeSpec(Qt::UTC);
    QString strss = datetimeutc11.toString(Qt::ISODate);
    datetimeutc11.setTimeSpec(Qt::OffsetFromUTC);
    strss = datetimeutc11.toString(Qt::ISODateWithMs);
    QDateTime datetimeutc = QDateTime::fromTime_t(0);
    QString str = date.toString("yyyy-MM-ddThh:mm:ss") + "Z" + datetimeutc.toString("hh:mm");
    return  str;
}

QDateTime CreatOrParSchedule::fromconvertiIGData(QString str)
{
    QStringList liststr = str.split("Z", QString::SkipEmptyParts);
    return QDateTime::fromString(liststr.at(0), "yyyy-MM-ddThh:mm:ss");
}

QString CreatOrParSchedule::CreateJob(const ScheduleDtailInfo &info)
{
    QString str = createScheduleDtailInfojson(info);
    return  str;
}

bool CreatOrParSchedule::GetJob(QString str, ScheduleDtailInfo &out)
{
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(str.toLocal8Bit(), &json_error));

    if (json_error.error != QJsonParseError::NoError) {
        return false;
    }

    QJsonObject ssubObj = jsonDoc.object();
    out = parsingScheduleDtailInfojsonID(ssubObj);

    return true;
}


