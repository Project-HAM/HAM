/*------------------------------------------------------------------------------------------------

# Copyright (c) 2016 Núcleo de Tecnologias Estratégicas em Saúde (NUTES)/Signove Tecnologia S/A .
# Licensed under the MIT license;
# You may obtain a copy of the License at:
# http://opensource.org/licenses/mit-license.php or see LICENSE file

------------------------------------------------------------------------------------------------*/

#include "agent.h"


Agent::Agent(QObject *parent) : QObject(parent),requestAttributes(false),requestConfiguratiosn(false)
{

}

void Agent::Connected(QString device, QString address)
{

    QDBusInterface dev("com.signove.health",device,"com.signove.health.device",QDBusConnection::systemBus());

    emit deviceConnected(address);
    emit currentStatus("Connecting...");
}

void Agent::Associated(QString device, QString xmlData)
{
    emit currentStatus("Associated!");

    QDBusInterface dev("com.signove.health",device,"com.signove.health.device",QDBusConnection::systemBus());

    if(requestConfiguratiosn){
        QString xml = dev.call("GetConfiguration").arguments().first().toString();
        emit xmlConfigurations(xml);
    }
    //Alterado

    //if(requestAttributes)
        dev.call("RequestDeviceAttributes");
}

void Agent::MeasurementData(QString device, QString xmlData)
{
    emit currentStatus("Receiving data...");
    emit xmlMeasures (xmlData);
}

void Agent::DeviceAttributes(QString device, QString xmlData)
{
    emit xmlDeviceAttributes(xmlData);
}

void Agent::Disassociated(QString device)
{
    emit currentStatus("Disassociating...");
}

void Agent::Disconnected(QString device)
{
    emit deviceDisconnected();
    emit currentStatus("Disconnected!");
}

void Agent::setRequestConfiguratiosn(bool value)
{
    requestConfiguratiosn = value;
}

void Agent::setRequestAttributes(bool value)
{
    requestAttributes = value;
}

