#pragma execution_character_set("utf-8")
#include "LibraryManagementSystem.h"
#include "ui_LibraryManagementSystem.h"
#include <fstream>
#include <QMessageBox>
#include <QDate>
#include <QDebug>
#include <QSet>
#include <qfiledialog.h>

LibraryManagementSystem::LibraryManagementSystem(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryManagementSystem)
    , bookTableModel(new QStandardItemModel(this))
    , bookDeleteTableModel(new QStandardItemModel(this))
    , studentTableModel(new QStandardItemModel(this))
    , studentDeleteTableModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    // 构建左侧树状导航菜单
    buildTreeMenu();

    // 设置默认显示的页面
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(0);
    ui->studentManagementPage->setCurrentIndex(0);
    ui->tabWidget_2->setCurrentIndex(0);
    ui->groupBoxModifyDetails->setVisible(false);
    ui->groupBoxModifyDetails_2->setVisible(false);
    ui->dateEditPubDay->setDate(QDate::currentDate());
    // 初始化模型并设置到视图
    setupModelsAndViews();

    // 加载数据
    bookSet.OpenBookList();
    studentSet.OpenStuList();

    sbList.OpenBorrowList();
    //sbList.setstudentnum(sbList.sblist.size());

    int totalBorrowNum = 0;
    for (const auto& studentNode : sbList.sblist) {
        totalBorrowNum += studentNode.getborrownum();
    }
    sbList.setborrownum(totalBorrowNum);

    // 更新界面显示
    updateAllBooksTable();
    updateDeleteBooksTable();
    updateStudentTable();
    updateDeleteStudentTable();
    updateBorrowRecordTable();
    updateOverdueRecordsTable();
    on_pushButtonRefreshNewBooks_clicked();

    // 连接信号与槽
    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &LibraryManagementSystem::onTreeItemClicked);
    connect(ui->pushButtonAddBook, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonAddBook_clicked);
    connect(ui->pushButtonDeleteBook, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonDeleteBook_clicked);
    connect(ui->pushButtonSearchBook, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonSearchBook_clicked);

    connect(ui->pushButtonAddStudent, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonAddStudent_clicked);
    connect(ui->pushButtonSaveChanges_2, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonSaveStudentChanges_clicked);
    connect(ui->pushButtonSearchStudent, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonSearchStudent_clicked);

    connect(ui->pushButtonSearchStudent_2, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonSearchStudent_clicked_2);
    connect(ui->tableViewStudentSearchResults->selectionModel(), &QItemSelectionModel::selectionChanged, this, &LibraryManagementSystem::on_studentSelectionChanged);
    connect(ui->pushButtonSearchBook_2, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonSearchBook_clicked_2);
    connect(ui->tableViewBookSearchResults->selectionModel(), &QItemSelectionModel::selectionChanged, this, &LibraryManagementSystem::on_bookSelectionChanged);
    connect(ui->pushButtonBorrowSelectedBook, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonBorrowBook_clicked);

    connect(ui->pushButtonSearchStudent_3, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonSearchStudent_clicked_2);
    connect(ui->tableViewStudentSearchResults_2->selectionModel(), &QItemSelectionModel::selectionChanged, this, &LibraryManagementSystem::on_studentSelectionChanged_2);
    connect(ui->tableViewStudentBorrowedBooks->selectionModel(), &QItemSelectionModel::selectionChanged, this, &LibraryManagementSystem::on_borrowedBookSelectionChanged);
    connect(ui->pushButtonSearchBook_3, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonSearchBorrowedBook_clicked);

    connect(ui->pushButtonSearchByMajor, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonSearchByMajor_clicked);
    connect(ui->pushButtonRefreshNewBooks, &QPushButton::pressed, this, &LibraryManagementSystem::on_pushButtonRefreshNewBooks_clicked);
    
    connect(ui->exportBookInfo, &QPushButton::pressed, this, &LibraryManagementSystem::on_actionExportBookInfo_triggered);
    connect(ui->exportStudentInfo, &QPushButton::pressed, this, &LibraryManagementSystem::on_actionExportStudentInfo_triggered);
    connect(ui->exportBorrowInfo, &QPushButton::pressed, this, &LibraryManagementSystem::on_actionExportBorrowInfo_triggered);

    connect(ui->inportBookInfo, &QPushButton::pressed, this, &LibraryManagementSystem::inportBookInfo);
    connect(ui->inportStudentInfo, &QPushButton::pressed, this, &LibraryManagementSystem::inportStudentInfo);
}

void LibraryManagementSystem::setupModelsAndViews()
{
    // 初始化 bookTableModel
    bookTableModel->setHorizontalHeaderLabels(QStringList()
        << "书号" << "书名" << "作者" << "出版社" << "库存" << "借阅量" << "出版日期");
    ui->tableViewAllBooks->setModel(bookTableModel);
    ui->tableViewAllBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 初始化 bookDeleteTableModel
    bookDeleteTableModel->setHorizontalHeaderLabels(QStringList()
        << "书号" << "书名" << "作者" << "出版社" << "库存" << "借阅量" << "出版日期");
    ui->tableViewBooksToDelete->setModel(bookDeleteTableModel);
    ui->tableViewBooksToDelete->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 初始化 tableViewStudents
    studentTableModel->setHorizontalHeaderLabels(QStringList()
        << "学号" << "姓名" << "专业" << "班级" << "手机号");
    ui->tableViewStudents->setModel(studentTableModel);
    ui->tableViewStudents->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 初始化 tableViewStudentsToDelete
    studentDeleteTableModel->setHorizontalHeaderLabels(QStringList()
        << "学号" << "姓名" << "专业" << "班级" << "手机号");
    ui->tableViewStudentsToDelete->setModel(studentDeleteTableModel);
    ui->tableViewStudentsToDelete->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    borrowRecordTableModel = new QStandardItemModel(this);
    borrowRecordTableModel->setHorizontalHeaderLabels(QStringList() 
        << "学生编号" << "图书编号" << "借阅日期");
    ui->tableViewBorrowRecords->setModel(borrowRecordTableModel);
    ui->tableViewBorrowRecords->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 初始化学生搜索模型
    studentSearchModel = new QStandardItemModel(this);
    studentSearchModel->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "专业" << "班级" << "手机");
    ui->tableViewStudentSearchResults->setModel(studentSearchModel);
    ui->tableViewStudentSearchResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 初始化书籍搜索模型
    bookSearchModel = new QStandardItemModel(this);
    bookSearchModel->setHorizontalHeaderLabels(QStringList() << "书号" << "书名" << "作者" << "出版社" << "库存" << "借阅量" << "出版日期");
    ui->tableViewBookSearchResults->setModel(bookSearchModel);
    ui->tableViewBookSearchResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    studentSearchModel_2 = new QStandardItemModel(this);
    studentSearchModel_2->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "专业" << "班级" << "手机");
    ui->tableViewStudentSearchResults_2->setModel(studentSearchModel);
    ui->tableViewStudentSearchResults_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    studentBorrowedBooksModel = new QStandardItemModel(this);
    studentBorrowedBooksModel->setHorizontalHeaderLabels(QStringList() << "书号" << "书名" << "借阅日期");
    ui->tableViewStudentBorrowedBooks->setModel(studentBorrowedBooksModel);
    ui->tableViewStudentBorrowedBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 初始化逾期借阅记录模型
    overdueRecordsModel = new QStandardItemModel(this);
    overdueRecordsModel->setHorizontalHeaderLabels(QStringList() << "学生编号" << "学生姓名" << "书号" << "书名" << "借阅日期" << "逾期天数");
    ui->tableViewOverdueRecords->setModel(overdueRecordsModel);
    ui->tableViewOverdueRecords->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 初始化专业推荐模型
    majorRecommendationsModel = new QStandardItemModel(this);
    majorRecommendationsModel->setHorizontalHeaderLabels(QStringList() << "书号" << "书名" << "作者" << "出版社" << "被借次数");
    ui->tableViewMajorRecommendations->setModel(majorRecommendationsModel);
    ui->tableViewMajorRecommendations->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 初始化新书推荐模型
    newBookRecommendationsModel = new QStandardItemModel(this);
    newBookRecommendationsModel->setHorizontalHeaderLabels(QStringList() << "书号" << "书名" << "作者" << "出版社" << "出版日期");
    ui->tableViewNewBookRecommendations->setModel(newBookRecommendationsModel);
    ui->tableViewNewBookRecommendations->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

