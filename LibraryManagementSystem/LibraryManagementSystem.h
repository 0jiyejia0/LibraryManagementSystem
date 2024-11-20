#pragma once

#ifndef LIBRARYMANAGEMENTSYSTEM_H
#define LIBRARYMANAGEMENTSYSTEM_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTreeWidgetItem>
#include "BookSet.h"
#include "StudentSet.h"
#include "SBList.h"

namespace Ui {
    class LibraryManagementSystem;
}

class LibraryManagementSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibraryManagementSystem(QWidget* parent = nullptr);
    ~LibraryManagementSystem();

private slots:
    void onTreeItemClicked(QTreeWidgetItem* item, int column);

    void on_pushButtonAddBook_clicked();
    void on_pushButtonDeleteBook_clicked();
    void on_pushButtonFindBook_clicked();
    void on_pushButtonSaveChanges_clicked();
    void on_pushButtonSearchBook_clicked();

    void on_pushButtonAddStudent_clicked();
    void on_pushButtonDeleteStudent_clicked();
    void on_pushButtonFindStudent_clicked();
    void on_pushButtonSaveStudentChanges_clicked();
    void on_pushButtonSearchStudent_clicked();

    void on_pushButtonBorrowBook_clicked();
    void on_pushButtonReturnBook_clicked();
    void on_pushButtonSearchStudent_clicked_2();
    void on_pushButtonSearchBook_clicked_2();
    void on_studentSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void on_bookSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

    void on_pushButtonSearchStudent_clicked_3();
    void on_studentSelectionChanged_2(const QItemSelection& selected, const QItemSelection& deselected);
    void updateStudentBorrowedBooksTable(const QString& studentNo);
    void on_borrowedBookSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void on_pushButtonSearchBorrowedBook_clicked();
    
    void updateOverdueRecordsTable(); // 更新逾期借阅记录表格

    void on_pushButtonSearchByMajor_clicked(); // 根据专业查询并推荐图书
    void on_pushButtonRefreshNewBooks_clicked(); // 刷新新书推荐列表

    void exportBookInfo(const QString& filePath);
    void exportStudentInfo(const QString& filePath);
    void exportBorrowInfo(const QString& filePath);
    void on_actionExportBookInfo_triggered();
    void on_actionExportStudentInfo_triggered();
    void on_actionExportBorrowInfo_triggered();

    void inportBookInfo();
    void inportStudentInfo();

private:
    Ui::LibraryManagementSystem* ui;

    // 数据成员
    BookSet bookSet;
    StudentSet studentSet;
    SBList sbList;

    int currentModifyIndex=-1;
    int currentModifyStudentIndex = -1;    // 当前修改的学生索引

    // 模型成员变量
    QStandardItemModel* bookTableModel;         // 用于显示全部书籍的模型
    QStandardItemModel* studentTableModel; // 学生信息的模型
    QStandardItemModel* bookDeleteTableModel;   // 用于删除书籍页面的模型
    QStandardItemModel* studentDeleteTableModel;
    QStandardItemModel* borrowRecordTableModel;

    // 学生和书籍搜索结果的模型
    QStandardItemModel* studentSearchModel;
    QStandardItemModel* bookSearchModel;

    // 选中的学生学号和书号
    QString selectedStudentNo;
    QString selectedBookNo;

    QStandardItemModel* studentSearchModel_2;
    QString selectedStudentNo_2;

    QStandardItemModel* studentBorrowedBooksModel;
    QString selectedBorrowedBookNo;

    QStandardItemModel* overdueRecordsModel; // 逾期借阅记录的模型

    QStandardItemModel* majorRecommendationsModel; // 专业推荐的模型
    QStandardItemModel* newBookRecommendationsModel; // 新书推荐的模型

    // 私有成员函数
    void buildTreeMenu();
    void setupModelsAndViews();

    void updateAllBooksTable();
    void updateDeleteBooksTable();

    void updateStudentTable();
    void updateDeleteStudentTable();

    void updateBorrowRecordTable();
};

#endif // LIBRARYMANAGEMENTSYSTEM_H

