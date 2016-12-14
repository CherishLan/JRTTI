#include "jbcbrtti.h"

JClassInfoList		JBcbRtti::m_buffer;

JClassInfo JBcbRtti::getClassInfo(ea_t ea)
{
    if (ea == BADADDR || ea == 0)
    {
        return JClassInfo();
    }

    JClassInfo cls = getClassInfo(ea, true);

    if (cls.isValid())
        m_buffer.append(cls);

    return cls;
}

bool JBcbRtti::find(JClassInfo &cls, ea_t ea)
{
    return find(cls, ea, m_buffer);
}

JClassInfo JBcbRtti::getClassInfo(ea_t ea, bool flag)
{
    JClassInfo cls;
    cls.beginEA = ea;
    if (ea == BADADDR || ea == 0)
	{
		return cls;
	}

    //  查找缓存
    //bool rv = find(cls, ea);
    //if (rv)
    //{
        //return cls;
    //}

    quint16 tpMask = get_word(ea + offs_tpMask);
    if (tpMask & TM_IS_CLASS)
    {
        quint16 nameOffset = get_word(ea + offs_tpName);
        ea_t nameEA = ea + nameOffset;

        for (char data = get_byte(nameEA); data != 0; data = get_byte(nameEA))
        {
            cls.name += data;
            nameEA++;
        }
        if (cls.name.toLatin1().constData() == "")//  此处禁止使用cls.name.isEmpty()函数判断，因为cls.name.size不为0
        {
            return cls;
        }
        //msg("[0x%x]class: [%s]\n", cls.beginEA, cls.name.toLatin1().constData());

        //  假，则不再继续获取基类信息
        if (!flag)
        {
            return cls;
        }


        quint32 tpcFlags = get_long(ea + offs_tpcFlags);
        if (tpcFlags & CF_HAS_DTOR)
        {
            quint32 pfn = get_long(ea + offs_DtorAddr);
            if (pfn)
            {
                //msg("class name: %s\n", name);
            }
        }

        if (tpcFlags & CF_DELPHICLASS)
        {
            flag = false;
        }

        quint16 tpcBaseListOffset = get_word(ea + 16);
        if (tpcBaseListOffset != 0)
        {
            while (1)
            {
                quint32 baseClsAddr = get_long(ea + tpcBaseListOffset);

                if (baseClsAddr != BADADDR && baseClsAddr != 0)
                {
                    JInherit inherit;
                    inherit.jit = JIT_Normal;
                    inherit.clsinfo = new JClassInfo;
                    //msg("[Normal]->");
                    *(inherit.clsinfo) = getClassInfo(baseClsAddr, flag);

                    //msg(">----jit: %d, clsinfo: %p\n", inherit.jit, inherit.clsinfo);

                        //JInherit temp = inherit;
                    if (inherit.isValid())
                    {
                        //JInherit temp = inherit;
                        cls.inheritList.append(inherit);
                    }

                    tpcBaseListOffset += 4;		//  long
                }
                else
                {
                    break;
                }
            }
        }

        quint16 tpcVBaseListOffset = get_word(ea + 18);
        if (tpcVBaseListOffset != 0)
        {
            while (1)
            {
                quint32 vbaseClsAddr = get_long(ea + tpcVBaseListOffset);
                if (vbaseClsAddr != BADADDR && vbaseClsAddr != 0)
                {
                    JInherit inherit;
                    inherit.jit = JIT_Virtual;
                    //msg("[Virtual]->");
                    inherit.clsinfo = new JClassInfo;
                    *(inherit.clsinfo) = getClassInfo(vbaseClsAddr, flag);

                    if (inherit.isValid())
                        cls.inheritList.append(inherit);

                    tpcVBaseListOffset += 4;	//  long
                }
                else
                {
                    break;
                }
            }
        }
    }

    return cls;
}

bool JBcbRtti::find(JClassInfo &cls, ea_t ea, const JClassInfoList &from)
{
    foreach (const JClassInfo &temp, from)
    {
        if (temp.beginEA == ea)
        {
            cls = temp;
            return true;
        }

        return find(cls, ea, temp.inheritList);
    }

    return false;
}

bool JBcbRtti::find(JClassInfo &cls, ea_t ea, const JInheritList &from)
{
    foreach (const JInherit &temp, from)
    {
		if (temp.clsinfo == NULL)
		{
			continue;
		}
        if (temp.clsinfo->beginEA == ea)
        {
            cls = *temp.clsinfo;
            return true;
        }

        return find(cls, ea, temp.clsinfo->inheritList);
    }

    return false;
}

JBcbRtti::JBcbRtti(QObject *parent) : QObject(parent)
{

}
