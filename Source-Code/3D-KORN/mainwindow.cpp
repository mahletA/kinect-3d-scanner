#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionImport_from_scan_triggered()
{
    TDK_ScanWindow *tdk_scanWindow = new TDK_ScanWindow(this);
    if(tdk_scanWindow->mv_SensorController->mf_IsSensorAvailable()){
        tdk_scanWindow->mf_setupUI();
        tdk_scanWindow->setWindowTitle("3D KORN SCANNER - SCAN WINDOW");
        tdk_scanWindow->showMaximized();
        tdk_scanWindow->setMinimumSize(tdk_scanWindow->size());
    }
    else{
        bool retryFlag = true;
        while(retryFlag){
            QMessageBox sensorWarningMessageBox;
            sensorWarningMessageBox.setIcon(QMessageBox::Warning);
            sensorWarningMessageBox.setText("No sensor connected. Please connect sensor and click retry.");
            sensorWarningMessageBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
            sensorWarningMessageBox.setDefaultButton(QMessageBox::Retry);
            int retryValue = sensorWarningMessageBox.exec();
            switch (retryValue) {
            case QMessageBox::Retry:
                if(tdk_scanWindow->mv_SensorController->mf_IsSensorAvailable()){
                    tdk_scanWindow->mf_setupUI();
                    tdk_scanWindow->setWindowTitle("3D KORN SCANNER - SCAN WINDOW");
                    tdk_scanWindow->showMaximized();
                    tdk_scanWindow->setMinimumSize(tdk_scanWindow->size());
                    retryFlag = false;
                }
                break;
            case QMessageBox::Cancel:
                retryFlag = false;
                break;
            default:
                retryFlag = false;
                break;
            }
        }

    }
}
