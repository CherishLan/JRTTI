#ifndef JCLSFILE_H
#define JCLSFILE_H

#include "jtypes.h"

#include <QFile>
#include <QObject>
#include <QString>


class JClsFile
{

public:
    static void generateFiles(const JClassInfo &cls, const QString &targetDirPath);
    static void generateFiles(const JClassInfoList &clsList, const QString &targetDirPath);
    static void generateFiles(const JInherit &inherit, const QString &targetDirPath);
    static void generateFiles(const JInheritList &inheritList, const QString &targetDirPath);

public:
    explicit JClsFile();
};

#endif // JCLSFILE_H
