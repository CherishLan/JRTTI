#include "jtypes.h"
#include <QDebug>


stru_JInherit::stru_JInherit() :
    clsinfo(NULL)
{

    //qDebug() << "this new : " << this;
}

stru_JInherit::stru_JInherit(const stru_JInherit &other) :
    clsinfo(NULL)
{
    *this = other;
}

stru_JInherit::~stru_JInherit()
{
    //qDebug() << "this delete : " << this;

    if (clsinfo != NULL)
    {
        delete clsinfo;
        clsinfo = NULL;
    }
}

stru_JInherit &stru_JInherit::operator =(const stru_JInherit &other)
{
    //qDebug() << "this: " << this << ", other: " << &other;

    {
        if (other.clsinfo != NULL)
        {
            if (clsinfo != NULL)
            {
                delete clsinfo;
            }
            clsinfo = new stru_JClassInfo;
            *clsinfo = *(other.clsinfo);
        }
        else if (other.clsinfo == NULL && clsinfo != NULL)
        {
            delete clsinfo;
        }
        jit = other.jit;

        return *this;
    }
}

bool stru_JInherit::isValid() const
{

    {
        if (clsinfo != NULL && clsinfo->isValid())
        {
            return true;
        }

        return false;
    }
}

stru_JClassInfo::stru_JClassInfo() :
    beginEA(0)
{

}

stru_JClassInfo::stru_JClassInfo(const stru_JClassInfo &other) :
    beginEA(0)
{
    *this = other;
}

stru_JClassInfo::~stru_JClassInfo()
{

}

stru_JClassInfo &stru_JClassInfo::operator =(const stru_JClassInfo &other)
{

    {
        beginEA = other.beginEA;
        name = other.name;
        inheritList = other.inheritList;

        return *this;
    }
}

bool stru_JClassInfo::isValid() const
{

    {
        if (beginEA != BADADDR && !name.isEmpty())
        {
            return true;
        }

        return false;
    }
}

QString stru_JClassInfo::toText() const
{
    QString text = QString("[%1]%2").arg(QString::number(beginEA, 16).toUpper()).arg(name);

    return text += inheritList.toText();
}

QString JInheritList::toText() const
{
    QString text;
    const QList<JInherit> &ref = *this;
    foreach (const JInherit &inherit, ref)
    {
        if (!inherit.isValid())
            continue;

        if (inherit.jit == JIT_Normal)
            text += QString("\n    -[%1]->").arg("Normal");
        else if (inherit.jit == JIT_Virtual)
            text += QString("\n    -[%1]->").arg("Virtual");

        text += inherit.clsinfo->toText();
    }

    return text;
}

JInheritList &JInheritList::operator =(const JInheritList &other)
{
    QList<JInherit> *tag = static_cast<QList<JInherit> *>(this);
    *tag = static_cast<QList<JInherit>>(other);

    return *this;
}

QString JClassInfoList::toText() const
{
    QString text;
    foreach (const JClassInfo &cls, (QList<JClassInfo>)(*this))
    {
        text += cls.toText();
        text += ",";
    }

    if (!text.isEmpty())
        text.remove(text.length() - 1, 1);

    return text;
}

JClassInfoList &JClassInfoList::operator =(const JClassInfoList &other)
{
    QList<JClassInfo> *tag = static_cast<QList<JClassInfo> *>(this);
    *tag = static_cast<QList<JClassInfo>>(other);

    return *this;
}

JEA::JEA() :
    beginEA(0),
    endEA(0)
{

}

JEA::JEA(const JEA &other) :
    beginEA(0),
    endEA(0)
{
    *this = other;
}

JEA::~JEA()
{

}

JEA &JEA::operator =(const JEA &other)
{
    beginEA = other.beginEA;
    endEA = other.endEA;

    return *this;
}