LibraryManagementSystem::~LibraryManagementSystem()
{
    delete ui;
}

void LibraryManagementSystem::buildTreeMenu()
{
    // 信息管理
    QTreeWidgetItem* infoManagement = new QTreeWidgetItem(ui->treeWidget);
    infoManagement->setText(0, "信息管理");

    QTreeWidgetItem* bookInfoItem = new QTreeWidgetItem(infoManagement);
    bookInfoItem->setText(0, "图书管理");
    bookInfoItem->setData(0, Qt::UserRole, QVariant(0)); // 页面索引0

    QTreeWidgetItem* studentInfoItem = new QTreeWidgetItem(infoManagement);
    studentInfoItem->setText(0, "学生管理");
    studentInfoItem->setData(0, Qt::UserRole, QVariant(1)); // 页面索引1

    // 借阅管理
    QTreeWidgetItem* borrowManagement = new QTreeWidgetItem(ui->treeWidget);
    borrowManagement->setText(0, "借阅管理");

    QTreeWidgetItem* bookBorrowItem = new QTreeWidgetItem(borrowManagement);
    bookBorrowItem->setText(0, "图书借阅");
    bookBorrowItem->setData(0, Qt::UserRole, QVariant(2)); // 页面索引2

    QTreeWidgetItem* bookReturnItem = new QTreeWidgetItem(borrowManagement);
    bookReturnItem->setText(0, "逾期信息");
    bookReturnItem->setData(0, Qt::UserRole, QVariant(3)); // 页面索引3

    // 推荐系统
    QTreeWidgetItem* recommendation = new QTreeWidgetItem(ui->treeWidget);
    recommendation->setText(0, "推荐系统");

    QTreeWidgetItem* borrowRecommendationItem = new QTreeWidgetItem(recommendation);
    borrowRecommendationItem->setText(0, "借阅推荐");
    borrowRecommendationItem->setData(0, Qt::UserRole, QVariant(4)); // 页面索引4

    QTreeWidgetItem* newBookRecommendationItem = new QTreeWidgetItem(recommendation);
    newBookRecommendationItem->setText(0, "新书推荐");
    newBookRecommendationItem->setData(0, Qt::UserRole, QVariant(5)); // 页面索引5

    // 数据备份
    QTreeWidgetItem* dataBackupItem = new QTreeWidgetItem(ui->treeWidget);
    dataBackupItem->setText(0, "数据备份");
    dataBackupItem->setData(0, Qt::UserRole, QVariant(6)); // 页面索引6

    // 展开所有节点
    ui->treeWidget->expandAll();
}

void LibraryManagementSystem::onTreeItemClicked(QTreeWidgetItem* item, int column)
{
    QVariant pageIndexData = item->data(0, Qt::UserRole);
    if (pageIndexData.isValid()) {
        int pageIndex = pageIndexData.toInt();
        ui->stackedWidget->setCurrentIndex(pageIndex);
    }
}

//书籍相关

void LibraryManagementSystem::updateAllBooksTable()
{
    if (!bookTableModel) {
        qDebug() << "bookTableModel is nullptr!";
        return;
    }

    // 清空模型数据
    bookTableModel->removeRows(0, bookTableModel->rowCount());

    // 加载数据
    for (const auto& book : bookSet) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(book.getbookno()));
        rowItems << new QStandardItem(QString::fromStdString(book.getbookname()));
        rowItems << new QStandardItem(QString::fromStdString(book.getauthor()));
        rowItems << new QStandardItem(QString::fromStdString(book.getpublisher()));
        rowItems << new QStandardItem(QString::number(book.gettotalnum()));
        rowItems << new QStandardItem(QString::number(book.getborrownum()));
        rowItems << new QStandardItem(QString("%1-%2-%3")
            .arg(book.getpubday().getYear())
            .arg(book.getpubday().getMonth())
            .arg(book.getpubday().getDay()));
        bookTableModel->appendRow(rowItems);
    }
}

void LibraryManagementSystem::updateDeleteBooksTable()
{
    if (!bookDeleteTableModel) {
        qDebug() << "bookDeleteTableModel is nullptr!";
        return;
    }

    // 清空模型数据
    bookDeleteTableModel->removeRows(0, bookDeleteTableModel->rowCount());

    // 加载数据
    for (const auto& book : bookSet.getBooks()) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(book.getbookno()));
        rowItems << new QStandardItem(QString::fromStdString(book.getbookname()));
        rowItems << new QStandardItem(QString::fromStdString(book.getauthor()));
        rowItems << new QStandardItem(QString::fromStdString(book.getpublisher()));
        rowItems << new QStandardItem(QString::number(book.gettotalnum()));
        rowItems << new QStandardItem(QString::number(book.getborrownum()));
        rowItems << new QStandardItem(QString("%1-%2-%3")
            .arg(book.getpubday().getYear())
            .arg(book.getpubday().getMonth())
            .arg(book.getpubday().getDay()));

        bookDeleteTableModel->appendRow(rowItems);
    }
}

