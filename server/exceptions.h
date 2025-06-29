#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <QString>
#include <QMessageBox>
class MyException : public std::runtime_error {
private:
    QString Expmessage;
protected:
        QMessageBox msgBox;

public:
    explicit MyException(const QString& message);
    QString getMessage() const;
};

class openForReadException : public MyException
{
public:
    openForReadException();
};

class openForWriteException : public MyException
{
public:
    openForWriteException();
};

class createJSONdocException : public MyException
{
public:
    createJSONdocException();
};


#endif // EXCEPTIONS_H
