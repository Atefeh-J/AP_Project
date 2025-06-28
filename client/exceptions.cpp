#include "exceptions.h"

MyException::MyException(const QString& message)
    : std::runtime_error(message.toStdString()),
    Expmessage(message)
{
}

QString MyException::getMessage() const {
    return Expmessage;
}

PhoneException::PhoneException()
    : MyException("Invalid phone number")
{
}

EmailException::EmailException()
    : MyException("Invalid email address")
{
}

CharactersException::CharactersException()
    : MyException("Invalid characters detected. donnot use !#^*& and enter. \n donnot use space in email,phone,oassword,username.")
{
}

UsernameException::UsernameException(const QString& username)
    : MyException("Username '" + username + "' already exists")
{
}
EmptyFieldException::EmptyFieldException()
    : MyException("field cannot be empty")
{
}