void LibraryManagementSystem::on_pushButtonAddBook_clicked()
{
    qDebug() << "on_pushButtonAddBook_clicked() called";
    // 获取用户输入
    QString bookNo = ui->lineEditBookNo->text();
    QString bookName = ui->lineEditBookName->text();
    QString author = ui->lineEditAuthor->text();
    QString publisher = ui->lineEditPublisher->text();
    int totalNum = ui->spinBoxTotalNum->value();
    QDate pubDay = ui->dateEditPubDay->date();

    // 输入验证

    if (bookNo.trimmed().isEmpty() || bookName.trimmed().isEmpty() || author.trimmed().isEmpty() || publisher.trimmed().isEmpty()) {
        QMessageBox::warning(this, "添加失败", "请填写完整信息！");
        return;
    }

    // 检查书号是否已存在
    bool exists = false;
    for (const auto& book : bookSet) {
        if (book.getbookno() == bookNo.toStdString()) {
            exists = true;
            break;
        }
    }

    if (exists) {
        QMessageBox::warning(this, "添加失败", "书号信息已存在！");
        return;
    }

    // 创建新书籍对象
    Book newBook;
    newBook.setbookno(bookNo.toStdString());
    newBook.setbookname(bookName.toStdString());
    newBook.setauthor(author.toStdString());
    newBook.setpublisher(publisher.toStdString());
    newBook.settotal(totalNum);
    newBook.setborrow(0); // 初始借阅量为0
    Date pubDate(pubDay.year(), pubDay.month(), pubDay.day());
    newBook.setpubday(pubDate);

    // 添加到 bookSet
    bookSet.ListInsert_B(newBook);
    qDebug() << "Book added. Total books:" << bookSet.ListLength_B();

    // 更新显示全部书籍页面
    updateAllBooksTable();
    updateDeleteBooksTable(); // 同时更新删除页面的表格

    // 保存到文件
    bookSet.SaveBookList();

    QMessageBox::information(this, "成功", "书籍信息添加成功！");

    // 清空输入框
    ui->lineEditBookNo->clear();
    ui->lineEditBookName->clear();
    ui->lineEditAuthor->clear();
    ui->lineEditPublisher->clear();
    ui->spinBoxTotalNum->setValue(0);
    ui->dateEditPubDay->setDate(QDate::currentDate());
}

void LibraryManagementSystem::on_pushButtonDeleteBook_clicked()
{
    // 获取选中的行
    QItemSelectionModel* selectionModel = ui->tableViewBooksToDelete->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();

    if (selectedRows.empty()) {
        QMessageBox::warning(this, "删除失败", "请选择要删除的书籍！");
        return;
    }

    // 收集要删除的书号
    QSet<QString> bookNosToDelete;
    for (const QModelIndex& selectedIndex : selectedRows) {
        QString bookNo = selectedIndex.sibling(selectedIndex.row(), 0).data().toString(); // 假设书号在第0列
        bookNosToDelete.insert(bookNo);
    }

    // 确认删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "confirm", QString("确定要删除选中的 %1 本书籍吗？").arg(bookNosToDelete.size()),
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // 从 bookSet 中删除选中的书籍
        auto& books = bookSet.getBooks(); // 获取 books 的引用
        bool removed = false;

        auto it = books.begin();
        while (it != books.end()) {
            if (bookNosToDelete.contains(QString::fromStdString(it->getbookno()))) {
                it = books.erase(it);
                removed = true;
            }
            else {
                ++it;
            }
        }

        if (removed) {
            // 更新显示
            updateDeleteBooksTable();
            updateAllBooksTable(); // 如果“显示全部书籍”页面也需要更新

            // 保存到文件
            bookSet.SaveBookList();

            QMessageBox::information(this, "success", "del");
        }
        else {
            QMessageBox::warning(this, "fail", "not find");
        }
    }
}

void LibraryManagementSystem::on_pushButtonFindBook_clicked()
{
    QString bookNo = ui->lineEditModifyBookNo->text();

    if (bookNo.isEmpty()) {
        QMessageBox::warning(this, "输入失败", "请输入书号信息！");
        return;
    }

    // 查找书籍
    int index = -1;
    for (size_t i = 0; i < bookSet.ListLength_B(); ++i) {
        if (bookSet.getBooks()[i].getbookno() == bookNo.toStdString()) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        QMessageBox::warning(this, "查找失败", "没有此书！");
        return;
    }

    // 显示书籍信息
    currentModifyIndex = index; // 保存当前修改的书籍索引
    const Book& book = bookSet.getBooks()[index];

    ui->lineEditModifyBookName->setText(QString::fromStdString(book.getbookname()));
    ui->lineEditModifyAuthor->setText(QString::fromStdString(book.getauthor()));
    ui->lineEditModifyPublisher->setText(QString::fromStdString(book.getpublisher()));
    ui->spinBoxModifyTotalNum->setValue(book.gettotalnum());
    ui->dateEditModifyPubDay->setDate(QDate(book.getpubday().getYear(), book.getpubday().getMonth(), book.getpubday().getDay()));

    // 显示修改区域
    ui->groupBoxModifyDetails->setVisible(true);
}

void LibraryManagementSystem::on_pushButtonSaveChanges_clicked()
{
    if (currentModifyIndex == -1) {
        QMessageBox::warning(this, "错误", "请先查找要修改的书籍！");
        return;
    }

    // 获取修改后的信息
    QString bookName = ui->lineEditModifyBookName->text();
    QString author = ui->lineEditModifyAuthor->text();
    QString publisher = ui->lineEditModifyPublisher->text();
    int totalNum = ui->spinBoxModifyTotalNum->value();
    QDate pubDay = ui->dateEditModifyPubDay->date();

    if (bookName.isEmpty() || author.isEmpty() || publisher.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请完整填写所有信息！");
        return;
    }

    // 修改 bookSet 中的数据
    Book& book = bookSet.getBooks()[currentModifyIndex];
    book.setbookname(bookName.toStdString());
    book.setauthor(author.toStdString());
    book.setpublisher(publisher.toStdString());
    book.settotal(totalNum);
    Date pubDate(pubDay.year(), pubDay.month(), pubDay.day());
    book.setpubday(pubDate);

    // 更新显示全部书籍页面
    updateAllBooksTable();
    updateDeleteBooksTable();

    // 保存到文件
    bookSet.SaveBookList();

    QMessageBox::information(this, "修改成功", "书籍信息已成功修改！");

    // 重置
    currentModifyIndex = -1;
    ui->lineEditModifyBookNo->clear();
    ui->groupBoxModifyDetails->setVisible(false);
}

void LibraryManagementSystem::on_pushButtonSearchBook_clicked()
{
    QString condition = ui->comboBoxSearchCondition->currentText();
    QString keyword = ui->lineEditSearchKeyword->text();
    if (keyword.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入查询关键字！");
        return;
    }

    // 创建模型
    QStandardItemModel* model = new QStandardItemModel(this);
    model->clear();
    model->setHorizontalHeaderLabels(QStringList() << "书号" << "书名" << "作者" << "出版社" << "库存" << "借阅量" << "出版日期");
    // 查找匹配的书籍
    for (const auto& book : bookSet) {
        bool match = false;
        if (condition == "书号") {
            match = book.getbookno().find(keyword.toStdString()) != std::string::npos;
        }
        else if (condition == "书名") {
            match = book.getbookname().find(keyword.toStdString()) != std::string::npos;
        }
        else if (condition == "作者") {
            match = book.getauthor().find(keyword.toStdString()) != std::string::npos;
        }
        else if (condition == "出版社") {
            match = book.getpublisher().find(keyword.toStdString()) != std::string::npos;
        }

        if (match) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(book.getbookno()));
            rowItems << new QStandardItem(QString::fromStdString(book.getbookname()));
            rowItems << new QStandardItem(QString::fromStdString(book.getauthor()));
            rowItems << new QStandardItem(QString::fromStdString(book.getpublisher()));
            rowItems << new QStandardItem(QString::number(book.gettotalnum()));
            rowItems << new QStandardItem(QString::number(book.getborrownum()));
            rowItems << new QStandardItem(QString("%1-%2-%3").arg(book.getpubday().getYear()).arg(book.getpubday().getMonth()).arg(book.getpubday().getDay()));

            model->appendRow(rowItems);
        }
    }

    // 设置模型到视图
    ui->tableViewSearchResults->setModel(model);
    ui->tableViewSearchResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//学生相关

