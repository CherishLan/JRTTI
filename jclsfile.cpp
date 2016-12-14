#include "jclsfile.h"

void JClsFile::generateFiles(const JClassInfo &cls, const QString &targetDirPath)
{
    QString filename = targetDirPath + "/";
    if (cls.name.indexOf("::") != -1)
    {
        filename += cls.name.section("::", 1, 1).toLower();
    }
    else
    {
        filename += cls.name.toLower();
    }
    QString filenameHeader = filename + ".h";
    QString filenameSource = filename + ".cpp";

    QFile fileHeader(filenameHeader);
    QFile fileSource(filenameSource);

    if (fileHeader.open(QIODevice::WriteOnly))
    {
        QString text;

        /**	#ifndef __NAMESPACE_NAME_H__
          * #define	__NAMESPACE_NAME_H__
          *
          * #include "inherit.h"
          *
          * namespace NAMESPACE
          * {
          *
          * class Name : public Inherit
          * {
          * public:
          * 	explicit Name();
          * 	~Name();
          * };
          *
          * }
          *
          * #endif
          */

        QString namespaceName;
        QString name;
        if (cls.name.indexOf("::") != -1)
        {
            name = cls.name.section("::", 0, 0);
            namespaceName = cls.name.section("::", 1, 1);
        }
        else
        {
            name = cls.name;
        }

        QString macro;
        if (namespaceName.isEmpty())
        {
            macro = "__" + name.toUpper() + "_H__";
        }
        else
        {
            macro = "__" + namespaceName.toUpper() + "_" + name.toUpper() + "_H__";
        }

        text += "\n#ifndef " + macro;
        text += "\n#define " + macro;

        //  include inherits
        foreach (const JInherit &inherit, cls.inheritList)
        {
            if (inherit.clsinfo != NULL)
            {
                text += "\n\n#include \"";
                if (inherit.clsinfo->name.indexOf("::") != -1)
                {
                    text += inherit.clsinfo->name.section("::", 1, 1).toLower();
                }
                else
                {
                    text += inherit.clsinfo->name.toLower();
                }
                text += ".h\"";
            }
        }

        if (!namespaceName.isEmpty())
        {
            text += "\n\nnamespace " + namespaceName + " {";
        }

        text += "\n\nclass " + name;
        if (cls.inheritList.count() > 0)
        {
            text += " : ";
            foreach (const JInherit &inherit, cls.inheritList)
            {
                text += (inherit.jit == JIT_Normal ? "" : "virtual ") + QString("public ");
                text += inherit.clsinfo->name + ", ";
            }
            text.remove(text.length() - 2, 2);
        }
        text += "\n{";
        text += "\npublic:\n    " + name + "();";
        text += "\n    ~" + name + "();\n};  //  end of class " + name;

        if (!namespaceName.isEmpty())
        {
            text += "\n\n}   //  end of namespace " + namespaceName;
        }
        text += "\n\n#endif  //  " + macro;

        fileHeader.write(text.toLatin1());
        fileHeader.close();
    }
    else
    {
        msg("Failed to generate [%x]%s : %s\n", cls.beginEA, filenameHeader.toLatin1().constData(), fileHeader.errorString().toLatin1().constData());
    }


    if (fileSource.open(QIODevice::WriteOnly))
    {
        QString text;

        /**
          * #include "name.h"
          *
          * namespace NAMESPACE {
          *
          * Name::Name()
          * {
          *
          * }
          * Name::~Name()
          * {
          *
          * }
          *
          * }
          *
          */

        QString namespaceName;
        QString name;
        if (cls.name.indexOf("::") != -1)
        {
            name = cls.name.section("::", 0, 0);
            namespaceName = cls.name.section("::", 1, 1);
        }
        else
        {
            name = cls.name;
        }

        text += "\n#include \"" + name.toLower() + ".h\"";

        if (!namespaceName.isEmpty())
        {
            text += "\n\nnamespace " + namespaceName + " {";
        }

        text += "\n\n" + name + "::" + name + "()\n{\n\n}";
        text += "\n\n" + name + "::~" + name + "()\n{\n\n}";

        if (!namespaceName.isEmpty())
        {
            text += "\n\n}   //  end of namespace " + namespaceName;
        }

        fileSource.write(text.toLatin1());
        fileSource.close();
    }
    else
    {
        msg("Failed to generate [%x]%s : %s\n", cls.beginEA, filenameSource.toLatin1().constData(), fileSource.errorString().toLatin1().constData());
    }

    generateFiles(cls.inheritList, targetDirPath);
}

void JClsFile::generateFiles(const JClassInfoList &clsList, const QString &targetDirPath)
{
    foreach (const JClassInfo &cls, clsList)
    {
        generateFiles(cls, targetDirPath);
    }
}

void JClsFile::generateFiles(const JInherit &inherit, const QString &targetDirPath)
{
    if (inherit.isValid())
    {
        generateFiles(*inherit.clsinfo, targetDirPath);
    }
}

void JClsFile::generateFiles(const JInheritList &inheritList, const QString &targetDirPath)
{
    foreach (const JInherit &inherit, inheritList)
    {
        generateFiles(inherit, targetDirPath);
    }
}

JClsFile::JClsFile()
{

}
