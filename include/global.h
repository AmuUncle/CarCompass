#ifndef GLOBAL_H
#define GLOBAL_H


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "iconhelper.h"

#include <QDebug>
#include <QtWidgets>
#include <QPainter>
#include <QMouseEvent>

#define GLOBAL_FUNC \
        void CreateAllChildWnd(); \
        void InitCtrl(); \
        void InitSolts(); \
        void Relayout();

#define GLOBAL_FUNC_RUN \
        CreateAllChildWnd(); \
        InitCtrl(); \
        InitSolts(); \
        Relayout();

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

enum EMainTabTitle
{
    TABTITLE_MAIN = 0,       // 消息会话
    TABTITLE_DROPBOX = 1,      // 通讯录
    TABTITLE_CALL = 2,      // 日程
    TABTITLE_MUSIC = 3,       // 工作台
    TABTITLE_COMPASS = 4,      // 微文档
    TABTITLE_WEDRIVE = 5,      // 微盘
    TABTITLE_MEETING = 6,      // 会议
};

#endif // GLOBAL_H