void LibraryManagementSystem::updateStudentTable()
{
    if (!studentTableModel) {
        qDebug() << "studentTableModel is nullptr!";
        return;
    }

    // 清空模型数据
    studentTableModel->removeRows(0, studentTableModel->rowCount());

    // 加载数据
    for (const auto& student : studentSet) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(student.getstuno()));
        rowItems << new QStandardItem(QString::fromStdString(student.getstuname()));
        rowItems << new QStandardItem(QString::fromStdString(student.getstumajor()));
        rowItems << new QStandardItem(QString::fromStdString(student.getstuclass()));
        rowItems << new QStandardItem(QString::fromStdString(student.getstumobi()));
        studentTableModel->appendRow(rowItems);
    }
}

void LibraryManagementSystem::updateDeleteStudentTable() {
    if (!studentDeleteTableModel) {
        qDebug() << "studentDeleteTableModel is nullptr!";
        return;
    }

    // 清空模型数据
    studentDeleteTableModel->removeRows(0, studentDeleteTableModel->rowCount());

    // 加载数据
    for (const auto& student : studentSet) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(student.getstuno()));
        rowItems << new QStandardItem(QString::fromStdString(student.getstuname()));
        rowItems << new QStandardItem(QString::fromStdString(student.getstumajor()));
        rowItems << new QStandardItem(QString::fromStdString(student.getstuclass()));
        rowItems << new QStandardItem(QString::fromStdString(student.getstumobi()));
        studentDeleteTableModel->appendRow(rowItems);
    }
}

void LibraryManagementSystem::on_pushButtonAddStudent_clicked() {
    qDebug() << "on_pushButtonAddStudent_clicked() called";
    // 获取用户输入
    QString studentNo = ui->lineEditStudentNo->text();
    QString studentName = ui->lineEditStudentName->text();
    QString major = ui->lineEditMajor->text();
    QString studentClass = ui->lineEditClass->text();
    QString mobi = ui->lineEditMobi->text();

    // 输入验证

    if (studentNo.trimmed().isEmpty() || studentName.trimmed().isEmpty() || major.trimmed().isEmpty() || studentClass.trimmed().isEmpty() || mobi.trimmed().isEmpty()) {
        QMessageBox::warning(this, "添加失败", "请输入完整信息！");
        return;
    }

    // 检查书号是否已存在
    bool exists = false;
    for (const auto& student : studentSet) {
        if (student.getstuno() == studentNo.toStdString()) {
            exists = true;
            break;
        }
    }

    if (exists) {
        QMessageBox::warning(this, "添加失败", "该学号已存在！");
        return;
    }

    // 创建新书籍对象
    Student newStudent;
    newStudent.setstuno(studentNo.toStdString());
    newStudent.setstuname(studentName.toStdString());
    newStudent.setstumajor(major.toStdString());
    newStudent.setstuclass(studentClass.toStdString());
    newStudent.setstumobi(mobi.toStdString());

    // 添加到 bookSet
    studentSet.ListInsert_S(newStudent);
    qDebug() << "Student added. Total students:" << studentSet.ListLength_S();

    // 更新显示全部书籍页面
    updateStudentTable();
    updateDeleteStudentTable(); // 同时更新删除页面的表格

    // 保存到文件
    studentSet.SaveStuList();

    QMessageBox::information(this, "添加成功", "学生信息添加成功！");

    // 清空输入框
    ui->lineEditStudentNo->clear();
    ui->lineEditStudentName->clear();
    ui->lineEditMajor->clear();
    ui->lineEditClass->clear();
    ui->lineEditMobi->clear();
}

void LibraryManagementSystem::on_pushButtonDeleteStudent_clicked() {
    // 获取选中的行
    QItemSelectionModel* selectionModel = ui->tableViewStudentsToDelete->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();

    if (selectedRows.empty()) {
        QMessageBox::warning(this, "删除失败", "请选择要删除的书籍！");
        return;
    }

    // 收集要删除的书号
    QSet<QString> studentNosToDelete;
    for (const QModelIndex& selectedIndex : selectedRows) {
        QString studentNo = selectedIndex.sibling(selectedIndex.row(), 0).data().toString(); // 假设书号在第0列
        studentNosToDelete.insert(studentNo);
    }

    // 确认删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "confirm", QString("确定要删除选中的 %1 位同学吗？").arg(studentNosToDelete.size()),
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // 从 bookSet 中删除选中的书籍
        auto& student = studentSet; // 获取 books 的引用
        bool removed = false;

        auto it = student.begin();
        while (it != student.end()) {
            if (studentNosToDelete.contains(QString::fromStdString(it->getstuno()))) {
                it = student.erase(it);
                removed = true;
            }
            else {
                ++it;
            }
        }

        if (removed) {
            // 更新显示
            updateDeleteStudentTable();
            updateStudentTable(); // 如果“显示全部书籍”页面也需要更新

            // 保存到文件
            studentSet.SaveStuList();

            QMessageBox::information(this, "success", "del");
        }
        else {
            QMessageBox::warning(this, "fail", "not find");
        }
    }
}

void LibraryManagementSystem::on_pushButtonFindStudent_clicked()
{
    QString studentNo = ui->lineEditModifyStudentNo->text();

    if (studentNo.isEmpty()) {
        QMessageBox::warning(this, "输入失败", "请输入要查询的书号！");
        return;
    }

    // 查找书籍
    int index = -1;
    for (size_t i = 0; i < studentSet.ListLength_S(); ++i) {
        if (studentSet[i].getstuno() == studentNo.toStdString()) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        QMessageBox::warning(this, "FAIL", "NO STUDENT");
        return;
    }

    // 显示书籍信息
    currentModifyStudentIndex = index; // 保存当前修改的书籍索引
    const Student& student = studentSet[index];

    ui->lineEditModifyStudentName->setText(QString::fromStdString(student.getstuname()));
    ui->lineEditModifyMajor->setText(QString::fromStdString(student.getstumajor()));
    ui->lineEditModifyClass->setText(QString::fromStdString(student.getstuclass()));
    ui->lineEditModifyMobi->setText(QString::fromStdString(student.getstumobi()));

    // 显示修改区域
    ui->groupBoxModifyDetails_2->setVisible(true);
}

