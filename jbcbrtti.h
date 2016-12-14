#ifndef JBCBRTTI_H
#define JBCBRTTI_H

#include "jtypes.h"

#include <QObject>
#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <bytes.hpp>


class JBcbRtti : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief getClassInfo
     * @param ea
     * @return
     */
    static JClassInfo getClassInfo(ea_t ea);

    /**
     * @brief find			默认查找当前缓存
     * @param cls
     * @param ea
     * @return
     */
    static bool find(JClassInfo &cls, ea_t ea);

private:
    /**
     * @brief getClassInfo
     * @param ea
     * @param flag			是否继续获取更上一层的基类信息
     * @return
     */
    static JClassInfo getClassInfo(ea_t ea, bool flag);

    /**
     * @brief clearBuffer	清空缓存，对于不同的可执行文件进行操作之前，需要清空缓�?
     */
    static void clearBuffer();

    /**
     * @brief find
     * @param cls			查找结果
     * @param ea
     * @param from			指定去哪查找
     * @return
     */
    static bool find(JClassInfo &cls, ea_t ea, const JClassInfoList &from);

    /**
     * @brief find
     * @param cls
     * @param ea
     * @param from
     * @return
     */
    static bool find(JClassInfo &cls, ea_t ea, const JInheritList &from);

private:
    explicit JBcbRtti(QObject *parent = 0);

signals:

public slots:

private:
    static JClassInfoList			m_buffer;			//  缓存
};

#endif // JBCBRTTI_H
