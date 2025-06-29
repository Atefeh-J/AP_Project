#include "exceptions.h"

MyException::MyException(const QString& message)
    : std::runtime_error(message.toStdString()),
    Expmessage(message)
{

    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Warning");
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

QString MyException::getMessage() const {
    return Expmessage;
}

openForReadException::openForReadException()
    : MyException("Couldn't open file for reading!")
{


}
openForWriteException::openForWriteException()
    : MyException("Couldn't open file for writing!")
{
}
createJSONdocException::createJSONdocException()
    : MyException("Failed to create JSON doc.")
{
}