void LibraryManagementSystem::on_pushButtonSaveStudentChanges_clicked() {
    if (currentModifyStudentIndex == -1) {
        QMessageBox::warning(this, "错误", "请先查找要修改的书籍！");
        return;
    }

    // 获取修改后的信息
    QString studentName = ui->lineEditModifyStudentName->text();
    QString major = ui->lineEditModifyMajor->text();
    QString studentClass = ui->lineEditModifyClass->text();
    QString mobi = ui->lineEditModifyMobi->text();

    if (studentName.isEmpty() || major.isEmpty() || studentClass.isEmpty() || mobi.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请完整填写所有信息！");
        return;
    }

    // 修改 bookSet 中的数据
    Student& student = studentSet[currentModifyStudentIndex];
    student.setstuname(studentName.toStdString());
    student.setstumajor(major.toStdString());
    student.setstuclass(studentClass.toStdString());
    student.setstumobi(mobi.toStdString());

    // 更新显示全部书籍页面
    updateStudentTable();
    updateDeleteStudentTable();

    // 保存到文件
    studentSet.SaveStuList();

    QMessageBox::information(this, "修改成功", "学生信息已成功修改！");

    // 重置
    currentModifyStudentIndex = -1;
    ui->lineEditModifyStudentNo->clear();
    ui->groupBoxModifyDetails_2->setVisible(false);
}

void LibraryManagementSystem::on_pushButtonSearchStudent_clicked() {
    QString condition = ui->comboBoxSearchStudentCondition->currentText();
    QString keyword = ui->lineEditSearchStudentKeyword->text();
    if (keyword.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入查询关键字！");
        return;
    }

    // 创建模型
    QStandardItemModel* model = new QStandardItemModel(this);
    model->clear();
    model->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "专业" << "班级" << "手机");
    // 查找匹配的书籍
    for (const auto& student : studentSet) {
        bool match = false;
        if (condition == "学号") {
            match = student.getstuno().find(keyword.toStdString()) != std::string::npos;
        }
        else if (condition == "姓名") {
            match = student.getstuname().find(keyword.toStdString()) != std::string::npos;
        }
        else if (condition == "专业") {
            match = student.getstumajor().find(keyword.toStdString()) != std::string::npos;
        }
        else if (condition == "班级") {
            match = student.getstuclass().find(keyword.toStdString()) != std::string::npos;
        }
        else if (condition == "手机") {
            match = student.getstumobi().find(keyword.toStdString()) != std::string::npos;
        }

        if (match) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(student.getstuno()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstuname()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstumajor()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstuclass()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstumobi()));

            model->appendRow(rowItems);
        }
    }

    // 设置模型到视图
    ui->tableViewSearchStudentResults->setModel(model);
    ui->tableViewSearchStudentResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//借阅相关

void LibraryManagementSystem::on_pushButtonSearchStudent_clicked_2()
{
    QString criteria = ui->comboBoxStudentSearchCriteria->currentText();
    QString keyword = ui->lineEditStudentSearchKeyword->text().trimmed();

    // 清空模型数据
    studentSearchModel->removeRows(0, studentSearchModel->rowCount());

    // 执行搜索
    for (const auto& student : studentSet) {
        bool match = false;
        if (criteria == "学号") {
            match = QString::fromStdString(student.getstuno()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "姓名") {
            match = QString::fromStdString(student.getstuname()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "专业") {
            match = QString::fromStdString(student.getstumajor()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "班级") {
            match = QString::fromStdString(student.getstuclass()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "手机") {
            match = QString::fromStdString(student.getstumobi()).contains(keyword, Qt::CaseInsensitive);
        }

        if (match) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(student.getstuno()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstuname()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstumajor()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstuclass()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstumobi()));
            studentSearchModel->appendRow(rowItems);
        }
    }
}

void LibraryManagementSystem::on_studentSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    QModelIndexList selectedRows = ui->tableViewStudentSearchResults->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        QModelIndex index = selectedRows.first();
        selectedStudentNo = index.sibling(index.row(), 0).data().toString();
    }
    else {
        selectedStudentNo.clear();
    }
}

void LibraryManagementSystem::on_pushButtonSearchBook_clicked_2()
{
    QString criteria = ui->comboBoxBookSearchCriteria->currentText();
    QString keyword = ui->lineEditBookSearchKeyword->text().trimmed();

    // 清空模型数据
    bookSearchModel->removeRows(0, bookSearchModel->rowCount());

    // 执行搜索
    for (const auto& book : bookSet) {
        bool match = false;
        if (criteria == "书号") {
            match = QString::fromStdString(book.getbookno()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "书名") {
            match = QString::fromStdString(book.getbookname()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "作者") {
            match = QString::fromStdString(book.getauthor()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "出版社") {
            match = QString::fromStdString(book.getpublisher()).contains(keyword, Qt::CaseInsensitive);
        }

        if (match) {
            int available = book.gettotalnum();
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(book.getbookno()));
            rowItems << new QStandardItem(QString::fromStdString(book.getbookname()));
            rowItems << new QStandardItem(QString::fromStdString(book.getauthor()));
            rowItems << new QStandardItem(QString::fromStdString(book.getpublisher()));
            rowItems << new QStandardItem(QString::number(available));
            rowItems << new QStandardItem(QString::number(book.getborrownum()));
            rowItems << new QStandardItem(QString("%1-%2-%3")
                .arg(book.getpubday().getYear())
                .arg(book.getpubday().getMonth())
                .arg(book.getpubday().getDay()));
            bookSearchModel->appendRow(rowItems);
        }
    }
}

void LibraryManagementSystem::on_bookSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    QModelIndexList selectedRows = ui->tableViewBookSearchResults->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        QModelIndex index = selectedRows.first();
        selectedBookNo = index.sibling(index.row(), 0).data().toString();
    }
    else {
        selectedBookNo.clear();
    }
}

