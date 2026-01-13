// 缺失的函数实现
void MainWindow::switchToChatPage()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
    loadLocalData();
}

void MainWindow::switchToPrivateChat(const QString &contact)
{
    m_currentContact = contact;
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    ui->privateTextEdit->clear();
    
    // 加载聊天历史
    loadChatHistory(contact);
    
    // 更新联系人未读消息数
    m_contactModel->updateUnreadCount(contact, 0);
}

void MainWindow::switchToContactsPage()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
    loadContactsFromDatabase();
    loadGroupsFromDatabase();
}

void MainWindow::switchToLoginPage()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_userListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;
    
    QString userName = item->text();
    if (userName.endsWith("*")) return; // 是自己
    
    ui->sayLineEdit->setText("@" + userName + " ");
    ui->sayLineEdit->setFocus();
}

void MainWindow::onNetworkConnected()
{
    qDebug() << "Network connected";
    updateConnectionStatus();
}

void MainWindow::onNetworkDisconnected()
{
    qDebug() << "Network disconnected";
    updateConnectionStatus();
}

void MainWindow::onNetworkError(const QString &error)
{
    QMessageBox::warning(this, "网络错误", error);
    updateConnectionStatus();
}

void MainWindow::onNetworkMessageReceived(const QJsonObject &message)
{
    jsonReceived(message);
}

void MainWindow::onReconnectionAttempt(int attempt)
{
    qDebug() << "Reconnection attempt:" << attempt;
    updateConnectionStatus();
}