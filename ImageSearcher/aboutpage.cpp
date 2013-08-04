#include "aboutpage.h"
#include <QtGui>

AboutPage::AboutPage(QWidget *parent) :
    QWidget(parent)
{
    QLabel *aboutLabel = new QLabel;
    aboutLabel->setAlignment(Qt::AlignTop);
    aboutLabel->setText(tr("<p>&nbsp;</p><p>&nbsp;</p>"
                           "<p align=center><font size=6><b>Face Searcher</b></font></p></br>"
                           "<p><font size=4><b>Author&nbsp;:&nbsp;&nbsp;</b><u>HelloYou</u></font></p>"
                           "<p><font size=4><b>Blog&nbsp;:&nbsp;&nbsp;</b><a href=http://blog.sina.com.cn/zhenzhenhello>http://blog.sina.com.cn/zhenzhenhello</a></font></p>"
                           "<p><font size=4><b>E-Mail:&nbsp;&nbsp;</b><a href=mailto://HelloYou2012@gmail.com>HelloYou2012@gmail.com</a></font></p>"
                           "<p><font size=4><b>Q Q:&nbsp;&nbsp;</b>865702942</font></p>"
                           "<p><font size=4><b>Version:&nbsp;&nbsp;</b>1.0.0</font></p>"));
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addSpacing(100);
    mainLayout->addWidget(aboutLabel);
    mainLayout->addSpacing(100);
    setLayout(mainLayout);
}