void LibraryManagementSystem::on_pushButtonBorrowBook_clicked() {
    if (selectedStudentNo.isEmpty() || selectedBookNo.isEmpty()) {
        QMessageBox::warning(this, "操作错误", "请先选择学生和图书！");
        return;
    }

    QString studentNo = selectedStudentNo;
    QString bookNo = selectedBookNo;

    // 检查学生是否存在
    int studentIndex = studentSet.findStudent(studentNo.toStdString());
    if (studentIndex == -1) {
        QMessageBox::warning(this, "借书失败", "未找到对应的学生！");
        return;
    }

    // 检查图书是否存在
    int bookIndex = bookSet.findBook(bookNo.toStdString());
    if (bookIndex == -1) {
        QMessageBox::warning(this, "借书失败", "未找到对应的图书！");
        return;
    }

    Book& book = bookSet.getBooks()[bookIndex];

    // 检查图书库存是否足够
    if (book.gettotalnum() <= 0) {
        QMessageBox::warning(this, "借书失败", "该图书已被借完！");
        return;
    }

    // 检查学生是否已经借过此书
    if (sbList.BookWhetherIn(studentNo.toStdString(), bookNo.toStdString()) != -1) {
        QMessageBox::warning(this, "借书失败", "您已借过此书，尚未归还！");
        return;
    }

    // 更新图书已借出数量
    book.setborrow(book.getborrownum() + 1);
    book.settotal(book.gettotalnum() - 1);

    // 创建借阅信息
    BorrowInfo bi;
    bi.setbookno(bookNo.toStdString());
    bi.setborrowday(Date::fromQDate(QDate::currentDate()));

    // 在 sbList 中添加借阅关系
    int stuIndexInSBList = sbList.StuWhetherIn(studentNo.toStdString());
    if (stuIndexInSBList == -1) {
        // 学生第一次借书
        StudentNode newStudentNode;
        newStudentNode.setstudentno(studentNo.toStdString());
        newStudentNode.pushbook(bi);
        sbList.pushelem(newStudentNode);
    }
    else {
        // 学生已存在
        StudentNode& existingStudentNode = sbList.sblist[stuIndexInSBList];
        existingStudentNode.setborrownum(existingStudentNode.getborrownum() + 1);
        existingStudentNode.pushbook(bi);
    }

    // 更新借阅总数
    sbList.setborrownum(sbList.getborrownum() + 1);

    // 保存数据
    bookSet.SaveBookList();
    sbList.SaveBorrowList();

    QMessageBox::information(this, "借书成功", "图书已成功借出！");

    // 更新界面
    updateAllBooksTable();
    updateDeleteBooksTable();
    updateBorrowRecordTable();
    updateOverdueRecordsTable();

    // 清空输入框
    ui->tableViewStudentSearchResults->selectionModel()->clearSelection();
    ui->tableViewBookSearchResults->selectionModel()->clearSelection();
    selectedStudentNo.clear();
    selectedBookNo.clear();
}

void LibraryManagementSystem::updateBorrowRecordTable()
{
    if (!borrowRecordTableModel) {
        qDebug() << "borrowRecordTableModel is nullptr!";
        return;
    }

    // 清空模型数据
    borrowRecordTableModel->removeRows(0, borrowRecordTableModel->rowCount());

    // 加载数据
    for (const auto& studentNode : sbList.sblist) {
        for (const auto& borrowInfo : studentNode.bilist) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(studentNode.getstudentno()));
            rowItems << new QStandardItem(QString::fromStdString(borrowInfo.getbookno()));
            rowItems << new QStandardItem(QString("%1-%2-%3")
                .arg(borrowInfo.getborrowday().getYear())
                .arg(borrowInfo.getborrowday().getMonth())
                .arg(borrowInfo.getborrowday().getDay()));
            // 可以添加更多信息，例如是否逾期等
            borrowRecordTableModel->appendRow(rowItems);
        }
    }

    // 设置模型到视图
    ui->tableViewBorrowRecords->setModel(borrowRecordTableModel);
    ui->tableViewBorrowRecords->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//归还

void LibraryManagementSystem::updateStudentBorrowedBooksTable(const QString& studentNo)
{
    ui->lineEditBorrowedBookSearchKeyword->clear();
    ui->comboBoxBorrowedBookSearchCriteria->setCurrentIndex(0);

    studentBorrowedBooksModel->removeRows(0, studentBorrowedBooksModel->rowCount());

    int studentIndex = sbList.StuWhetherIn(studentNo.toStdString());
    if (studentIndex != -1) {
        const StudentNode& studentNode = sbList.sblist[studentIndex];
        for (const auto& borrowInfo : studentNode.bilist) {
            int bookIndex = bookSet.findBook(borrowInfo.getbookno());
            QString bookTitle = (bookIndex != -1) ? QString::fromStdString(bookSet.getBooks()[bookIndex].getbookname()) : "未知";
            QString author = (bookIndex != -1) ? QString::fromStdString(bookSet.getBooks()[bookIndex].getauthor()) : "未知";
            QString publisher = (bookIndex != -1) ? QString::fromStdString(bookSet.getBooks()[bookIndex].getpublisher()) : "未知";

            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(borrowInfo.getbookno()));
            rowItems << new QStandardItem(bookTitle);
            rowItems << new QStandardItem(author);
            rowItems << new QStandardItem(publisher);
            rowItems << new QStandardItem(QString("%1-%2-%3")
                .arg(borrowInfo.getborrowday().getYear())
                .arg(borrowInfo.getborrowday().getMonth())
                .arg(borrowInfo.getborrowday().getDay()));
            studentBorrowedBooksModel->appendRow(rowItems);
        }
    }
}

void LibraryManagementSystem::on_pushButtonSearchStudent_clicked_3()
{
    QString criteria = ui->comboBoxStudentSearchCriteria_2->currentText();
    QString keyword = ui->lineEditStudentSearchKeyword_2->text().trimmed();

    // 清空模型数据
    studentSearchModel_2->removeRows(0, studentSearchModel->rowCount());

    // 执行搜索
    for (const auto& student : studentSet) {
        bool match = false;
        if (criteria == "学号") {
            match = QString::fromStdString(student.getstuno()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "姓名") {
            match = QString::fromStdString(student.getstuname()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "专业") {
            match = QString::fromStdString(student.getstumajor()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "班级") {
            match = QString::fromStdString(student.getstuclass()).contains(keyword, Qt::CaseInsensitive);
        }
        else if (criteria == "手机") {
            match = QString::fromStdString(student.getstumobi()).contains(keyword, Qt::CaseInsensitive);
        }

        if (match) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(student.getstuno()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstuname()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstumajor()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstuclass()));
            rowItems << new QStandardItem(QString::fromStdString(student.getstumobi()));
            studentSearchModel_2->appendRow(rowItems);
        }
    }
}

void LibraryManagementSystem::on_studentSelectionChanged_2(const QItemSelection& selected, const QItemSelection& deselected)
{
    QModelIndexList selectedRows = ui->tableViewStudentSearchResults_2->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        QModelIndex index = selectedRows.first();
        selectedStudentNo = index.sibling(index.row(), 0).data().toString();

        // 更新已借阅书籍列表
        updateStudentBorrowedBooksTable(selectedStudentNo);
    }
    else {
        selectedStudentNo.clear();
        // 清空已借阅书籍列表
        studentBorrowedBooksModel->removeRows(0, studentBorrowedBooksModel->rowCount());
    }
}

