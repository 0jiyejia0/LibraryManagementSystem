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
    
    void updateOverdueRecordsTable(); // �������ڽ��ļ�¼���

    void on_pushButtonSearchByMajor_clicked(); // ����רҵ��ѯ���Ƽ�ͼ��
    void on_pushButtonRefreshNewBooks_clicked(); // ˢ�������Ƽ��б�

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

    // ���ݳ�Ա
    BookSet bookSet;
    StudentSet studentSet;
    SBList sbList;

    int currentModifyIndex=-1;
    int currentModifyStudentIndex = -1;    // ��ǰ�޸ĵ�ѧ������

    // ģ�ͳ�Ա����
    QStandardItemModel* bookTableModel;         // ������ʾȫ���鼮��ģ��
    QStandardItemModel* studentTableModel; // ѧ����Ϣ��ģ��
    QStandardItemModel* bookDeleteTableModel;   // ����ɾ���鼮ҳ���ģ��
    QStandardItemModel* studentDeleteTableModel;
    QStandardItemModel* borrowRecordTableModel;

    // ѧ�����鼮���������ģ��
    QStandardItemModel* studentSearchModel;
    QStandardItemModel* bookSearchModel;

    // ѡ�е�ѧ��ѧ�ź����
    QString selectedStudentNo;
    QString selectedBookNo;

    QStandardItemModel* studentSearchModel_2;
    QString selectedStudentNo_2;

    QStandardItemModel* studentBorrowedBooksModel;
    QString selectedBorrowedBookNo;

    QStandardItemModel* overdueRecordsModel; // ���ڽ��ļ�¼��ģ��

    QStandardItemModel* majorRecommendationsModel; // רҵ�Ƽ���ģ��
    QStandardItemModel* newBookRecommendationsModel; // �����Ƽ���ģ��

    // ˽�г�Ա����
    void buildTreeMenu();
    void setupModelsAndViews();

    void updateAllBooksTable();
    void updateDeleteBooksTable();

    void updateStudentTable();
    void updateDeleteStudentTable();

    void updateBorrowRecordTable();
};

#endif // LIBRARYMANAGEMENTSYSTEM_H

