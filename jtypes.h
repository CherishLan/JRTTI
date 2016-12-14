#ifndef JSTRUCTURE_H
#define JSTRUCTURE_H

#include <QObject>


#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <bytes.hpp>

//
#define offs_tpMask		0x00000004L
#define offs_tpName		0x00000006L
#define offs_tpBase		0x00000008L
#define offs_tpcFlags	0x0000000CL
#define offs_Elements	0x0000000CL
#define offs_Size		0x00000010L
#define offs_DtorAddr	0x00000028L
#define offs_FullSize	0x0000002EL

//	tpMask flags
#define TM_IS_STRUCT    0x0001
#define TM_IS_CLASS     0x0002
#define TM_IS_UNK04     0x0004
#define TM_IS_UNK08     0x0008
#define TM_IS_PTR       0x0010
#define TM_IS_REF       0x0020
#define TM_IS_VOIDPTR   0x0040
#define TM_LOCALTYPE    0x0080
#define TM_IS_CONST     0x0100
#define TM_IS_VOLATILE  0x0200
#define TM_IS_ARRAY     0x0400

//	Class flags tpcFlags follow:
#define CF_HAS_CTOR     0x00000001
#define CF_HAS_DTOR     0x00000002
#define CF_HAS_BASES    0x00000004
#define CF_HAS_VBASES   0x00000008
#define CF_HAS_VTABPTR  0x00000010
#define CF_HAS_VIRTDT   0x00000020
#define CF_HAS_RTTI     0x00000040
#define CF_DELPHICLASS  0x00000080
#define CF_HAS_FARVPTR  0x00001000
#define CF_HAS_GUID     0x00002000  // The tpcGuid field is valid and filled in

//	kinds of name
#define tkSimple 1
#define tkPtr 2
#define tkRef 3
#define tkArr 4

#include <QDebug>


struct stru_JInherit;
struct stru_JClassInfo;

enum JInheritType
{
    JIT_Normal,
    JIT_Virtual
};

typedef struct stru_JInherit
{
    stru_JClassInfo			*clsinfo;		//	类信息
    JInheritType			jit;			//  基类被继承的方式

    stru_JInherit();
    stru_JInherit(const stru_JInherit &other);
    virtual ~stru_JInherit();

    /**
     * @brief operator =
     * @param other
     * @return
     */
    stru_JInherit &operator =(const stru_JInherit &other);

    /**
     * @brief isValid
     * @return
     */
    bool isValid() const;
} JInherit;

struct JInheritList : public QList<JInherit>
{
public:
    QString toText() const;

    JInheritList &operator =(const JInheritList &other);
};

typedef struct stru_JClassInfo
{
    ea_t					beginEA;		//  起始地址
    QString					name;			//  类名
    JInheritList			inheritList;	//	继承信息

    stru_JClassInfo();
    stru_JClassInfo(const stru_JClassInfo &other);
    virtual ~stru_JClassInfo();

    /**
     * @brief operator =
     * @param other
     * @return
     */
    stru_JClassInfo &operator =(const stru_JClassInfo &other);

    /**
     * @brief isValid
     * @return
     */
    bool isValid() const;

    /**
     * @brief toText
     * @return
     */
    QString toText() const;
} JClassInfo;


struct JClassInfoList : public QList<JClassInfo>
{
public:
    QString toText() const;

    JClassInfoList &operator =(const JClassInfoList &other);
};


struct JEA
{
    ea_t			beginEA;
    ea_t			endEA;

    JEA();
    JEA(const JEA &other);
    ~JEA();

    JEA &operator =(const JEA &other);
};

typedef QList<JEA>		JEAList;

#endif // JSTRUCTURE_H
