/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mapwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    MapWidget *LeftWidget;
    QWidget *RightWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *TravelerLayout1;
    QPushButton *addTravelerButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *TravelerLayout;
    QLabel *TravelerChoseLabel;
    QComboBox *TravelerComboBox;
    QVBoxLayout *ComboLayout2;
    QHBoxLayout *StrategyLayout;
    QLabel *StrategyLabel;
    QComboBox *StrategyComboBox;
    QHBoxLayout *StartCityLayout;
    QLabel *StartLabel;
    QComboBox *StartComboBox;
    QHBoxLayout *DestinationCityLayout;
    QLabel *DestinationLabel;
    QComboBox *DestinationComboBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *ThroughCityCheckBox;
    QFrame *ThroughCityFrame;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *CityThroughGridLayout;
    QCheckBox *city4cbox;
    QCheckBox *city9cbox;
    QCheckBox *city3cbox;
    QCheckBox *city0cbox;
    QCheckBox *city2cbox;
    QCheckBox *city5cbox;
    QCheckBox *city6cbox;
    QCheckBox *city7cbox;
    QCheckBox *city8cbox;
    QCheckBox *city1cbox;
    QCheckBox *city10cbox;
    QCheckBox *city11cbox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *TimeEditLayout4;
    QHBoxLayout *CurrentTimeLayout;
    QLabel *TimeLabel;
    QDateTimeEdit *StartDateTimeEdit;
    QHBoxLayout *DeadlineLayout;
    QLabel *DeadlineLabel;
    QDateTimeEdit *DeadlineDateTimeEdit;
    QHBoxLayout *StartButtonLayout5;
    QSpacerItem *horizontalSpacer;
    QPushButton *StartButton;
    QVBoxLayout *PathListLayout6;
    QLabel *SolutionLabel;
    QScrollArea *PathList;
    QWidget *PathListContent;
    QVBoxLayout *FareTimeDurLayout7;
    QHBoxLayout *TotalFareLayout;
    QLabel *FareLabel;
    QLineEdit *FareEdit;
    QHBoxLayout *TotalTimeLayout;
    QLabel *TotalTimeLabel;
    QLineEdit *TotalTimeEdit;
    QHBoxLayout *DurationLayout;
    QLabel *DurationLabel;
    QLineEdit *DurationText;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1280, 720);
        LeftWidget = new MapWidget(Widget);
        LeftWidget->setObjectName(QStringLiteral("LeftWidget"));
        LeftWidget->setGeometry(QRect(11, 11, 928, 698));
        RightWidget = new QWidget(Widget);
        RightWidget->setObjectName(QStringLiteral("RightWidget"));
        RightWidget->setGeometry(QRect(968, 11, 301, 691));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(RightWidget->sizePolicy().hasHeightForWidth());
        RightWidget->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(RightWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        TravelerLayout1 = new QHBoxLayout();
        TravelerLayout1->setSpacing(6);
        TravelerLayout1->setObjectName(QStringLiteral("TravelerLayout1"));
        addTravelerButton = new QPushButton(RightWidget);
        addTravelerButton->setObjectName(QStringLiteral("addTravelerButton"));
        addTravelerButton->setMinimumSize(QSize(70, 0));
        addTravelerButton->setMaximumSize(QSize(59, 16777215));

        TravelerLayout1->addWidget(addTravelerButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        TravelerLayout1->addItem(horizontalSpacer_3);

        TravelerLayout = new QHBoxLayout();
        TravelerLayout->setSpacing(6);
        TravelerLayout->setObjectName(QStringLiteral("TravelerLayout"));
        TravelerChoseLabel = new QLabel(RightWidget);
        TravelerChoseLabel->setObjectName(QStringLiteral("TravelerChoseLabel"));

        TravelerLayout->addWidget(TravelerChoseLabel);

        TravelerComboBox = new QComboBox(RightWidget);
        TravelerComboBox->setObjectName(QStringLiteral("TravelerComboBox"));

        TravelerLayout->addWidget(TravelerComboBox);


        TravelerLayout1->addLayout(TravelerLayout);


        verticalLayout->addLayout(TravelerLayout1);

        ComboLayout2 = new QVBoxLayout();
        ComboLayout2->setSpacing(6);
        ComboLayout2->setObjectName(QStringLiteral("ComboLayout2"));
        StrategyLayout = new QHBoxLayout();
        StrategyLayout->setSpacing(6);
        StrategyLayout->setObjectName(QStringLiteral("StrategyLayout"));
        StrategyLabel = new QLabel(RightWidget);
        StrategyLabel->setObjectName(QStringLiteral("StrategyLabel"));

        StrategyLayout->addWidget(StrategyLabel);

        StrategyComboBox = new QComboBox(RightWidget);
        StrategyComboBox->setObjectName(QStringLiteral("StrategyComboBox"));

        StrategyLayout->addWidget(StrategyComboBox);


        ComboLayout2->addLayout(StrategyLayout);

        StartCityLayout = new QHBoxLayout();
        StartCityLayout->setSpacing(6);
        StartCityLayout->setObjectName(QStringLiteral("StartCityLayout"));
        StartLabel = new QLabel(RightWidget);
        StartLabel->setObjectName(QStringLiteral("StartLabel"));

        StartCityLayout->addWidget(StartLabel);

        StartComboBox = new QComboBox(RightWidget);
        StartComboBox->setObjectName(QStringLiteral("StartComboBox"));

        StartCityLayout->addWidget(StartComboBox);


        ComboLayout2->addLayout(StartCityLayout);

        DestinationCityLayout = new QHBoxLayout();
        DestinationCityLayout->setSpacing(6);
        DestinationCityLayout->setObjectName(QStringLiteral("DestinationCityLayout"));
        DestinationLabel = new QLabel(RightWidget);
        DestinationLabel->setObjectName(QStringLiteral("DestinationLabel"));

        DestinationCityLayout->addWidget(DestinationLabel);

        DestinationComboBox = new QComboBox(RightWidget);
        DestinationComboBox->setObjectName(QStringLiteral("DestinationComboBox"));

        DestinationCityLayout->addWidget(DestinationComboBox);


        ComboLayout2->addLayout(DestinationCityLayout);


        verticalLayout->addLayout(ComboLayout2);


        verticalLayout_3->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        ThroughCityCheckBox = new QCheckBox(RightWidget);
        ThroughCityCheckBox->setObjectName(QStringLiteral("ThroughCityCheckBox"));

        horizontalLayout->addWidget(ThroughCityCheckBox);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);

        ThroughCityFrame = new QFrame(RightWidget);
        ThroughCityFrame->setObjectName(QStringLiteral("ThroughCityFrame"));
        ThroughCityFrame->setAutoFillBackground(true);
        ThroughCityFrame->setStyleSheet(QStringLiteral(""));
        ThroughCityFrame->setFrameShape(QFrame::StyledPanel);
        ThroughCityFrame->setFrameShadow(QFrame::Plain);
        ThroughCityFrame->setLineWidth(5);
        ThroughCityFrame->setMidLineWidth(5);
        horizontalLayout_2 = new QHBoxLayout(ThroughCityFrame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        CityThroughGridLayout = new QGridLayout();
        CityThroughGridLayout->setSpacing(6);
        CityThroughGridLayout->setObjectName(QStringLiteral("CityThroughGridLayout"));
        CityThroughGridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        city4cbox = new QCheckBox(ThroughCityFrame);
        city4cbox->setObjectName(QStringLiteral("city4cbox"));

        CityThroughGridLayout->addWidget(city4cbox, 1, 1, 1, 1);

        city9cbox = new QCheckBox(ThroughCityFrame);
        city9cbox->setObjectName(QStringLiteral("city9cbox"));

        CityThroughGridLayout->addWidget(city9cbox, 3, 0, 1, 1);

        city3cbox = new QCheckBox(ThroughCityFrame);
        city3cbox->setObjectName(QStringLiteral("city3cbox"));

        CityThroughGridLayout->addWidget(city3cbox, 1, 0, 1, 1);

        city0cbox = new QCheckBox(ThroughCityFrame);
        city0cbox->setObjectName(QStringLiteral("city0cbox"));

        CityThroughGridLayout->addWidget(city0cbox, 0, 0, 1, 1);

        city2cbox = new QCheckBox(ThroughCityFrame);
        city2cbox->setObjectName(QStringLiteral("city2cbox"));

        CityThroughGridLayout->addWidget(city2cbox, 0, 2, 1, 1);

        city5cbox = new QCheckBox(ThroughCityFrame);
        city5cbox->setObjectName(QStringLiteral("city5cbox"));

        CityThroughGridLayout->addWidget(city5cbox, 1, 2, 1, 1);

        city6cbox = new QCheckBox(ThroughCityFrame);
        city6cbox->setObjectName(QStringLiteral("city6cbox"));

        CityThroughGridLayout->addWidget(city6cbox, 2, 0, 1, 1);

        city7cbox = new QCheckBox(ThroughCityFrame);
        city7cbox->setObjectName(QStringLiteral("city7cbox"));

        CityThroughGridLayout->addWidget(city7cbox, 2, 1, 1, 1);

        city8cbox = new QCheckBox(ThroughCityFrame);
        city8cbox->setObjectName(QStringLiteral("city8cbox"));

        CityThroughGridLayout->addWidget(city8cbox, 2, 2, 1, 1);

        city1cbox = new QCheckBox(ThroughCityFrame);
        city1cbox->setObjectName(QStringLiteral("city1cbox"));

        CityThroughGridLayout->addWidget(city1cbox, 0, 1, 1, 1);

        city10cbox = new QCheckBox(ThroughCityFrame);
        city10cbox->setObjectName(QStringLiteral("city10cbox"));

        CityThroughGridLayout->addWidget(city10cbox, 3, 1, 1, 1);

        city11cbox = new QCheckBox(ThroughCityFrame);
        city11cbox->setObjectName(QStringLiteral("city11cbox"));

        CityThroughGridLayout->addWidget(city11cbox, 3, 2, 1, 1);


        horizontalLayout_2->addLayout(CityThroughGridLayout);


        verticalLayout_4->addWidget(ThroughCityFrame);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        TimeEditLayout4 = new QVBoxLayout();
        TimeEditLayout4->setSpacing(6);
        TimeEditLayout4->setObjectName(QStringLiteral("TimeEditLayout4"));
        CurrentTimeLayout = new QHBoxLayout();
        CurrentTimeLayout->setSpacing(6);
        CurrentTimeLayout->setObjectName(QStringLiteral("CurrentTimeLayout"));
        TimeLabel = new QLabel(RightWidget);
        TimeLabel->setObjectName(QStringLiteral("TimeLabel"));

        CurrentTimeLayout->addWidget(TimeLabel);

        StartDateTimeEdit = new QDateTimeEdit(RightWidget);
        StartDateTimeEdit->setObjectName(QStringLiteral("StartDateTimeEdit"));

        CurrentTimeLayout->addWidget(StartDateTimeEdit);


        TimeEditLayout4->addLayout(CurrentTimeLayout);

        DeadlineLayout = new QHBoxLayout();
        DeadlineLayout->setSpacing(6);
        DeadlineLayout->setObjectName(QStringLiteral("DeadlineLayout"));
        DeadlineLabel = new QLabel(RightWidget);
        DeadlineLabel->setObjectName(QStringLiteral("DeadlineLabel"));

        DeadlineLayout->addWidget(DeadlineLabel);

        DeadlineDateTimeEdit = new QDateTimeEdit(RightWidget);
        DeadlineDateTimeEdit->setObjectName(QStringLiteral("DeadlineDateTimeEdit"));

        DeadlineLayout->addWidget(DeadlineDateTimeEdit);


        TimeEditLayout4->addLayout(DeadlineLayout);


        verticalLayout_2->addLayout(TimeEditLayout4);

        StartButtonLayout5 = new QHBoxLayout();
        StartButtonLayout5->setSpacing(6);
        StartButtonLayout5->setObjectName(QStringLiteral("StartButtonLayout5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        StartButtonLayout5->addItem(horizontalSpacer);

        StartButton = new QPushButton(RightWidget);
        StartButton->setObjectName(QStringLiteral("StartButton"));
        StartButton->setEnabled(true);
        StartButton->setMinimumSize(QSize(62, 0));
        StartButton->setMaximumSize(QSize(59, 16777215));

        StartButtonLayout5->addWidget(StartButton);


        verticalLayout_2->addLayout(StartButtonLayout5);


        verticalLayout_4->addLayout(verticalLayout_2);

        PathListLayout6 = new QVBoxLayout();
        PathListLayout6->setSpacing(6);
        PathListLayout6->setObjectName(QStringLiteral("PathListLayout6"));
        SolutionLabel = new QLabel(RightWidget);
        SolutionLabel->setObjectName(QStringLiteral("SolutionLabel"));

        PathListLayout6->addWidget(SolutionLabel);

        PathList = new QScrollArea(RightWidget);
        PathList->setObjectName(QStringLiteral("PathList"));
        PathList->setMinimumSize(QSize(0, 0));
        PathList->setMaximumSize(QSize(16777215, 256));
        PathList->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        PathList->setMidLineWidth(1);
        PathList->setWidgetResizable(true);
        PathListContent = new QWidget();
        PathListContent->setObjectName(QStringLiteral("PathListContent"));
        PathListContent->setGeometry(QRect(0, 0, 275, 158));
        PathList->setWidget(PathListContent);

        PathListLayout6->addWidget(PathList);


        verticalLayout_4->addLayout(PathListLayout6);

        FareTimeDurLayout7 = new QVBoxLayout();
        FareTimeDurLayout7->setSpacing(6);
        FareTimeDurLayout7->setObjectName(QStringLiteral("FareTimeDurLayout7"));
        TotalFareLayout = new QHBoxLayout();
        TotalFareLayout->setSpacing(6);
        TotalFareLayout->setObjectName(QStringLiteral("TotalFareLayout"));
        FareLabel = new QLabel(RightWidget);
        FareLabel->setObjectName(QStringLiteral("FareLabel"));

        TotalFareLayout->addWidget(FareLabel);

        FareEdit = new QLineEdit(RightWidget);
        FareEdit->setObjectName(QStringLiteral("FareEdit"));

        TotalFareLayout->addWidget(FareEdit);


        FareTimeDurLayout7->addLayout(TotalFareLayout);

        TotalTimeLayout = new QHBoxLayout();
        TotalTimeLayout->setSpacing(6);
        TotalTimeLayout->setObjectName(QStringLiteral("TotalTimeLayout"));
        TotalTimeLabel = new QLabel(RightWidget);
        TotalTimeLabel->setObjectName(QStringLiteral("TotalTimeLabel"));

        TotalTimeLayout->addWidget(TotalTimeLabel);

        TotalTimeEdit = new QLineEdit(RightWidget);
        TotalTimeEdit->setObjectName(QStringLiteral("TotalTimeEdit"));

        TotalTimeLayout->addWidget(TotalTimeEdit);


        FareTimeDurLayout7->addLayout(TotalTimeLayout);

        DurationLayout = new QHBoxLayout();
        DurationLayout->setSpacing(6);
        DurationLayout->setObjectName(QStringLiteral("DurationLayout"));
        DurationLabel = new QLabel(RightWidget);
        DurationLabel->setObjectName(QStringLiteral("DurationLabel"));

        DurationLayout->addWidget(DurationLabel);

        DurationText = new QLineEdit(RightWidget);
        DurationText->setObjectName(QStringLiteral("DurationText"));

        DurationLayout->addWidget(DurationText);


        FareTimeDurLayout7->addLayout(DurationLayout);


        verticalLayout_4->addLayout(FareTimeDurLayout7);

        ThroughCityFrame->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        addTravelerButton->setText(QApplication::translate("Widget", "\346\267\273\345\212\240\346\227\205\345\256\242", 0));
        TravelerChoseLabel->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\346\227\205\345\256\242\357\274\232", 0));
        StrategyLabel->setText(QApplication::translate("Widget", "\347\255\226\347\225\245\351\200\211\346\213\251\357\274\232", 0));
        StrategyComboBox->clear();
        StrategyComboBox->insertItems(0, QStringList()
         << QApplication::translate("Widget", "\350\264\271\347\224\250\346\234\200\345\260\221", 0)
         << QApplication::translate("Widget", "\350\200\227\346\227\266\346\234\200\347\237\255", 0)
         << QApplication::translate("Widget", "\351\231\220\346\227\266\350\264\271\347\224\250\346\234\200\345\260\221", 0)
        );
        StartLabel->setText(QApplication::translate("Widget", "\345\247\213\345\217\221\345\234\260\357\274\232", 0));
        StartComboBox->clear();
        StartComboBox->insertItems(0, QStringList()
         << QApplication::translate("Widget", "\345\214\227\344\272\254", 0)
         << QApplication::translate("Widget", "\344\270\212\346\265\267", 0)
         << QApplication::translate("Widget", "\350\245\277\345\256\211", 0)
         << QApplication::translate("Widget", "\346\255\246\346\261\211", 0)
         << QApplication::translate("Widget", "\346\267\261\345\234\263", 0)
         << QApplication::translate("Widget", "\351\203\221\345\267\236", 0)
         << QApplication::translate("Widget", "\346\265\267\345\215\227", 0)
         << QApplication::translate("Widget", "\346\213\211\350\220\250", 0)
         << QApplication::translate("Widget", "\347\272\275\347\272\246", 0)
         << QApplication::translate("Widget", "\351\246\226\345\260\224", 0)
         << QApplication::translate("Widget", "\345\223\210\345\260\224\346\273\250", 0)
         << QApplication::translate("Widget", "\350\216\253\346\226\257\347\247\221", 0)
        );
        DestinationLabel->setText(QApplication::translate("Widget", "\347\233\256\347\232\204\345\234\260\357\274\232", 0));
        DestinationComboBox->clear();
        DestinationComboBox->insertItems(0, QStringList()
         << QApplication::translate("Widget", "\345\214\227\344\272\254", 0)
         << QApplication::translate("Widget", "\344\270\212\346\265\267", 0)
         << QApplication::translate("Widget", "\350\245\277\345\256\211", 0)
         << QApplication::translate("Widget", "\346\255\246\346\261\211", 0)
         << QApplication::translate("Widget", "\346\267\261\345\234\263", 0)
         << QApplication::translate("Widget", "\351\203\221\345\267\236", 0)
         << QApplication::translate("Widget", "\346\265\267\345\215\227", 0)
         << QApplication::translate("Widget", "\346\213\211\350\220\250", 0)
         << QApplication::translate("Widget", "\347\272\275\347\272\246", 0)
         << QApplication::translate("Widget", "\351\246\226\345\260\224", 0)
         << QApplication::translate("Widget", "\345\223\210\345\260\224\346\273\250", 0)
         << QApplication::translate("Widget", "\350\216\253\346\226\257\347\247\221", 0)
        );
        ThroughCityCheckBox->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\351\200\224\345\276\204\345\237\216\345\270\202", 0));
        city4cbox->setText(QApplication::translate("Widget", "\346\267\261\345\234\263", 0));
        city9cbox->setText(QApplication::translate("Widget", "\351\246\226\345\260\224", 0));
        city3cbox->setText(QApplication::translate("Widget", "\346\255\246\346\261\211", 0));
        city0cbox->setText(QApplication::translate("Widget", "\345\214\227\344\272\254", 0));
        city2cbox->setText(QApplication::translate("Widget", "\350\245\277\345\256\211", 0));
        city5cbox->setText(QApplication::translate("Widget", "\351\203\221\345\267\236", 0));
        city6cbox->setText(QApplication::translate("Widget", "\346\265\267\345\215\227", 0));
        city7cbox->setText(QApplication::translate("Widget", "\346\213\211\350\220\250", 0));
        city8cbox->setText(QApplication::translate("Widget", "\347\272\275\347\272\246", 0));
        city1cbox->setText(QApplication::translate("Widget", "\344\270\212\346\265\267", 0));
        city10cbox->setText(QApplication::translate("Widget", "\345\223\210\345\260\224\346\273\250", 0));
        city11cbox->setText(QApplication::translate("Widget", "\350\216\253\346\226\257\347\247\221", 0));
        TimeLabel->setText(QApplication::translate("Widget", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", 0));
        DeadlineLabel->setText(QApplication::translate("Widget", "\346\210\252\346\255\242\346\227\266\351\227\264\357\274\232", 0));
        StartButton->setText(QApplication::translate("Widget", "\345\274\200\345\247\213", 0));
        SolutionLabel->setText(QApplication::translate("Widget", "\350\247\243\345\206\263\346\226\271\346\241\210\357\274\232", 0));
        FareLabel->setText(QApplication::translate("Widget", "\351\242\204\350\256\241\350\264\271\347\224\250\357\274\232", 0));
        TotalTimeLabel->setText(QApplication::translate("Widget", "\351\242\204\350\256\241\346\227\266\351\227\264\357\274\232", 0));
        DurationLabel->setText(QApplication::translate("Widget", "\345\267\262\347\224\250\346\227\266\351\227\264\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
