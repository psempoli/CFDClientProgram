#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <QObject>
#include <QList>

class RemoteFileWindow;
class FileMetaData;
class RemoteDataInterface;

enum class RequestState;

class FileOperator : public QObject
{
    Q_OBJECT

public:
    FileOperator(RemoteDataInterface * newDataLink, RemoteFileWindow * parent);

    void totalResetErrorProcedure();
    void enactFolderRefresh(FileMetaData folderToRemoteLS);
    bool operationIsPending();

private slots:
    void getLSReply(RequestState cmdReply, QList<FileMetaData> * fileDataList);

    void sendDeleteReq();
    void getDeleteReply(RequestState replyState, QString * oldFilePath);
    void sendMoveReq();
    void getMoveReply(RequestState replyState, QString * oldFilePath, FileMetaData * revisedFileData);
    void sendCopyReq();
    void getCopyReply(RequestState replyState, FileMetaData * newFileData);
    void sendRenameReq();
    void getRenameReply(RequestState replyState, QString * oldFilePath, FileMetaData * newFileData);

    void sendCreateFolderReq();
    void getMkdirReply(RequestState replyState, FileMetaData * newFolderData);

    void sendUploadReq();
    void getUploadReply(RequestState replyState, FileMetaData * newFileData);
    void sendDownloadReq();
    void getDownloadReply(RequestState replyState, QString * localDest);

    void sendCompressReq();
    void getCompressReply(RequestState finalState, QJsonDocument * rawData);
    void sendDecompressReq();
    void getDecompressReply(RequestState finalState, QJsonDocument * rawData);

    void sendManualRefresh();

private:
    RemoteFileWindow * myFileWindow;

    RemoteDataInterface * dataLink;
    bool fileOperationPending = false;
};

#endif // FILEOPERATOR_H