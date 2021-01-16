#include "overview.h"
#include <assert.h>

Overview::Overview(QTableWidget* table) : _tableWidget(table)
{
    assert(_tableWidget != nullptr);

   _tableWidget->setItem(0, 1, new QTableWidgetItem(_name.c_str()));
   _tableWidget->setItem(1, 1, new QTableWidgetItem(_cash));
   _tableWidget->setItem(2, 1, new QTableWidgetItem(_investment));
   _tableWidget->setItem(3, 1, new QTableWidgetItem(_liabilities));
   _tableWidget->setItem(4, 1, new QTableWidgetItem(_netWorth));
}
