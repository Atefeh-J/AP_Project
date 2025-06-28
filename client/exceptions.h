#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <QString>

class MyException : public std::runtime_error {
private:
    QString Expmessage;

public:
    explicit MyException(const QString& message);
    QString getMessage() const;
};

class PhoneException : public MyException
{
public:
    PhoneException();
};

class EmailException : public MyException
{
public:
    EmailException();
};

class CharactersException : public MyException
{
public:
    CharactersException();
};

class UsernameException : public MyException
{
public:
    explicit UsernameException(const QString& username);
};
class EmptyFieldException : public MyException
{
public:
    explicit EmptyFieldException();
};

#endif // EXCEPTIONS_H