void LibraryManagementSystem::on_pushButtonSearchBorrowedBook_clicked()
{
    QString criteria = ui->comboBoxBorrowedBookSearchCriteria->currentText();
    QString keyword = ui->lineEditBorrowedBookSearchKeyword->text().trimmed();

    if (selectedStudentNo.isEmpty()) {
        QMessageBox::warning(this, "操作错误", "请先选择学生！");
        return;
    }

    studentBorrowedBooksModel->removeRows(0, studentBorrowedBooksModel->rowCount());

    int studentIndex = sbList.StuWhetherIn(selectedStudentNo.toStdString());
    if (studentIndex != -1) {
        const StudentNode& studentNode = sbList.sblist[studentIndex];

        for (const auto& borrowInfo : studentNode.bilist) {
            int bookIndex = bookSet.findBook(borrowInfo.getbookno());
            if (bookIndex != -1) {
                const Book& book = bookSet.getBooks()[bookIndex];

                bool match = false;
                if (keyword.isEmpty()) {
                    match = true;
                }
                else if (criteria == "书号") {
                    match = QString::fromStdString(book.getbookno()).contains(keyword, Qt::CaseInsensitive);
                }
                else if (criteria == "书名") {
                    match = QString::fromStdString(book.getbookname()).contains(keyword, Qt::CaseInsensitive);
                }
                else if (criteria == "作者") {
                    match = QString::fromStdString(book.getauthor()).contains(keyword, Qt::CaseInsensitive);
                }
                else if (criteria == "出版社") {
                    match = QString::fromStdString(book.getpublisher()).contains(keyword, Qt::CaseInsensitive);
                }

                if (match) {
                    QList<QStandardItem*> rowItems;
                    rowItems << new QStandardItem(QString::fromStdString(book.getbookno()));
                    rowItems << new QStandardItem(QString::fromStdString(book.getbookname()));
                    rowItems << new QStandardItem(QString::fromStdString(book.getauthor()));
                    rowItems << new QStandardItem(QString::fromStdString(book.getpublisher()));
                    rowItems << new QStandardItem(QString("%1-%2-%3")
                        .arg(borrowInfo.getborrowday().getYear())
                        .arg(borrowInfo.getborrowday().getMonth())
                        .arg(borrowInfo.getborrowday().getDay()));
                    studentBorrowedBooksModel->appendRow(rowItems);
                }
            }
        }
    }
}

void LibraryManagementSystem::on_borrowedBookSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    QModelIndexList selectedRows = ui->tableViewStudentBorrowedBooks->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        QModelIndex index = selectedRows.first();
        selectedBorrowedBookNo = index.sibling(index.row(), 0).data().toString();
    }
    else {
        selectedBorrowedBookNo.clear();
    }
}

void LibraryManagementSystem::on_pushButtonReturnBook_clicked() {
    if (selectedStudentNo.isEmpty() || selectedBorrowedBookNo.isEmpty()) {
        QMessageBox::warning(this, "操作错误", "请先选择学生和要归还的图书！");
        return;
    }

    QString studentNo = selectedStudentNo;
    QString bookNo = selectedBorrowedBookNo;

    if (studentNo.trimmed().isEmpty() || bookNo.trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请完整填写学生编号和图书编号！");
        return;
    }

    // 检查学生是否存在
    int studentIndex = sbList.StuWhetherIn(studentNo.toStdString());
    if (studentIndex == -1) {
        QMessageBox::warning(this, "还书失败", "未找到对应的学生借阅记录！");
        return;
    }

    StudentNode& studentNode = sbList.sblist[studentIndex];

    // 检查借阅记录是否存在
    int borrowIndex = studentNode.BookWhetherIn(bookNo.toStdString());
    if (borrowIndex == -1) {
        QMessageBox::warning(this, "还书失败", "该学生未借阅此图书！");
        return;
    }

    // 更新图书借阅量
    int bookIndex = bookSet.findBook(bookNo.toStdString());
    if (bookIndex != -1) {
        Book& book = bookSet.getBooks()[bookIndex];
        if (book.getborrownum() > 0) {
            book.setborrow(book.getborrownum() - 1);
            book.settotal(book.gettotalnum() + 1);
        }
        else {
            QMessageBox::warning(this, "还书失败", "图书借阅数量数据异常！");
            return;
        }
    }
    else {
        QMessageBox::warning(this, "还书失败", "未找到对应的图书！");
        return;
    }

    // 从学生借阅记录中移除该书
    studentNode.returnbook(bookNo.toStdString());
    studentNode.setborrownum(studentNode.getborrownum() - 1);

    // 更新借阅总数
    sbList.setborrownum(sbList.getborrownum() - 1);

    // 如果该学生不再有借阅，移除学生记录
    if (studentNode.getborrownum() <= 0) {
        sbList.sblist.erase(sbList.sblist.begin() + studentIndex);
        sbList.setstudentnum(sbList.getstudentnum() - 1);
    }

    // 保存数据
    bookSet.SaveBookList();
    sbList.SaveBorrowList();

    QMessageBox::information(this, "还书成功", "图书已成功归还！");

    // 更新界面
    updateAllBooksTable();
    updateDeleteBooksTable();
    updateBorrowRecordTable();
    updateOverdueRecordsTable();

    updateStudentBorrowedBooksTable(selectedStudentNo);
    // 清空选中的书籍
    ui->tableViewStudentBorrowedBooks->selectionModel()->clearSelection();
    selectedBorrowedBookNo.clear();
}

//逾期未还

void LibraryManagementSystem::updateOverdueRecordsTable()
{
    if (!overdueRecordsModel) {
        qDebug() << "overdueRecordsModel is nullptr!";
        return;
    }

    // 清空模型数据
    overdueRecordsModel->removeRows(0, overdueRecordsModel->rowCount());

    // 获取当前日期
    Date currentDate = Date::fromQDate(QDate::currentDate());

    // 遍历所有借阅记录，查找逾期未还的记录
    for (const auto& studentNode : sbList.sblist) {
        // 获取学生信息
        int studentIndex = studentSet.findStudent(studentNode.getstudentno());
        QString studentName = (studentIndex != -1) ? QString::fromStdString(studentSet[studentIndex].getstuname()) : "未知";

        for (const auto& borrowInfo : studentNode.bilist) {
            if (borrowInfo.isOverdue(currentDate)) {
                // 获取图书信息
                int bookIndex = bookSet.findBook(borrowInfo.getbookno());
                QString bookName = (bookIndex != -1) ? QString::fromStdString(bookSet.getBooks()[bookIndex].getbookname()) : "未知";

                // 计算逾期天数
                int daysBetween = borrowInfo.getborrowday().daysBetween(currentDate);
                int overdueDays = daysBetween - 30;

                // 添加到模型
                QList<QStandardItem*> rowItems;
                rowItems << new QStandardItem(QString::fromStdString(studentNode.getstudentno()));
                rowItems << new QStandardItem(studentName);
                rowItems << new QStandardItem(QString::fromStdString(borrowInfo.getbookno()));
                rowItems << new QStandardItem(bookName);
                rowItems << new QStandardItem(QString("%1-%2-%3")
                    .arg(borrowInfo.getborrowday().getYear())
                    .arg(borrowInfo.getborrowday().getMonth())
                    .arg(borrowInfo.getborrowday().getDay()));
                rowItems << new QStandardItem(QString::number(overdueDays));

                overdueRecordsModel->appendRow(rowItems);
            }
        }
    }
}

//推荐

void LibraryManagementSystem::on_pushButtonSearchByMajor_clicked()
{
    QString majorName = ui->lineEditMajorName->text().trimmed();

    if (majorName.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入专业名称！");
        return;
    }

    // 创建一个映射，用于统计每本书被该专业学生借阅的次数
    QMap<std::string, int> bookBorrowCount;

    // 遍历所有学生，找到指定专业的学生
    for (const auto& student : studentSet) {
        if (QString::fromStdString(student.getstumajor()) == majorName) {
            // 查找该学生的借阅记录
            int stuIndexInSBList = sbList.StuWhetherIn(student.getstuno());
            if (stuIndexInSBList != -1) {
                const StudentNode& studentNode = sbList.sblist[stuIndexInSBList];
                for (const auto& borrowInfo : studentNode.bilist) {
                    bookBorrowCount[borrowInfo.getbookno()] += 1;
                }
            }
        }
    }

    // 将统计结果转换为列表，并按借阅次数从高到低排序
    QList<QPair<std::string, int>> bookList;
    for (auto it = bookBorrowCount.begin(); it != bookBorrowCount.end(); ++it) {
        bookList.append(qMakePair(it.key(), it.value()));
    }
    std::sort(bookList.begin(), bookList.end(), [](const QPair<std::string, int>& a, const QPair<std::string, int>& b) {
        return a.second > b.second;
        });

    // 清空模型数据
    majorRecommendationsModel->removeRows(0, majorRecommendationsModel->rowCount());

    // 将结果添加到模型中
    for (const auto& pair : bookList) {
        int bookIndex = bookSet.findBook(pair.first);
        if (bookIndex != -1) {
            const Book& book = bookSet.getBooks()[bookIndex];

            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(book.getbookno()));
            rowItems << new QStandardItem(QString::fromStdString(book.getbookname()));
            rowItems << new QStandardItem(QString::fromStdString(book.getauthor()));
            rowItems << new QStandardItem(QString::fromStdString(book.getpublisher()));
            rowItems << new QStandardItem(QString::number(pair.second));

            majorRecommendationsModel->appendRow(rowItems);
        }
    }
}

void LibraryManagementSystem::on_pushButtonRefreshNewBooks_clicked()
{
    // 获取图书列表的副本
    std::vector<Book> bookList = bookSet.getBooks(); // 假设 getBooks() 返回的是副本

    // 按出版日期从新到旧排序
    std::sort(bookList.begin(), bookList.end(), [](const Book& a, const Book& b) {
        return a.getpubday() > b.getpubday(); // 假设 Date 类已重载 > 运算符
        });

    // 清空模型数据
    newBookRecommendationsModel->removeRows(0, newBookRecommendationsModel->rowCount());

    // 将排序后的图书添加到模型中
    for (const auto& book : bookList) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(book.getbookno()));
        rowItems << new QStandardItem(QString::fromStdString(book.getbookname()));
        rowItems << new QStandardItem(QString::fromStdString(book.getauthor()));
        rowItems << new QStandardItem(QString::fromStdString(book.getpublisher()));
        rowItems << new QStandardItem(QString("%1-%2-%3")
            .arg(book.getpubday().getYear())
            .arg(book.getpubday().getMonth())
            .arg(book.getpubday().getDay()));

        newBookRecommendationsModel->appendRow(rowItems);
    }
}

//导出数据

void LibraryManagementSystem::exportBookInfo(const QString& filePath)
{
    std::ofstream outFile(filePath.toStdString());
    if (!outFile.is_open()) {
        QMessageBox::warning(this, "导出失败", "无法打开文件进行写入！");
        return;
    }

    // 写入表头
    outFile << "书号,书名,作者,出版社,剩余库存数,已借出,入库日期\n";

    for (const auto& book : bookSet) {
        outFile << book.getbookno() << ","
            << book.getbookname() << ","
            << book.getauthor() << ","
            << book.getpublisher() << ","
            << book.gettotalnum() << ","
            << book.getborrownum() << ","
            << book.getpubday().getYear() << "-" << book.getpubday().getMonth() << "-" << book.getpubday().getDay()
            << "\n";
    }

    outFile.close();
    QMessageBox::information(this, "导出成功", "图书信息已成功导出！");
}

void LibraryManagementSystem::exportStudentInfo(const QString& filePath)
{
    std::ofstream outFile(filePath.toStdString());
    if (!outFile.is_open()) {
        QMessageBox::warning(this, "导出失败", "无法打开文件进行写入！");
        return;
    }

    // 写入表头
    outFile << "学号,姓名,专业,年级,手机\n";

    for (const auto& student : studentSet) {
        outFile << student.getstuno() << ","
            << student.getstuname() << ","
            << student.getstumajor() << ","
            << student.getstuclass() << ","
            << student.getstumobi()
            << "\n";
    }

    outFile.close();
    QMessageBox::information(this, "导出成功", "学生信息已成功导出！");
}

void LibraryManagementSystem::exportBorrowInfo(const QString& filePath)
{
    std::ofstream outFile(filePath.toStdString());
    if (!outFile.is_open()) {
        QMessageBox::warning(this, "导出失败", "无法打开文件进行写入！");
        return;
    }

    // 写入表头
    outFile << "学号,书号,借阅日期\n";

    for (const auto& studentNode : sbList.sblist) {
        const std::string& studentNo = studentNode.getstudentno();
        for (const auto& borrowInfo : studentNode.bilist) {
            outFile << studentNo << ","
                << borrowInfo.getbookno() << ","
                << borrowInfo.getborrowday().getYear() << "-" << borrowInfo.getborrowday().getMonth() << "-" << borrowInfo.getborrowday().getDay()
                << "\n";
        }
    }

    outFile.close();
    QMessageBox::information(this, "导出成功", "借阅信息已成功导出！");
}

void LibraryManagementSystem::on_actionExportBookInfo_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "导出图书信息", "", "CSV文件 (*.csv)");
    if (!filePath.isEmpty()) {
        exportBookInfo(filePath);
    }
}

void LibraryManagementSystem::on_actionExportStudentInfo_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "导出图书信息", "", "CSV文件 (*.csv)");
    if (!filePath.isEmpty()) {
        exportBookInfo(filePath);
    }
}

void LibraryManagementSystem::on_actionExportBorrowInfo_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "导出图书信息", "", "CSV文件 (*.csv)");
    if (!filePath.isEmpty()) {
        exportBookInfo(filePath);
    }
}

void LibraryManagementSystem::inportBookInfo() {
    bookSet.AppendBookList();
    bookSet.SaveBookList();
    updateAllBooksTable();
    updateStudentTable();
    updateDeleteStudentTable();
    updateDeleteBooksTable();
    updateBorrowRecordTable();
    updateOverdueRecordsTable();
}

void LibraryManagementSystem::inportStudentInfo() {
    studentSet.AppendStuList();
    studentSet.SaveStuList();
    updateAllBooksTable();
    updateStudentTable();
    updateDeleteStudentTable();
    updateDeleteBooksTable();
    updateBorrowRecordTable();
    updateOverdueRecordsTable();
}